
#include <iostream>
using namespace std;

// Pieces
const int EMPTY = 0;
const int PAWN = 1;
const int KNIGHT = 2;
const int BISHOP = 3;
const int ROOK = 4;
const int QUEEN = 5;
const int KING = 6;

const int WHITE = 1;
const int BLACK = 2;
int currentTurn = WHITE;

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

bool IsValidPawnMove(Piece pawn, int startRow, int startCol,
                     int endRow, int endCol)
{
    int direction;
    int startingRow;

    // Determine movement direction
    if (pawn.color == WHITE)
    {
        direction = 1;
        startingRow = 1;
    }
    else
    {
        direction = -1;
        startingRow = 6;
    }

    // Rule 1: Move forward by one square
    if (endCol == startCol &&
        endRow == startRow + direction &&
        board[endRow][endCol].type == EMPTY)
    {
        return true;
    }

    // Rule 2: Move forward by two squares on first move
    if (endCol == startCol &&
        startRow == startingRow &&
        endRow == startRow + (2 * direction) &&
        board[startRow + direction][startCol].type == EMPTY &&
        board[endRow][endCol].type == EMPTY)
    {
        return true;
    }

    // Rule 3: Capture diagonally
    if ((endCol == startCol + 1 || endCol == startCol - 1) &&
        endRow == startRow + direction &&
        board[endRow][endCol].type != EMPTY &&
        board[endRow][endCol].color != pawn.color)
    {
        return true;
    }

    return false;
}


bool IsValidKnightMove(int startRow, int startCol,
                       int endRow, int endCol)
{
    int rowDifference = endRow - startRow;
    int colDifference = endCol - startCol;

    // Knight moves 2 in one direction and 1 in another
    if ((rowDifference == 2 || rowDifference == -2) &&
        (colDifference == 1 || colDifference == -1))
    {
        return true;
    }

    if ((colDifference == 2 || colDifference == -2) &&
        (rowDifference == 1 || rowDifference == -1))
    {
        return true;
    }

    return false;
}


bool IsValidRookMove(int startRow, int startCol,
                     int endRow, int endCol)
{
    // Rook must move horizontally or vertically
    if (startRow != endRow && startCol != endCol)
    {
        return false;
    }

    // Cannot stay in the same square
    if (startRow == endRow && startCol == endCol)
    {
        return false;
    }

    int rowStep = 0;
    int colStep = 0;

    if (endRow > startRow)
        rowStep = 1;
    else if (endRow < startRow)
        rowStep = -1;

    if (endCol > startCol)
        colStep = 1;
    else if (endCol < startCol)
        colStep = -1;

    int row = startRow + rowStep;
    int col = startCol + colStep;

    // Check whether another piece blocks the path
    while (row != endRow || col != endCol)
    {
        if (board[row][col].type != EMPTY)
        {
            return false;
        }

        row += rowStep;
        col += colStep;
    }

    return true;
}

bool IsValidBishopMove(int startRow, int startCol,
                       int endRow, int endCol)
{
    int rowDifference = endRow - startRow;
    int colDifference = endCol - startCol;

    // Bishop must move diagonally
    if (rowDifference != colDifference &&
        rowDifference != -colDifference)
    {
        return false;
    }

    // alada square
    if (rowDifference == 0)
    {
        return false;
    }

    int rowStep;
    int colStep;

    if (rowDifference > 0)
        rowStep = 1;
    else
        rowStep = -1;

    if (colDifference > 0)
        colStep = 1;
    else
        colStep = -1;

    int row = startRow + rowStep;
    int col = startCol + colStep;

    // Check whether another piece blocks the path
    while (row != endRow)
    {
        if (board[row][col].type != EMPTY)
        {
            return false;
        }

        row += rowStep;
        col += colStep;
    }

    return true;
}

bool IsValidQueenMove(int startRow, int startCol,
                      int endRow, int endCol)
{
    if (IsValidRookMove(startRow, startCol, endRow, endCol) ||
        IsValidBishopMove(startRow, startCol, endRow, endCol))
    {
        return true;
    }

    return false;
}

