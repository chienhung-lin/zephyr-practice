cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr)
project(03-pwm-led)

target_sources(app PRIVATE src/main.c)
