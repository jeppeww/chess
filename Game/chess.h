//
//  File:       chess.h
//  Class:      chess
//  Author:     Jesper Persson & Jesper Wikström
//              All code is our own except where credited to others.
//
//	Copyright (c) 2012 by Jesper Persson & Jesper Wikström. All Rights Reserved.
//  Date: 		21/12-2012
//
//  Description: 
//
#pragma once
#include "board.h"

class Chess
{
public:
	Chess();
	~Chess();
	Piece* GetPieceAt(Point _Position);
	bool Move(Point _Position, Point _Destination);
private:
	Board m_Board;
};