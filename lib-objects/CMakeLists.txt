cmake_minimum_required(VERSION 3.7.0)

project(BJ_OBJECTS LANGUAGES CXX)
set(PROJECT_LABEL blackjack-objects)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 1)
set(PROJECT_VERSION
  "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
set(PROJECT_SOVERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")

#-------------------------------------------------------------------------------
set(CMAKE_VERBOSE_MAKEFILE ON)
set(BUILD_SHARED_LIBS ON)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -save-temps")

#-------------------------------------------------------------------------------
set(SOURCES_FILES
  card.cpp
  hand.cpp
)

#-------------------------------------------------------------------------------
set(HEADERS_FILES
  include/blackjack_objects_global.hpp
  include/blackjack/card.h
  include/blackjack/hand.h
)

#-------------------------------------------------------------------------------
add_library(${PROJECT_LABEL} SHARED
  ${SOURCES_FILES}
  ${HEADERS_FILES}
)

target_setup(${PROJECT_LABEL})

set_target_properties(${PROJECT_LABEL} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_SOVERSION}
)

target_compile_definitions(${PROJECT_LABEL} PRIVATE
  $<$<NOT:$<CONFIG:Debug>>:USING_SRAND>
  -DBLACKJACK_LIBRARY=1
)

target_include_directories(${PROJECT_LABEL} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

