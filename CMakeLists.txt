cmake_minimum_required(VERSION 3.14)

project(libopendnp3)
include_directories(include)

set(SOURCE
        src/outstation/DatabaseConfig.cpp
        src/outstation/DNP3Manager.cpp
        src/outstation/EventBuffer.cpp
        )

add_library(opendnp3 SHARED ${SOURCE})