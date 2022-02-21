cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(
  model
  VERSION 0.1.0
  LANGUAGES C)

find_package(hmr REQUIRED)
find_package(imm REQUIRED)
find_package(lite_pack REQUIRED)

include(cmake/sanitizers.cmake)

# Generate compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(
  ${PROJECT_NAME}
  src/logger.c
  src/nuclt_dist.c
  src/profile.c
  src/profile_types.c
  src/protein_codec.c
  src/protein_model.c
  src/protein_profile.c
  src/protein_state.c
  src/standard_profile.c
  src/standard_state.c
  src/to_str.c)

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC $<INSTALL_INTERFACE:include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
  PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_link_libraries(${PROJECT_NAME} PUBLIC HMR::hmr)
target_link_libraries(${PROJECT_NAME} PUBLIC IMM::imm)
target_link_libraries(${PROJECT_NAME} PUBLIC LITE_PACK::lite_pack)
target_link_libraries(${PROJECT_NAME} INTERFACE $<$<BOOL:${UNIX}>:m>)

target_compile_features(${PROJECT_NAME} PRIVATE c_std_11)

target_compile_definitions(
  ${PROJECT_NAME} PRIVATE $<$<BOOL:${WIN32}>:_CRT_NONSTDC_NO_DEPRECATE>)
target_compile_definitions(${PROJECT_NAME} PRIVATE _XOPEN_SOURCE=700)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  include(CheckIPOSupported)
  check_ipo_supported()
  set_target_properties(${PROJECT_NAME} PROPERTIES INTERPROCEDURAL_OPTIMIZATION
                                                   TRUE)
endif()

enable_testing()
add_subdirectory(test)
