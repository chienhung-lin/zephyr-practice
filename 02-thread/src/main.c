/* 
 * Copyright (c) 2021 Chien
 *
 * SPDX-License-Identifier: MIT
 */

#include <zephyr.h>
#include <sys/printk.h>

/* size of stack area used by threadA */
#define STACKSIZE 1024

/* scheduling priority of threadA */
#define PRIORITY 7

void threadA(void *dummy1, void *dummy2, void *dummy3)
{
  ARG_UNUSED(dummy1);
  ARG_UNUSED(dummy2);
  ARG_UNUSED(dummy3);

  uint32_t cycle, uptime;
  int64_t uptime_ticks;
  k_timeout_t sleep_timeout = K_MSEC(1000);

  while (1) {
    /* retrive cycle count, uptime, and uptime tick */
    cycle = k_cycle_get_32();
    uptime = k_uptime_get_32();
    uptime_ticks = k_uptime_ticks();
    printk("cycle %u, uptime %u ms, uptime ticks %lld: "
           "%s says helloworld!\n",
           cycle, uptime, uptime_ticks, __func__);

    /* sleep 1s */
    k_sleep(sleep_timeout);
  }
}

/* stack area of threadA*/
K_THREAD_STACK_DEFINE(threadA_stack_area, STACKSIZE);

/* thread control block of threadA */
static struct k_thread threadA_data;

void main(void)
{
  printk("main thread starts\n");

  printk("create threadA\n");
  k_thread_create(&threadA_data, threadA_stack_area,
                  K_THREAD_STACK_SIZEOF(threadA_stack_area),
                  threadA, NULL, NULL, NULL,
                  PRIORITY, 0, K_FOREVER);

  printk("start scheduling threadA\n");
  k_thread_start(&threadA_data);
}
