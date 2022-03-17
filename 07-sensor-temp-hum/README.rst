====================
 07-sensor-temp-hum
====================


Overview
========

This project is a copy of zephyr/samples/sensor/hts221 and configured for running on ST Disco L475 IOT01.


Configuration
=============

The project configure BOARD and SHIELD in CMakeLists.txt. The SHIELD configuration is not affect, so it can be removed.

::

  set(BOARD disco_l475_iot1)
  set(SHIELD adafruit_2_8_tft_touch_v2)


Build and Flash
===============

::

  west build
  west flash


Notes
=====

Both `CONFIG_HTS221_TRIGGER_GLOBAL_THREAD` and `CONFIG_HTS221_TRIGGER_OWN_THREAD` are currently not supported. There are two places in zephyr/drivers/sensor/hts221/hts221.c needed to fix.

The trigger_set callback function in sensor structure is not intialized at compile time because `HTS211_TRIGGER_ENALBED` is not defined. It is better replaced as `CONFIG_HTS221_TRIGGER`.

Then, name of hts221 gpio properties is not correct. It is not `irq-gpios`. From zephyr/dts/bindings/sensor/st,hts221-common.yaml, its gpio property name is `drdy-gpios`.

After fixing them, drdy-gpios phandles must be described in device tree file. It can be done either modifing disco_l475_iot1.dts or adding overlay files under the project.

::

        /* 07-sesnor-temperature-humidity/boards/disco_l475_iot1.overlay */
        &i2c2 {
          hts221@5f {
            drdy-gpios = <&gpiod 15 GPIO_ACTIVE_HIGHT>;
          };
        };
