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
#pragma once

#include "structs.h"
class Board;

class Piece 
{
public:
	Piece(Point _Position, Players _Owner, int _Index, Board* _Board)
	{
		m_Position = _Position;
		m_Owner = _Owner;
		m_Index = _Index;
		m_Board = _Board;
		m_NumMoves = 0;
	}
	~Piece(){}
	// Return the position of the piece.
	Point getPosition();
	// Set the position of the piece.
	void setPosition(Point _Position);
	// Return true if the piece can move to the specicied position, otherwise false.
	virtual Moves canMove(Point _Destination) = 0;
	// Destroy the piece.
	void kill();
	// Returns the owner of the piece.
	Players getOwner();
	// Returns the character for the Piece
	virtual char getChar() = 0;

protected:
	//Checks wether the position is on the board and isn't on the piece istelf
	bool ValidDestination(Point _Destination);
	//Checks if there are any pieces blocking the path
	bool PiecesOnPath(Point _Destination);
	//Common handling if there's a piece on your destination
	Moves PieceOnDest(Piece* _DestPiece);
	int m_Index;
	int m_NumMoves;
	Point m_Position;
	Board* m_Board;
	Players m_Owner;
};

class King : public Piece
{
public:
	King(Point _Position, Players _Owner, int _Index, Board* _Board) : Piece(_Position, _Owner, _Index, _Board) {}
	virtual Moves canMove(Point _Destination);
	virtual char getChar(){ return (m_Owner == WHITE) ? 'k' : 'K';}
};

class Queen : public Piece
{
public:
	Queen(Point _Position, Players _Owner, int _Index, Board* _Board) : Piece(_Position, _Owner, _Index, _Board) {}
	virtual Moves canMove(Point _Destination);
	virtual char getChar(){ return (m_Owner == WHITE) ? 'q' : 'Q';}
};

class Rook : public Piece
{
public:
	Rook(Point _Position, Players _Owner, int _Index, Board* _Board) : Piece(_Position, _Owner, _Index, _Board) {}
	virtual Moves canMove(Point _Destination);
	virtual char getChar(){ return (m_Owner == WHITE) ? 'r' : 'R';}
};

class Bishop : public Piece
{
public:
	Bishop(Point _Position, Players _Owner, int _Index, Board* _Board) : Piece(_Position, _Owner, _Index, _Board) {}
	virtual Moves canMove(Point _Destination);
	virtual char getChar(){ return (m_Owner == WHITE) ? 'b' : 'B';}
};

class Knight : public Piece
{
public:
	Knight(Point _Position, Players _Owner, int _Index, Board* _Board) : Piece(_Position, _Owner, _Index, _Board) {}
	virtual Moves canMove(Point _Destination);
	virtual char getChar(){ return (m_Owner == WHITE) ? 'n' : 'N';}
};

class Pawn : public Piece
{
public:
	Pawn(Point _Position, Players _Owner, int _Index, Board* _Board) : Piece(_Position, _Owner, _Index, _Board) {}
	virtual Moves canMove(Point _Destination);
	virtual char getChar(){ return (m_Owner == WHITE) ? 'p' : 'P';}
};