#include <fstream>
#include <unordered_map>
#include <vector>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <random>

typedef uint64_t bitboard;

void
PrintHeader (std::fstream &target)
{
    target << "#include <array>" << std::endl;
    target << "#include \"Defs.hpp\"" << std::endl << std::endl;
    target << "namespace chess {" << std::endl;
    target << "namespace data {" << std::endl;
}

void
PrintCloser (std::fstream &target)
{
    target << "}" << std::endl << "}" << std::endl;
    target.close ();
}

int
pop_lsb (bitboard &b)
{
    int res = __builtin_ffsll (b) - 1;
    if (res > -1)
        {
            b ^= (bitboard)1 << res;
        }

    return res;
}

std::string
visualize_bitboard (bitboard b)
{
    std::array<uint, 64> occupations;
    for (uint i = 0; i < 64; i++)
        {
            occupations[i] = 0;
        }
    while (b > 0)
        {
            uint i = pop_lsb (b);
            occupations[i] = 1;
        }
    std::string res;
    for (uint i = 0; i < 8; i++)
        {
            for (uint j = 0; j < 8; j++)
                {
                    res += occupations[i * 8 + j] == 1 ? "o" : "-";
                }
            res += "\n";
        }
    return res;
}

std::array<std::vector<bitboard>, 64>
getOccupanciesForEachSquare_rook (std::array<bitboard, 64> &relevantoccupancy_masks)
{

    std::array<std::vector<bitboard>, 64> occupanciesForEachSquare;
    for (uint square = 0; square < 64; square++)
        {
            uint file = square % 8;
            uint rank = (square - file) / 8;
            bitboard zeroRankMask = 0x000000000000007E;
            bitboard zeroFileMask = 0x0001010101010100;
            bitboard relevantoccupancy_mask = (zeroRankMask << (rank * 8)) | (zeroFileMask << file);
            relevantoccupancy_mask &= ~((bitboard)1 << square);
            relevantoccupancy_masks[square] = relevantoccupancy_mask;

            std::vector<uint> places;
            while (relevantoccupancy_mask > 0)
                {
                    places.push_back (pop_lsb (relevantoccupancy_mask));
                }
            bitboard numberOfOccs = (bitboard)1 << places.size ();

            std::vector<bitboard> occupancies;
            for (uint occupation_index = 0; occupation_index < numberOfOccs; occupation_index++)
                {
                    bitboard occupation = (bitboard)0;
                    for (uint bit_index = 0; bit_index < places.size (); bit_index++)
                        {
                            uint bit = (occupation_index >> bit_index) & (bitboard)1;
                            occupation |= (bitboard)bit << places[bit_index];
                        }
                    occupancies.push_back (occupation);
                }
            /*std::cout << "square: " << std::to_string (square) << std::endl;*/
            /*std::cout << visualize_bitboard (occupancies.back ()) << std::endl;*/
            occupanciesForEachSquare[square] = occupancies;
        }
    return occupanciesForEachSquare;
}

std::array<std::vector<bitboard>, 64>
getOccupanciesForEachSquare_bishop (std::array<bitboard, 64> &relevantoccupancy_masks)
{
    std::array<std::vector<bitboard>, 64> occupanciesForEachSquare;
    for (uint square = 0; square < 64; square++)
        {
            uint file = square % 8;
            uint rank = (square - file) / 8;
            bitboard a1h8 = 0x0102040810204080;
            bitboard a8h1 = 0x8040201008040201;
            bitboard edgetrimmer = 0xFF818181818181FF;
            bitboard northborder = 0x00000000000000FF;
            bitboard eastborder = 0x8080808080808080;
            bitboard southborder = 0xFF00000000000000;
            bitboard westborder = 0x0101010101010101;
            int disttoa1h8 = file - (7 - rank);
            int disttoa8h1 = rank - file;
            bitboard mask_a1h8 = a1h8;
            if (disttoa1h8 > 0)
                {
                    for (int offset = 0; offset < disttoa1h8; offset++)
                        {
                            mask_a1h8 &= ~(southborder | eastborder);
                            mask_a1h8 = mask_a1h8 << 8;
                        }
                }
            else
                {
                    for (int offset = disttoa1h8; offset < 0; offset++)
                        {
                            mask_a1h8 &= ~(northborder | westborder);
                            mask_a1h8 = mask_a1h8 >> 8;
                        }
                }
            bitboard mask_a8h1 = a8h1;
            if (disttoa8h1 > 0)
                {
                    for (int offset = 0; offset < disttoa8h1; offset++)
                        {
                            mask_a8h1 &= ~(southborder | westborder);
                            mask_a8h1 = mask_a8h1 << 8;
                        }
                }
            else
                {
                    for (int offset = disttoa8h1; offset < 0; offset++)
                        {
                            mask_a8h1 &= ~(northborder | eastborder);
                            mask_a8h1 = mask_a8h1 >> 8;
                        }
                }
            bitboard mask = mask_a8h1 | mask_a1h8;
            mask &= ~((bitboard)1 << square);
            mask &= ~edgetrimmer;
            relevantoccupancy_masks[square] = mask;

            std::vector<uint> places;
            while (mask > 0)
                {
                    places.push_back (pop_lsb (mask));
                }
            bitboard numberOfOccs = (bitboard)1 << places.size ();

            std::vector<bitboard> occupancies;
            for (uint occupation_index = 0; occupation_index < numberOfOccs; occupation_index++)
                {
                    bitboard occupation = (bitboard)0;
                    for (uint bit_index = 0; bit_index < places.size (); bit_index++)
                        {
                            uint bit = (occupation_index >> bit_index) & (bitboard)1;
                            occupation |= (bitboard)bit << places[bit_index];
                        }
                    occupancies.push_back (occupation);
                }
            occupanciesForEachSquare[square] = occupancies;
        }
    return occupanciesForEachSquare;
}

