cmake_minimum_required(VERSION 3.30)
project(Vm C)

set(CMAKE_C_STANDARD 23)

add_executable(Vm main.c
        common.h
        chunk.h
        chunk.c
        memory.h
        memory.c
        debug.h
        debug.c
        value.h
        value.c
        vm.h
        vm.c)
