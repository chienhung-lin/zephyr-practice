==========
02-threads
==========

The lab only has one thread. The thread prints out cycle count, uptime in miscrosecond, ticks converted from uptime, and function name every 1 minute.

Build
-----
The lab is built for running `STM32 B-L475E-IOT01A`_

::

  west build -b disco_l475_iot1

Flash
-----

::

  west flash

Output
------

::

  *** Booting Zephyr OS build v2.7.99-1198-g123841091459  ***
  main thread starts
  create threadA
  start scheduling threadA
  cycle 5076, uptime 0 ms, uptime ticks 0: threadA says helloworld!
  cycle 12012368, uptime 1001 ms, uptime ticks 1001: threadA says helloworld!
  cycle 24024368, uptime 2002 ms, uptime ticks 2002: threadA says helloworld!

Timing APIs
-----------

The lab retrives time in three different types from corresponding APIs.

+--------------+--------------+--------------------------------------+
| type         | uint         | API                                  |
+==============+==============+======================================+
| cycle        | count        | k_cycle_get_32() or k_cycle_get_64() |
+--------------+--------------+--------------------------------------+
| uptime       | micro second | k_uptime_get() or k_uptime_get_32()  |
+--------------+--------------+--------------------------------------+
| uptime ticks | tick count   | k_uptime_ticks()                     |
+--------------+--------------+--------------------------------------+

Every unit per second is defined in configuration via Kconfig.

+--------------+------------------------------------+------------------------------+
| type         | configuration                      | value                        |
+==============+====================================+==============================+
| cycle        | CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC | default: 80000000Hz          |
+--------------+------------------------------------+------------------------------+
| uptime ticks | CONFIG_SYS_CLOCK_TICKS_PER_SEC     | default: 100; prj.conf: 1000 |
+--------------+------------------------------------+------------------------------+

.. _STM32 B-L475E-IOT01A: https://www.st.com/en/evaluation-tools/b-l475e-iot01a.html
