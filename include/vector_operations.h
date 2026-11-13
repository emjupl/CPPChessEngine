#pragma once
#include <vector>
#include "types.h"

void DisplayMovesVector(std::vector<Move> movesVector);
void PushMoveToVector(uint64_t fromField, uint64_t toField, std::vector<Move>& movesVector);