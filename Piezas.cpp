#include "Piezas.h"
#include <vector>
#include <algorithm>
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and 
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and 
 * specifies it is X's turn first
**/
Piezas::Piezas()
{
    //Sets first turn to X
    turn = X;
    
    //Size board according to CONST variables
    board.resize( BOARD_ROWS );
    for( auto &it : board )
    {
        it.resize( BOARD_COLS );
    }

    //Fill board with Blanks
    for( auto &it : board )
    {
        for( unsigned i = 0; i < it.size(); i++ )
        {
            it[i] = Blank;
        }
    }
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
    //Resets board to all Blank
    for( auto &it : board )
    {
        for( unsigned i = 0; i < it.size(); i++ )
        {
            it[i] = Blank;
        }
    }
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does 
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value 
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/ 
Piece Piezas::dropPiece(int column)
{
    //Default value, if Peice is inbounds and column is full
    //Temp is set to Invalid if out of bounds, or peice placed if possible
    Piece temp = Blank;
    bool dropped = false;
    unsigned i = 0;

    // Check for out of bounds
    if( column >= BOARD_COLS || column < 0 )
        temp = Invalid;

    // Not out of bounds, check for first Blank spot, fill if available
    else
    {    
        while ( i < BOARD_ROWS && !dropped )
        {
            if( board[i][column] == Blank )
            {
                board[i][column] = turn;
                temp = board[i][column];
                dropped = true;
            }
            else
                i++;
            
        }
    }    
    
    // Toogle turn
    if( turn == X )
        turn = O;
    else
        turn = X;  
    
    return temp;
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
    if( row >= BOARD_ROWS || row < 0 || column >= BOARD_COLS || column < 0)
        return Invalid;

    return board[row][column];
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's 
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
    unsigned longestX = 0;
    unsigned longestO = 0;
    unsigned count = 0;

    Piece start;
    
    //Checks if board is full, returns Invalid if not full
    for( unsigned i = 0; i < BOARD_ROWS; i++ )
    {
        for( unsigned j = 0; j < BOARD_COLS; j++ )
        {
            if( board[i][j] == Blank)
                return Invalid;
        }
    }

    //Checks for longest adjacent peices horizontally
    for( unsigned i = 0; i < BOARD_ROWS; i++ )
    {
        for( unsigned j = 0; j < BOARD_COLS; j++ )
        {
            start = board[i][j];
            count = 0;

            unsigned k = j;

            while ( k < BOARD_COLS && board[i][k] == start )
            {
                count++;
                
                if( start == X )
                    longestX = std::max( count, longestX );
                else
                    longestO = std::max( count, longestO );

                k++;
            }            
        }
    }

    //Checks for longest adjacent peices vertically
    for( unsigned j = 0; j < BOARD_COLS; j++ )
    {
        for( unsigned i = 0; i < BOARD_ROWS; i++ )
        {
            start = board[i][j];
            count = 0;

            unsigned k = i;

            while ( k < BOARD_ROWS && board[k][j] == start )
            {
                count++;
                
                if( start == X )
                    longestX = std::max( count, longestX );
                else
                    longestO = std::max( count, longestO );

                k++;
            } 
        }
    }

    //Return winner or Blank if tied.
    if( longestO == longestX )
        return Blank;
    else if( longestO > longestO)
        return O;
    else
        return X;
}