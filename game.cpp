#pragma once


#include <iostream>
#include <string>
#include <random>
#include <thread>
#include <Windows.h>
#include "MasterSprite.h"
#include "PowerUp.h"
#include "SpeedZone.h"
#include "Ball.h"
#include "Bullet.h"
#include "BrickMap.h"
#include "Framework.h"


/* Test Framework realization */
class MyFramework : public Framework {

public:

	MyFramework(int w, int h, bool fs) : inputWidth(w), inputHeight(h), inputFullscreen(fs) {}

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = inputWidth;
		height = inputHeight;
		fullscreen = inputFullscreen;

		if (fullscreen)
		{
			width = 3840;
			height = 2160;
		}	
	}

	// Initialize all variables
	virtual bool Init()
	{
		getScreenSize(screenWidth, screenHeight);
		platform = std::make_unique<Platform>(screenWidth/2, screenHeight - (screenHeight * 50) / 1080, screenWidth, screenHeight);
		bricks = std::make_unique<BrickMap>(2, 12, screenWidth, screenHeight);
		speedZone = new SpeedZone(screenWidth * 300 / 1920, screenHeight * 700 / 1080, screenWidth, screenHeight, ZoneType::speedUp);
		speedZoneSlow = new SpeedZone(screenWidth * 1600 / 1920, screenHeight * 400 / 1080, screenWidth, screenHeight, ZoneType::speedDown);
		winSprite = createSprite("data/win.png");
		looseSprite = createSprite("data/lost.png");
		speedZones.push_back(speedZone);
		speedZones.push_back(speedZoneSlow);
		platform->SetSize(screenWidth*250/1920, screenHeight * 50 / 1080);
		ball = platform->GetBall();
		score = 0;
		inGame = false;
		noBricks = false;
		win = false;
		lost = false;
		powerUp = nullptr;
		fallBrick = nullptr;
		bullet = nullptr;
		timer = 0;
		gunTimer = 0;
		
		return true;
	}

	virtual void Close() {
	}



	virtual bool Tick() {

		/* ----------------------------------------------------------------------------------- DRAW ----------------------------------------------------------------------------------------*/
		drawTestBackground();
		speedZones[0]->Draw();
		speedZones[1]->Draw();
		bricks->DrawBrickMap();
		ball->Draw();
		platform->Draw();
		/* --------------------*/
		
		/* ----------------------------------------------------------------------------- AIMING THE BALL -----------------------------------------------------------------------------------*/
		// Moves platform and ball
		platform->Move(moveBall, screenWidth);

		// If player has not shot the ball..
		if (!inGame)
		{
			// If the platform is colliding with the screen limits..
			if (!moveBall)
			{
				ball->SetSpeedX(0);		// Stop the ball over the platform
			}
			else
			{
															// If the platform is not colliding with the screen limits..
				ball->SetX(platform->GetX());				// "Attach" the ball to the platform
				ball->SetSpeedX(platform->GetSpeed());		// When player moves the platform, the ball moves with it
			}
		}

		/* ----------------------------------------------------------------------------------- GAME STARTS ----------------------------------------------------------------------------------*/

		/* ----------------------------------------------------------------------------------- BALL COLLISIONS ------------------------------------------------------------------------------*/

		// 1. Check if bounce with screen size. If platform could not catch the ball, lost is set to true
		ball->CheckScreenCollision(screenWidth, screenHeight, lost);

		// 2. Check if bounce with platform. If there are no bricks, win is set to true
		ball->CheckBouncePlatform(platform->GetX(), platform->GetY(), platform->GetWidth(), platform->GetHeight(), noBricks, win);

		// 3. Check if ball overlaps with a speed zone
		ball->CheckSpeedZoneCollision(speedZones);

		// 4. Check if the ball has collided with a brick and increases score
		if (bricks->CheckBricksMapCollision(nullptr, ball))
		{
			++score;
		}

		noBricks = (bricks->GetBricksNumber() == score);

		/* ----------------------------------------------------------------------------------- POWER UPS ------------------------------------------------------------------------------------*/
		// 5. Try to generate a power up 
		randomInterval = rand() % getTickCount() + getTickCount() / 2;
		randomX = rand() % (screenWidth + 50) + 50;
		randomY = rand() % (screenHeight - platform->GetHeight() - 300) + 50;

		if (!powerUp && randomInterval % 200 == 0 && inGame)
		{
			PowerUpType type = PowerUpType::fast;

			if (randomInterval % 150 == 0)
				type = PowerUpType::slow;
			else if (randomInterval % 175 == 0)
				type = PowerUpType::gun;

			powerUp = new PowerUp(randomX - 100, randomY - 100, screenWidth, screenHeight, type);
		}

		// 6. Check if platform catch the power up and modifies its speed or gives the gun to the player. Once the power up collides with screen down side or the platform,
		// its destroyed and the pointer is changed to null, saying to the game that can create another powerup
		if (powerUp)
		{
			powerUp->Draw();
			powerUp->Fall();

			if (powerUp->CheckPlatformCollision(platform->GetX(), platform->GetY(), platform->GetWidth(), platform->GetHeight()))
			{
				platform->ApplyPowerUp(powerUp);

				if (powerUp->GetType() == PowerUpType::slow || powerUp->GetType() == PowerUpType::fast)
					timer = 0;
				else
					gunTimer = 0;

				powerUp->~PowerUp();
				powerUp = nullptr;
			}
			else if (powerUp->CheckDownCollision(screenHeight))
			{
				powerUp->~PowerUp();
				powerUp = nullptr;
			}
		}

		// 7. Check if a bullet collides with a brick or with the screen. Like powerups, if the bullet collides, its pointer is set to null
		if (bullet)
		{
			bullet->Draw();
			bullet->Shoot();

			if (bricks->CheckBricksMapCollision(bullet, nullptr))
			{
					
				++score;

				bullet->~Bullet();
				bullet = nullptr;
				
			}
			else if (bullet->CheckUpCollision())
			{
				bullet->~Bullet();
				bullet = nullptr;
			}
		}

		// 8. Check if platform speed has been changed and, if that is true, increase the timer
		if (platform->GetSpeed() !=
			platform->GetSpeed() * platform->GetIncreaseSpeed())
		{
			++timer;
		}

		// 9. Check if has the gun and, if its true, increase the gun timer. This is done to separate both timers
		if (platform->HaveGun())
			++gunTimer;
			
		// 10. After 20 seconds, platform speed is set to its default value
		if (timer >= 2000)
			platform->SetIncreaseSpeed(1.0);

		// 11. After 10 seconds, gun disappear
		if (gunTimer >= 1000)
			platform->SetHaveGun(false);

		/* ----------------------------------------------------------------------------------- BRICKS FALL ------------------------------------------------------------------------------------*/

		// 12. Try to generate a brick to drop
		if (!fallBrick && randomInterval % 300 == 0 && bricks && inGame)
		{
			fallBrick = bricks->SelectBrickToFall();
		}

		// 13. Drops the brick. If collides with the platform, lost is set to true.
		// On the other hand, if the brick collides with screen down side, it is destroyed and score is increased
		if (fallBrick && !fallBrick->isDestroyed())
		{
			fallBrick->Fall();

			if (fallBrick->CheckPlatformCollision(platform->GetX(), platform->GetY(), platform->GetWidth(), platform->GetHeight()))
			{
				lost = true;
			}
			
			if (fallBrick->CheckDownCollision(screenHeight))
			{
				++score;
				fallBrick->~Brick();
				fallBrick = nullptr;
			}
		}


		/* ----------------------------------------------------------------------------------- WIN & LOOSE ------------------------------------------------------------------------------------*/
		// 14. If the player loses, restart
		if (lost)
		{
			//drawSprite(looseSprite, (screenWidth / 2) - (screenWidth * 500 / 1920) / 2, screenHeight / 2);
			Init();
		}

		// 12. If the player wins, restart
		if (win)
		{
			//drawSprite(winSprite, (screenWidth / 2) - (screenWidth * 500 / 1920) / 2, screenHeight/2);
			Init();
		}

		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative)
	{
		mouseX = x;
		mouseY = y;
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased)
	{
		switch (button)
		{
		case FRMouseButton::LEFT:

			// If the player has shot the ball, game starts
			if (!inGame && platform->ShootBall(mouseX, mouseY))
			{
				inGame = true;
			}

			// If there is no bullet in game and the player has the gun, invoke another bullet
			if (!bullet && platform->HaveGun() )
				bullet = new Bullet(platform->GetX(), platform->GetY() - platform->GetHeight() / 2 - 20, screenWidth, screenHeight);
	
			break;
		case FRMouseButton::MIDDLE:
			break;
		case FRMouseButton::RIGHT:
			break;
		case FRMouseButton::COUNT:
			break;
		default:
			break;
		}
	}

	virtual void onKeyPressed(FRKey k)
	{
			switch (k)
			{
			case FRKey::RIGHT:

				platform->MoveRight();

				// If the player has not shot the ball, it moves with the platform
				if (!inGame)
				{
					platform->MoveBall(platform->GetRightSpeed());
				}

				break;
			case FRKey::LEFT:

				platform->MoveLeft();

				// If the player has not shot the ball, it moves with the platform
				if (!inGame)
				{
					platform->MoveBall(platform->GetLeftSpeed());
				}

				break;
			case FRKey::DOWN:
				break;
			case FRKey::UP:
				break;
			case FRKey::COUNT:
				break;
			default:
				break;
			}
	}


	virtual void onKeyReleased(FRKey k)
	{
		switch (k)
		{
		case FRKey::RIGHT:

			platform->StopMoveRight();

			// If the player has not shot the ball, it stops with the platform
			if (!inGame)
			{
				platform->MoveBall(0);
			}
			
			break;
		case FRKey::LEFT:

			platform->StopMoveLeft();

			// If the player has not shot the ball, it stops with the platform
			if (!inGame)
			{
				platform->MoveBall(0);
			}
			
			break;
		case FRKey::DOWN:
			break;
		case FRKey::UP:
			break;
		case FRKey::COUNT:
			break;
		default:
			
			break;
		}
	}
	
	virtual const char* GetTitle() override
	{
		return "Arcanoid";
	}

private:
	int inputWidth;
	int inputHeight;
	int randomInterval, randomX, randomY;
	bool inputFullscreen;
	std::unique_ptr<Platform> platform;
	std::unique_ptr<BrickMap> bricks;
	Ball* ball;
	Brick* brickToDestroy;
	Brick* fallBrick;
	PowerUp* powerUp;
	Bullet* bullet;
	Sprite* winSprite;
	Sprite* looseSprite;
	SpeedZone* speedZone;
	SpeedZone* speedZoneSlow;
	std::vector<SpeedZone*> speedZones;
	bool inGame;
	int mouseX, mouseY;
	int screenWidth, screenHeight;
	int score;
	int timer, gunTimer;
	bool noBricks;
	bool win, lost;
	bool moveBall;
};

int main(int argc, char *argv[])
{
	int x = 1920;
	int y = 1080;
	bool fullscreen = false;
	
	if (strcmp(argv[1], "-window") == 0)
	{
		x = atoi(argv[2]);
		y = atoi(argv[3]);
	}
	else if (strcmp(argv[1], "-fullscreen") == 0)
	{
		fullscreen = true;
	}
	
	return run(new MyFramework(x, y, fullscreen));
}
