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
#include <iostream>


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

//Renders the board.
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

//Parses move input.
bool ParseInput(char* _Input, Point& _Result1, Point& _Result2)
{
    int posX, posY, desX, desY;
	if(strncmp(_Input, "0-0", 3) == 0) //Castling special cases.
	{
		_Result1 = Point( 4, (7 + 7 * -ChessGame.GetCurrentPlayer())/2);
		_Result2 = Point( 7 , (7 + 7 * -ChessGame.GetCurrentPlayer())/2);
		return true;
	}
	else if(strncmp(_Input, "0-0-0", 5) == 0)
	{
		_Result1 = Point( 4, (7 + 7 * -ChessGame.GetCurrentPlayer())/2);
		_Result2 = Point( 0, (7 + 7 * -ChessGame.GetCurrentPlayer())/2);
		return true;
	}
    
    if (_Input[0] >= 'a' && _Input[0] <= 'h')
    {
        posX = (int) (_Input[0] - 'a');
    }
    else if (_Input[0] >= 'A' && _Input[0] <= 'Z')
    {
        posX = (int) (_Input[0] - 'A');
    }
    else
        return false;
    
    if (_Input[1] >= '1' && _Input[1] <= '8')
    {
        posY = (int) (_Input[1] - '1');
    }
    else
        return false;
    
    if (_Input[3] >= 'a' && _Input[3] <= 'h')
    {
        desX = (int) (_Input[3] - 'a');
    }
    else if (_Input[3] >= 'A' && _Input[3] <= 'Z')
    {
        desX = (int) (_Input[3] - 'A');
    }
    else
        return false;
    
    if (_Input[4] >= '1' && _Input[4] <= '8')
    {
        desY = (int) (_Input[4] - '1');
    }
    else
        return false;
    
    _Result1.m_X = posX;
    _Result1.m_Y = posY;
    _Result2.m_X = desX;
    _Result2.m_Y = desY;
    return true;
}

//Parses pawn promotion input.
bool ParsePromotionInput(char* _Input, PieceTypes& _Result)
{
    if (_Input[0] == 'q' && _Input[0] == 'Q')
    {
		_Result = QUEEN;
    }
    else if (_Input[0] == 'r' && _Input[0] == 'R')
    {
		_Result = ROOK;
    }
	else if (_Input[0] == 'b' && _Input[0] == 'B')
    {
		_Result = BISHOP;
    }
	else if (_Input[0] == 'n' && _Input[0] == 'N')
    {
		_Result = KNIGHT;
    }
    else
        return false;
    return true;
}

void PrintMoves(vector<pair<Point,Point>> _Moves)
{
	for(unsigned int i = 0; i < _Moves.size(); i++)
	{
		printf("\n%c%i-%c%i",
			(char) ((int)'a' + _Moves[i].first.m_X),
			_Moves[i].first.m_Y + 1,
			(char) ((int)'a' + _Moves[i].second.m_X),
			_Moves[i].second.m_Y + 1);
	}
}

int main()
{
	GameState gState = ChessGame.StateOfGame();
	while(gState == UNDECIDED)
	{
		system("cls");
		Render();
		bool noProperMove = true;
		while(noProperMove)
		{
			printf("\nInput move (format xy-xy, type \"MOVES\" for list): ");
			char input[100];
			cin >> input;
			if(strncmp(input,"MOVES",5) == 0)
			{
				PrintMoves(ChessGame.getPossibleMoves());
				continue;
			}
			Point position, destination;
			if(ParseInput(input, position, destination))
			{
				MoveReturns moveReturn = ChessGame.Move(position, destination);
				noProperMove = (moveReturn == INVALID);
				if(noProperMove)
				{
					printf("\nInvalid move.");
				}
				else if(moveReturn == PROMOTION)
				{
					PieceTypes type;
					while(true)
					{
						printf("\nA pawn is to be promoted, input piece type (Q, R, B or N): ");
						cin >> input;
						if(!ParsePromotionInput(input, type))
							break;
						printf("\nInvalid input.");
					}
					ChessGame.Promote(destination, type);
				}
			}
			else
			{
				printf("\nPlease provide proper input next time.");
			}
		}
		ChessGame.ChangeTurn();
		gState = ChessGame.StateOfGame();
	}
	if(gState == DRAW)
		printf("\nGame resulted in a draw");
	else
		printf("\n%s player won the game.", (ChessGame.GetCurrentPlayer() == WHITE) ? "White" : "Black");
	cin.get();
	cin.get();
	return 0;
}