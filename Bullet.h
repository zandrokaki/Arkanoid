#pragma once

#include "MasterSprite.h"

class Bullet : public MasterSprite
{
public:

	/*
	* @brief Constructor
	* @param x: x-coordinate to set bullet (position)
	* @param y: y-coordinate to set the bullet (position)
	* @param s_w: screen witdh to scale bullet
	* @param s_h: screen height to scale the bullet
	*/
	Bullet(int x, int y, int s_w, int s_h);

	/*
	* @brief Destructor
	*/
	~Bullet();

	/*
	* @brief Moves the bullet 
	*/
	void Shoot();

	/*
	* @brief Sets the bullet above the platform, ready to be shot
	* @param x: x-coordinate to set the bullet
	* @param y: y-coordinate to set the bullet
	*/
	void Ready(int x, int y);

	/*
	* @brief Check if the bullet collides with screen height
	* @return true if the bullet collides with screen height
	*/
	bool CheckUpCollision();

	/*
	* @brief Check if the bullet collides with a brick
	* @return true if the bullet collides with a brick
	*/
	bool CheckBrickCollision();

private:
	const int speed = 10;      // Constant speed of the bullet

};
