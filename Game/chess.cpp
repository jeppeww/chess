//
//  File:       chess.cpp
//  Class:      chess
//  Author:     Jesper Persson & Jesper Wikström
//              All code is our own except where credited to others.
//
//	Copyright (c) 2012 by Jesper Persson & Jesper Wikström. All Rights Reserved.
//  Date: 		21/12-2012
//
//  Description: 
//
#include "chess.h"
#include "pieces.h"

Chess::Chess()
{
	m_CurrentPlayer = WHITE;
}

Chess::~Chess()
{

}

Piece* Chess::GetPieceAt(Point _Position)
{
	return m_Board.getPieceInPosition(_Position);
}

bool Chess::Move(Point _Position, Point _Destination)
{
	Piece* movingPiece = m_Board.getPieceInPosition(_Position);
	if(movingPiece == 0)
		return false;
	if(movingPiece->getOwner() != m_CurrentPlayer)
		return false;
	switch(movingPiece->canMove(_Destination))
	{
	case CANT:
		return false;
	case MOVE:
		movingPiece->setPosition(_Destination);
		if(InCheck(m_CurrentPlayer))
		{
			movingPiece->setPosition(_Position);
			return false;
		}
		return true;
	case KILL:
		{
			Piece* killedPiece = m_Board.getPieceInPosition(_Destination);
			killedPiece->detach();
			movingPiece->setPosition(_Destination);
			if(InCheck(m_CurrentPlayer))
			{
				movingPiece->setPosition(_Position);
				killedPiece->attach();
				return false;
			}
			delete killedPiece;
		}
		return true;
	case CASTLING:
		return false;
	case ENPASSANT:
		return false;
	}
}

bool Chess::InCheck(Players _Player)
{
	Piece* king = m_CurrentPlayer == WHITE ? m_Board.getWhitePiece(KINGINDEX) : m_Board.getBlackPiece(KINGINDEX);
	Piece** opposingPieces = m_CurrentPlayer == WHITE ? m_Board.getWhitePieces() : m_Board.getBlackPieces();
	Point kingPosition = king->getPosition();
	for(int i = 0; i < 16; i++)
	{
		if( opposingPieces[i] != 0)
		{
			if(opposingPieces[i]->canMove(kingPosition) == KILL)
				return true;
		}
	}
	return false;
}

void Chess::ChangeTurn()
{
	m_CurrentPlayer = m_CurrentPlayer == WHITE ? BLACK : WHITE;
}