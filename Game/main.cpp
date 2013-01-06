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
#include <stdlib.h>


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
	printf("\n");
	for(int y = 7; y > -1; y--)
	{
		printf("%i ",y+1);
		for(int x = 0; x < 8; x++)
			printf("|%c",GetChar(ChessGame.GetPieceAt(Point(x,y))));
		printf("|\n");
	}
	printf("   a b c d e f g h");
}

bool ParseInput(char* _Input, Point& _Result1, Point& _Result2)
{
    int posX, posY, desX, desY;
    
    if (_Input[0] >= 'a' && _Input[0] <= 'h')
    {
        posX =(int) (_Input[0] - 'a');
    }
    else if (_Input[0] >= 'A' && _Input[0] <= 'Z')
    {
        posX = (int) (_Input[0] - 'A');
    }
    else
        return false;
    
    if (_Input[1] >= '1' && _Input[1] <= '8')
    {
        posY =(int) (_Input[1] - '1');
    }
    else
        return false;
    
    if (_Input[3] >= 'a' && _Input[3] <= 'h')
    {
        desX =(int) (_Input[3] - 'a');
    }
    else if (_Input[3] >= 'A' && _Input[3] <= 'Z')
    {
        desX = (int) (_Input[3] - 'A');
    }
    else
        return false;
    
    if (_Input[4] >= '1' && _Input[4] <= '8')
    {
        desY =(int) (_Input[4] - '1');
    }
    else
        return false;
    
    _Result1.m_X = posX;
    _Result1.m_Y = posY;
    _Result2.m_X = desX;
    _Result2.m_Y = desY;
    return true;
}

int main()
{
	GameState gState = UNDECIDED;
	while(gState == UNDECIDED)
	{
		gState = ChessGame.StateOfGame();
		int number = ChessGame.getPossibleMoves().size();
		printf("\n Number moves possible: %d", number);
		Render();
		bool noProperMove = true;
		while(noProperMove)
		{
			printf("\nInput move (format xy-xy): ");
			char input[100];
			fgets(input, 100, stdin);
			Point position, destination;
			if(ParseInput(input, position, destination))
			{
				noProperMove = !ChessGame.Move(position, destination);
				if(noProperMove)
				{
					printf("\nnej");
				}
			}
			else
			{
				printf("\nPlease input properly next time.");
			}
		}
		ChessGame.ChangeTurn();
	}
	//Game is over, do shit.
	return 0;
}