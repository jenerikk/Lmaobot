cmake_minimum_required(VERSION 3.19)
project(lmaobot)

find_package(Geode REQUIRED)

geode_create_mod(lmaobot
    src/main.cpp
)
