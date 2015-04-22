SET (backend_src ${CMAKE_CURRENT_SOURCE_DIR}/src/back/library.cpp
		 ${CMAKE_CURRENT_SOURCE_DIR}/src/back/passage.cpp		 
)

source_group("backend_src" FILES ${backend_src})

SET (frontend_src ${CMAKE_CURRENT_SOURCE_DIR}/src/front/display.cpp
                  ${CMAKE_CURRENT_SOURCE_DIR}/src/front/parser.cpp
		  ${CMAKE_CURRENT_SOURCE_DIR}/src/front/interface.cpp
		  ${CMAKE_CURRENT_SOURCE_DIR}/src/front/pager.cpp
  
)

source_group("frontend_src" FILES ${frontend_src})

SET (main_src ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
source_group("main_src" FILES ${main_src})

SET ( bibish_srcs
      ${backend_src}
      ${frontend_src}
      ${main_src}
)
