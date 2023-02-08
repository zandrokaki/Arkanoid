#pragma once

#include "Framework.h"
#include "PowerUp.h"

PowerUp::PowerUp(int posx, int posy, int s_w, int s_h, PowerUpType inputType)
{
	if (inputType == PowerUpType::fast)
		sprite = createSprite("data/fast.png");
	else if (inputType == PowerUpType::slow)
		sprite = createSprite("data/slow.png");
	else
		sprite = createSprite("data/gun.png");

	SetSize(s_w * 100 / 1920, s_h * 100 / 1080);
	getSpriteSize(sprite, width, height);
	x = posx;
	y = posy;

	type = inputType;

}

PowerUp::~PowerUp()
{
	destroySprite(sprite);
}

void PowerUp::Fall()
{
	y += 2;
} 

bool PowerUp::CheckDownCollision(int s_h)
{
	bool collision = false;

	if (y + height / 2 > s_h)
		collision = true;
	else
		collision = false;

	return collision;
}

/* ------- Getters -------*/
PowerUpType PowerUp::GetType(){ return type; }

