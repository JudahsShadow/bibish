cmake_minimum_required(VERSION 2.6)
project(bibish)


INCLUDE("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Sources.cmake")
# add_executable(bibish ${bibish_srcs})
add_executable(bibish ${CMAKE_CURRENT_SOURCE_DIR}/src/front/interface.cpp ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)


#add_library(interface ${CMAKE_CURRENT_SOURCE_DIR}/src/front/interface.cpp)

#find_package(Sword REQUIRED)
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
FIND_PACKAGE(Sword 1.7.0 REQUIRED)

include_directories("${Sword_INCLUDE_DIRS}")
target_link_libraries("bibish" "${Sword_LDFLAGS}")


install(TARGETS bibish RUNTIME DESTINATION bin)
