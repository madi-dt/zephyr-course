cmake_minimum_required(VERSION 3.20.0)

set(BOARD esp32_devkitc_wroom/esp32/procpu)

find_package(Zephyr REQUIRED)
project(my_zephyr_app)

target_sources(app PRIVATE src/main.cpp)
