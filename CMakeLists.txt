#BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
#inspired by debian's bible package
#Copyright (C) 2015-2021 its contributors. See CONTRIBUTORS file for more info
#
#This program is free software; you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation version 2
#
#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#with this program; if not, write to the Free Software Foundation, Inc.,
#51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

cmake_minimum_required(VERSION 3.5.0)
project(bibish)


INCLUDE("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Sources.cmake")
SET(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_BUILD_TYPE="Debug")
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
add_executable(bibish ${bibish_srcs})



LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
FIND_PACKAGE(Sword 1.9.0 REQUIRED)

include_directories("${Sword_INCLUDE_DIRS}")
target_link_libraries("bibish" "${Sword_LDFLAGS}")


install(TARGETS bibish RUNTIME DESTINATION bin)
