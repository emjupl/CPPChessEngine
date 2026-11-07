#include <iostream>
#include <cstdint>
#include <vector>

using namespace std;

const uint64_t bit = 1;
const uint64_t fileA = 0x0101010101010101;
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

vector<Move> CalculateMovesForKing(uint64_t bitmap){
    // Trzeba rozjebać tą funkcje na liczenie atakowanych pol przez króla i zrobic druga zwracajaca mozliwe ruchy
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

        PushMoveToVector(bitmap, firstKingLegalMoveBitmap, legalMoves);
    }
    return legalMoves;
}

// Liczenie ruchow dla bialych pionkow

vector<Move> CalculateMovesForWhitePawns(uint64_t bitmap){
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


// OBLICZANIE ATAKOWANYCH POL

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

// Liczenie ktore pola atakowane przez figury sa zajete przez przeciwne figury

vector<Move> CalculateCaptures(vector<Move> attackedFields, uint64_t oppositeFigures){
    vector<Move> capturesFields;
    for (int i = 0; i < attackedFields.size(); i++) {
        if(attackedFields[i].toField & oppositeFigures){
            PushMoveToVector(attackedFields[i].fromField, attackedFields[i].toField, capturesFields);
        }
    }
    return capturesFields;
}


// Wyswietlanie szachownicy 
// Biale figury to duze litery
// Czarne figury to male litery
void DisplayChessboard(){
        for(int i=0; i<64; i++){
        uint64_t fieldIndex = bit << i;
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

        if(i%8==7){
            cout << endl;
        }
    }
}

int main(){
    DisplayChessboard();
    
    cout << "All legal moves for white pawns: " << endl;
    vector<Move> pawnsLegalMoves = CalculateMovesForWhitePawns(whitePawns);
    DisplayMovesVector(pawnsLegalMoves);

    cout << "All attacked fields for white pawns: " << endl;
    vector<Move> pawnsAttackingMoves = CalculateAttackedFieldsForWhitePawns(whitePawns);
    DisplayMovesVector(pawnsAttackingMoves);

    cout << "All captures for white pawns: " << endl;
    vector<Move> pawnsCapturingMoves = CalculateCaptures(pawnsAttackingMoves, blackFigures);
    DisplayMovesVector(pawnsCapturingMoves);

    cout << "All legal moves for white king: " << endl;
    vector<Move> kingLegalMoves = CalculateMovesForKing(whiteKing);
    DisplayMovesVector(kingLegalMoves);
    
    return 0;
}