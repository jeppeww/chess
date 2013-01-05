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
#include <vector>
#include <utility>
#include "structs.h"

using namespace std;

class Chess
{
public:
	Chess();
	~Chess();
	Piece* GetPieceAt(Point _Position);
	Moves TryMove(Point _Position, Point _Destination);
	bool Move(Point _Position, Point _Destination);
	void ChangeTurn();
    GameState StateOfGame();
    vector<pair<Point, Point>> getPossibleMoves();
    
private:
    void updatePossibleMoves(Piece* _Piece);
	bool InCheck(Players _Player);
	Board m_Board;
	Players m_CurrentPlayer;
    vector<pair<Point, Point>> m_PossibleMoves;
}; 