void
genMagics_rook (const uint n, std::array<bitboard, 64> &magicNumbers, std::array<bitboard, 64> &relevantoccupancy_masks, std::array<std::vector<bitboard>, 64> &occupanciesForEachSquare)
{
    std::random_device rd;
    std::mt19937_64 e2 (rd ());
    std::uniform_int_distribution<bitboard> dist (std::llround (std::pow (2, 0)), std::llround (std::pow (2, 62)));
    occupanciesForEachSquare = getOccupanciesForEachSquare_rook (relevantoccupancy_masks);
    uint magicShift = 64 - n;
    std::array<std::vector<bitboard>, 64> indicesForEachSquare;
    for (uint square = 0; square < 64; square++)
        {
            bitboard magicNumber = dist (e2);
            std::vector<bitboard> occupancies = occupanciesForEachSquare[square];
            std::vector<bitboard> indices;
            while (indices.size () < occupancies.size ())
                {
                    for (uint occupancy_index = 0; occupancy_index < occupancies.size (); occupancy_index++)
                        {
                            std::cout << " square: " << std::to_string (square);
                            std::cout << " magic: " << std::to_string (magicNumber) << "\r";
                            bitboard newIndex = (occupancies[occupancy_index] * magicNumber) >> magicShift;
                            if (std::count (indices.begin (), indices.end (), newIndex) > 0)
                                {
                                    indices.clear ();
                                    magicNumber = dist (e2);
                                    break;
                                }

                            indices.push_back (newIndex);
                        }
                }
            magicNumbers[square] = magicNumber;
            std::cout << std::endl;
        }
}

void
genMagics_bishop (const uint n, std::array<bitboard, 64> &magicNumbers, std::array<bitboard, 64> &relevantoccupancy_masks, std::array<std::vector<bitboard>, 64> &occupanciesForEachSquare)
{
    std::random_device rd;
    std::mt19937_64 e2 (rd ());
    std::uniform_int_distribution<bitboard> dist (std::llround (std::pow (2, 0)), std::llround (std::pow (2, 62)));
    occupanciesForEachSquare = getOccupanciesForEachSquare_bishop (relevantoccupancy_masks);
    uint magicShift = 64 - n;
    std::array<std::vector<bitboard>, 64> indicesForEachSquare;
    for (uint square = 0; square < 64; square++)
        {
            bitboard magicNumber = dist (e2);
            std::vector<bitboard> occupancies = occupanciesForEachSquare[square];
            std::vector<bitboard> indices;
            while (indices.size () < occupancies.size ())
                {
                    for (uint occupancy_index = 0; occupancy_index < occupancies.size (); occupancy_index++)
                        {
                            std::cout << " square: " << std::to_string (square);
                            std::cout << " magic: " << std::to_string (magicNumber) << "\r";
                            bitboard newIndex = (occupancies[occupancy_index] * magicNumber) >> magicShift;
                            if (std::count (indices.begin (), indices.end (), newIndex) > 0)
                                {
                                    indices.clear ();
                                    magicNumber = dist (e2);
                                    break;
                                }

                            indices.push_back (newIndex);
                        }
                }
            magicNumbers[square] = magicNumber;
            std::cout << std::endl;
        }
}

