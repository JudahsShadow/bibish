#BIBISH Is [a] Bible Interactive SHell, a front-end for the SWORD Project
#inspired by Debian's bible package
#Copyright (C) 2015-2021  David "Judah's Shadow" Blue <yudahsshadow@gmx.com>
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
#You should have received a copy of the GNU General Public License along
#with this program; if not, write to the Free Software Foundation, Inc.,
#51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

SET (backend_src ${CMAKE_CURRENT_SOURCE_DIR}/src/back/parser.cpp
                ${CMAKE_CURRENT_SOURCE_DIR/src/back/lexicon.cpp}
                ${CMAKE_CURRENT_SOURCE_DIR}/src/back/passage.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/back/search.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/back/library.cpp
)

source_group("backend_src" FILES ${backend_src})

SET (frontend_src ${CMAKE_CURRENT_SOURCE_DIR}/src/front/display.cpp
		  ${CMAKE_CURRENT_SOURCE_DIR}/src/front/interface.cpp
		  ${CMAKE_CURRENT_SOURCE_DIR}/src/front/pager.cpp
		  ${CMAKE_CURRENT_SOURCE_DIR}/src/front/reader.cpp
)

source_group("frontend_src" FILES ${frontend_src})

SET (main_src ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
source_group("main_src" FILES ${main_src})

SET ( bibish_srcs
      ${backend_src}
      ${frontend_src}
      ${main_src}
)
