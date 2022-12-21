#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(net_echo_client_sample, LOG_LEVEL_DBG);

#include <zephyr/net/net_if.h>
#include <zephyr/net/net_mgmt.h>
#include <zephyr/net/wifi_mgmt.h>

int wifi_connect(struct wifi_connect_req_params *cnx_params)
{
	int ret;
	struct net_if *iface = net_if_get_default();

	LOG_INF("Request wifi connect");

	ret = net_mgmt(NET_REQUEST_WIFI_CONNECT, iface,
									cnx_params, sizeof(struct wifi_connect_req_params));
	return ret;
}
