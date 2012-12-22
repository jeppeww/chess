//
//  File:       pieces.cpp
//
//  Author:     Jesper Persson & Jesper Wikström
//              All code is our own except where credited to others.
//
//	Copyright (c) 2012 by Jesper Persson & Jesper Wikström. All Rights Reserved.
//  Date: 		21/12-2012
//
//  Description: 
//

#include "pieces.h"
#include "board.h"

inline bool ValidDestination(Point _Destination)
{
	return !(_Destination.m_X > 7 || _Destination.m_X < 0 || _Destination.m_Y > 7 || _Destination.m_Y < 0);
}

Point Piece::getPosition()
{
	return m_Position;
}

void Piece::setPosition(Point _Position)
{
	m_Board->setPieceAtPosition(m_Position, 0);
	m_Position = _Position;
	m_Board->setPieceAtPosition(_Position, this);
}

void Piece::kill()
{
	m_Board->setPieceAtPosition(m_Position, 0);
	if(m_Owner == Players::WHITE)
		m_Board->getWhitePieces()[m_Index] = 0;
	else
		m_Board->getBlackPieces()[m_Index] = 0;
	delete this;
}

Players Piece::getOwner()
{
	return m_Owner;
}

Moves King::canMove(Point _Destination)
{
	if(!ValidDestination(_Destination) || _Destination == m_Position)
		return CANT;

	Point diff = m_Position - _Destination;

	if(diff.LengthSquared() >= 4)
		return CANT;

	Piece* destPiece = m_Board->getPieceInPosition(_Destination);
	if (destPiece != 0)
	{
		if(destPiece->getOwner() == m_Owner)
			//TODO: Castling should probably be in here?
			return CANT;
		else
			return KILL;
	}
	else
		return MOVE;
}

Moves Queen::canMove(Point _Destination)
{
	return CANT;
}

Moves Rook::canMove(Point _Destination)
{
	return CANT;
}

Moves Bishop::canMove(Point _Destination)
{
	return CANT;
}

Moves Knight::canMove(Point _Destination)
{
	return CANT;
}

Moves Pawn::canMove(Point _Destination)
{
	return CANT;
}