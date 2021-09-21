cmake_minimum_required(VERSION 3.7.0)
cmake_policy(SET CMP0077 NEW)

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

set(CMAKE_INCLUDE_CURRENT_DIR ON)

#-------------------------------------------------------------------------------
if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_EXE_LINKER_FLAGS "-Wl,-rpath,'$ORIGIN'/../lib,-rpath,'$ORIGIN'")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin CACHE PATH
    "Путь до исполняемых файлов сборки")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib CACHE PATH
    "Путь до динамических библиотек")
else()
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin CACHE PATH
    "Путь до исполняемых файлов сборки")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin CACHE PATH
    "Путь до динамических библиотек")
endif()

#-------------------------------------------------------------------------------
macro(target_setup target)
  target_compile_features(${target} PRIVATE
    cxx_auto_type
    cxx_generic_lambdas
  )

  target_compile_options(${target} PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wnonnull
  #  -Wno-deprecated-copy
  #  -save-temps
  )
endmacro()

#-------------------------------------------------------------------------------
add_subdirectory(lib-objects)

set(app_target "blackjack")
add_executable(${app_target} WIN32
  src/main.cpp
  src/game.cpp
  src/game.h
)
target_setup(${app_target})

target_link_libraries(${app_target} PRIVATE
  blackjack-objects
)

target_compile_definitions(${app_target} PRIVATE
  TARGET="${app_target}"
  $<$<NOT:$<CONFIG:Debug>>:USING_SRAND>
)

#-------------------------------------------------------------------------------
if(DEFINED BUILD_TESTING AND BUILD_TESTING)
  add_subdirectory(tests)
endif()
