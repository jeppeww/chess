//
//  File:       main.cpp
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

//returns the apropriate character to display for each piece/player combination
char GetChar(Piece* _Piece)
{
	if(_Piece == 0)
		return ' ';
	switch (_Piece->getType())
	{
	case KING:
		return (_Piece->getOwner() == WHITE) ? 'k' : 'K';
	case QUEEN:
		return (_Piece->getOwner() == WHITE) ? 'q' : 'Q';
	case ROOK:
		return (_Piece->getOwner() == WHITE) ? 'r' : 'R';
	case BISHOP:
		return (_Piece->getOwner() == WHITE) ? 'b' : 'B';
	case KNIGHT:
		return (_Piece->getOwner() == WHITE) ? 'n' : 'N';
	case PAWN:
		return (_Piece->getOwner() == WHITE) ? 'p' : 'P';
	default:
		return '?';
	}
}

void main()
{

}