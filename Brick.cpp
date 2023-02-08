#pragma once

#include <iostream>
#include "Framework.h"
#include "Ball.h"
#include "Bullet.h"
#include "Brick.h"

Brick::Brick(int posx, int posy, int s_w, int s_h)
{
	sprite = createSprite("data/normal_brick.png");
	SetSize(s_w*150/1920, s_h*70/1080);
	getSpriteSize(sprite, width, height);
	x = posx;
	y = posy;
	speed = 1.0;
	is_destroyed = false;
}

Brick::~Brick()
{
	destroySprite(sprite);
}

bool Brick::CheckBrickCollision(Ball* ball, double xBall, double yBall)
{
	double radius = ball->GetRadius();
	BrickCollision collision = BrickCollision::nothing;

	if (!ball)
		return false;

	// Vertical collision
	if (((x + width / 2 > xBall - radius - SAFE) && (x - width / 2 < xBall + radius + SAFE))
		&& (y - height / 2 <= yBall + radius - SAFE) && (y + height / 2 >= yBall - radius + SAFE))
	{
		collision = BrickCollision::vertical;
		ball->SetSpeedX(ball->GetSpeedX() * -1);
	}

	// Horizontal and Both collisions
	if (((y + height / 2 > yBall - radius - SAFE) && (y - height / 2 < yBall + radius + SAFE))
		&& (x - width / 2 <= xBall + radius - SAFE) && (x + width / 2 >= xBall - radius + SAFE))
	{
		if (collision == BrickCollision::vertical)
		{
			ball->SetSpeedY(ball->GetSpeedY() * -1);
			ball->SetSpeedX(ball->GetSpeedX() * -1);
		}
		else
		{
			collision = BrickCollision::horizontal;
			ball->SetSpeedY(ball->GetSpeedY() * -1);
		}
	}

	if (collision!=BrickCollision::nothing)
		is_destroyed = true;

	return is_destroyed;
}

bool Brick::CheckBulletCollision(Bullet* bullet, int b_x, int b_y)
{

	if (((y + height / 2 > b_y - bullet->GetHeight()/2 - SAFE) && (y - height / 2 < b_y + bullet->GetHeight()/2 + SAFE))
		&& (x - width / 2 <= b_x + bullet->GetWidth()/2 - SAFE) && (x + width / 2 >= b_x - bullet->GetWidth()/2 + SAFE))
	{
		is_destroyed = true;
	}

	return is_destroyed;
}

void Brick::Fall()
{
	y += speed;
}

bool Brick::CheckDownCollision(int s_h)
{
	bool collision = false;

	if (y + height / 2 > s_h)
	{
		is_destroyed = true;
		collision = true;
	}else
		collision = false;

	return collision;
}

/* ------- Getters -------*/
bool Brick::isDestroyed(){ return is_destroyed; }

/* ------- Setters -------*/
void Brick::SetSpeed(double newS){ speed = newS; }