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

Chess::Chess()
{

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
	return false;
}