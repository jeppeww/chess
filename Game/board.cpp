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

Board::Board ()
{
	//Clear middle of board.
	for (int y = 2; y < 6; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			m_Board[x][y] = 0;
		}
	}

	//TODO create pieces in fitting locations.
}

Pieces* Board::getPieceInPosition(Point _Position)
{
	return m_Board[_Position.m_X][_Position.m_Y];
}

Pieces* Board::getWhitePiece(int _Index)
{
	return m_WhitePieces[_Index];
}

Pieces* Board::getBlackPiece(int _Index)
{
	return m_BlackPieces[_Index];
}

void Board::setPieceAtPosition(Point _Position, Piece* _Piece)
{
	m_Board[_Position.m_X][_Position.m_Y] = _Piece;
}

Pieces* Board::getWhitePieces()
{
	return m_WhitePieces;
}
Pieces* Board::getBlackPieces()
{
	return m_BlackPieces;
}
