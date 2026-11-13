#include <cstdint>
#pragma once

const uint64_t bit = 1;
const uint64_t fileA = 0x0101010101010101;
const uint64_t fileB = 0x0202020202020202;
const uint64_t fileG = 0x4040404040404040;
const uint64_t fileH = 0x8080808080808080;

struct Board {
    uint64_t whitePawns = 0xFF00;
    uint64_t whiteBishops = 0x24;
    uint64_t whiteQueen = 0x8;
    uint64_t whiteKing = 0x10;
    uint64_t whiteRooks = 0x1 | 0x80;
    uint64_t whiteKnights = 0x2 | 0x40 ;

    uint64_t customFigure = 0x0000;

    uint64_t whiteFigures = whitePawns | whiteBishops | whiteQueen | whiteKing | whiteRooks| whiteKnights;

    uint64_t blackPawns = 0x00FF000000000000;
    uint64_t blackBishops = 0x2400000000000000;
    uint64_t blackQueen = 0x0800000000000000;
    uint64_t blackKing = 0x1000000000000000;
    uint64_t blackRooks = 0x0100000000000000 | 0x8000000000000000;
    uint64_t blackKnights = 0x0200000000000000 | 0x4000000000000000;

    uint64_t blackFigures = customFigure | blackPawns | blackBishops | blackQueen | blackKing | blackRooks | blackKnights;
};

struct Move {
    uint64_t fromField;
    uint64_t toField;
};