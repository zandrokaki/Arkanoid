#pragma once


#include "MasterSprite.h"

class Platform : public MasterSprite 
{

public:

	/*
	* @brief Default Constructor
	*/
	Platform();

	/*
	* @brief Constructor
	* @param x: x-coordinate to set the platform
	* @param y: y-coordinate to set the platform
	* @param s_w: screen witdh to scale
	* @param s_h: screen height to scale 
	*/
	Platform(int x, int y, int s_w, int s_h);

	/*
	* @brief Destructor
	*/
	~Platform();

	/*
	* @brief Moves the platform to the left
	*/
	void MoveLeft();

	/*
	* @brief Moves the platform to the right
	*/
	void MoveRight();

	/*
	* @brief Stop the platform left movement instantly
	*/
	void StopMoveLeft();

	/*
	* @brief Stop the platform right movement instantly
	*/
	void StopMoveRight();

	/*
	* @brief Moves the platform and check if it collides with screen sides
	* @param moveBall (Output): if the platfom collides with screen sides, change this to true
	* @param s_w: width of the screen
	*/
	void Move(bool &moveBall, int s_w);

	/*
	* @brief Shoot the ball to the target point
	* @param targetX: X coordinate of the target point
	* @param targetY: Y coordinate of the target point
	* @return If ball was shot or not
	*/
	bool ShootBall(double targetX, double targetY);

	/*
	* @brief Moves the ball with the platform at the beginning of the game
	* @param speed: speed to move the ball with the platform
	*/
	void MoveBall(double speed);

	/*
	* @brief Applies a power up to the platform
	* @param p_up: power up to apply
	*/
	void ApplyPowerUp(class PowerUp* p_up);

	/*
	* @brief Gets a pointer of the ball
	*/
	class Ball* GetBall();

	/*
	* @brief Gets left speed of the platform
	*/
	int GetLeftSpeed();

	/*
	* @brief Gets right speed of the platform
	*/
	int GetRightSpeed();

	/*
	* @brief Gets platform speed
	*/
	int GetSpeed();

	/*
	* @brief Gets if platform has the gun
	*/
	bool HaveGun();

	/*
	* @brief Gets speed increase of the platform
	*/
	double GetIncreaseSpeed();

	/*
	* @brief Sets platform speed
	*/
	void SetSpeed(int newSpeed);

	/*
	* @brief Sets speed increase of the platform
	*/
	void SetIncreaseSpeed(double newInc);

	/*
	* @brief Sets the gun of the platform
	*/
	void SetHaveGun(bool newHG);

private:
	double speedIncrease;			// Speed Increase
	const int speed = 7;			// Constant speed
	int leftSpeed, rightSpeed;		// Left and right speed
	class Ball* ball;				// Ball
	bool haveGun;					// Check if platform can shoot bullets
};