bool IsValidKingMove(int startRow, int startCol,
                     int endRow, int endCol)
{
    int rowDifference = endRow - startRow;
    int colDifference = endCol - startCol;

    // King can move only one square in any direction
    if (rowDifference >= -1 && rowDifference <= 1 &&
        colDifference >= -1 && colDifference <= 1)
    {
        // Cannot stay in the same square
        if (rowDifference == 0 && colDifference == 0)
            return false;

        return true;
    }

    return false;
}



void MovePiece(int startRow, int startCol, int endRow, int endCol)
{
    // Check board boundaries
    if (startRow < 0 || startRow > 7 ||
        startCol < 0 || startCol > 7 ||
        endRow < 0 || endRow > 7 ||
        endCol < 0 || endCol > 7)
    {
        cout << "Invalid position!" << endl;
        return;
    }

    // Check starting square
    if (board[startRow][startCol].type == EMPTY)
    {
        cout << "No piece at starting position!" << endl;
        return;
    }

    Piece movingPiece = board[startRow][startCol];
    // Check whose turn it is
if (movingPiece.color != currentTurn)
{
    cout << "It's not your turn!" << endl;
    return;
}
    // Cannot capture your own piece
    if (board[endRow][endCol].color == movingPiece.color &&
        board[endRow][endCol].type != EMPTY)
    {
        cout << "You cannot capture your own piece!" << endl;
        return;
    }

// Check pawn movement rules
if (movingPiece.type == PAWN)
{
    if (!IsValidPawnMove(movingPiece, startRow, startCol,
                         endRow, endCol))
    {
        cout << "Invalid pawn move!" << endl;
        return;
    }
}

// Check knight movement rules
else if (movingPiece.type == KNIGHT)
{
    if (!IsValidKnightMove(startRow, startCol,
                           endRow, endCol))
    {
        cout << "Invalid knight move!" << endl;
        return;
    }
}


else if (movingPiece.type == ROOK)
{
    if (!IsValidRookMove(startRow, startCol,
                         endRow, endCol))
    {
        cout << "Invalid rook move!" << endl;
        return;
    }
}

else if (movingPiece.type == BISHOP)
{
    if (!IsValidBishopMove(startRow, startCol,
                           endRow, endCol))
    {
        cout << "Invalid bishop move!" << endl;
        return;
    }
}

else if (movingPiece.type == QUEEN)
{
    if (!IsValidQueenMove(startRow, startCol,
                          endRow, endCol))
    {
        cout << "Invalid queen move!" << endl;
        return;
    }
}

else if (movingPiece.type == KING)
{
    if (!IsValidKingMove(startRow, startCol,
                         endRow, endCol))
    {
        cout << "Invalid king move!" << endl;
        return;
    }
}

    // Move the piece
    board[endRow][endCol] = movingPiece;

    board[startRow][startCol].type = EMPTY;
    board[startRow][startCol].color = EMPTY;

    cout << "Piece moved successfully!" << endl;
    // Switch turns
if (currentTurn == WHITE)
{
    currentTurn = BLACK;
}
else
{
    currentTurn = WHITE;
}

// Display next player's turn
if (currentTurn == WHITE)
    cout << "White's turn!" << endl;
else
    cout << "Black's turn!" << endl;
}



int main()
{
    InitializeBoard();

    while (true)
    {
        PrintBoard();

        if (currentTurn == WHITE)
            cout << "\nWhite's turn!" << endl;
        else
            cout << "\nBlack's turn!" << endl;

        int startRow, startCol;
        int endRow, endCol;

        cout << "Enter starting position (row column): ";
        cin >> startRow >> startCol;

        // Enter -1 to quit
        if (startRow == -1)
            break;

        cout << "Enter destination (row column): ";
        cin >> endRow >> endCol;

        MovePiece(startRow, startCol, endRow, endCol);
    }

    cout << "Game ended!" << endl;

    return 0;
}
