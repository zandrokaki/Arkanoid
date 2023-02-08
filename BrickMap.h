#pragma once
#include <vector>
#include "Brick.h"

class BrickMap
{

public:

	/*
	* @brief Constructor
	* @param files: number of files to construct the map
	* @param cols: number of columns to construct the map
	* @param s_w: screen width to scale the bricks
	* @param s_h: screen height to scale the bricks
	*/
	BrickMap( int files, int cols, int s_w, int s_h);

	/*
	* @brief Draw the bricks that are not destroyed
	*/
	void DrawBrickMap();

	/*
	* @brief Select a brick to drop
	* @return Brick to drop
	*/
	Brick* SelectBrickToFall();

	/*
	* @brief Checks if the ball or a bullet collides with any brick
	* @param ball: ball to check the collision
	* @param bullet: bullet to check the collision
	* @return Brick collided by the ball or by the bullet
	*/
	Brick* CheckBricksMapCollision(class Bullet* bullet, class Ball* ball);

	/*
	* @brief Gets number of files of the map
	*/
	int GetFils();

	/*
	* @brief Gets number of columns of the map
	*/
	int GetCols();

	/*
	* @brief Gets number of total bricks of the map
	*/
	int GetBricksNumber();

private:
	std::vector<std::vector <Brick*>> bricks;		// Stores the bricks
	int files, cols;								// Files and columns of the map
	int brickNumber;								// Total of bricks
	int index = 0;
};
