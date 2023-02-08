#pragma once

#include <vector>
#include "MasterSprite.h"

class Ball : public MasterSprite
{

public:

	/*
	* @brief Default constructor
	*/
	Ball();

	/*
	* @brief Constructor
	* @param x: x-coordinate to set the ball (position)
	* @param y: y-coordinate to set the ball (position)
	* @param s_w: screen witdh to scale the ball
	* @param s_h: screen height to scale the ball
	*/
	Ball(int x, int y, int s_w, int s_h);

	/*
	* @brief Destructor
	*/
	~Ball();

	/*
	* @brief Shoots the ball to the target point
	* @param x: x-coordinate from the target point
	* @param y: y-coordinate from the target point
	* @return If ball was shot or not
	*/
	bool Shoot(double x, double y);

	/*
	* @brief Moves the ball around the screen
	*/
	void Move();

	/*
	* @brief Checks if the ball has to bounce in the platform and if is the last bounce
	* @param p_x: x-coordinate of the platform
	* @param p_y: y-coordinate of the platform
	* @param p_w: width of the platform
	* @param p_h: height of the platform
	* @param noBricks: check if there are no bricks alive
	* @param win (Output): if there are no bricks alive, change this to true
	*/
	void CheckBouncePlatform(double p_x, double p_y, double p_w, double p_h, bool noBricks, bool &win);

	/*
	* @brief Checks if the ball collides with the screen
	* @param s_w: Screen width
	* @param s_h: Screen height
	* @param lost (Output): if the ball collides with down side, change this to true
	*/
	void CheckScreenCollision(double s_w, double s_h, bool &lost);

	/*
	* @brief Checks if the ball overlaps with any SpeedZone from the level and changes the ball speed
	* @param zones: Vector that contains all SpeedZones of the level
	*/
	void CheckSpeedZoneCollision(std::vector<class SpeedZone*> zones);

	/*
	* @brief Sets ball speed in x-axis
	*/
	void SetSpeedX(double newX);

	/*
	* @brief Sets ball speed in y-axis
	*/
	void SetSpeedY(double newY);

	/*
	* @brief Gets ball speed in x-axis
	*/
	double GetSpeedX();

	/*
	* @brief Gets ball speed in y-axis
	*/
	double GetSpeedY();

	/*
	* @brief Gets ball radius
	*/
	double GetRadius();

private:
	double speedX;			 // Ball speed in x-axis
	double speedY;			 // Ball speed in y-axis
	const double speed = 10; // Ball constant speed		
	double speedIncrease;	 // Amount of speed increase to apply to the ball
	double radius;			 // Ball radius
};
