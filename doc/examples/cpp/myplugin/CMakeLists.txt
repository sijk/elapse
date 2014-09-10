cmake_minimum_required(VERSION 2.8)
project(myplugin)

find_package(Elapse REQUIRED)

add_elapse_plugin(
    HEADER  myplugin.h
    SOURCES eegpower.cpp
)
