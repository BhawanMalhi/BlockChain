cmake_minimum_required(VERSION 3.14)
project(BlockChain C)

set(CMAKE_C_STANDARD 99)

add_executable(BlockChain main.c)
add_executable(Blockchain BlockChain.c)