void
PrintMagics_rook (std::fstream &target, const std::array<bitboard, 64> &magics, const std::array<bitboard, 64> &relevantoccupancy_masks, const std::array<std::vector<bitboard>, 64> &occupanciesForEachSquare, const uint width)
{
    uint size = std::pow (2, width);
    target << "const uint width_rook=" << std::to_string (width) << ";" << std::endl;
    target << "const std::array<chess::consts::bitboard,64> magics_rook = {";
    std::string dataString = "";
    for (const bitboard b : magics)
        {
            dataString += std::to_string (b) + ",";
        }
    dataString = dataString.substr (0, dataString.length () - 1);
    target << dataString << "};" << std::endl;

    target << "const std::array<chess::consts::bitboard,64> relevantoccupancy_masks_rook = {";
    dataString = "";
    for (const bitboard b : relevantoccupancy_masks)
        {
            dataString += std::to_string (b) + ",";
        }
    dataString = dataString.substr (0, dataString.length () - 1);
    target << dataString << "};" << std::endl;

    target << "const std::array<std::vector<chess::consts::bitboard>,64> occupanciesForEachSquare_rook = {std::vector<chess::consts::bitboard>{";
    dataString = "";
    for (const std::vector<bitboard> &vb : occupanciesForEachSquare)
        {
            for (const bitboard b : vb)
                {
                    dataString += std::to_string (b) + ",";
                }
            dataString = dataString.substr (0, dataString.length () - 1);
            dataString += "},std::vector<chess::consts::bitboard>{";
        }
    dataString = dataString.substr (0, dataString.length () - 38);
    target << dataString << "};" << std::endl;

    target << "std::array<std::array<chess::consts::bitboard," << std::to_string (size) << ">,64> rookMoves;" << std::endl;
}

void
PrintMagics_bishop (std::fstream &target, const std::array<bitboard, 64> &magics, const std::array<bitboard, 64> &relevantoccupancy_masks, const std::array<std::vector<bitboard>, 64> &occupanciesForEachSquare, const uint width)
{
    uint size = std::pow (2, width);
    target << "const uint width_bishop=" << std::to_string (width) << ";" << std::endl;
    target << "const std::array<chess::consts::bitboard,64> magics_bishop = {";
    std::string dataString = "";
    for (const bitboard b : magics)
        {
            dataString += std::to_string (b) + ",";
        }
    dataString = dataString.substr (0, dataString.length () - 1);
    target << dataString << "};" << std::endl;

    target << "const std::array<chess::consts::bitboard,64> relevantoccupancy_masks_bishop = {";
    dataString = "";
    for (const bitboard b : relevantoccupancy_masks)
        {
            dataString += std::to_string (b) + ",";
        }
    dataString = dataString.substr (0, dataString.length () - 1);
    target << dataString << "};" << std::endl;

    target << "const std::array<std::vector<chess::consts::bitboard>,64> occupanciesForEachSquare_bishop = {std::vector<chess::consts::bitboard>{";
    dataString = "";
    for (const std::vector<bitboard> &vb : occupanciesForEachSquare)
        {
            for (const bitboard b : vb)
                {
                    dataString += std::to_string (b) + ",";
                }
            dataString = dataString.substr (0, dataString.length () - 1);
            dataString += "},std::vector<chess::consts::bitboard>{";
        }
    dataString = dataString.substr (0, dataString.length () - 38);
    target << dataString << "};" << std::endl;

    target << "std::array<std::array<chess::consts::bitboard," << std::to_string (size) << ">,64> bishopMoves;" << std::endl;
}

int
main ()
{
    uint width_rook = 14;
    std::array<bitboard, 64> magics_rook, relevantoccupancy_masks_rook;
    std::array<std::vector<bitboard>, 64> occupanciesForEachSquare_rook;
    genMagics_rook (width_rook, magics_rook, relevantoccupancy_masks_rook, occupanciesForEachSquare_rook);

    uint width_bishop = 11;
    std::array<bitboard, 64> magics_bishop, relevantoccupancy_masks_bishop;
    std::array<std::vector<bitboard>, 64> occupanciesForEachSquare_bishop;
    genMagics_bishop (width_bishop, magics_bishop, relevantoccupancy_masks_bishop, occupanciesForEachSquare_bishop);

    std::fstream target ("magicData.hpp", std::ios::out);
    PrintHeader (target);
    PrintMagics_rook (target, magics_rook, relevantoccupancy_masks_rook, occupanciesForEachSquare_rook, width_rook);
    PrintMagics_bishop (target, magics_bishop, relevantoccupancy_masks_bishop, occupanciesForEachSquare_bishop, width_bishop);
    PrintCloser (target);
    return 0;
}
