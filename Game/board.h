//
//  File:       board.h
//  Class:      board
//  Author:     Jesper Persson & Jesper Wikström
//              All code is our own except where credited to others.
//
//	Copyright (c) 2012 by Jesper Persson & Jesper Wikström. All Rights Reserved.
//  Date: 		21/12-2012
//
//  Description: 
//

#include "structs.h"
class Pieces;

class Board
{

public:
	Board();
	~Board();

	Pieces* getPieceInPosition(Point _Position);
	Pieces* getWhitePiece(int _Index);
	Pieces* getBlackPiece(int _Index);

	void setPieceAtPosition(Point _Position, Piece* _Piece);

	Pieces* getWhitePieces();
	Pieces* getBlackPieces();

private:
	Pieces* m_Board [8][8];
	Pieces* m_BlackPieces [16];
	Pieces* m_WhitePieces [16];

}