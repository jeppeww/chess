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
#include "math.h"

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

MoveReturns Chess::Move(Point _Position, Point _Destination)
{
	Moves moveResult = TryMove(_Position, _Destination);
	if(moveResult == CANT)
		return INVALID;

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
	else if(moveResult == CASTLING)
	{
		Point diff = _Destination - _Position;
		Point rookPosition = Point( (7 + 7 * diff.Normalized().m_X)/2, _Position.m_Y);
		Piece* rook = m_Board.getPieceInPosition(rookPosition);
		rook->setPosition(_Destination - diff.Normalized());
	}
	movingPiece->setPosition(_Destination);
	m_Board.setEnPassant(moveResult == DOUBLE ? movingPiece : 0); //resets the enPassant unless a pawn did a DOUBLE move.
	if(movingPiece->getType() == PAWN && ( _Destination.m_Y == 0 || _Destination.m_Y == 0))
		return PROMOTION;
	return VALID;
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
			return CHECK;
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
				return CHECK;
			return KILL;
		}
	case CASTLING:
		{
			Point diff = _Destination - _Position;
			Point rookPosition = Point( (7 + 7 * diff.Normalized().m_X)/2, _Position.m_Y);
			Piece* rook = m_Board.getPieceInPosition(rookPosition);
			movingPiece->setPosition(_Destination);
			rook->setPosition(_Destination - diff.Normalized());
			check = InCheck(m_CurrentPlayer);
			movingPiece->setPosition(_Position);
			rook->setPosition(rookPosition);
			if(check)
				return CHECK;
			return CASTLING;
		}
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
			return CHECK;
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
    m_PossibleMoves.clear();
    Piece** playersPieces = m_CurrentPlayer == WHITE ?
        m_Board.getWhitePieces() : m_Board.getBlackPieces();
    
    for (int i = 0; i < 16; i++)
    {
        if (playersPieces[i] != 0)
        {
            updatePossibleMoves(playersPieces[i]);
        }
    }
    if (m_PossibleMoves.size() != 0)
        return UNDECIDED;
    
    return InCheck(m_CurrentPlayer) ? CHECKMATE : DRAW;
}

