#pragma once
#include"Brick.h"

class ArrayOfBricks
{
	const int num;
	const int startX;
	const int startY;


public:
	Brick *arr[32];

	ArrayOfBricks(int n, int sX, int sY) :startX(sX), startY(sY),num(n)
	{
		int j = sX;
		for (int i = 0; i < n; i++)
		{
			arr[i] = new Brick(j,sY);
			j += arr[i]->getSizeX() + 2;
			if (!arr[i]->getBitMap())
				fprintf(stderr, "Failed to create brick!\n");
		}
		
		for (int i = n; i < 32; i++)
		{
			arr[i] = NULL;
		}
	};

	int getNum()
	{
		return num;
	}

	~ArrayOfBricks();
};

