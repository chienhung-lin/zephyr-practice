/*
 * Copyright (c) 2020 Mark Olsson <mark@markolsson.se>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>
#include <drivers/kscan.h>

#define LOG_LEVEL LOG_LEVEL_DBG
#include <logging/log.h>

LOG_MODULE_REGISTER(main);

struct touch_item_type {
	int row;
	int col;
};

#define TOUCH_MSGQ_SIZE 10
#define TOUCH_MSGQ_ALIGN 4

K_MSGQ_DEFINE(touch_msgq, sizeof(struct touch_item_type),
						  TOUCH_MSGQ_SIZE, TOUCH_MSGQ_ALIGN);

#define TOUCH_CONTROLLER_NODE DT_ALIAS(kscan0)

const struct device *kscan_dev = DEVICE_DT_GET(TOUCH_CONTROLLER_NODE);

static void k_callback(const struct device *dev, uint32_t row, uint32_t col,
		       bool pressed)
{
	struct touch_item_type touch_item;
	int ret;

	ARG_UNUSED(dev);

	if (pressed) {
		printk("kscan callback row = %u col = %u\n", row, col);
		touch_item.row = row;
		touch_item.col = col;
		ret = k_msgq_put(&touch_msgq, &touch_item, K_NO_WAIT);
		if (ret != 0) {
			printk("k_msgq_put failed - %d\n", ret);
		}
	}
}

static void touch_entry(void *p1, void *p2, void *p3)
{
	struct touch_item_type touch_item;
	int ret;

	if (!device_is_ready(kscan_dev)) {
		LOG_ERR("kscan device %s not ready", kscan_dev->name);
		return;
	}

	kscan_config(kscan_dev, k_callback);
	kscan_enable_callback(kscan_dev);

	while (1) {
		if ((ret = k_msgq_get(&touch_msgq, &touch_item, K_FOREVER)) == 0) {
			LOG_INF("get touch_item: row = %u, col = %u",
					     touch_item.row, touch_item.col);
		} else {
			LOG_ERR("k_msgq_get failed - %d", ret);
		}
	}
}

#define TOUCH_TASK_STACK_SIZE 1024
#define TOUCH_TASK_PRIORITY 8

K_THREAD_DEFINE(touch_tid, TOUCH_TASK_STACK_SIZE,
							touch_entry, NULL, NULL, NULL,
							TOUCH_TASK_PRIORITY, 0, 0);

void main(void)
{
	printk("empty main function\n");
}
