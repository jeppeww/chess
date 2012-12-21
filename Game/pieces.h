//
//  File:       pieces.h
//  Author:     Jesper Persson & Jesper Wikström
//              All code is our own except where credited to others.
//
//	Copyright (c) 2012 by Jesper Persson & Jesper Wikström. All Rights Reserved.
//  Date: 		21/12-2012
//
//  Description: 
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

	Point getPosition()
	{
		return m_Position;
	}

	void setPosition(Point _Position);
	virtual bool canMove (Point _Destination) = 0;
	void kill();

private:
	Point m_Position;
	Board* m_Board;
	Players m_Owner;
}