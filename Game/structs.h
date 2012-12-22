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

#include <math.h>

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
	float Length()
	{
		return sqrtf((float)(m_X * m_X + m_Y * m_Y));
	}
	int LengthSquared()
	{
		return m_X * m_X + m_Y * m_Y;
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