cmake_minimum_required(VERSION 4.0)
project(MLP_Core C)

set(CMAKE_C_STANDARD 23)

add_executable(MLP_Core main.c
        layer.c
        layer.h
        activations.c
        activations.h
        losses.c
        losses.h)
