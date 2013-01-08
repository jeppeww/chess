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
	//Returns the piece at the given position.
	Piece* GetPieceAt(Point _Position);
	//Attemps a move, returns the resulting type of move
	Moves TryMove(Point _Position, Point _Destination);
	//Moves a piece, returns wether the move was VALID, INVALID or resulted in a PROMOTION.
	MoveReturns Move(Point _Position, Point _Destination);
	//Changes the current player
	void ChangeTurn();
	//Checks the gamestate, updates the list of possible moves.
    GameState StateOfGame();
	//Returns a list of all possible moves this turn.
    vector<pair<Point, Point>> getPossibleMoves();
	//Promotes a piece at _Position to _Type.
	void Promote(Point _Position, PieceTypes _Type);
    
private:
    void updatePossibleMoves(Piece* _Piece);
	bool InCheck(Players _Player);
	Board m_Board;
	Players m_CurrentPlayer;
    vector<pair<Point, Point>> m_PossibleMoves;
}; 