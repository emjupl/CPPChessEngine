#include <vector>
#include "types.h"
#include "chessboard_operations.h"
#include "vector_operations.h"

std::vector<Move> CalculateMovesForBlackPawns(uint64_t pawnsBitmap, Board& board){
    uint64_t row7 = 0xFF000000000000;
    std::vector<Move> legalMoves;
    while (pawnsBitmap){
        uint64_t firstPawnIndex = __builtin_ctzll(pawnsBitmap);
        uint64_t firstPawnBitmap = bit << firstPawnIndex;
        uint64_t singlePawnMove = firstPawnBitmap >> 8;
        pawnsBitmap &= ~firstPawnBitmap;
        if (!IsFieldOccupiedBy(board.whiteFigures | board.blackFigures, singlePawnMove))
        {
            PushMoveToVector(firstPawnBitmap, singlePawnMove, legalMoves);
            uint64_t doublePawnMove = singlePawnMove>>8;
            if(firstPawnBitmap & row7){
                if (!IsFieldOccupiedBy(board.whiteFigures | board.blackFigures, doublePawnMove)){
                    PushMoveToVector(firstPawnBitmap, doublePawnMove, legalMoves);
                }
            }
        }
    }
    return legalMoves;
}

// Obliczanie atakowanych pol przez biale pionki
// Nie obejmuje jeszcze bicia w przelocie
std::vector<Move> CalculateAttackedFieldsForBlackPawns(Board board){
    std::vector<Move> attackedFields;
    uint64_t pawnsBitmap = board.blackPawns;
    while(pawnsBitmap){
            uint64_t firstPawnIndex = __builtin_ctzll(pawnsBitmap);
            uint64_t firstPawnBitmap = bit << firstPawnIndex;
            pawnsBitmap &= ~firstPawnBitmap;

            uint64_t attackedFieldRight = firstPawnBitmap >> 7;
            uint64_t attackedFieldLeft = firstPawnBitmap >> 9;

        if(firstPawnBitmap & fileA){
            PushMoveToVector(firstPawnBitmap, attackedFieldRight, attackedFields);
        } else if(firstPawnBitmap & fileH){
            PushMoveToVector(firstPawnBitmap, attackedFieldLeft, attackedFields);
        } else {
            PushMoveToVector(firstPawnBitmap, attackedFieldLeft, attackedFields);
            PushMoveToVector(firstPawnBitmap, attackedFieldRight, attackedFields);
        }
    }
    return attackedFields;
}
