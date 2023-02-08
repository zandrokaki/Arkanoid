#pragma once

#include "Framework.h"
#include "Bullet.h"

Bullet::Bullet(int posx, int posy, int s_w, int s_h)
{
	sprite = createSprite("data/bullet.png");
	SetSize(s_w * 20 / 1920, s_h * 50 / 1080);
	getSpriteSize(sprite, width, height);
	x = posx;
	y = posy;
}

Bullet::~Bullet()
{
	destroySprite(sprite);
}

void Bullet::Shoot()
{
	y -= speed;
}

void Bullet::Ready(int posx, int posy)
{
	x = posx;
	y = posy;
}

bool Bullet::CheckUpCollision()
{
	bool collision = false;

	if (y - height/2 < 0)	
	{
		collision = true;
	}

	return collision;
}


