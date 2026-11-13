#pragma once
#include "types.h"
#include <vector>

std::vector<Move> CalculateMovesForWhitePawns(uint64_t pawnsBitmap, Board board);
std::vector<Move> CalculateAttackedFieldsForWhitePawns(Board board);