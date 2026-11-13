#pragma once
#include <vector>
#include "types.h"

std::vector<Move> CalculateCaptures(std::vector<Move> attackedFields, uint64_t oppositeFigures);