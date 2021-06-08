cmake_minimum_required(VERSION 3.19)
project(stm32_remote_control_car)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(stm32_remote_control_car
        gamepad.cpp
        stm32-remote-control-car.ino)
