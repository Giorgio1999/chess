#ifndef DEFS_DEFS_HPP
#define DEFS_DEFS_HPP

#include <string>
#include <iostream>
#include <functional>
#include "engine.hpp"
#include <cstdint>

typedef std::function<std::string (chess::engine::Engine &, std::string)> Command;
typedef uint64_t bitboard;

const std::string release = "release";
const std::string debug = "debug";
const std::string pieces = "PNBRQKpnbqk";

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
