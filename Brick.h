#pragma once

#include "MasterSprite.h"

/* ------- Type of brick collision ------- */
enum class BrickCollision 
{
	vertical,		// Vertical collision
	horizontal,		// Horizontal collision
	both,			// Horizontal and Vertical collision
	nothing			// No collision
};
/* --------------------------------------- */

class Brick : public MasterSprite
{
public:

	/*
	* @brief Constructor
	* @param x: x-coordinate to set the brick (position)
	* @param y: y-coordinate to set the brick (position)
	* @param s_w: screen width to scale the brick
	* @param s_h: screen height to scale the brick
	*/
	Brick(int x, int y, int s_w, int s_h);

	/*
	* @brief Destructor
	*/
	~Brick();

	/*
	* @brief Checks if the ball collides with a brick
	* @param ball: ball to check collision
	* @param x: ball x-coordinate
	* @param y: ball y-coordinate
	* @return true if brick is destroyed
	*/
	bool CheckBrickCollision(class Ball* ball, double x, double y);

	/*
	* @brief Checks if a bullet collides with a brick
	* @param bullet: bullet to check collision
	* @param x: bullet x-coordinate
	* @param y: bullet y-coordinate
	* @return true if brick is destroyed
	*/
	bool CheckBulletCollision(class Bullet* bullet, int x, int y);

	/*
	* @brief Drops the brick on y-axis
	*/
	void Fall();

	/*
	* @brief Checks if the brick collides with down side of the screen
	* @param s_h: screen height
	* @return True if the sprite falls into the void
	*/
	bool Brick::CheckDownCollision(int s_h);

	/*
	* @brief Checks if the brick is destroyed
	* @return true if bricks is destroyed
	*/
	bool isDestroyed();

	/*
	* @brief Sets brick speed on y-axis
	*/
	void SetSpeed(double newS);


private:
	bool is_destroyed;		// Brick state in-game
	double speed;			// Brick speed on y-axis (fall)
};
