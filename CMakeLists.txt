cmake_minimum_required(VERSION 3.10)

project(UNITS
  LANGUAGES CXX
)

find_package(Threads)

add_executable(testUnits
  testUnits.cc
  googletest/googletest/src/gtest-all.cc
)

target_include_directories(testUnits
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest"
)

target_link_libraries(testUnits
  PRIVATE
    Threads::Threads
)

target_compile_options(testUnits
  PRIVATE
    "-Wall" "-Wextra" "-g" "-O2"
)

target_compile_features(testUnits
  PUBLIC
    cxx_std_17
)

set_target_properties(testUnits
  PROPERTIES
    CXX_EXTENSIONS OFF
)
