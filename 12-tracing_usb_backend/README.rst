.. _12-tracing_usb_backend:

11 USB CDC ACM Sample Application
#################################

Overview
********

This sample app is a copy from "tracing" sample, but it is set for 
running on :ref:`disco_l475_iot1_board`. The details of original README file 
can be found under "tracing". in the Zephyr project tree.

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
  west build -p always -b disco_l475_iot1 -- -DCONF_FILE="prj.conf;prj_usb_ctf.conf"
  

Running
=======

Flash program in to discovery board

.. code-block:: console
  west flash

Connecting through USB
**********************

Udev Configuration
==================

To access usb device from python codes without permission, udev rules for usb port 
to L475 IOT board have to be set.

Add scripts/80-local.rules under /etc/udev/rules.d/

Capturing Tracing by USB
========================

.. code-block:: console
   python3 scripts/trace_capture_usb.py -v 0x2FE9 -p 0x100 -o ctf/channel0_0

Interpreting CTF file
=====================

.. code-block:: console
   python3 scripts/parse_ctf.py -t ctf

TODO
****

Import barectf to make sure coherence of trace format on both metadate and trace codes
