#include <vector>
#include "vector_operations.h"
#include "types.h"


std::vector<Move> CalculateMovesForKnights(uint64_t knightsBitmap, Board board){    
    uint64_t friendlyFigures;
    if (knightsBitmap & board.whiteFigures){
        friendlyFigures = board.whiteFigures;
    } else {
        friendlyFigures = board.blackFigures;
    }
    std::vector<Move> legalMoves;
    while(knightsBitmap){
       uint64_t firstKnightIndex = __builtin_ctzll(knightsBitmap);
       uint64_t firstKnightBitmap = bit << firstKnightIndex;
       knightsBitmap = knightsBitmap & ~firstKnightBitmap;

       std::vector<uint64_t>  movesBeforeCheckingFieldOccupancy;
       movesBeforeCheckingFieldOccupancy.push_back(firstKnightBitmap << 6); //knightMoveLeftUp
       movesBeforeCheckingFieldOccupancy.push_back(firstKnightBitmap >> 10); //knighMoveLeftDown

       movesBeforeCheckingFieldOccupancy.push_back(firstKnightBitmap << 15); //knightMoveUpLeft 
       movesBeforeCheckingFieldOccupancy.push_back(firstKnightBitmap << 17); //knightMoveUpRight

       movesBeforeCheckingFieldOccupancy.push_back(firstKnightBitmap << 10); //knightMoveRightUp
       movesBeforeCheckingFieldOccupancy.push_back(firstKnightBitmap >> 6); //knightMoveRightDown

       movesBeforeCheckingFieldOccupancy.push_back(firstKnightBitmap >> 17); //knightMoveDownLeft
       movesBeforeCheckingFieldOccupancy.push_back(firstKnightBitmap >> 15); //knightMoveDownRight

       for(size_t i = 0; i<movesBeforeCheckingFieldOccupancy.size(); i++){
        if(firstKnightBitmap & fileA){
            movesBeforeCheckingFieldOccupancy[i] = movesBeforeCheckingFieldOccupancy[i] & ~(fileG | fileH);
        } else if(firstKnightBitmap & fileB){
            movesBeforeCheckingFieldOccupancy[i] = movesBeforeCheckingFieldOccupancy[i] & ~fileH;
        } else if(firstKnightBitmap & fileG){
            movesBeforeCheckingFieldOccupancy[i] = movesBeforeCheckingFieldOccupancy[i] & ~fileA;
        } else if(firstKnightBitmap & fileH){
            movesBeforeCheckingFieldOccupancy[i] = movesBeforeCheckingFieldOccupancy[i] & ~(fileA | fileB);
        }

        if(!(movesBeforeCheckingFieldOccupancy[i] & friendlyFigures)){
            if(movesBeforeCheckingFieldOccupancy[i]){
                PushMoveToVector(firstKnightBitmap, movesBeforeCheckingFieldOccupancy[i], legalMoves);
            }
        }
       }
    }
    return legalMoves;
}