void Chess::updatePossibleMoves(Piece* _Piece)
{
    Point curPos = _Piece->getPosition();
    static const int kDirections [4] = {0, 1, -1, 0};
    static const int hDirections [4] = {1, -1};
    Moves moveResult;
    
    switch (_Piece->getType())
    {
        case ROOK:
            for (int i = 0; i < 4; i++)
            {
                for (int l = 1; l < 8; l++)
                {
                    Moves attemptedMove = TryMove(curPos, curPos + Point(l * kDirections[i],
                                                                         l * kDirections[(2 + i) % 4]));
                    if (attemptedMove == CANT)
                        break;
                    if (attemptedMove == CHECK)
                        continue;
                    
                    pair<Point, Point> move = pair<Point,Point> (curPos,
                                        curPos + Point(l * kDirections[i],l * kDirections[(2 + i) % 4]));
                    
                    m_PossibleMoves.push_back(move);
                }
            }
            
        case BISHOP:
            for (int i = 0; i < 4; i++)
            {
                for (int l = 1; l < 8; l++)
                {
                    Moves attemptedMove = TryMove(curPos, curPos + Point(l * hDirections[i],
                                                                         l * hDirections[(2 + i) % 4]));
                    if (attemptedMove == CANT)
                        break;
                    if (attemptedMove == CHECK)
                        continue;
                    
                    pair<Point, Point> move = pair<Point,Point> (curPos,
                                                                 curPos + Point(l * hDirections[i],l * hDirections[(int)floor(i/2)]));
                    
                    m_PossibleMoves.push_back(move);
                }
            }
            
        case QUEEN:
            for (int i = 0; i < 4; i++)
            {
                for (int l = 1; l < 8; l++)
                {
                    Moves attemptedMove = TryMove(curPos, curPos + Point(l * hDirections[i],
                                                                         l * hDirections[(2 + i) % 4]));
                    if (attemptedMove == CANT)
                        break;
                    if (attemptedMove == CHECK)
                        continue;
                    
                    pair<Point, Point> move = pair<Point,Point> (curPos,
                                                                 curPos + Point(l * hDirections[i],l * hDirections[(int)floor(i/2)]));
                    
                    m_PossibleMoves.push_back(move);
                }
                for (int l = 1; l < 8; l++)
                {
                    Moves attemptedMove = TryMove(curPos, curPos + Point(l * hDirections[i],
                                                                         l * hDirections[(2 + i) % 4]));
                    if (attemptedMove == CANT)
                        break;
                    if (attemptedMove == CHECK)
                        continue;
                    
                    pair<Point, Point> move = pair<Point,Point> (curPos,
                                                                 curPos + Point(l * hDirections[i],l * hDirections[(int)floor(i/2)]));
                    
                    m_PossibleMoves.push_back(move);
                }
            }
            
        case KING:
            
            moveResult = TryMove(curPos, curPos + Point(1,0));
            if (moveResult != CANT && moveResult != CHECK)
                m_PossibleMoves.push_back(pair<Point,Point> (curPos, curPos + Point(1,0)));
            
            moveResult = TryMove(curPos, curPos + Point(1,1));
            if (moveResult != CANT && moveResult != CHECK)
                m_PossibleMoves.push_back(pair<Point,Point> (curPos, curPos + Point(1,1)));
            
            moveResult = TryMove(curPos, curPos + Point(0,1));
            if (moveResult != CANT && moveResult != CHECK)
                m_PossibleMoves.push_back(pair<Point,Point> (curPos, curPos + Point(0,1)));
            
            moveResult = TryMove(curPos, curPos + Point(-1,1));
            if (moveResult != CANT && moveResult != CHECK)
                m_PossibleMoves.push_back(pair<Point,Point> (curPos, curPos + Point(-1,1)));
            
            moveResult = TryMove(curPos, curPos + Point(-1,0));
            if (moveResult != CANT && moveResult != CHECK)
                m_PossibleMoves.push_back(pair<Point,Point> (curPos, curPos + Point(-1,0)));
            
            moveResult = TryMove(curPos, curPos + Point(-1,-1));
            if (moveResult != CANT && moveResult != CHECK)
                m_PossibleMoves.push_back(pair<Point,Point> (curPos, curPos + Point(-1,-1)));
            
            moveResult = TryMove(curPos, curPos + Point(0,-1));
            if (moveResult != CANT && moveResult != CHECK)
                m_PossibleMoves.push_back(pair<Point,Point> (curPos, curPos + Point(0,-1)));
            
            moveResult = TryMove(curPos, curPos + Point(1,-1));
            if (moveResult != CANT && moveResult != CHECK)
                m_PossibleMoves.push_back(pair<Point,Point> (curPos, curPos + Point(1,-1)));
            
            moveResult = TryMove(curPos, curPos + Point(2,0));
            if (moveResult != CANT && moveResult != CHECK)
                m_PossibleMoves.push_back(pair<Point,Point> (curPos, curPos + Point(2,0)));
            
            moveResult = TryMove(curPos, curPos + Point(-2,0));
            if (moveResult != CANT && moveResult != CHECK)
                m_PossibleMoves.push_back(pair<Point,Point> (curPos, curPos + Point(-2,0)));
            
        case PAWN:
        {
            int direction = _Piece->getOwner();     // -1 or 1
            
            
            moveResult = TryMove(curPos, curPos + Point(0,direction));
            if (moveResult != CANT && moveResult != CHECK)
                m_PossibleMoves.push_back(pair<Point,Point> (curPos, curPos + Point(0,direction)));
            
            moveResult = TryMove(curPos, curPos + Point(0,direction * 2));
            if (moveResult != CANT && moveResult != CHECK)
                m_PossibleMoves.push_back(pair<Point,Point> (curPos, curPos + Point(0,direction * 2)));
            
            
            moveResult = TryMove(curPos, curPos + Point(1,direction));
            if (moveResult != CANT && moveResult != CHECK)
                m_PossibleMoves.push_back(pair<Point,Point> (curPos, curPos + Point(1,direction)));
            
            moveResult = TryMove(curPos, curPos + Point(-1,direction));
            if (moveResult != CANT && moveResult != CHECK)
                m_PossibleMoves.push_back(pair<Point,Point> (curPos, curPos + Point(-1,direction)));
        }
        case KNIGHT:
            
            moveResult = TryMove(curPos, curPos + Point(-2,1));
            if (moveResult != CANT && moveResult != CHECK)
                m_PossibleMoves.push_back(pair<Point,Point> (curPos, curPos + Point(-2,1)));
            
            moveResult = TryMove(curPos, curPos + Point(-1,2));
            if (moveResult != CANT && moveResult != CHECK)
                m_PossibleMoves.push_back(pair<Point,Point> (curPos, curPos + Point(-1,-2)));
            
            moveResult = TryMove(curPos, curPos + Point(1,2));
            if (moveResult != CANT && moveResult != CHECK)
                m_PossibleMoves.push_back(pair<Point,Point> (curPos, curPos + Point(1,2)));
            
            moveResult = TryMove(curPos, curPos + Point(2,1));
            if (moveResult != CANT && moveResult != CHECK)
                m_PossibleMoves.push_back(pair<Point,Point> (curPos, curPos + Point(2,1)));
            
            moveResult = TryMove(curPos, curPos + Point(2,-1));
            if (moveResult != CANT && moveResult != CHECK)
                m_PossibleMoves.push_back(pair<Point,Point> (curPos, curPos + Point(2,-1)));
            
            moveResult = TryMove(curPos, curPos + Point(1,-2));
            if (moveResult != CANT && moveResult != CHECK)
                m_PossibleMoves.push_back(pair<Point,Point> (curPos, curPos + Point(1,-2)));
            
            moveResult = TryMove(curPos, curPos + Point(-1,-2));
            if (moveResult != CANT && moveResult != CHECK)
                m_PossibleMoves.push_back(pair<Point,Point> (curPos, curPos + Point(-1,-2)));
            
            moveResult = TryMove(curPos, curPos + Point(-2,-1));
            if (moveResult != CANT && moveResult != CHECK)
                m_PossibleMoves.push_back(pair<Point,Point> (curPos, curPos + Point(-2,-1)));
    }
}

void Chess::ChangeTurn()
{
	m_CurrentPlayer = m_CurrentPlayer == WHITE ? BLACK : WHITE;
}

vector<pair<Point,Point>> Chess::getPossibleMoves()
{
	return m_PossibleMoves;
}


void Chess::Promote(Point _Position, PieceTypes _Type)
{
	Piece* promotionPiece = m_Board.getPieceInPosition(_Position);
	int index = promotionPiece->getIndex();
	Players owner = promotionPiece->getOwner();
	promotionPiece->detach();
	delete promotionPiece;
	switch (_Type)
	{
	case QUEEN:
		promotionPiece = new Queen(_Position, owner, index, &m_Board);
		break;
	case ROOK:
		promotionPiece = new Rook(_Position, owner, index, &m_Board);
		break;
	case KNIGHT:
		promotionPiece = new Knight(_Position, owner, index, &m_Board);
		break;
	case BISHOP:
		promotionPiece = new Bishop(_Position, owner, index, &m_Board);
		break;
	}
	m_Board.setPieceAtPosition(_Position, promotionPiece);
	if(owner == WHITE) 
		m_Board.getWhitePieces()[index] = promotionPiece;
	else
		m_Board.getBlackPieces()[index] = promotionPiece;
}