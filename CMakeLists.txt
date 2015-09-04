cmake_minimum_required(VERSION 3.3)
project(pomodori)

INCLUDE(FindPkgConfig)

pkg_check_modules(GTKLIB REQUIRED "gtk+-2.0")
include_directories(${GTKLIB_INCLUDE_DIRS})
link_directories(${GTKLIB_LIBRARY_DIRS})

set(CMAKE_CXX_FLAGS " -std=c++11 -lnotify")

set(SOURCE_FILES main.cpp totimer.cpp totimer.h logging.cpp logging.h)
add_executable(pomodori ${SOURCE_FILES})

target_link_libraries(pomodori ${GTKLIB_LIBRARIES})