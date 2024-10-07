#ifndef DEFS_DEFS_HPP
#define DEFS_DEFS_HPP

#include <string>
#include <iostream>
#include <functional>
#include "engine.hpp"

typedef std::function<std::string (chess::engine::Engine &, std::string)> Command;

const std::string release = "release";
const std::string debug = "debug";

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
