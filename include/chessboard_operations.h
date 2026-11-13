#pragma once
#include <cstdint>
#include <utility>

uint64_t TransformFieldIntoBitmap(char col, int row);
std::pair<char, int> TransformBitmapIntoField(uint64_t fieldBitmap);
bool IsFieldOccupiedBy(uint64_t figuresBitmap, uint64_t fieldBitmap);
void DisplayChessboard(Board board);