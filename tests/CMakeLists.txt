file(GLOB TEST_SOURCES "*.cpp")

add_executable(full ${TEST_SOURCES})
set_target_properties(full PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)
target_include_directories(full PRIVATE ${CMAKE_SOURCE_DIR}/include
                                        ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(full PRIVATE chess gtest gtest_main)
target_compile_options(
  full
  PRIVATE $<$<CONFIG:DEBUG>:-Wall
          -Werror
          -Wextra
          -Wpedantic
          -Wno-unused
          -fno-inline
          -g
          >
          $<$<CONFIG:Release>:-DNDEBUG
          >
          $<$<CONFIG:Profile>:
          -DNDEBUG
          -g
          -pg>)

add_executable(bitboard run_tests.cpp bitboard_tests.cpp)
set_target_properties(bitboard PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED
                                                          ON)
target_include_directories(bitboard PRIVATE ${CMAKE_SOURCE_DIR}/include
                                            ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(bitboard PRIVATE chess gtest gtest_main)
target_compile_options(
  bitboard
  PRIVATE $<$<CONFIG:DEBUG>:-Wall
          -Werror
          -Wextra
          -Wpedantic
          -Wno-unused
          -fno-inline
          -g
          >
          $<$<CONFIG:Release>:-DNDEBUG
          >
          $<$<CONFIG:Profile>:
          -DNDEBUG
          -g
          -pg>)

add_executable(board run_tests.cpp board_tests.cpp)
set_target_properties(board PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)
target_include_directories(board PRIVATE ${CMAKE_SOURCE_DIR}/include
                                         ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(board PRIVATE chess gtest gtest_main)
target_compile_options(
  board
  PRIVATE $<$<CONFIG:DEBUG>:-Wall
          -Werror
          -Wextra
          -Wpedantic
          -Wno-unused
          -fno-inline
          -g
          >
          $<$<CONFIG:Release>:-DNDEBUG
          >
          $<$<CONFIG:Profile>:
          -DNDEBUG
          -g
          -pg>)

add_executable(engine_handler run_tests.cpp engine_handler_tests.cpp)
set_target_properties(engine_handler PROPERTIES CXX_STANDARD 20
                                                CXX_STANDARD_REQUIRED ON)
target_include_directories(engine_handler PRIVATE ${CMAKE_SOURCE_DIR}/include
                                                  ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(engine_handler PRIVATE chess gtest gtest_main)
target_compile_options(
  engine_handler
  PRIVATE $<$<CONFIG:DEBUG>:-Wall
          -Werror
          -Wextra
          -Wpedantic
          -Wno-unused
          -fno-inline
          -g
          >
          $<$<CONFIG:Release>:-DNDEBUG
          >
          $<$<CONFIG:Profile>:
          -DNDEBUG
          -g
          -pg>)

add_executable(engine run_tests.cpp engine_tests.cpp)
set_target_properties(engine PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED
                                                        ON)
target_include_directories(engine PRIVATE ${CMAKE_SOURCE_DIR}/include
                                          ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(engine PRIVATE chess gtest gtest_main)
target_compile_options(
  engine
  PRIVATE $<$<CONFIG:DEBUG>:-Wall
          -Werror
          -Wextra
          -Wpedantic
          -Wno-unused
          -fno-inline
          -g
          >
          $<$<CONFIG:Release>:-DNDEBUG
          >
          $<$<CONFIG:Profile>:
          -DNDEBUG
          -g
          -pg>)

add_executable(flag run_tests.cpp flag_tests.cpp)
set_target_properties(flag PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)
target_include_directories(flag PRIVATE ${CMAKE_SOURCE_DIR}/include
                                        ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(flag PRIVATE chess gtest gtest_main)
target_compile_options(
  flag
  PRIVATE $<$<CONFIG:DEBUG>:-Wall
          -Werror
          -Wextra
          -Wpedantic
          -Wno-unused
          -fno-inline
          -g
          >
          $<$<CONFIG:Release>:-DNDEBUG
          >
          $<$<CONFIG:Profile>:
          -DNDEBUG
          -g
          -pg>)

add_executable(moveGenerator_quick run_tests.cpp moveGenerator_quick_tests.cpp)
set_target_properties(moveGenerator_quick PROPERTIES CXX_STANDARD 20
                                                     CXX_STANDARD_REQUIRED ON)
target_include_directories(
  moveGenerator_quick PRIVATE ${CMAKE_SOURCE_DIR}/include
                              ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(moveGenerator_quick PRIVATE chess gtest gtest_main)
target_compile_options(
  moveGenerator_quick
  PRIVATE $<$<CONFIG:DEBUG>:-Wall
          -Werror
          -Wextra
          -Wpedantic
          -Wno-unused
          -fno-inline
          -g
          >
          $<$<CONFIG:Release>:-DNDEBUG
          >
          $<$<CONFIG:Profile>:
          -DNDEBUG
          -g
          -pg>)

add_executable(moveGenerator_long run_tests.cpp moveGenerator_long_tests.cpp)
set_target_properties(moveGenerator_long PROPERTIES CXX_STANDARD 20
                                                    CXX_STANDARD_REQUIRED ON)
target_include_directories(
  moveGenerator_long PRIVATE ${CMAKE_SOURCE_DIR}/include
                             ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(moveGenerator_long PRIVATE chess gtest gtest_main)
target_compile_options(
  moveGenerator_long
  PRIVATE $<$<CONFIG:DEBUG>:-Wall
          -Werror
          -Wextra
          -Wpedantic
          -Wno-unused
          -fno-inline
          -g
          >
          $<$<CONFIG:Release>:-DNDEBUG
          >
          $<$<CONFIG:Profile>:
          -DNDEBUG
          -g
          -pg>)

add_executable(moves run_tests.cpp moves_tests.cpp)
set_target_properties(moves PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)
target_include_directories(moves PRIVATE ${CMAKE_SOURCE_DIR}/include
                                         ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(moves PRIVATE chess gtest gtest_main)
target_compile_options(
  moves
  PRIVATE $<$<CONFIG:DEBUG>:-Wall
          -Werror
          -Wextra
          -Wpedantic
          -Wno-unused
          -fno-inline
          -g
          >
          $<$<CONFIG:Release>:-DNDEBUG
          >
          $<$<CONFIG:Profile>:
          -DNDEBUG
          -g
          -pg>)

add_executable(hash run_tests.cpp hash_tests.cpp)
set_target_properties(hash PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)
target_include_directories(hash PRIVATE ${CMAKE_SOURCE_DIR}/include
                                        ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(hash PRIVATE chess gtest gtest_main)
target_compile_options(
  hash
  PRIVATE $<$<CONFIG:DEBUG>:-Wall
          -Werror
          -Wextra
          -Wpedantic
          -Wno-unused
          -fno-inline
          -g
          >
          $<$<CONFIG:Release>:-DNDEBUG
          >
          $<$<CONFIG:Profile>:
          -DNDEBUG
          -g
          -pg>)

add_executable(board_state run_tests.cpp board_state_tests.cpp)
set_target_properties(board_state PROPERTIES CXX_STANDARD 20
                                             CXX_STANDARD_REQUIRED ON)
target_include_directories(board_state PRIVATE ${CMAKE_SOURCE_DIR}/include
                                               ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(board_state PRIVATE chess gtest gtest_main)
target_compile_options(
  board_state
  PRIVATE $<$<CONFIG:DEBUG>:-Wall
          -Werror
          -Wextra
          -Wpedantic
          -Wno-unused
          -fno-inline
          -g
          >
          $<$<CONFIG:Release>:-DNDEBUG
          >
          $<$<CONFIG:Profile>:
          -DNDEBUG
          -g
          -pg>)

enable_testing()
add_test(NAME bitboard COMMAND bitboard)
add_test(NAME board COMMAND board)
add_test(NAME engine_handler COMMAND engine_handler)
add_test(NAME engine COMMAND engine)
add_test(NAME flag COMMAND flag)
add_test(NAME moveGenerator_quick COMMAND moveGenerator_quick)
add_test(NAME moveGenerator_long COMMAND moveGenerator_long)
add_test(NAME moves COMMAND moves)
add_test(NAME hash COMMAND hash)
add_test(NAME board_state COMMAND board_state)
