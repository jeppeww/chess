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
#include "chess.h"
#include "pieces.h"
#include <stdio.h>


Chess ChessGame;

//returns the apropriate character to display for each piece/player combination
char GetChar(Piece* _Piece)
{
	if(_Piece == 0)
		return '_';
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

void Render()
{
	for(int y = 0; y < 8; y++)
	{
		printf("%i ",8-y);
		for(int x = 0; x < 8; x++)
			printf("|%c",GetChar(ChessGame.GetPieceAt(Point(x,y))));
		printf("|\n");
	}
	printf("   a b c d e f g h");
}

int main()
{
	Render();
	getchar();
	return 0;
}