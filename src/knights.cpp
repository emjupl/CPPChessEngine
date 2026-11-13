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
        std::vector<uint64_t>  attackedFields;
        attackedFields.push_back((firstKnightBitmap << 6) & ~(fileG | fileH)); //knightMoveLeftUp
        attackedFields.push_back((firstKnightBitmap >> 10) & ~(fileG | fileH)); //knighMoveLeftDown
        attackedFields.push_back((firstKnightBitmap << 15) & ~fileH); //knightMoveUpLeft 
        attackedFields.push_back((firstKnightBitmap << 17)& ~fileA); //knightMoveUpRight
        attackedFields.push_back((firstKnightBitmap << 10) & ~(fileA | fileB)); //knightMoveRightUp
        attackedFields.push_back((firstKnightBitmap >> 6)  & ~(fileA | fileB)); //knightMoveRightDown
        attackedFields.push_back((firstKnightBitmap >> 17) & ~fileH); //knightMoveDownLeft
        attackedFields.push_back((firstKnightBitmap >> 15)  & ~fileA); //knightMoveDownRight
        for(size_t i = 0; i<attackedFields.size(); i++){
            if(!(attackedFields[i] & friendlyFigures)){
                if(attackedFields[i]){
                    PushMoveToVector(firstKnightBitmap, attackedFields[i], legalMoves);
                }
            }
        }
    }
    return legalMoves;
}
