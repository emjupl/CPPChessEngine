#include <iostream>
#include "vector_operations.h"

void DisplayMovesVector(std::vector<Move> movesVector){
    for (int i = 0; i < movesVector.size(); i++) {
        std::cout << movesVector[i].fromField << "<- From | To ->" << movesVector[i].toField << '\n';
    }
}

void PushMoveToVector(uint64_t fromField, uint64_t toField, std::vector<Move>& movesVector){
    Move move;
    move.fromField = fromField;
    move.toField = toField;
    movesVector.push_back(move);
}