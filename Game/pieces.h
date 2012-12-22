//
//  File:       pieces.h
//  Author:     Jesper Persson & Jesper Wikström
//              All code is our own except where credited to others.
//
//	Copyright (c) 2012 by Jesper Persson & Jesper Wikström. All Rights Reserved.
//  Date: 		21/12-2012
//
//  Description: A class for representing a general Piece. Should be used as a abstract class, and thus, never be implemented, only inherited.
//  Contains a position and an owner (black or white). Keeps a reference to the gameboard upon which it is placed.
//

#include "structs.h"
class Board;

class Piece 
{

public:
	Piece (Point _Position, Players _Owner, Board* _Board)
	{
		m_Position = _Position;
		m_Owner = _Owner;
		m_Board = _Board;
	}
	~Piece(){}
	// Return the position of the piece.
	Point getPosition()
	{
		return m_Position;
	}
	// Set the position of the piece.
	void setPosition(Point _Position);
	// Return true if the piece can move to the specicied position, otherwise false.
	virtual bool canMove (Point _Destination) = 0;
	// Destroy the piece.
	void kill();

private:
	Point m_Position;
	Board* m_Board;
	Players m_Owner;
}