===========================
 06 LittlevGL GUI practice
===========================

Overview
========

The code is copied from zephyr/samples/subsys/display/lvgl can compiled for 
running on ST Disco L475 IOT01A. The project creates two ui objects: label and 
button with label. First one is a label just showing a count number and increment 
one per seconds, and second one is a button with built-in button click event acting.

Building and Programming
========================

::

  west build
  west flash


Configuration
=============


Board and Shield configuration
------------------------------

BOARD and SHIELD are configured in CMakeLists.txt::

  set(BOARD disco_l475_iot1)
  set(SHIELD adafruit_2_8_tft_touch_v2)


Memeory related configuration
-----------------------------

There is one buffer declared in lvgl.c for storing temporal data to render, and its size is cacluated from:

1. bits per pixel (CONFIG_LV_Z_BITS_PER_PIXEL)
2. screen horizen resolution (CONFIG_LV_HOR_RES_MAX)
3. screen vertical resolution (CONFIG_LV_Z_VER_RES_MAX)
4. percentage of render buffer (CONFIG_LV_Z_VDB_SIZE)

Total size is

::

  CONFIG_LV_Z_BITS_PER_PIXEL*(CONFIG_LV_HOR_RES_MAX*CONFIG_LV_Z_RES_MAX*(CONFIG_LV_Z_VDB_SIZE/100))/8

If project uses default adafruit_2_8_tft_touch shield configuration, buffer will static allocate around 150 KB. However, ST disco l475 iot board has only 96 KB on-chip sram. To reduce ram usage, percentage of render buffer is set from 64 to 16.

::

  CONFIG_LV_Z_VDB_SIZE=16


Input device configuration
--------------------------

Ft5336 is configured as polling mode in default, and interval is configured as 50ms.

::

  CONFIG_KSCAN_FT5336_PERIOD=50

There are two reasons not using interrupt mode at this time. First, LVGL task handler is better calling periodically in a task. LVGL has its own time stamp, so it can process some kinds of behavior with continous change. For example, lvgl can not only detect click event but also long press or sliding.

Another reason is that the interrupt mode does not have a flow control on incoming event from touch pad. When a user presses touch pad and not release, message queue for delivering point package between system work queue thread to lv_tash_handler will be full. This situation may lead some press or release events lost and some widgets can not process its corresponding UI changing like button release act.
