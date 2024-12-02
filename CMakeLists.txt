cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Setze Release-Flags auf -Ofast und entferne andere optimierende Flags
set(CMAKE_CXX_FLAGS_RELEASE
    "-Ofast"
    CACHE STRING "Compiler flags for release build" FORCE)

project(chess VERSION 1.0.0)
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_library(chess STATIC ${SOURCES})

target_include_directories(chess PUBLIC include ${CMAKE_CURRENT_BINARY_DIR})

set_target_properties(chess PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_compile_options(
  chess
  PRIVATE $<$<CONFIG:Debug>:
          -Wall
          -Werror
          -Wextra
          -Wpedantic
          -Wno-unused
          -fno-inline
          -g>
          $<$<CONFIG:Release>:
          -DNDEBUG>)

add_executable(magicGenerator src/magicGenerator.cpp)
target_include_directories(magicGenerator PUBLIC include
                                                 ${CMAKE_CURRENT_BINARY_DIR})
set(DATA_FILE "${CMAKE_BINARY_DIR}/magicData.hpp")
add_custom_command(
  OUTPUT ${DATA_FILE}
  COMMAND magicGenerator
  DEPENDS magicGenerator
  COMMENT "Generating magic number:")
add_custom_target(generateMagics DEPENDS ${DATA_FILE})
add_dependencies(chess generateMagics)

add_executable(example_program examples/example_program.cpp)
target_link_libraries(example_program PRIVATE chess)
set_target_properties(example_program PROPERTIES CXX_STANDARD 17
                                                 CXX_STANDARD_REQUIRED ON)
target_compile_options(
  example_program
  PRIVATE $<$<CONFIG:Debug>:
          -Wall
          -Werror
          -Wextra
          -Wpedantic
          -Wno-unused
          -fno-inline
          -g>
          $<$<CONFIG:Release>:
          -DNDEBUG>)

add_executable(example_engine examples/example_engine.cpp)
target_link_libraries(example_engine PRIVATE chess)
set_target_properties(example_engine PROPERTIES CXX_STANDARD 17
                                                CXX_STANDARD_REQUIRED ON)
target_compile_options(
  example_engine
  PRIVATE $<$<CONFIG:Debug>:
          -Wall
          -Werror
          -Wextra
          -Wpedantic
          -Wno-unused
          -fno-inline
          -g>
          $<$<CONFIG:Release>:
          -DNDEBUG>)

install(
  TARGETS chess
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
  ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
install(TARGETS example_engine DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
install(TARGETS example_program DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

execute_process(
  COMMAND
    ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_BINARY_DIR}/compile_commands.json
    ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json)
configure_file(chessConfig.h.in chessConfig.h)

add_subdirectory(tests)
enable_testing()
