===========
 08-eswifi
===========


Overview
========

This sample is copied from zephyr/samples/net/wifi. It is configured with net shell, wifi shell, and eswifi at command shell. Target board is ST L475 IOT-01A.

Building and Running
********************

::

  west build
  west flash

Sample console interaction
==========================

.. code-block:: console
  uart:~$ *** Booting Zephyr OS build zephyr-v3.0.0-1072-gc31cb0075ad1  ***
  
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
  uart:~$ eswifi
  eswifi - esWiFi debug shell
  Subcommands:
    atcmd  :<atcmd>
  uart:~$

Notices
=======

Wifi scan seems not to be supported in this Inventek Wifi moudle. It won't respond scan result after either 'wifi scan' or 'eswifi atcmd F0' command, and it also leads module not to respond any further AT command.
