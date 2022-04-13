===========
 08-eswifi
===========


Overview
========

This sample is copied from zephyr/samples/net/wifi. It is configured with net shell, wifi shell, and eswifi at command shell. Target board is ST L475 IOT-01A.


Configuration
=============

The prj.conf is almost same as samples but only has two extra configuration for testing at command through shell::

  CONFIG_WIFI_ESWIFI_SHELL=y
  CONFIG_SHELL_WILDCARD=n

Question mark, "?", is regarded as wildcard in shell, so disable wildcard funtionality for being able to entering "?" in at command.

Building and Running
====================

::

  west build
  west flash

Sample console interaction
==========================

Boot up
-------

.. code:: console

  uart:~$ *** Booting Zephyr OS build zephyr-v3.0.0-2591-g215efc02c209  ***


Net commands
------------

.. code:: console

  uart:~$ net
  net - Networking commands
  Subcommands:
    allocs     :Print network memory allocations.
    arp        :Print information about IPv4 ARP cache.
    capture    :Configure network packet capture.
    conn       :Print information about network connections.
    dns        :Show how DNS is configured.
    events     :Monitor network management events.
    gptp       :Print information about gPTP support.
    iface      :Print information about network interfaces.
    ipv6       :Print information about IPv6 specific information and
                configuration.
    mem        :Print information about network memory usage.
    nbr        :Print neighbor information.
    ping       :Ping a network host.
    pkt        :net_pkt information.
    ppp        :PPP information.
    resume     :Resume a network interface
    route      :Show network route.
    stacks     :Show network stacks information.
    stats      :Show network statistics.
    suspend    :Suspend a network interface
    tcp        :Connect/send/close TCP connection.
    udp        :Send/recv UDP packet
    virtual    :Show virtual network interfaces.
    vlan       :Show VLAN information.
    websocket  :Print information about WebSocket connections.
  uart:~$


Wifi commands
-------------

.. code:: console

  uart:~$ wifi
  wifi - Wifi commands
  Subcommands:
    connect     :"<SSID>"
                 <channel number (optional), 0 means all>
                 <PSK (optional: valid only for secured SSIDs)>
    disconnect  :Disconnect from Wifi AP
    scan        :Scan Wifi AP
    ap          :Access Point mode commands
  uart:~$


Eswifi commands
---------------

.. code:: console

  uart:~$ eswif
  eswif: command not found
  uart:~$ eswifi
  eswifi - esWiFi debug shell
  Subcommands:
    atcmd  :<atcmd>
  uart:~$


Tcp testing
===========

1. Run server.js:

   .. code:: console

     node server.js

2. Connect shell console through minicom:

   .. code:: console

     minicom

3. Connect wifi router:

   .. code:: console

     uart:~$ wifi connect *<SSID>* *<PSK>*

4. Connect server:

   .. code:: console

     uart:~$ net tcp connect <server_ip> <server_port>

5. Set up tcp receive and send data to server:

   .. code:: console

     uart:~$ net tcp recv
     uart:~$ net tcp send helloworld

Notices
=======

Wifi Scan
---------

Wifi scan seems not to be supported in this Inventek Wifi moudle. It won't respond scan result after either 'wifi scan' or 'eswifi atcmd F0' command, and it also leads module not to respond any further AT command.

Server host
-----------

  The server.js is running on Ubuntu 20.04 LTS on virtualbox. To have private ip address from router, you need to setup network interface of vm as "Bridge". You can see ip address by following command in termianl from Ubuntu::

    ip address show

  The private address usually is 192.168.xxx.xxx
