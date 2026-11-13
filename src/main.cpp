#include <iostream>

#include "types.h"
#include "vector_operations.h"
#include "chessboard_operations.h"
#include "captures.h"
#include "whitepawns.h"
#include "knights.h"

// vector<Move> CalculateMovesForKing(uint64_t bitmap){
//     // Trzeba rozjebać tą funkcje na liczenie atakowanych pol przez króla i zrobic druga zwracajaca mozliwe ruchy
//     // UWAGA! W przyszlosci trzeba dodac rowniez sprawdzanie czy dane pole jest pod atakiem innej figury!
//     uint64_t kingMoves = bitmap << 8 | bitmap >> 8;
//     if(bitmap & fileA){
//         kingMoves = kingMoves | bitmap << 9 | bitmap << 1 | bitmap >> 7;
//     }else if(bitmap & fileH){
//         kingMoves = kingMoves | bitmap << 7 | bitmap >> 1 | bitmap >> 9;
//     } else {
//         kingMoves = kingMoves | bitmap << 1 | bitmap << 7 | bitmap << 8 | bitmap << 9 | bitmap >> 1 | bitmap >> 7 | bitmap >> 8 | bitmap >> 9;
//     }

//     uint64_t kingLegalMoves = kingMoves & ~(whiteFigures | blackFigures);
//     vector<Move> legalMoves;
//     while(kingLegalMoves){
//         uint64_t firstKingLegalMoveIndex = __builtin_ctzll(kingLegalMoves);
//         uint64_t firstKingLegalMoveBitmap = bit << firstKingLegalMoveIndex;
//         kingLegalMoves = kingLegalMoves & ~firstKingLegalMoveBitmap;

//         PushMoveToVector(bitmap, firstKingLegalMoveBitmap, legalMoves);
//     }
//     return legalMoves;
// }


int main(){
    Board board;
    DisplayChessboard(board);

    std::cout << "All legal moves for white knights:" << std::endl;
    std::vector<Move> knightsLegalMoves = CalculateMovesForKnights(board.whiteKnights, board);
    DisplayMovesVector(knightsLegalMoves);
    
    auto field = TransformBitmapIntoField(board.blackQueen);
    
    std::cout << field.first << field.second;
    return 0;
}