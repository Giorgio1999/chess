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
const std::string squares = "A1B1C1D1E1F1G1H1A2B2C2D2E2F2G2H2A3B3C3D3E3F3G3H3A4B4C4D4E4F4G4H4A5B5C5D5E5F5G5H5A6B6C6D6E6F6G6H6A7B7C7D7E7F7G7H7A8B8C8D8E8F8G8H8";
const std::string ranks = "12345678";
const std::string files = "ABCDEFGH";
const bitboard BITBOARD_MAX = UINT64_MAX;
const flag BOARD_FLAG_MAX = 0b10111111;

const flag WTP_FLAG = (flag)0b00000001;
const flag ENP_FLAG = (flag)0b00000010;
const flag Q_FLAG = (flag)0b00000100;
const flag K_FLAG = (flag)0b00001000;
const flag q_FLAG = (flag)0b00010000;
const flag k_FLAG = (flag)0b00100000;
const flag BOARD = (flag)0b10000000;

enum castling_rights_name
{
    CASTLE_K,
    CASTLE_Q,
    CASTLE_k,
    CASTLE_q
};

enum Piece
{
    P,
    N,
    B,
    R,
    Q,
    K,
    p,
    n,
    b,
    r,
    q,
    k
};

enum Square
{
    A1,
    B1,
    C1,
    D1,
    E1,
    F1,
    G1,
    H1,
    A2,
    B2,
    C2,
    D2,
    E2,
    F2,
    G2,
    H2,
    A3,
    B3,
    C3,
    D3,
    E3,
    F3,
    G3,
    H3,
    A4,
    B4,
    C4,
    D4,
    E4,
    F4,
    G4,
    H4,
    A5,
    B5,
    C5,
    D5,
    E5,
    F5,
    G5,
    H5,
    A6,
    B6,
    C6,
    D6,
    E6,
    F6,
    G6,
    H6,
    A7,
    B7,
    C7,
    D7,
    E7,
    F7,
    G7,
    H7,
    A8,
    B8,
    C8,
    D8,
    E8,
    F8,
    G8,
    H8
};

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
