//
//  File:       structs.h
//  Author:     Jesper Persson & Jesper Wikström
//              All code is our own except where credited to others.
//
//	Copyright (c) 2012 by Jesper Persson & Jesper Wikström. All Rights Reserved.
//  Date: 		21/12-2012
//
//  Description: Contains different kinds of helper data.
//
#pragma once

inline int abs(const int _Input)
{
	int s = _Input >> 31;
	return (_Input ^ s) - s;
}

class Point
{
public:
	Point()
	{
		m_X = 0;
		m_Y = 0;
	}
	Point(int _X, int _Y)
	{
		m_X = _X;
		m_Y = _Y;
	}
	bool operator==(const Point& _Point)
	{
		return (m_X = _Point.m_X && m_Y == _Point.m_Y);
	}
	Point operator-(const Point& _Point)
	{
		return Point(m_X - _Point.m_X , m_Y - _Point.m_Y);
	}
	Point operator+(const Point& _Point)
	{
		return Point(m_X + _Point.m_X , m_Y + _Point.m_Y);
	}
	Point operator*(const int& _Factor)
	{
		return Point(m_X * _Factor, m_Y * _Factor);
	}
	/*float Length()
	{
		return sqrtf((float)(m_X * m_X + m_Y * m_Y));
	}*/
	int LengthSquared()
	{
		return m_X * m_X + m_Y * m_Y;
	}
	Point Normalized() const
	{
		return Point( (m_X == 0) ? 0 : m_X / abs(m_X), (m_Y == 0) ? 0 : m_Y / abs(m_Y));
	}
	int m_X, m_Y;
};

enum Players
{
	BLACK = 1,
	WHITE = -1
};

enum Moves
{
	CANT,
	MOVE,
	KILL,
	CASTLING,
	ENPASSANT
};

enum PieceTypes
{
	KING,
	QUEEN,
	ROOK,
	BISHOP,
	KNIGHT,
	PAWN
};