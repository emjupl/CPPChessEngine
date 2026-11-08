#include <iostream>
#include <cstdint>
#include <vector>

using namespace std;

// PROGRAM OBSLUGUJE:
// LICZENIE MOZLIWYCH RUCHOW DLA BIALYCH PIONKOW
// LICZENIE MOZLIWYCH BIC DLA BIALYCH PIONKOW

// LICZENIE MOZLIWYCH RUCHOW DLA SKOCZKOW


const uint64_t bit = 1;
const uint64_t fileA = 0x0101010101010101;
const uint64_t fileB = 0x0202020202020202;
const uint64_t fileG = 0x4040404040404040;
const uint64_t fileH = 0x8080808080808080;

uint64_t whitePawns = 0xFF00;
uint64_t whiteBishops = 0x24;
uint64_t whiteQueen = 0x8;
uint64_t whiteKing = 0x10;
uint64_t whiteRooks = 0x1 | 0x80;
uint64_t whiteKnights = 0x2 | 0x40 ;

uint64_t customFigure = 0x0000;

uint64_t whiteFigures = whitePawns | whiteBishops | whiteQueen | whiteKing | whiteRooks| whiteKnights;

uint64_t blackPawns = 0x00FF000000000000;
uint64_t blackBishops = 0x2400000000000000;
uint64_t blackQueen = 0x0800000000000000;
uint64_t blackKing = 0x1000000000000000;
uint64_t blackRooks = 0x0100000000000000 | 0x8000000000000000;
uint64_t blackKnights = 0x0200000000000000 | 0x4000000000000000;

uint64_t blackFigures = customFigure | blackPawns | blackBishops | blackQueen | blackKing | blackRooks | blackKnights;

struct Move {
    uint64_t fromField;
    uint64_t toField;
};

///////////////////////////////////////////////////////////////////////////////
//vectorop.h
///////////////////////////////////////////////////////////////////////////////

void DisplayMovesVector(vector<Move> movesVector){
    for (int i = 0; i < movesVector.size(); i++) {
        cout << movesVector[i].fromField << "<- From | To ->" << movesVector[i].toField << '\n';
    }
}

void PushMoveToVector(uint64_t fromField, uint64_t toField, vector<Move>& movesVector){
    Move move;
    move.fromField = fromField;
    move.toField = toField;
    movesVector.push_back(move);
}
///////////////////////////////////////////////////////////////////////////////
//chessboardops.h
///////////////////////////////////////////////////////////////////////////////
uint64_t GenerateBitmaskForField(char col, int row){
    uint64_t bitMask = bit << (col-97) << (row-1)*8;
    return bitMask;
}

bool IsFieldOccupiedBy(uint64_t figuresBitmap, uint64_t fieldBitmap){
    if(fieldBitmap & figuresBitmap){
        return true;
    }
    return false; 
}

// Wyswietlanie szachownicy 
// Biale figury to duze litery
// Czarne figury to male litery
void DisplayChessboard(){
    for(int row=7; row>=0; row--){
        for(int col=0; col<=7; col++){
            uint64_t fieldIndex = bit << 8*row << col;
            if(IsFieldOccupiedBy(whitePawns, fieldIndex)){
                cout << "[P]";
            } else if(IsFieldOccupiedBy(whiteBishops, fieldIndex)){
                cout << "[B]";
            }else if(IsFieldOccupiedBy(whiteKing, fieldIndex)){
                cout << "[K]";
            }else if(IsFieldOccupiedBy(whiteRooks, fieldIndex)){
                cout << "[R]";
            }else if(IsFieldOccupiedBy(whiteKnights, fieldIndex)){
                cout << "[N]";
            }else if(IsFieldOccupiedBy(whiteQueen, fieldIndex)){
                cout << "[Q]";
            }else if (IsFieldOccupiedBy(blackPawns, fieldIndex)){
                cout << "[p]";
            } else if(IsFieldOccupiedBy(blackBishops, fieldIndex)){
                cout << "[b]";
            }else if(IsFieldOccupiedBy(blackKing, fieldIndex)){
                cout << "[k]";
            }else if(IsFieldOccupiedBy(blackRooks, fieldIndex)){
                cout << "[r]";
            }else if(IsFieldOccupiedBy(blackKnights, fieldIndex)){
                cout << "[n]";
            }else if(IsFieldOccupiedBy(blackQueen, fieldIndex)){
                cout << "[q]";
            }else {
                cout << "[ ]";
            }

            if(col%8==7){
                cout << endl;
            }
        }
    }
}


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

