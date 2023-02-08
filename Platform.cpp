#pragma once

#include <iostream>
#include "MasterSprite.h"
#include "Framework.h"
#include "PowerUp.h"
#include "Ball.h"
#include "Platform.h"

Platform::Platform()
{
	leftSpeed = 0;
	rightSpeed = 0;
	speedIncrease = 1.0;
	ball = nullptr;
	haveGun = false;
}

Platform::Platform(int posx, int posy, int s_w, int s_h)
{
	sprite = createSprite("data/platform.png");
	getSpriteSize(sprite, width, height);
	x = posx;
	y = posy;
	ball = new Ball(x, y - height / 3 - 5, s_w, s_h);
	leftSpeed = 0;
	rightSpeed = 0;
	speedIncrease = 1.0;
	haveGun = false;
}

Platform::~Platform()
{
	destroySprite(sprite);
}

void Platform::MoveLeft()
{
	leftSpeed = -speed * speedIncrease;
}

void Platform::MoveRight()
{
	rightSpeed = speed * speedIncrease;
}
void Platform::StopMoveLeft()
{
	leftSpeed = 0;
}

void Platform::StopMoveRight()
{
	rightSpeed = 0;
}

void Platform::Move(bool &moveBall, int s_w)
{
	double leftSide = x - width / 2;
	double rightSide = x + width / 2;

	// Check if the platform is colliding with the screen
	moveBall = leftSide >= 0 && rightSide < s_w;

	x += rightSpeed;
	x += leftSpeed;
	
	if (leftSide < 0)
	{
		StopMoveLeft();
	}

	if (rightSide > s_w)
	{
		StopMoveRight();
	}

	ball->Move();
}

bool Platform::ShootBall(double targetX, double targetY)
{
	// Avoid clicks on the platform
	if ((targetX > x - width/2 && targetX < x + width/2) 
		&& (targetY > y - height/2 && targetY < y + height/2))
	{
		return false;
	}

	ball->Shoot(targetX, targetY);

	return true;
}

void Platform::MoveBall(double speed)
{
		ball->SetSpeedX(speed);
		ball->SetX(ball->GetX() + ball->GetSpeedX());
}

void Platform::ApplyPowerUp(PowerUp* p_up)
{
	if (p_up->GetType() == PowerUpType::fast)
	{
		if (speedIncrease * speed < speed * 2)
			speedIncrease *= 1.5;
		else
			speedIncrease = 2.0;

	}
	else if (p_up->GetType() == PowerUpType::slow)
	{
		if (speedIncrease * speed > speed / 2)
			speedIncrease /= 1.2;
		else
			speedIncrease = 0.5;
	}
	else
	{
		haveGun = true;
	}
}

/* ------- Getters -------*/
Ball* Platform::GetBall(){ return ball; }
int Platform::GetLeftSpeed(){ return leftSpeed; }
int Platform::GetRightSpeed(){ return rightSpeed; }
int Platform::GetSpeed() { return speed; }
double Platform::GetIncreaseSpeed() { return speedIncrease; }
bool Platform::HaveGun() { return haveGun; }

/* ------- Setters -------*/
void Platform::SetSpeed(int newSpeed){ speedIncrease = newSpeed; }
void Platform::SetIncreaseSpeed(double newInc){ speedIncrease = newInc; }
void Platform::SetHaveGun(bool newHG) { haveGun = newHG; }

