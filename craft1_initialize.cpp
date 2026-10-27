
#include <iostream>
using namespace std;

// Piece types
const int EMPTY = 0;
const int PAWN = 1;
const int KNIGHT = 2;
const int BISHOP = 3;
const int ROOK = 4;
const int QUEEN = 5;
const int KING = 6;

// Piece colors
const int WHITE = 1;
const int BLACK = 2;

struct Piece
{
    int type;
    int color;
};

Piece board[8][8];

int main()
{
    cout << "ChessCraft started!" << endl;

    return 0;
}

void InitializeBoard()
{
    // 1: Make all 64 squares empty
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            board[row][col].type = EMPTY;
            board[row][col].color = EMPTY;
        }
    }

    // 2: Place White's back-row pieces 
    board[0][0] = {ROOK, WHITE};
    board[0][1] = {KNIGHT, WHITE};
    board[0][2] = {BISHOP, WHITE};
    board[0][3] = {QUEEN, WHITE};
    board[0][4] = {KING, WHITE};
    board[0][5] = {BISHOP, WHITE};
    board[0][6] = {KNIGHT, WHITE};
    board[0][7] = {ROOK, WHITE};

    // 3: Place White's pawns 
    for (int col = 0; col < 8; col++)
    {
        board[1][col] = {PAWN, WHITE};
    }

    // 4: Place Black's pawns
    for (int col = 0; col < 8; col++)
    {
        board[6][col] = {PAWN, BLACK};
    }

    // 5: Place Black's back-row pieces
    board[7][0] = {ROOK, BLACK};
    board[7][1] = {KNIGHT, BLACK};
    board[7][2] = {BISHOP, BLACK};
    board[7][3] = {QUEEN, BLACK};
    board[7][4] = {KING, BLACK};
    board[7][5] = {BISHOP, BLACK};
    board[7][6] = {KNIGHT, BLACK};
    board[7][7] = {ROOK, BLACK};
}