///////////////////////////////////////////////////////////////////////////////
//whitepawns.h
///////////////////////////////////////////////////////////////////////////////

// Liczenie ruchow do przodu dla bialych pionkow

vector<Move> CalculateMovesForWhitePawns(uint64_t pawnsBitmap){
    uint64_t row2 = 0xFF00;
    vector<Move> legalMoves;
    while (pawnsBitmap){
        uint64_t firstPawnIndex = __builtin_ctzll(pawnsBitmap);
        uint64_t firstPawnBitmap = bit << firstPawnIndex;
        uint64_t singlePawnMove = firstPawnBitmap << 8;
        pawnsBitmap &= ~firstPawnBitmap;
        if (!IsFieldOccupiedBy(whiteFigures | blackFigures, singlePawnMove))
        {
            PushMoveToVector(firstPawnBitmap, singlePawnMove, legalMoves);
            uint64_t doublePawnMove = singlePawnMove<<8;
            if(firstPawnBitmap & row2){
                if (!IsFieldOccupiedBy(whiteFigures | blackFigures, doublePawnMove)){
                    PushMoveToVector(firstPawnBitmap, doublePawnMove, legalMoves);
                }
            }
        }
    }
    return legalMoves;
}

// Obliczanie atakowanych pol przez biale pionki
// Nie obejmuje jeszcze bicia w przelocie
vector<Move> CalculateAttackedFieldsForWhitePawns(uint64_t pawnsBitmap){
    vector<Move> attackedFields;
    while(pawnsBitmap){
            uint64_t firstPawnIndex = __builtin_ctzll(pawnsBitmap);
            uint64_t firstPawnBitmap = bit << firstPawnIndex;
            pawnsBitmap &= ~firstPawnBitmap;

            uint64_t attackedFieldLeft = firstPawnBitmap << 7;
            uint64_t attackedFieldRight = firstPawnBitmap << 9;

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

///////////////////////////////////////////////////////////////////////////////
//knights.h
///////////////////////////////////////////////////////////////////////////////

vector<Move> CalculateMovesForKnights(uint64_t knightsBitmap, uint64_t friendlyFigures){
    vector<Move> legalMoves;
    while(knightsBitmap){
       uint64_t firstKnightIndex = __builtin_ctzll(knightsBitmap);
       uint64_t firstKnightBitmap = bit << firstKnightIndex;
       knightsBitmap = knightsBitmap & ~firstKnightBitmap;

       vector<uint64_t>  movesBeforeCheckingFieldOccupancy;
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

///////////////////////////////////////////////////////////////////////////////
//captures.h
///////////////////////////////////////////////////////////////////////////////

vector<Move> CalculateCaptures(vector<Move> attackedFields, uint64_t oppositeFigures){
    vector<Move> capturesFields;
    for (size_t i = 0; i < attackedFields.size(); i++) {
        if(attackedFields[i].toField & oppositeFigures){
            PushMoveToVector(attackedFields[i].fromField, attackedFields[i].toField, capturesFields);
        }
    }
    return capturesFields;
}


int main(){
    DisplayChessboard();

    cout << "All legal moves for white knights:" << endl;
    vector<Move> knightsLegalMoves = CalculateMovesForKnights(whiteKnights, whiteFigures);
    DisplayMovesVector(knightsLegalMoves);
    
    return 0;
}