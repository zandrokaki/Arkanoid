#pragma once

#include "Framework.h"
#include "SpeedZone.h"

SpeedZone::SpeedZone(int posx, int posy, int s_w, int s_h, ZoneType inputType)
{
	if (inputType == ZoneType::speedUp)
		sprite = createSprite("data/speedGreen.png");
	else
		sprite = createSprite("data/speedRed.png");

	SetSize(s_w * 500 / 1920, s_h * 100 / 1080);
	getSpriteSize(sprite, width, height);
	x = posx;
	y = posy;

	type = inputType;
}

SpeedZone::~SpeedZone()
{
	destroySprite(sprite);
}

/* ------- Getters -------*/
ZoneType SpeedZone::GetType(){ return type; }