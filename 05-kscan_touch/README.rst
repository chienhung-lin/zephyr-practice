=========================
 05 KSCAN touch practicee
=========================

Overview
--------

This sample is modified from zephyr/samples/drivers/kscan_touch. It demonstrates 
how to interface with a touch panel. When touches are detected, defined callback 
function will send a package of row and col via message queue to touch thread, 
a user defined thread.

Building and Programming
------------------------

::

  west flash

Configuration
-------------

The sample is built and executed on ST Disco L475 IOT01A with Adafruit 2.8" TFT 
Touch Shield v2.

The BOARD and SHIELD variables are set in CMakeLists.txt.

::

  set(BOARD disco_l475_iot1)
  set(SHIELD adafruit_2_8_tft_touch_v2)

The device is retrieved by alias of kscan0, so alias name is described in 
boards/disco_l475_iot1.overlay

::

  / {
    aliases {
      kscan0 = &touch_controller;
    };
  };

Touch controller in this shield is FT6206, and corresponding driver is 
"focaltech,ft5336". Driver should be configured in prj.conf as below:

::

  CONFIG_KSCAN=y
  CONFIG_I2C=y
  CONFIG_KSCAN_FT5336=y

Adafruit 2.8" TFT touch shield provides two modes to get touch events: polling 
and interrupt. The interrupt only works when TS_int jumper is connected. 

Driver supports these two mode and can be configured with

::

  CONFIG_KSCAN_FT5336_INTERRUPT=y

The default is polling, and value is `n`.


Sample output
-------------

::

  *** Booting Zephyr OS build zephyr-v3.0.0-537-gba02864d4125  ***
  empty main function
  kscan callback row = 155 col = 111
  kscan callback row = 155 col = 111
  kscan callback row = 155 col = 111
  kscan callback row = 155 col = 111
  [00:00:02.616,000] <inf> main: get touch_item: row = 155, col = 111
  [00:00:02.625,000] <inf> main: get touch_item: row = 155, col = 111
  [00:00:02.635,000] <inf> main: get touch_item: row = 155, col = 111
  [00:00:02.644,000] <inf> main: get touch_item: row = 155, col = 111
