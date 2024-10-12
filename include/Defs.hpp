#ifndef DEFS_DEFS_HPP
#define DEFS_DEFS_HPP

#include <string>
#include <iostream>
#include <functional>
#include "engine.hpp"
#include <cstdint>

namespace chess
{
namespace consts
{
typedef std::function<std::string (chess::engine::Engine &, std::string)> Command;
typedef uint64_t bitboard;
typedef uint8_t flag;

const std::string release = "release";
const std::string debug = "debug";
const std::string pieces = "PNBRQKpnbqkGg";
const bitboard BITBOARD_MAX = UINT64_MAX;
const flag BOARD_FLAG_MAX = 0b10111111;

const flag WTP = (flag)0b00000001;
const flag ENP = (flag)0b00000010;
const flag Q = (flag)0b00000100;
const flag K = (flag)0b00001000;
const flag q = (flag)0b00010000;
const flag k = (flag)0b00100000;
const flag BOARD = (flag)0b10000000;

}
}
#ifdef NDEBUG
#define CERR                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       \
    if (false)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     \
    std::cerr
#define CONFIGURATION release
#else
#define CERR std::cerr << "Debug: " << __FILE__ << " " << __LINE__ << ": "
#define CONFIGURATION debug
#endif

#endif
