#include <iostream>
#include <cstdint>
#include <vector>

using namespace std;

uint64_t bit = 1;

uint64_t fileA = 0x0101010101010101;
uint64_t fileH = 0x8080808080808080;

uint64_t whitePawns = 0xFF00;
uint64_t whiteBishops = 0x24;
uint64_t whiteQueen = 0x8;
uint64_t whiteKing = 0x10;
uint64_t whiteRookQueenSide = 0x1;
uint64_t whiteRookKingSide = 0x80;
uint64_t whiteKnightQueenSide = 0x2;
uint64_t whiteKnightKingSide = 0x40;

uint64_t customWhiteFigure = 0x10000;

uint64_t whiteFigures = customWhiteFigure | whitePawns | whiteBishops | whiteQueen | whiteKing | whiteRookQueenSide | whiteRookKingSide | whiteKnightQueenSide | whiteKnightKingSide;

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

void DisplayMovesStruct(vector<Move> movesVector){
    for (int i = 0; i < movesVector.size(); i++) {
        cout << movesVector[i].fromField << "<- From | To ->" << movesVector[i].toField << '\n';
    }
}

uint64_t GenerateBitMaskForField(char col, int row){
    uint64_t bitMask = bit << col-97 << (row-1)*8;
    return bitMask;
}

bool IsFieldOccupiedBy(uint64_t figuresBitmask, uint64_t fieldBitmask){
    if(fieldBitmask & figuresBitmask){
        return true;
    }
    return false; 
}

vector<Move> CalculateMoveForKing(uint64_t bitmap){
    // UWAGA! W przyszlosci trzeba dodac rowniez sprawdzanie czy dane pole jest pod atakiem innej figury!
    uint64_t kingMoves = bitmap << 8 | bitmap >> 8;
    if(bitmap & fileA){
        kingMoves = kingMoves | bitmap << 9 | bitmap << 1 | bitmap >> 7;
    }else if(bitmap & fileH){
        kingMoves = kingMoves | bitmap << 7 | bitmap >> 1 | bitmap >> 9;
    } else {
        kingMoves = kingMoves | bitmap << 1 | bitmap << 7 | bitmap << 8 | bitmap << 9 | bitmap >> 1 | bitmap >> 7 | bitmap >> 8 | bitmap >> 9;
    }

    uint64_t kingLegalMoves = kingMoves & ~(whiteFigures | blackFigures);
    vector<Move> legalMoves;
    while(kingLegalMoves){
        uint64_t firstKingLegalMoveIndex = __builtin_ctzll(kingLegalMoves);
        uint64_t firstKingLegalMoveBitmap = bit << firstKingLegalMoveIndex;
        kingLegalMoves = kingLegalMoves & ~firstKingLegalMoveBitmap;

        Move kingMove;
        kingMove.fromField = bitmap;
        kingMove.toField = firstKingLegalMoveBitmap;
        legalMoves.push_back(kingMove);
    }
    return legalMoves;
}

vector<Move> CalculateSingleMoveForWhitePawns(uint64_t bitmap){
    uint64_t row2 = 0xFF00;
    uint64_t row7 = 0xFF000000000000;
    uint64_t remainedPawnsBitmap = bitmap;
    vector<Move> legalMoves;

    while (remainedPawnsBitmap){
        uint64_t firstPawnIndex = __builtin_ctzll(remainedPawnsBitmap);
        uint64_t firstPawnBitmap = bit << firstPawnIndex; // bitmapa wskazujaca na pierwszego pionka (najpierw sprawdza rzedy od A do H, a potem od lewej do prawej)
        // musze odjac od whitePawns bitmape firstPawnIndex i bede miec bitmape kolejnych pionkow do sprawdzenia
        uint64_t singlePawnMove = firstPawnBitmap << 8;
        remainedPawnsBitmap &= ~firstPawnBitmap;
        if (!IsFieldOccupiedBy(whiteFigures | blackFigures, singlePawnMove))
        {
            Move pawnMove;
            pawnMove.fromField = firstPawnBitmap;
            pawnMove.toField = singlePawnMove;
            legalMoves.push_back(pawnMove);
            uint64_t doublePawnMove = singlePawnMove<<8;
            if(firstPawnBitmap & row2){
                if (!IsFieldOccupiedBy(whiteFigures | blackFigures, doublePawnMove)){
                Move pawnMove;
                pawnMove.fromField = firstPawnBitmap;
                pawnMove.toField = doublePawnMove;
                legalMoves.push_back(pawnMove);
                }
            }
        }
    }
    return legalMoves;
}

void DisplayChessboard(){
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
        }else {
            cout << "[ ]";
        }

        if(i%8==7){
            cout << endl;
        }
    }
}

int main(){
    DisplayChessboard();
    
    cout << "All legal moves for white pawns: " << endl;
    vector<Move> pawnsLegalMoves = CalculateSingleMoveForWhitePawns(whitePawns);
    DisplayMovesStruct(pawnsLegalMoves);

    cout << "All legal moves for white king: " << endl;
    vector<Move> kingLegalMoves = CalculateMoveForKing(whiteKing);
    DisplayMovesStruct(kingLegalMoves);
    
    return 0;
}