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

bool Piece::ValidDestination(Point _Destination)
{
	return !(	_Destination.m_X > 7 ||
				_Destination.m_X < 0 ||
				_Destination.m_Y > 7 ||
				_Destination.m_Y < 0 ||
				(_Destination.m_X == m_Position.m_X && _Destination.m_Y == m_Position.m_Y ));
}

bool Piece::PiecesOnPath(Point _Difference)
{
	int max = (absolute(_Difference.m_X) < absolute(_Difference.m_Y)) ? absolute(_Difference.m_Y) : (_Difference.m_X);
	Point step = _Difference.Normalized();
	for(int i = 1; i < max; ++i)
	{
		if ( m_Board->getPieceInPosition( m_Position + step*i) != 0)
			return true;
	}
	return false;
}

Moves Piece::PieceOnDest(Piece*  _DestPiece)
{
	if (_DestPiece != 0)
	{
		if(_DestPiece->getOwner() == m_Owner)
			return CANT;
		else
			return KILL;
	}
	else
		return MOVE;
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

void Piece::detach()
{
	m_Board->setPieceAtPosition(m_Position, 0);
	if(m_Owner == Players::WHITE)
		m_Board->getWhitePieces()[m_Index] = 0;
	else
		m_Board->getBlackPieces()[m_Index] = 0;
}

void Piece::attach()
{
	m_Board->setPieceAtPosition(m_Position, this);
	if(m_Owner == Players::WHITE)
		m_Board->getWhitePieces()[m_Index] = this;
	else
		m_Board->getBlackPieces()[m_Index] = this;
}

Players Piece::getOwner()
{
	return m_Owner;
}

void Piece::IncrementNumMoves()
{
	m_NumMoves++;
}

int Piece::GetNumMoves()
{
	return m_NumMoves;
}

Moves King::canMove(Point _Destination)
{
	if(!ValidDestination(_Destination))
		return CANT;

	Point diff = _Destination - m_Position;

	if((diff.m_X == 2 || diff.m_X == -2) && m_NumMoves == 0) //Castling
	{
		Point rookPosition = Point( (7 + 7 * diff.Normalized().m_X)/2, m_Position.m_Y);
		Piece* rook = m_Board->getPieceInPosition(rookPosition);
		if(rook == 0)
			return CANT;
		if(rook->GetNumMoves() != 0)
			return CANT;

		int max = absolute((rookPosition - m_Position).m_X);
		Point step = diff.Normalized();
		Piece** opposingPieces = m_Owner == BLACK ? m_Board->getWhitePieces() : m_Board->getBlackPieces();
		for(int i = 1; i < max; ++i)
		{
			if ( m_Board->getPieceInPosition( m_Position + step*i) != 0)
				return CANT;
			if(i < 3) //only the two first steps are were the king will pass.
			{
				for(int i = 0; i < 16; i++)
				{
					if( opposingPieces[i] != 0)
					{
						if(opposingPieces[i]->canMove(m_Position + step*i) == MOVE)
							return CANT;
					}
				}
			}
		}
		return CASTLING;
	}
	if(diff.LengthSquared() >= 4) //only allows a single step in any direction
		return CANT;

	Piece* destPiece = m_Board->getPieceInPosition(_Destination);
	return PieceOnDest(destPiece);
}

Moves Queen::canMove(Point _Destination)
{
	if(!ValidDestination(_Destination))
	return CANT;

	Point diff = _Destination - m_Position;
	if((absolute(diff.m_X) != 0 && absolute(diff.m_Y) != 0) && absolute(diff.m_X) != absolute(diff.m_Y)) //non-zero in both cardinal directions or length along both axises isn't equal
		return CANT;

	
	if ( PiecesOnPath(diff))
		return CANT;
	

	Piece* destPiece = m_Board->getPieceInPosition(_Destination);
	return PieceOnDest(destPiece);
}

Moves Rook::canMove(Point _Destination)
{
	if(!ValidDestination(_Destination))
	return CANT;

	Point diff = _Destination - m_Position;
	if(absolute(diff.m_X) != 0 && absolute(diff.m_Y) != 0) //non-zero in both cardinal directions
		return CANT;

	if ( PiecesOnPath(diff))
		return CANT;

	Piece* destPiece = m_Board->getPieceInPosition(_Destination);
	return PieceOnDest(destPiece);
}

Moves Bishop::canMove(Point _Destination)
{
	if(!ValidDestination(_Destination))
	return CANT;

	Point diff = _Destination - m_Position;
	if(absolute(diff.m_X) != absolute(diff.m_Y)) //Length along both axises isn't equal
		return CANT;

	if ( PiecesOnPath(diff))
		return CANT;

	Piece* destPiece = m_Board->getPieceInPosition(_Destination);
	return PieceOnDest(destPiece);
}

Moves Knight::canMove(Point _Destination)
{
	if(!ValidDestination(_Destination))
		return CANT;

	Point diff = _Destination - m_Position;
	if(diff.LengthSquared() != 5) //Must be one step along one axis, and two along the other
		return CANT;

	Piece* destPiece = m_Board->getPieceInPosition(_Destination);
	return PieceOnDest(destPiece);
}

Moves Pawn::canMove(Point _Destination)
{
	if(!ValidDestination(_Destination))
		return CANT;

	Point diff = _Destination - m_Position;
	if ( !((diff.m_Y == m_Owner) || (diff.m_Y == m_Owner * 2 && m_NumMoves == 0)) || absolute(diff.m_X) > 1) //Owner is the direction pawns can move
		return CANT;

	
	Piece* destPiece = m_Board->getPieceInPosition(_Destination);
	if (destPiece != 0)
	{
		if(destPiece->getOwner() == m_Owner)
			return CANT;
		else if(absolute(diff.m_X) == 1 && diff.m_Y == m_Owner) //only if it's a diagonal move
			return KILL;
		else
			return CANT;
	}
	else if (absolute(diff.m_X) == 0)
	{
		if(absolute(diff.m_Y) == 2)
		{
			if(PiecesOnPath(diff))
				return CANT;
			m_Board->setEnPassant(this);
			return DOUBLE;
		}
		return MOVE;
	}
	else
	{
		destPiece = m_Board->getPieceInPosition(m_Position + Point(diff.m_X, 0));
		if (destPiece == m_Board->getEnPassant())
			return ENPASSANT;
		return CANT;
	}
}