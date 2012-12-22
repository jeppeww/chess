//
//  File:       board.h
//  Class:      board
//  Author:     Jesper Persson & Jesper Wikström
//              All code is our own except where credited to others.
//
//	Copyright (c) 2012 by Jesper Persson & Jesper Wikström. All Rights Reserved.
//  Date: 		21/12-2012
//
//  Description: Class for representing a regular chessboard. Contains information
//  about the state of every position in the board, as well as references to each 
//  piece in any of the two colours.
//

#include "structs.h"
class Pieces;

class Board
{

public:
	Board();
	~Board();

	// Return the piece in the specified position. Returns NULL if the position is illegal or there is no piece in it. 
	Pieces* getPieceInPosition(Point _Position);
	// Return the n'th white piece
	Pieces* getWhitePiece(int _Index);
	// Return the n'th black piece
	Pieces* getBlackPiece(int _Index);

	// Put the selected piece unto the selected position, or 0 if the position is to be cleared.
	void setPieceAtPosition(Point _Position, Piece* _Piece);

	// Returns an Array containing every white piece.
	Pieces* getWhitePieces();
	// Returns an array containing every black piece.
	Pieces* getBlackPieces();

private:
	// The gameboard
	Pieces* m_Board [8][8];
	// Array of all black pieces.
	Pieces* m_BlackPieces [16];
	// Array of all white pieces.
	Pieces* m_WhitePieces [16];

}