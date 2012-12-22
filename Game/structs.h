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
	int m_X, m_Y;
};

enum Players
{
	BLACK = 1,
	WHITE = -1
};