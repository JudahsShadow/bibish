cmake_minimum_required(VERSION 2.6)
project(bibish)

add_executable(bibish main.cpp)

install(TARGETS bibish RUNTIME DESTINATION bin)
