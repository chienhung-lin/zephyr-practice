#include <zephyr/kernel.h>

#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(http_client_test, LOG_LEVEL_DBG);

#include <stdio.h>

#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/hwinfo.h>

#include <zephyr/net/socket.h>

#include <zephyr/net/net_if.h>
#include <zephyr/net/net_mgmt.h>
#include <zephyr/net/wifi_mgmt.h>

#include <zephyr/net/http_client.h>

#define SERVER_ADDR4 "192.168.1.150"
#define SERVER_PORT 8000

//#define WIFI_SSID "NETGEAR70"
//#define WIFI_PSK "jaggedroad871"

struct sensor_package
{
	double temp;
	double hum;
};

static struct wifi_connect_req_params cnx_params =
{
	.ssid = CONFIG_WIFI_SSID,
	.ssid_length = sizeof(CONFIG_WIFI_SSID),
	.psk = CONFIG_WIFI_PSK,
	.psk_length = sizeof(CONFIG_WIFI_PSK),
	.channel = WIFI_CHANNEL_ANY,
	.security = WIFI_SECURITY_TYPE_PSK
};

static uint8_t recv_buf_ipv4[512];

static int setup_socket(sa_family_t family, const char *server, int port,
		        int *sock, struct sockaddr *addr, socklen_t addr_len)
{
	int ret = 0;

	memset(addr, 0, addr_len);

	net_sin(addr)->sin_family = family;
	net_sin(addr)->sin_port = htons(port);
	inet_pton(family, server, &net_sin(addr)->sin_addr);

	*sock = socket(family, SOCK_STREAM, IPPROTO_TCP);

	if (*sock < 0) {
		LOG_ERR("Failed to create IPv4 HTTP socket (%d)", -errno);
	}

	return ret;
}

static int connect_socket(sa_family_t family, const char *server, int port,
			  int *sock, struct sockaddr *addr, socklen_t addr_len)
{
	int ret;

	ret = setup_socket(family, server, port, sock, addr, addr_len);
	if (ret < 0 || *sock < 0) {
		return -1;
	}

	ret = connect(*sock, addr, addr_len);
	if (ret < 0) {
		LOG_ERR("Cannot connect to %s remote (%d)",
			 "IPv4", -errno);
		ret = -errno;
	}

	return ret;
}

static void response_cb(struct http_response *rsp,
			enum http_final_call final_data, 
			void *user_data)
{
	if (final_data == HTTP_DATA_MORE) {
		LOG_INF("Partial data received (%zd bytes)", rsp->data_len);
	} else if (final_data == HTTP_DATA_FINAL) {
		LOG_INF("All the data received (%zd bytes)", rsp->data_len);
	}

	LOG_INF("Response to %s", (const char *)user_data);
	LOG_INF("Response status %s", rsp->http_status);
	LOG_INF("Recieved %s", rsp->recv_buf);
}

static int get_temp_hum(const struct device *dev, struct sensor_package *pk)
{
	struct sensor_value temp_val, hum_val;
	int rc = 0;

	if ((rc = sensor_sample_fetch(dev)) < 0) {
		LOG_ERR("Fail fetch sensor data (%d)", -rc);
		return rc;
	}

	if ((rc = sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temp_val)) < 0) {
		LOG_ERR("Fail get temperature from sensor channel (%d)", -rc);
		return rc;
	}

	if ((rc = sensor_channel_get(dev, SENSOR_CHAN_HUMIDITY, &hum_val)) < 0) {
		LOG_ERR("Fail get humidity from sensor channel (%d)", -rc);
		return rc;
	}

	pk->temp = sensor_value_to_double(&temp_val);
	pk->hum = sensor_value_to_double(&hum_val);

	return 0;
}

static int run_post(const char *payload, int payload_len)
{
	struct http_request req;
	struct sockaddr_in addr4;
	int32_t timeout = 3 * MSEC_PER_SEC;
	int sock4 = -1;
	int ret = 0;

	(void)connect_socket(AF_INET, SERVER_ADDR4, SERVER_PORT,
			&sock4, (struct sockaddr *)&addr4,
			sizeof(addr4));

	if (sock4 < 0) {
		LOG_ERR("Cannot create HTTP connection.");
		return -ECONNABORTED;
	}

	memset(&req, 0, sizeof(req));

	req.method = HTTP_POST;
	req.url = "/";
	req.host = SERVER_ADDR4;
	req.protocol = "HTTP/1.1";
	req.payload = payload;
	req.payload_len = payload_len;
	req.response = response_cb;
	req.recv_buf = recv_buf_ipv4;
	req.recv_buf_len = sizeof(recv_buf_ipv4);

	ret = http_client_req(sock4, &req, timeout, "IPv4 POST");

	close(sock4);

	return ret;
}

static int connect_wifi_ap(void)
{
	int ret;
	struct net_if *iface = net_if_get_default();

	LOG_INF("Request wifi connect");

	ret = net_mgmt(NET_REQUEST_WIFI_CONNECT, iface,
			&cnx_params, sizeof(cnx_params));

	return ret;
}

static uint8_t dev_uuid[8];

static char payload[128];
static int payload_len;

static void http_client(void)
{
	struct sensor_package pk;
	int ret = 0;
	const struct device *dev = DEVICE_DT_GET_ONE(st_hts221);

	if (dev == NULL) {
		LOG_ERR("fail to get hts221 device");
		return;
	}

	if (!device_is_ready(dev)) {
		LOG_ERR("hts221 is not ready");
		return;
	}

	if (IS_ENABLED(CONFIG_HWINFO)) {
		ret =  hwinfo_get_device_id(dev_uuid, sizeof(dev_uuid));
	}

	if (ret < 0) {
		dev_uuid[0] = 0xAA;
		dev_uuid[1] = 0xAA;
		dev_uuid[2] = 0xAA;
		dev_uuid[3] = 0xAA;
	}

	if ((ret = connect_wifi_ap())) {
		LOG_ERR("wifi connect failed (%d)", -ret);
		return;
	}

	LOG_INF("wifi connect command finished");

	while (true) {

		if ((ret = get_temp_hum(dev, &pk)) < 0) {
			return;
		}

		payload_len = snprintf(
				payload, sizeof(payload), 
				"%x%x%x%x, %.2lf, %.2lf",
				dev_uuid[3], dev_uuid[2],
				dev_uuid[1], dev_uuid[0],
				pk.temp,pk.hum);

		LOG_INF("size: %d, payload: %s", payload_len, payload);

		(void)run_post(payload, payload_len);
		k_sleep(K_SECONDS(1));
	}
}

#define HTTP_CLIENT_PRIO 5
#define HTTP_CLIENT_STACK 2048

K_THREAD_DEFINE(http_client_tid, HTTP_CLIENT_STACK, http_client,
		NULL, NULL, NULL, HTTP_CLIENT_PRIO, K_USER, 0);

void main(void)
{
	while (1) {
		k_sleep(K_SECONDS(2));
	}
}
