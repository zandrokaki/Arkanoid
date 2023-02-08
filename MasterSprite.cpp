#pragma once

#include "Framework.h"
#include "MasterSprite.h"

MasterSprite::MasterSprite()
{
	x = 0;
	y = 0;
	width = 0;
	height = 0;
}


MasterSprite::MasterSprite(const char* path, int posx, int posy)
{
	sprite = createSprite(path);
	getSpriteSize(sprite, width, height);

	x = posx;
	y = posy;
}

void MasterSprite::Draw()
{
	getSpriteSize(sprite, width, height);
	drawSprite(sprite, x - width / 2, y - height / 2);
}

bool MasterSprite::CheckPlatformCollision(int p_x, int p_y, int p_w, int p_h)
{
	bool collision = false;

	if (y + height / 2 < p_y + (p_h / 2) && y + height / 2 > p_y - (p_h / 2)
		&& x + width / 2 < p_x + (p_w / 2) && x + width / 2 > p_x - (p_w / 2))
	{
		collision = true;
	}

	return collision;
}

void MasterSprite::SetSize(int w, int h)
{
	setSpriteSize(sprite, w, h);
	getSpriteSize(sprite, w, h);
}

/* ------- Getters -------*/
int MasterSprite::GetX() { return x; }
int MasterSprite::GetY() { return y; }
int MasterSprite::GetHeight() { return height; }
int MasterSprite::GetWidth() { return width;  }
Sprite* MasterSprite::GetSprite() { return sprite;  }

/* ------- Setters -------*/
void MasterSprite::SetX(int newX) { x = newX; }
void MasterSprite::SetY(int newY) { y = newY; }

