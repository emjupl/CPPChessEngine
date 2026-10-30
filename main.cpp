#include <iostream>
#include <cstdint>

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

uint64_t blackPawns = 0xFF000000000000;



uint64_t GenerateBitMaskForField(char col, int row){

    uint64_t selectedRow = row-1;
    uint64_t selectedCol = col;

    switch(col){
        case 'a':
        case 'A':
            selectedCol = 0;
            break;
        case 'b':
        case 'B':
            selectedCol = 1;
            break;
        case 'c':
        case 'C':
            selectedCol = 2;
            break;
        case 'd':
        case 'D':
            selectedCol = 3;
            break;
        case 'e':
        case 'E':
            selectedCol = 4;
            break;
        case 'f':
        case 'F':
            selectedCol = 5;
            break;
        case 'g':
        case 'G':
            selectedCol = 6;
            break;
        case 'h':
        case 'H':
            selectedCol = 7;
            break;
    }

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

int main(){
    cout << GenerateBitMaskForField('g', 7) << endl;
    cout << IsFieldOccupiedBy(whitePawns, GenerateBitMaskForField('b', 1)) << endl;
    cout << IsFieldOccupiedBy(whiteBishops, GenerateBitMaskForField('c', 1)) << endl;

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
        } else {
            cout << "[ ]";
        }
        if(i%8==7){
            cout << endl;
        }
    }
    return 0;
}