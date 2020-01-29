cmake_minimum_required(VERSION 3.13.4)

project(GOSCIU)

file(GLOB SOURCES
    *.h
    *.cpp
)

add_executable(GOSCIU ${SOURCES})

find_library(wiringPi_LIB wiringPi)
target_link_libraries(GOSCIU ${wiringPi_LIB})