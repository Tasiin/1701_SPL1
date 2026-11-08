
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


char GetPieceSymbol(Piece piece)
{
    if (piece.type == EMPTY)
        return '.';

    char symbol;

    if (piece.type == PAWN)
        symbol = 'P';
    else if (piece.type == KNIGHT)
        symbol = 'N';
    else if (piece.type == BISHOP)
        symbol = 'B';
    else if (piece.type == ROOK)
        symbol = 'R';
    else if (piece.type == QUEEN)
        symbol = 'Q';
    else
        symbol = 'K';

    // Lowercase letters represent Black pieces
    if (piece.color == BLACK)
    {
        symbol = symbol + 32;
    }

    return symbol;
}

void PrintBoard()
{
    cout << "\n   a b c d e f g h\n";

    // Start from row 7 and go down to row 0
    for (int row = 7; row >= 0; row--)
    {
        cout << row + 1 << "  ";

        for (int col = 0; col < 8; col++)
        {
            cout << GetPieceSymbol(board[row][col]) << " ";
        }

        cout << " " << row + 1 << endl;
    }

    cout << "\n   a b c d e f g h\n";
}

void MovePiece(int startRow, int startCol, int endRow, int endCol)
{
    // Check whether coordinates are within the board
    if (startRow < 0 || startRow > 7 ||
        startCol < 0 || startCol > 7 ||
        endRow < 0 || endRow > 7 ||
        endCol < 0 || endCol > 7)
    {
        cout << "Invalid position!" << endl;
        return;
    }

    // Check whether the starting square is empty
    if (board[startRow][startCol].type == EMPTY)
    {
        cout << "There is no piece at the starting position!" << endl;
        return;
    }

    // Copy the piece
    Piece movingPiece = board[startRow][startCol];

    // Move it to the destination
    board[endRow][endCol] = movingPiece;

    // Empty the original square
    board[startRow][startCol].type = EMPTY;
    board[startRow][startCol].color = EMPTY;

    cout << "Piece moved successfully!" << endl;
}

int main()
{
    InitializeBoard();

    PrintBoard();

    int startRow, startCol;
    int endRow, endCol;

    cout << "\nEnter starting position (row column): ";
    cin >> startRow >> startCol;

    cout << "Enter destination (row column): ";
    cin >> endRow >> endCol;

    MovePiece(startRow, startCol, endRow, endCol);

    PrintBoard();

    return 0;
}
