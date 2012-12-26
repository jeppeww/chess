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
	Moves moveResult = TryMove(_Position, _Destination);
	if(moveResult == CANT)
		return false;

	Piece* movingPiece = m_Board.getPieceInPosition(_Position);
	movingPiece->IncrementNumMoves(); //used for pawns and Castling.
	if(moveResult == KILL) //detach and delete the killed piece.
	{
		Piece* killedPiece = m_Board.getPieceInPosition(_Destination);
		killedPiece->detach();
		delete killedPiece;
	}
	else if(moveResult == ENPASSANT) //handled slightly differently from KILL
	{
		Piece* killedPiece = m_Board.getPieceInPosition(Point(_Destination.m_X, _Position.m_Y));
		killedPiece->detach();
		m_Board.setEnPassant(0);
		delete killedPiece;
	}
	movingPiece->setPosition(_Destination);
	m_Board.setEnPassant(moveResult == DOUBLE ? movingPiece : 0); //resets the enPassant unless a pawn did a DOUBLE move.
	return true;
}

Moves Chess::TryMove(Point _Position, Point _Destination)
{
	Piece* movingPiece = m_Board.getPieceInPosition(_Position);
	if(movingPiece == 0)
		return CANT;
	if(movingPiece->getOwner() != m_CurrentPlayer)
		return CANT;
	bool check;
	Moves moveResult = movingPiece->canMove(_Destination);
	switch(moveResult)
	{
	case CANT:
		return CANT;
	case DOUBLE: //DOUBLE and MOVE are handled in the same way.
	case MOVE:
		movingPiece->setPosition(_Destination);
		check = InCheck(m_CurrentPlayer);
		movingPiece->setPosition(_Position);
		if(check)
			return CANT;
		return moveResult;
	case KILL:
		{
			Piece* killedPiece = m_Board.getPieceInPosition(_Destination);
			killedPiece->detach();
			movingPiece->setPosition(_Destination);
			check = InCheck(m_CurrentPlayer);
			movingPiece->setPosition(_Position);
			killedPiece->attach();
			if(check)
				return CANT;
			return KILL;
		}
	case CASTLING:
		return CANT; //TODO: Implement
	case ENPASSANT:
		Piece* killedPiece = m_Board.getPieceInPosition(Point(_Destination.m_X, _Position.m_Y));
		killedPiece->detach();
		movingPiece->setPosition(_Destination);
		m_Board.setEnPassant(0);
		check = InCheck(m_CurrentPlayer);
		movingPiece->setPosition(_Position);
		killedPiece->attach();
		m_Board.setEnPassant(killedPiece);
		if(check)
			return CANT;
		return ENPASSANT;
	}
}

bool Chess::InCheck(Players _Player)
{
	Piece* king = m_CurrentPlayer == WHITE ? m_Board.getWhitePiece(KINGINDEX) : m_Board.getBlackPiece(KINGINDEX);
	Piece** opposingPieces = m_CurrentPlayer == BLACK ? m_Board.getWhitePieces() : m_Board.getBlackPieces();
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

GameState Chess::StateOfGame()
{
    Piece** playersPieces = m_CurrentPlayer == WHITE ?
        m_Board.getWhitePieces() : m_Board.getBlackPieces();
    
    for (int i = 0; i < 16; i++)
    {
        if (CanPreventCheck(playersPieces[i]))
            return UNDECIDED;
    }
    return InCheck(m_CurrentPlayer) ? CHECKMATE : DRAW;
}

bool Chess::CanPreventCheck(Piece* _Piece)
{
    //TODO fix the check
    return true;
}

void Chess::ChangeTurn()
{
	m_CurrentPlayer = m_CurrentPlayer == WHITE ? BLACK : WHITE;
}