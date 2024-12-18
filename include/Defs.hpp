#ifndef DEFS_DEFS_HPP
#define DEFS_DEFS_HPP

#include <string>
#include <iostream>
#include <functional>
#include <cstdint>

namespace chess
{
namespace engine
{
class Engine;
}
namespace consts
{
typedef std::function<std::string (chess::engine::Engine &, std::string)> Command;
typedef uint64_t bitboard;
typedef uint8_t flag;
typedef uint32_t move;
typedef uint64_t hash;

const std::string release = "release";
const std::string debug = "debug";
const std::string pieces = "PNBRQKpnbrqkGg";
// const std::string squares = "A1B1C1D1E1F1G1H1A2B2C2D2E2F2G2H2A3B3C3D3E3F3G3H3A4B4C4D4E4F4G4H4A5B5C5D5E5F5G5H5A6B6C6D6E6F6G6H6A7B7C7D7E7F7G7H7A8B8C8D8E8F8G8H8";
// const std::string squares = "A8B8C8D8E8F8G8H8A7B7C7D7E7F7G7H7A6B6C6D6E6F6G6H6A5B5C5D5E5F5G5H5A4B4C4D4E4F4G4H4A3B3C3D3E3F3G3H3A2B2C2D2E2F2G2H2A1B1C1D1E1F1G1H1";
// --------------------------0-1-2-3-4-5-6-7-8-9-101112131415161718192021222324252627282930313233343536373839404142434445464748495051525354555657585960616263
const std::string squares = "a8b8c8d8e8f8g8h8a7b7c7d7e7f7g7h7a6b6c6d6e6f6g6h6a5b5c5d5e5f5g5h5a4b4c4d4e4f4g4h4a3b3c3d3e3f3g3h3a2b2c2d2e2f2g2h2a1b1c1d1e1f1g1h1";
const std::string ranks = "12345678";
const std::string files = "ABCDEFGH";
const std::string startpos = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
const std::string kiwipete = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";
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
    k,
    empty
};

enum Square
{
    A8,
    B8,
    C8,
    D8,
    E8,
    F8,
    G8,
    H8,
    A7,
    B7,
    C7,
    D7,
    E7,
    F7,
    G7,
    H7,
    A6,
    B6,
    C6,
    D6,
    E6,
    F6,
    G6,
    H6,
    A5,
    B5,
    C5,
    D5,
    E5,
    F5,
    G5,
    H5,
    A4,
    B4,
    C4,
    D4,
    E4,
    F4,
    G4,
    H4,
    A3,
    B3,
    C3,
    D3,
    E3,
    F3,
    G3,
    H3,
    A2,
    B2,
    C2,
    D2,
    E2,
    F2,
    G2,
    H2,
    A1,
    B1,
    C1,
    D1,
    E1,
    F1,
    G1,
    H1
};

static std::unordered_map<std::string, std::vector<chess::consts::bitboard> >
getTestSuite ()
{
    std::unordered_map<std::string, std::vector<chess::consts::bitboard> > testsuite;
    testsuite[chess::consts::startpos] = { 1, 20, 400, 8902, 197281, 4865609 };
    testsuite[chess::consts::kiwipete] = { 1, 48, 2039, 97862, 4085603 };
    testsuite["8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -"] = { 1, 14, 191, 2812, 43238, 674624, 11030083 };
    testsuite["r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1"] = { 1, 6, 264, 9467, 422333, 15833292 };
    testsuite["rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8"] = { 1, 44, 1486, 62379, 2103487 };
    return testsuite;
}

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
