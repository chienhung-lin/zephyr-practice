# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

set(BOARD disco_l475_iot1)
set(SHIELD adafruit_2_8_tft_touch_v2)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(05-kscan_touch)

FILE(GLOB app_sources src/*.c)
target_sources(app PRIVATE ${app_sources})
