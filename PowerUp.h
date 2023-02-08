#pragma once
#include "MasterSprite.h"

/* ------- Type of power up ------- */
enum class PowerUpType
{
	slow,		// Decrease speed
	fast,		// Increase speed
	gun			// Shoot bullets
};
/* -------------------------------- */

class PowerUp : public MasterSprite
{
public:

	/*
	* @brief Constructor
	* @param x: x-coordinate to set the powerup (position)
	* @param y: y-coordinate to set the powerup (position)
	* @param s_w: screen width to scale the powerup
	* @param s_h: screen height to scale the powerup
	* @param type: type of the powerup
	*/
	PowerUp(int x, int y, int s_w, int s_h, PowerUpType type);

	/*
	* @brief Destructor
	*/
	~PowerUp();

	/*
	* @brief Drops the power up 
	*/
	void Fall();

	/*
	* @brief Checks if the power up collides with down side of the screen
	* @param s_h: screen height
	* @return True if the sprite falls into the void
	*/
	bool CheckDownCollision(int s_h);

	/*
	* @brief Gets the power up type
	*/
	PowerUpType GetType();

private:
	PowerUpType type;		// Power up type
};
