==========
03-pwm-led
==========

This is a copy of pwm led sample from Zephyr project. There is an extra device overlay file for setting pwm output pin. It overlays `pwm2` to set output on PA5 so that pwm controls LED1.


Build
-----
The project is built for running `STM32 B-L475E-IOT01A`_

::

  west build -b disco_l475_iot1

Flash
-----

::

  west flash

.. _STM32 B-L475E-IOT01A: https://www.st.com/en/evaluation-tools/b-l475e-iot01a.html
