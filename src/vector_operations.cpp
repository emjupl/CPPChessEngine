#include <iostream>
#include <string>
#include <format>
#include "vector_operations.h"
#include "chessboard_operations.h"


void DisplayMovesVector(std::vector<Move> movesVector){
    for (int i = 0; i < movesVector.size(); i++) {
        std::string fromField = std::format("{}{}" ,TransformBitmapIntoField(movesVector[i].fromField).first, TransformBitmapIntoField(movesVector[i].fromField).second);
        std::string toField = std::format("{}{}" ,TransformBitmapIntoField(movesVector[i].toField).first, TransformBitmapIntoField(movesVector[i].toField).second);
        std::cout << fromField << "<- From | To ->" << toField << '\n';
    }
}

void PushMoveToVector(uint64_t fromField, uint64_t toField, std::vector<Move>& movesVector){
    Move move;
    move.fromField = fromField;
    move.toField = toField;
    movesVector.push_back(move);
}