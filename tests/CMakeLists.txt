file(GLOB TEST_SOURCES "*.cpp")

add_executable(full ${TEST_SOURCES})
target_include_directories(full PRIVATE ${CMAKE_SOURCE_DIR}/include
                                        ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(full PRIVATE chess gtest gtest_main)

add_executable(bitboard run_tests.cpp bitboard_tests.cpp)
target_include_directories(bitboard PRIVATE ${CMAKE_SOURCE_DIR}/include
                                            ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(bitboard PRIVATE chess gtest gtest_main)

add_executable(board run_tests.cpp board_tests.cpp)
target_include_directories(board PRIVATE ${CMAKE_SOURCE_DIR}/include
                                         ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(board PRIVATE chess gtest gtest_main)

add_executable(engine_handler run_tests.cpp engine_handler_tests.cpp)
target_include_directories(engine_handler PRIVATE ${CMAKE_SOURCE_DIR}/include
                                                  ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(engine_handler PRIVATE chess gtest gtest_main)

add_executable(engine run_tests.cpp engine_tests.cpp)
target_include_directories(engine PRIVATE ${CMAKE_SOURCE_DIR}/include
                                          ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(engine PRIVATE chess gtest gtest_main)

add_executable(flag run_tests.cpp flag_tests.cpp)
target_include_directories(flag PRIVATE ${CMAKE_SOURCE_DIR}/include
                                        ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(flag PRIVATE chess gtest gtest_main)

add_executable(moveGenerator_quick run_tests.cpp moveGenerator_quick_tests.cpp)
target_include_directories(
  moveGenerator_quick PRIVATE ${CMAKE_SOURCE_DIR}/include
                              ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(moveGenerator_quick PRIVATE chess gtest gtest_main)

add_executable(moveGenerator_long run_tests.cpp moveGenerator_long_tests.cpp)
target_include_directories(
  moveGenerator_long PRIVATE ${CMAKE_SOURCE_DIR}/include
                             ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(moveGenerator_long PRIVATE chess gtest gtest_main)

add_executable(moves run_tests.cpp moves_tests.cpp)
target_include_directories(moves PRIVATE ${CMAKE_SOURCE_DIR}/include
                                         ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(moves PRIVATE chess gtest gtest_main)

enable_testing()
add_test(NAME bitboard COMMAND bitboard)
add_test(NAME board COMMAND board)
add_test(NAME engine_handler COMMAND engine_handler)
add_test(NAME engine COMMAND engine)
add_test(NAME flag COMMAND flag)
add_test(NAME moveGenerator_quick COMMAND moveGenerator_quick)
add_test(NAME moveGenerator_long COMMAND moveGenerator_long)
add_test(NAME moves COMMAND moves)
