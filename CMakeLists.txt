cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(
  deciphon_model
  VERSION 0.1.0
  LANGUAGES C)

find_package(hmr REQUIRED)
find_package(imm REQUIRED)
find_package(lite_pack REQUIRED)

# Generate compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/compiler-options.cmake)
include(cmake/sanitizers.cmake)

add_library(
  ${PROJECT_NAME}
  src/logger.c
  src/nuclt_dist.c
  src/profile.c
  src/profile_types.c
  src/protein_codec.c
  src/protein_h3reader.c
  src/protein_model.c
  src/protein_profile.c
  src/protein_state.c
  src/standard_profile.c
  src/standard_state.c
  src/to_str.c)
add_library(DECIPHON::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC $<INSTALL_INTERFACE:include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
  PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)

target_link_libraries(${PROJECT_NAME} PUBLIC HMR::hmr)
target_link_libraries(${PROJECT_NAME} PUBLIC IMM::imm)
target_link_libraries(${PROJECT_NAME} PUBLIC LITE_PACK::lite_pack)
target_link_libraries(${PROJECT_NAME} INTERFACE $<$<BOOL:${UNIX}>:m>)

target_compile_features(${PROJECT_NAME} PRIVATE c_std_11)

target_compile_options(${PROJECT_NAME} PRIVATE ${WARNING_FLAGS})
target_compile_definitions(
  ${PROJECT_NAME} PRIVATE $<$<BOOL:${WIN32}>:_CRT_NONSTDC_NO_DEPRECATE>)
target_compile_definitions(${PROJECT_NAME} PRIVATE _XOPEN_SOURCE=700)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  include(CheckIPOSupported)
  check_ipo_supported()
  set_target_properties(${PROJECT_NAME} PROPERTIES INTERPROCEDURAL_OPTIMIZATION
                                                   TRUE)
endif()

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-targets)
install(DIRECTORY include/${PROJECT_NAME}/ DESTINATION include/${PROJECT_NAME})
install(
  EXPORT ${PROJECT_NAME}-targets
  FILE ${PROJECT_NAME}-targets.cmake
  NAMESPACE DECIPHON::
  DESTINATION lib/cmake/${PROJECT_NAME})

include(CMakePackageConfigHelpers)
set(CMAKE_CONFIG_FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake)
configure_package_config_file(
  ${PROJECT_NAME}-config.cmake.in ${CMAKE_CONFIG_FILE}
  INSTALL_DESTINATION lib/cmake/${PROJECT_NAME})

install(FILES ${CMAKE_CONFIG_FILE} DESTINATION lib/cmake/${PROJECT_NAME})

enable_testing()
add_subdirectory(test)
