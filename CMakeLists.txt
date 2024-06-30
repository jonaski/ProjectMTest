cmake_minimum_required(VERSION 3.7)
project(projectmtest)

include(FindPkgConfig)

option(USE_PROJECTM4 OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND COMPILE_OPTIONS
  $<$<COMPILE_LANGUAGE:C>:-std=c11>
  $<$<COMPILE_LANGUAGE:CXX>:-std=c++17>
  -Wall
  -Wextra
  -Wpedantic
  -Wunused
  -Wshadow
  -Wundef
  -Wuninitialized
  -Wredundant-decls
  -Wcast-align
  -Winit-self
  -Wmissing-include-dirs
  -Wmissing-declarations
  -Wstrict-overflow=2
  -Wunused-parameter
  -Wformat=2
  -Wdisabled-optimization
  $<$<COMPILE_LANGUAGE:CXX>:-Woverloaded-virtual>
  $<$<COMPILE_LANGUAGE:CXX>:-Wold-style-cast>
)
add_compile_options(${COMPILE_OPTIONS})

add_definitions(
  -DQT_STRICT_ITERATORS
  -DQT_NO_CAST_FROM_BYTEARRAY
  -DQT_USE_QSTRINGBUILDER
  -DQT_NO_URL_CAST_FROM_STRING
  -DQT_NO_CAST_TO_ASCII
  -DQT_NO_NARROWING_CONVERSIONS_IN_CONNECT
  -DQT_NO_FOREACH
  -DQT_ASCII_CAST_WARNINGS
  -DQT_NO_CAST_FROM_ASCII
)

if(NOT QT_VERSION_MAJOR)
  set(QT_VERSION_MAJOR 6)
endif()

if(QT_VERSION_MAJOR EQUAL 5)
  option(USE_QGLWIDGET OFF)
else()
  set(USE_QGLWIDGET OFF)
endif()

set(QT_COMPONENTS Core Gui Widgets)

if (QT_VERSION_MAJOR EQUAL 5)
  list(APPEND QT_COMPONENTS OpenGL)
else()
  list(APPEND QT_COMPONENTS OpenGLWidgets)
endif()

message(STATUS "Using Qt version ${QT_VERSION_MAJOR}")
if(USE_QGLWIDGET)
  message(STATUS "Using QGLWidget")
else()
  message(STATUS "Using QOpenGLWidget")
endif()

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS ${QT_COMPONENTS})

if(USE_PROJECTM4)
  message(STATUS "Using ProjectM version 4")
  find_package(projectM4 COMPONENTS Playlist REQUIRED)
  set(LIBPROJECTM_FOUND ON)
  set(HAVE_PROJECTM4 ON)
  set(LIBPROJECTM_LIBRARIES libprojectM::projectM libprojectM::playlist)
else()
  pkg_check_modules(LIBPROJECTM REQUIRED libprojectM)
  message(STATUS "Using ProjectM version ${LIBPROJECTM_VERSION}")
endif()

add_subdirectory(src)
