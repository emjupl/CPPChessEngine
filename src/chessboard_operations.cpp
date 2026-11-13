#include <iostream>
#include <cstdint>
#include "types.h"

uint64_t TransformFieldIntoBitmap(char col, int row){
    uint64_t bitmap = bit << (col-97) << (row-1)*8;
    return bitmap;
}

std::pair<char, int> TransformBitmapIntoField(uint64_t fieldBitmap){
    int fieldIndex = __builtin_ctzll(fieldBitmap);
    return {'a' + fieldIndex%8, (fieldIndex/8)+1};
}

bool IsFieldOccupiedBy(uint64_t figuresBitmap, uint64_t fieldBitmap){
    if(fieldBitmap & figuresBitmap){
        return true;
    }
    return false; 
}

void DisplayChessboard(Board board){
    for(int row=7; row>=0; row--){
        std::cout << row+1 << " | ";
        for(int col=0; col<=7; col++){
            uint64_t fieldIndex = bit << 8*row << col;
            if(IsFieldOccupiedBy(board.whitePawns, fieldIndex)){
                std::cout << "[P]";
            } else if(IsFieldOccupiedBy(board.whiteBishops, fieldIndex)){
                std::cout << "[B]";
            }else if(IsFieldOccupiedBy(board.whiteKing, fieldIndex)){
                std::cout << "[K]";
            }else if(IsFieldOccupiedBy(board.whiteRooks, fieldIndex)){
                std::cout << "[R]";
            }else if(IsFieldOccupiedBy(board.whiteKnights, fieldIndex)){
                std::cout << "[N]";
            }else if(IsFieldOccupiedBy(board.whiteQueen, fieldIndex)){
                std::cout << "[Q]";
            }else if (IsFieldOccupiedBy(board.blackPawns, fieldIndex)){
                std::cout << "[p]";
            } else if(IsFieldOccupiedBy(board.blackBishops, fieldIndex)){
                std::cout << "[b]";
            }else if(IsFieldOccupiedBy(board.blackKing, fieldIndex)){
                std::cout << "[k]";
            }else if(IsFieldOccupiedBy(board.blackRooks, fieldIndex)){
                std::cout << "[r]";
            }else if(IsFieldOccupiedBy(board.blackKnights, fieldIndex)){
                std::cout << "[n]";
            }else if(IsFieldOccupiedBy(board.blackQueen, fieldIndex)){
                std::cout << "[q]";
            }else {
                std::cout << "[ ]";
            }
            if(col%8==7){
                std::cout << std::endl;
            }
        }
    }
    std::cout << "    ------------------------" << std::endl;
    std::cout << "     a  b  c  d  e  f  g  h " << std::endl;
}
