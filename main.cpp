#include <iostream>
#include <cstdint>
#include <vector>

using namespace std;

uint64_t bit = 1;
uint64_t whitePawns = 0xFF00;
uint64_t whiteBishops = 0x24;
uint64_t whiteQueen = 0x8;
uint64_t whiteKing = 0x10;
uint64_t whiteRookQueenSide = 0x1;
uint64_t whiteRookKingSide = 0x80;
uint64_t whiteKnightQueenSide = 0x2;
uint64_t whiteKnightKingSide = 0x40;

uint64_t whiteFigures = whitePawns | whiteBishops | whiteQueen | whiteKing | whiteRookQueenSide | whiteRookKingSide | whiteKnightQueenSide | whiteKnightKingSide;

uint64_t blackPawns = 0x00FF000000000000;
uint64_t blackBishops = 0x2400000000000000;
uint64_t blackQueen = 0x0800000000000000;
uint64_t blackKing = 0x1000000000000000;
uint64_t blackRookQueenSide = 0x0100000000000000;
uint64_t blackRookKingSide = 0x8000000000000000;
uint64_t blackKnightQueenSide = 0x0200000000000000;
uint64_t blackKnightKingSide = 0x4000000000000000;

uint64_t blackFigures = blackPawns | blackBishops | blackQueen | blackKing | blackRookQueenSide | blackRookKingSide | blackKnightQueenSide | blackKnightKingSide;

struct Move {
    uint64_t fromField;
    uint64_t toField;
};

uint64_t GenerateBitMaskForField(char col, int row){

    uint64_t selectedRow = row-1;
    uint64_t selectedCol = col;

    selectedCol = col-97;

    uint64_t bit = 1;
    uint64_t bitMask = bit <<selectedCol << selectedRow*8;

    return bitMask;
}

bool IsFieldOccupiedBy(uint64_t figuresBitmask, uint64_t fieldBitmask){
    if(fieldBitmask & figuresBitmask){
        return true;
    }
    return false; 
}

vector<Move> CalculateSingleMoveForWhitePawns(uint64_t bitmap){
    uint64_t row2 = 0xFF00;
    uint64_t row7 = 0xFF000000000000;
    uint64_t pawnsBitmap = bitmap;
    vector<Move> legalMoves;

    while (pawnsBitmap){
        uint64_t firstPawnIndex = __builtin_ctzll(pawnsBitmap);
        uint64_t firstPawnBitmap = bit << firstPawnIndex; // bitmapa wskazujaca na pierwszego pionka (najpierw sprawdza rzedy od A do H, a potem od lewej do prawej)
        
        // musze odjac od whitePawns bitmape firstPawnIndex i bede miec bitmape kolejnych pionkow do sprawdzenia
        uint64_t singlePawnMove = firstPawnBitmap << 8;
        pawnsBitmap &= ~firstPawnBitmap;

        if (IsFieldOccupiedBy(whiteFigures | blackFigures, singlePawnMove) == 0)
        {
            Move pawnMove;
            pawnMove.fromField = firstPawnBitmap;
            pawnMove.toField = singlePawnMove;

            legalMoves.push_back(pawnMove);
        }
    }
    return legalMoves;
}

void displayChessboard(){
        for(int i=0; i<64; i++){
        uint64_t fieldIndex = bit << i;
        if(IsFieldOccupiedBy(whitePawns, fieldIndex)){
            cout << "[P]";
        } else if(IsFieldOccupiedBy(whiteBishops, fieldIndex)){
            cout << "[B]";
        }else if(IsFieldOccupiedBy(whiteKing, fieldIndex)){
            cout << "[K]";
        }else if(IsFieldOccupiedBy(whiteRookQueenSide, fieldIndex)){
            cout << "[R]";
        }else if(IsFieldOccupiedBy(whiteRookKingSide, fieldIndex)){
            cout << "[R]";
        }else if(IsFieldOccupiedBy(whiteKnightQueenSide, fieldIndex)){
            cout << "[N]";
        }else if(IsFieldOccupiedBy(whiteKnightKingSide, fieldIndex)){
            cout << "[N]";
        }else if(IsFieldOccupiedBy(whiteQueen, fieldIndex)){
            cout << "[Q]";
        }else if (IsFieldOccupiedBy(blackPawns, fieldIndex)){
            cout << "[p]";
        } else if(IsFieldOccupiedBy(blackBishops, fieldIndex)){
            cout << "[b]";
        }else if(IsFieldOccupiedBy(blackKing, fieldIndex)){
            cout << "[k]";
        }else if(IsFieldOccupiedBy(blackRookQueenSide, fieldIndex)){
            cout << "[r]";
        }else if(IsFieldOccupiedBy(blackRookKingSide, fieldIndex)){
            cout << "[r]";
        }else if(IsFieldOccupiedBy(blackKnightQueenSide, fieldIndex)){
            cout << "[n]";
        }else if(IsFieldOccupiedBy(blackKnightKingSide, fieldIndex)){
            cout << "[n]";
        }else if(IsFieldOccupiedBy(blackQueen, fieldIndex)){
            cout << "[q]";
        }
        
        else {
            cout << "[ ]";
        }
        if(i%8==7){
            cout << endl;
        }
    }
}

int main(){
    displayChessboard();
    return 0;
}