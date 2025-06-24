cmake_minimum_required(VERSION 1.0.1)
project(lmaobot)

find_package(Geode REQUIRED)

geode_create_mod(lmaobot
    src/main.cpp
)