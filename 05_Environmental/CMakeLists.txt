cmake_minimum_required(VERSION 3.16)

INCLUDE(CheckIncludeFiles)

project(05_Environmental C)

find_library(NCURSES_LIBRARY ncursesw)
if (NOT NCURSES_LIBRARY)
	message(FATAL_ERROR "ncursesw library not found")
endif ()

find_library(PCRE_LIBRARY pcre2-8)
if (NOT PCRE_LIBRARY)
	message(FATAL_ERROR "pcre2-8 library not found")
endif ()

CHECK_INCLUDE_FILES("ncurses.h" FOUND_NCURSES_H)
if (NOT FOUND_NCURSES_H)
	message(FATAL_ERROR "ncurses.h not found")
endif ()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

option(WITHOUT_UTF "Remove PCRE2_UCP" OFF)
if (WITHOUT_UTF)
	add_compile_definitions(WITHOUT_UTF=1)
endif ()

add_executable(main Windowpcre.c)

target_link_libraries(main ${NCURSES_LIBRARY} ${PCRE_LIBRARY})

file(WRITE ${CMAKE_BINARY_DIR}/allclean.cmake
"set(cmake_generated \${CMAKE_BINARY_DIR}/CMakeCache.txt
                    \${CMAKE_BINARY_DIR}/cmake_install.cmake
                    \${CMAKE_BINARY_DIR}/Makefile
                    \${CMAKE_BINARY_DIR}/CMakeFiles
                    \${CMAKE_BINARY_DIR}/allclean.cmake
)

foreach(file \${cmake_generated})

  if (EXISTS \${file})
     file(REMOVE_RECURSE \${file})
  endif()

endforeach(file)
")

add_custom_target(allclean
	COMMAND ${CMAKE_BUILD_TOOL} clean
	COMMAND ${CMAKE_COMMAND} -P allclean.cmake
)
