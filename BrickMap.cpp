#pragma once

#include <iostream>
#include <vector>
#include <random>
#include "Ball.h"
#include "Bullet.h"
#include "BrickMap.h"


BrickMap::BrickMap(int fil, int col, int s_w, int s_h)
{
	int margin = s_w * 10 / 1920;
	int marginVert = s_h * 60 / 1080;
	Brick* tempBrick;

	files = fil;
	cols = col;

	for (int i = 1; i <= files; ++i)
	{
		std::vector <Brick*> temp;

		for (int j = 1; j <= cols; ++j)
		{
			tempBrick = new Brick(margin+j*(s_w * 150 / 1920), marginVert+i*(s_h * 70 / 1080), s_w, s_h);
			temp.push_back(tempBrick);
		}

		bricks.push_back(temp);
	}

	brickNumber = files * cols;
}

void BrickMap::DrawBrickMap()
{
	for (int i = 0; i < bricks.size(); ++i)
	{
		
		for (int j = 0; j < bricks[i].size(); ++j)
		{
			if (!bricks[i][j]->isDestroyed())
				bricks[i][j]->Draw();
			else
			{
				bricks[i].erase(bricks[i].begin() + j);
			}
		}
	}
}

Brick* BrickMap::SelectBrickToFall()
{
	Brick* brickToFall = nullptr;
	int max = 0;
	int pos = 0;

	if (bricks[files - 1].size() > 0)
	{
		max = bricks[files - 1].size() - 1;
		if (max > 1)
			pos = rand() % max;

		if (bricks[files - 1][pos])
		{
			bricks[files - 1][pos]->SetSpeed(3.0);
			brickToFall = bricks[files - 1][pos];
		}
	}

	return brickToFall;
}

Brick* BrickMap::CheckBricksMapCollision(Bullet* bullet ,Ball* ball)
{
	Brick* brick = nullptr;

	for (int i = 0; i < bricks.size(); ++i)
	{
		for (int j = 0; j < bricks[i].size(); ++j)
		{
			if (bricks[i][j])
			{
				if ((ball && bricks[i][j]->CheckBrickCollision(ball,ball->GetX(), ball->GetY()))
				   || ((bullet && bricks[i][j]->CheckBulletCollision(bullet, bullet->GetX(), bullet->GetY()))))
				{
					brick = bricks[i][j];
					bricks[i].erase(bricks[i].begin() + j);
				}	
			}
		}
	}

	return brick;
}

/* ------- Getters -------*/
int BrickMap::GetFils(){ return files; }
int BrickMap::GetCols(){ return cols; }
int BrickMap::GetBricksNumber(){ return brickNumber; }



