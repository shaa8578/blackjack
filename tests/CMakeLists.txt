cmake_minimum_required(VERSION 3.7.0)

project(UNIT_TESTS VERSION 0.0.1 LANGUAGES CXX)

#-------------------------------------------------------------------------------
include(CTest)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(BUILD_SHARED_LIBS OFF)

#-------------------------------------------------------------------------------
macro(change_output_dir target)
  set_target_properties(${target} PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
      ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
  )
endmacro()

#-------------------------------------------------------------------------------
find_path(GOOGLETEST_PATH ".git"
  PATHS "${CMAKE_CURRENT_SOURCE_DIR}/googletest"
  DOC "Googletest: Библиотека модульных тестов"
  NO_DEFAULT_PATH
)
if(${GOOGLETEST_PATH} STREQUAL "GOOGLETEST_PATH-NOTFOUND")
  find_package(Git)
  set(GOOGLETEST_PATH "${CMAKE_CURRENT_SOURCE_DIR}/googletest")
  set(GOOGLETEST_GIT "https://github.com/google/googletest.git")
  execute_process(
    COMMAND ${GIT_EXECUTABLE} clone ${GOOGLETEST_GIT} ${GOOGLETEST_PATH}
    RESULT_VARIABLE GIT_RESULT
    OUTPUT_VARIABLE GIT_OUTPUT)
  if(NOT (GIT_RESULT EQUAL "0") )
    message(FATAL_ERROR "Error downloading project googletest")
  endif()
endif()

set(BUILD_GMOCK OFF CACHE BOOL "Сборка GMock")
add_subdirectory(googletest)

change_output_dir(gtest)
change_output_dir(gtest_main)

#-------------------------------------------------------------------------------
set(tst_target "tst-blackjack-objects")

add_executable(${tst_target} WIN32
  main_test.cpp
  tst_card.cpp
  tst_hand.cpp
)
change_output_dir(${tst_target})

target_link_libraries(${tst_target} PRIVATE
  gtest gtest_main
#  gmock gmock_main
  blackjack-objects
)

target_compile_features(${tst_target} PRIVATE
  cxx_auto_type
  cxx_generic_lambdas
)

target_compile_options(${tst_target} PRIVATE
  -Wall
  -Wextra
  -Wpedantic
  -Wnonnull
)

add_test(NAME ${PROJECT_NAME} COMMAND ${tst_target})

