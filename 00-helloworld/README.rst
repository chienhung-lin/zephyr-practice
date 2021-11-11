===============
 00-helloworld
===============

Prerequisite
------------
Follow Offical Zephyr `Getting Started Guide`_. to prepare a proper enviroment.

Build
-----

Build the app for ``qemu_cortex_m3`` target::

  cd 00-helloworld
  west build -b qemu_cortex_m3

Run on qemu::

  west build -t run

Output::

  -- west build: running target run
  [0/1] To exit from QEMU enter: 'CTRL+a, x'[QEMU] CPU: cortex-m3
  qemu-system-arm: warning: nic stellaris_enet.0 has no peer
  Timer with period zero, disabling
  *** Booting Zephyr OS build v2.7.99-1198-g123841091459  ***
  Hello World! qemu_cortex_m3

.. _Getting Started Guide: https://docs.zephyrproject.org/latest/getting_started/index.html
