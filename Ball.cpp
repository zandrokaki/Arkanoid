#pragma once

#include <Windows.h>
#include <iostream>
#include <stdlib.h>    
#include <vector>
#include "Framework.h"
#include "SpeedZone.h"
#include "Brick.h"
#include "Ball.h"

Ball::Ball()
{
	speedIncrease = 1;
	speedX = 0;
	speedY = 0;
	radius = 0;
}

Ball::Ball(int posx, int posy, int s_w, int s_h)
{
	sprite = createSprite("data/ball.png");
	SetSize(s_w * 35 / 1920, s_h * 35 / 1080);
	getSpriteSize(sprite, width, height);
	x = posx;
	y = posy;

	speedX = 0;
	speedY = 0;
	speedIncrease = 1;
	
	if (width == height)
		radius = height / 2.0;
	else radius = 0;
}

Ball::~Ball()
{
	destroySprite(sprite);
}

bool Ball::Shoot(double targetX, double targetY)
{
	double absolute;

	// Calculate distance to target point
	speedX = targetX - x;
	speedY = targetY - y;
	absolute = abs(speedX) + abs(speedY);
	absolute = speed / absolute;
	speedX *= absolute;
	speedY *= absolute;

	return true;
}

void Ball::Move()
{
	x += speedIncrease*speedX;
	y += speedIncrease*speedY;
}

void Ball::CheckBouncePlatform(double p_x, double p_y, double p_w, double p_h, bool noBricks, bool& win)
{
	if (y + radius < p_y + (p_h / 2) + SAFE && y + radius > p_y - (p_h / 2) - SAFE
		&& x + radius  < p_x + (p_w / 2) + SAFE && x + radius > p_x - (p_w / 2) - SAFE)
	{
		/*if ((x + radius > p_x - p_w / 2 && y + radius > p_y - p_h / 2) ||
			(x - radius < p_x + p_w / 2 && y + radius > p_y - p_h / 2))
		{
			speedX *= -1;
		}*/

		speedY *= -1;

		if (noBricks)
			win = true;
	}
}

void Ball::CheckScreenCollision(double s_w, double s_h, bool& lost)
{
	if (y - radius < SAFE)	// Bounce up side
	{
		y += SAFE + 1;
		speedY *= -1;
	}

	if (x + radius > s_w - SAFE || x - radius < SAFE)	// Bounce left & right sides
	{
		if (speedX > 0)
			x -= SAFE+1;
		else
			x += SAFE+1;

		speedX *= -1;
	}

	if (y + radius > s_h - SAFE)
		lost = true;
}

void Ball::CheckSpeedZoneCollision(std::vector<SpeedZone*> zones)
{
	bool collision = false;

	for (auto zone : zones)
	{
		int z_x = zone->GetX();
		int z_y = zone->GetY();
		int z_w = zone->GetWidth();
		int z_h = zone->GetHeight();

		if (y + radius < z_y + (z_h / 2) + SAFE && y + radius > z_y - (z_h / 2) - SAFE
			&& x + radius  < z_x + (z_w / 2) + SAFE && x + radius > z_x - (z_w / 2) - SAFE)
		{

			if (zone->GetType() == ZoneType::speedUp)
			{
				speedIncrease = 1.5;
			}
			else
			{
				speedIncrease = 0.5;
			}

			collision = true;
		}
		else
		{
			speedIncrease = 1;
		}

		if (collision)
			break;
	}
}

/* ------- Setters -------*/
void Ball::SetSpeedX(double newX){ speedX = newX; }
void Ball::SetSpeedY(double newY){ speedY = newY; }

/* ------- Getters -------*/
double Ball::GetSpeedX(){ return speedX; }
double Ball::GetSpeedY(){ return speedY; }
double Ball::GetRadius(){ return radius; }





