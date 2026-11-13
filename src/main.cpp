#include <iostream>

#include "types.h"
#include "vector_operations.h"
#include "chessboard_operations.h"
#include "captures.h"
#include "whitepawns.h"
#include "knights.h"
#include "blackpawns.h"

int main(){
    Board board;
    DisplayChessboard(board);

    std::cout << "All legal moves for black pawns:" << std::endl;
    
    std::vector<Move> blackPawnsLegalMoves = CalculateMovesForBlackPawns(board.blackPawns, board);
    DisplayMovesVector(blackPawnsLegalMoves);
    return 0;
}