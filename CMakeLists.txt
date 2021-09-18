cmake_minimum_required(VERSION 3.7.0)

#-------------------------------------------------------------------------------
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR "The build directory can not equal source!!!")
endif()

if(NOT (CMAKE_BUILD_TYPE))
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Тип сборки" FORCE)
  message(STATUS "Set default build type: ${CMAKE_BUILD_TYPE}")
else()
  message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
endif()

#-------------------------------------------------------------------------------
project(BLACKJACK VERSION 0.0.1 LANGUAGES CXX)

#-------------------------------------------------------------------------------
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#-------------------------------------------------------------------------------
set(SOURCES_FILES
  main.cpp
  card.cpp
)

set(HEADERS_FILES
  card.h
)

set(app_target "blackjack")
add_executable(${app_target} WIN32
  ${SOURCES_FILES}
  ${HEADERS_FILES}
)

target_compile_features(${app_target} PRIVATE
  cxx_auto_type
  cxx_generic_lambdas
)

target_compile_options(${app_target} PRIVATE
  -Wall
  -Wextra
  -Wpedantic
  -Wnonnull
#  -Wno-deprecated-copy
#  -save-temps
)

target_compile_definitions(${app_target} PRIVATE
  $<$<NOT:$<CONFIG:Debug>>:USING_SRAND>
  TARGET="${app_target}"
)

