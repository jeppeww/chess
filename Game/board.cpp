//
//  File:       board.cpp
//  Class:      board
//  Author:     Jesper Persson & Jesper Wikström
//              All code is our own except where credited to others.
//
//	Copyright (c) 2012 by Jesper Persson & Jesper Wikström. All Rights Reserved.
//  Date: 		21/12-2012
//
//  Description: 
//

#include "board.h"
#include "pieces.h"

Board::Board()
{
	//Clear middle of board.
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			m_Board[x][y] = 0;
		}
	}

	//Create all the pieces.
	m_BlackPieces[0] = m_Board[0][7] = new Rook(Point(0,7), Players::BLACK, 0, this);
	m_BlackPieces[1] = m_Board[1][7] = new Knight(Point(1,7), Players::BLACK, 1, this);
	m_BlackPieces[2] = m_Board[2][7] = new Bishop(Point(2,7), Players::BLACK, 2, this);
	m_BlackPieces[3] = m_Board[3][7] = new Queen(Point(3,7), Players::BLACK, 3, this);
	m_BlackPieces[4] = m_Board[4][7] = new King(Point(4,7), Players::BLACK, 4, this);
	m_BlackPieces[5] = m_Board[5][7] = new Bishop(Point(5,7), Players::BLACK, 5, this);
	m_BlackPieces[6] = m_Board[6][7] = new Knight(Point(6,7), Players::BLACK, 6, this);
	m_BlackPieces[7] = m_Board[7][7] = new Rook(Point(7,7), Players::BLACK, 7, this);

	m_BlackPieces[8] = m_Board[0][6] = new Pawn(Point(0,6), Players::BLACK, 8, this);
	m_BlackPieces[9] = m_Board[1][6] = new Pawn(Point(1,6), Players::BLACK, 9, this);
	m_BlackPieces[10] = m_Board[2][6] = new Pawn(Point(2,6), Players::BLACK, 10, this);
	m_BlackPieces[11] = m_Board[3][6] = new Pawn(Point(3,6), Players::BLACK, 11, this);
	m_BlackPieces[12] = m_Board[4][6] = new Pawn(Point(4,6), Players::BLACK, 12, this);
	m_BlackPieces[13] = m_Board[5][6] = new Pawn(Point(5,6), Players::BLACK, 13, this);
	m_BlackPieces[14] = m_Board[6][6] = new Pawn(Point(6,6), Players::BLACK, 14, this);
	m_BlackPieces[15] = m_Board[7][6] = new Pawn(Point(7,6), Players::BLACK, 15, this);

	m_WhitePieces[0] = m_Board[0][0] = new Rook(Point(0,0), Players::WHITE, 0, this);
	m_WhitePieces[1] = m_Board[1][0] = new Knight(Point(1,0), Players::WHITE, 1, this);
	m_WhitePieces[2] = m_Board[2][0] = new Bishop(Point(2,0), Players::WHITE, 2, this);
	m_WhitePieces[3] = m_Board[3][0] = new Queen(Point(3,0), Players::WHITE, 3, this);
	m_WhitePieces[4] = m_Board[4][0] = new King(Point(4,0), Players::WHITE, 4, this);
	m_WhitePieces[5] = m_Board[5][0] = new Bishop(Point(5,0), Players::WHITE, 5, this);
	m_WhitePieces[6] = m_Board[6][0] = new Knight(Point(6,0), Players::WHITE, 6, this);
	m_WhitePieces[7] = m_Board[7][0] = new Rook(Point(7,0), Players::WHITE, 7, this);

	m_WhitePieces[8] = m_Board[0][1] = new Pawn(Point(0,1), Players::WHITE, 8, this);
	m_WhitePieces[9] = m_Board[1][1] = new Pawn(Point(1,1), Players::WHITE, 9, this);
	m_WhitePieces[10] = m_Board[2][1] = new Pawn(Point(2,1), Players::WHITE, 10, this);
	m_WhitePieces[11] = m_Board[3][1] = new Pawn(Point(3,1), Players::WHITE, 11, this);
	m_WhitePieces[12] = m_Board[4][1] = new Pawn(Point(4,1), Players::WHITE, 12, this);
	m_WhitePieces[13] = m_Board[5][1] = new Pawn(Point(5,1), Players::WHITE, 13, this);
	m_WhitePieces[14] = m_Board[6][1] = new Pawn(Point(6,1), Players::WHITE, 14, this);
	m_WhitePieces[15] = m_Board[7][1] = new Pawn(Point(7,1), Players::WHITE, 15, this);
}

Board::~Board()
{

}

Piece* Board::getPieceInPosition(Point _Position)
{
	return m_Board[_Position.m_X][_Position.m_Y];
}

Piece* Board::getWhitePiece(int _Index)
{
	return m_WhitePieces[_Index];
}

Piece* Board::getBlackPiece(int _Index)
{
	return m_BlackPieces[_Index];
}

void Board::setPieceAtPosition(Point _Position, Piece* _Piece)
{
	m_Board[_Position.m_X][_Position.m_Y] = _Piece;
}

Piece** Board::getWhitePieces()
{
	return m_WhitePieces;
}
Piece** Board::getBlackPieces()
{
	return m_BlackPieces;
}

void Board::setEnPassant(Piece* _EnPassant)
{
	m_EnPassant = _EnPassant;
}

Piece* Board::getEnPassant()
{
	return m_EnPassant;
}