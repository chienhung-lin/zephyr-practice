.. _10-http-client-sample:

10 http client sample
#####################

Overview
********

This is a sampel of sending device UUID, temperature, and humidity through 
POST in HTTP1.1 over wifi. The referenced code is :ref:
`sockets-http-client-sample`.

Requirements
************

- :ref:`disco_l475_iot1_board`
- wifi router

Configuration and Build
***********************

The board configuration is set in :file:`CMakeLists.txt`, and build command is:

.. zephyr-app-commands::
   :conf: "prj.conf wifi_setting.conf"
   :goals: build 

The wifi ssid and password should be set in :file:`wifi_setting.conf`.

Flash and run server
********************

The sever must be set up first. If not, press reset button on disco l475 board.

Run Server
==========

.. code-block:: console

    $ node server/server.js

Flash code
==========

.. zephyr-app-commands::
   :goals: flash

