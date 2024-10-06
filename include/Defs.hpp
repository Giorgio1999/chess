#ifndef DEFS_DEFS_HPP
#define DEFS_DEFS_HPP

#include <string>
#include <iostream>

const std::string release = "realease";
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
