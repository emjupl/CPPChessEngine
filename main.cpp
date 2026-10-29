#include <iostream>
#include <cstdint>

using namespace std;

uint64_t whitePawns = 0xFF00;


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

bool IsFieldOccupied(uint64_t fieldBitmask, uint64_t figureBitmask){
    bool IsFieldOccupied = fieldBitmask & figureBitmask;
    if(IsFieldOccupied){
        return true;
    }
    return false;
}

int main(){

    cout << GenerateBitMaskForField('a', 2) << endl;
    cout << IsFieldOccupied(GenerateBitMaskForField('a', 2), whitePawns) << endl;

    return 0;
}