#pragma once

#include "MasterSprite.h"

/* ------- Type of Speed Zone ------- */
enum class ZoneType
{
	speedUp,		// Speed Up
	speedDown		// Slowdown
};
/* ---------------------------------- */

class SpeedZone : public MasterSprite
{
public:

	/*
	* @brief Constructor
	* @param x: x-coordinate to set the speed zone (position)
	* @param y: y-coordinate to set the speed zone (position)
	* @param s_w: screen width to scale the speed zone
	* @param s_h: screen height to scale the speed zone
	* @param type: type of the speedzone
	*/
	SpeedZone(int x, int y, int s_w, int s_h, ZoneType type);

	/*
	* @brief Destructor
	*/
	~SpeedZone();

	/*
	* @brief Gets the speed zone type
	*/
	ZoneType GetType();

private:
	ZoneType type;

};
