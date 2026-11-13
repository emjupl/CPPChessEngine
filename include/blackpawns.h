#pragma once
#include "types.h"
#include <vector>

std::vector<Move> CalculateMovesForBlackPawns(uint64_t pawnsBitmap, Board board);
std::vector<Move> CalculateAttackedFieldsForBlackPawns(Board board);