============
 04-display
============

Overview
--------
This project is a copy from zephyr/samples/drivers/display, but it is built for running on **ST B-L475E-IOT01A** with **Adafruit 2.8" TFT Touch Shield v2**.

Both target board and shield are set in CMakeLists.txt.

::

  set(BOARD disco_l475_iot1)
  set(SHIELD adafruit_2_8_tft_touch_v2)

There is another difference from original one. The display code runs on its own thread but not on main thread.

Display code draws a rectangular on each corner in different color, and after that, redraws(refills) bottom left one every time interval from black to white in grayscale.

Prerequisite
------------
Follow Offical Zephyr `Getting Started Guide`_. to prepare a proper enviroment.

Requirements
------------

* `ST B-L475E-IOT01A`_
* `Adafruit 2.8" TFT Touch Shield v2`_

Build
-----

::

  west build -p always

.. _ST B-L475E-IOT01A: https://docs.zephyrproject.org/latest/boards/arm/disco_l475_iot1/doc/index.html
.. _Adafruit 2.8" TFT Touch Shield v2: https://docs.zephyrproject.org/latest/boards/shields/adafruit_2_8_tft_touch_v2/doc/index.html
.. _Getting Started Guide: https://docs.zephyrproject.org/latest/getting_started/index.html
