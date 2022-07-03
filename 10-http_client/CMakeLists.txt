
cmake_minimum_required(VERSION 3.20.0)

set(BOARD disco_l475_iot1)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(thermometer)

file(GLOB app_sources src/*.c)
target_sources(app PRIVATE ${app_sources})
