cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(chess VERSION 1.0.0)
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_library(chess ${SOURCES})

target_include_directories(chess PUBLIC
    include
    ${CMAKE_CURRENT_BINARY_DIR}
)

set_target_properties(chess PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON)

target_compile_options(chess PRIVATE
    -Wall -Werror -Wextra -Wpedantic -Wno-unused
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Release>:-O3 -DNDEBUG>
)

add_executable(example_program examples/example_program.cpp)
target_link_libraries(example_program PRIVATE chess)
set_target_properties(example_program PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

add_executable(example_engine examples/example_engine.cpp)
target_link_libraries(example_engine PRIVATE chess)
set_target_properties(example_engine PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

install(TARGETS chess
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json)
configure_file(chessConfig.h.in chessConfig.h)

add_subdirectory(tests)
enable_testing()

