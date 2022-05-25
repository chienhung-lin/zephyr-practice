.. _09-sockets-echo-client-sample:

09 Socket Echo Client
#####################

Overview
********

This echo-client sample application is modified from sockets echo client 
sample in zephyr, and :ref:`soeckets-echo-client` has more details about 
original sample. This modified sample implements a TCP client that will 
send IPv4 packets, wait for the data to be sent back. Original sample has 
some configurations file for different internet features or target 
platforms. This sample only supports TCP over IPv4 on :ref:
`disco_l475_iot1_board`.

The source code is copied from this sample application:
:zephyr_file:`samples/net/sockets/echo_client`.

Requirements
************

- :ref:`disco_l475_iot1_board`
- wifi router

Building and Running
********************

There are configuration files for different boards and setups in the
echo-client directory:

- :file:`prj.conf`
  Generic config file, normally you should use this.

- :file:`overlay-tls.conf`
  This overlay config enables support for TLS. Currently not support.

- :file:`overlay-vlan.conf`
  This overlay config enables support for VLAN. Currently not support.

- :file:`overlay-socks5.conf`
  Currently not support.

The board configuration is already set in :file:`CMakeLists.txt`, so 
build echo-client sample application like this:

.. zephyr-app-commands::
   :zephyr-app: samples/net/sockets/echo_client
   :goals: build

In a terminal window you can check if communication is happen:

.. code-block:: console

    $ minicom -D /dev/ttyACM1

Running echo-server in Linux Host
=================================

In a terminal window:

.. code-block:: console

    $ sudo ./echo-server -i tap0

Note that echo-server must be running in the Linux host terminal window
before you start the echo-client application.
