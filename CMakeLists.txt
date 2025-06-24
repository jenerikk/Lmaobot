cmake_minimum_required(VERSION 0.3.6)
project(lmaobot)

find_package(Geode REQUIRED)

geode_create_mod(lmaobot
    src/main.cpp
)