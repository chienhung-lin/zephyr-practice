.. _11-usb_cdc_acm:

11 USB CDC ACM Sample Application
#################################

Overview
********

This sample app is a copy from :ref:`usb_cdc-acm` sample, but it is set for 
running on :ref:`disco_l475_iot1_board`. The details of original README file 
can be found under :ref:`usb_cdc-acm`. in the Zephyr project tree.

Requirements
************

- :ref:`disco_l475_iot1_board`

Devicetree overlay setting
**************************

The only thing needed to set is clock source of USB OTG in STM32l475. 
The following details are referenced from RM0351(STM32L47xxx, STM32L48xxx, 
STM32L49xxx and STM32L4Axxx advanced Arm®-based 32-bit MCUs).

In :zephyr_file:`boards/arm/disco_l475_iot1/disco_l475_iot1.dts`, 
source of system clock is PLLR, and source of PLL is HSI16. The USB 
clock source will be set as PLLQ under this default dts. However, 
PLLQ does not fit the required frequency of 48MHz for USB. To feed 
that frequency, the source sould be from others.

The USB clock source uses PLLSA1Q as default when codes generated from 
STMCubeMX. However, stm usb-otg driver under zephyr has not supported 
PLLSA1 yet. So in that driver, it uses 48MHz MSI.

MSI in STML4 series has a unique feature. When a 32.768 kHz external 
oscillator is present, MSI can be configured in a PLL-mode. When in 
that mdoe, MSI automactically calibrates itself. So it is accurate 
enough to be source of USB OTG. It is also what usb otg driver only 
supports in zephyr.

The overlay file turns out:

.. code-block:: devicetree

  &clk_msi {
    msi-range = <11>; /* 48MHz */
    msi-pll-mode; /* MSI PLL mode enables */
    status = "okay"; /* MSI enable */
  };


Building and Running
********************

STM32 L475 IOT Node
===================

.. code-block:: console
  west build -p always -b disco_l475_iot1 -- -DDTC_OVERLAY_FILE="boards/disco_l475_iot1.overlay app.overlay"
  

Running
=======

Flash program in to discovery board

.. code-block:: console
  west flash

Plug the board into a host device, for example, a PC running Linux.
The board will be detected as shown by the Linux dmesg command:

.. code-block:: console

   usb 9-1: new full-speed USB device number 112 using uhci_hcd
   usb 9-1: New USB device found, idVendor=8086, idProduct=f8a1
   usb 9-1: New USB device strings: Mfr=1, Product=2, SerialNumber=3
   usb 9-1: Product: CDC-ACM
   usb 9-1: Manufacturer: Intel
   usb 9-1: SerialNumber: 00.01
   cdc_acm 9-1:1.0: ttyACM1: USB ACM device

The app prints on serial output (UART1), used for the console:

.. code-block:: console

   Wait for DTR

Open a serial port emulator, for example minicom
and attach it to detected CDC ACM device:

.. code-block:: console

   minicom --device /dev/ttyACM1

The app should respond on serial output with:

.. code-block:: console

   DTR set, start test
   Baudrate detected: 115200

And on ttyACM device, provided by zephyr USB device stack:

.. code-block:: console

   Send characters to the UART device
   Characters read:

The characters entered in serial port emulator will be echoed back.

Troubleshooting
===============

If the ModemManager runs on your operating system, it will try
to access the CDC ACM device and maybe you can see several characters
including "AT" on the terminal attached to the CDC ACM device.
You can add or extend the udev rule for your board to inform
ModemManager to skip the CDC ACM device.
For this example, it would look like this:

.. code-block:: none

   ATTRS{idVendor}=="8086" ATTRS{idProduct}=="f8a1", ENV{ID_MM_DEVICE_IGNORE}="1"

You can use
``/lib/udev/rules.d/77-mm-usb-device-blacklist.rules`` as reference.
