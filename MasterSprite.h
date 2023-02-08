#pragma once


class MasterSprite {

public:

	/*
	* @brief Default constructor
	*/
	MasterSprite();

	/*
	* @brief Constructor
	* @param path: path of the sprite to load
	* @param x: x-coordinate to set the sprite
	* @param y: y-coordinate to set the sprite
	*/
	MasterSprite(const char* path, int x, int y);

	/*
	* @brief Draws the sprite
	*/
	void Draw();

	/*
	* @brief Checks if the sprite collides with the platform
	* @param x: x-coordinate of the platform
	* @param y: y-coordinate of the platform
	* @param w: width of the platform
	* @param h: height of the platform
	*/
	bool CheckPlatformCollision(int x, int y, int w, int h);

	/*
	* @brief Sets the sprite size
	* @param w: new width
	* @param h: new height
	*/
	void SetSize(int w, int h);

	/*
	* @brief Gets x-coordinate of the sprite
	*/
	int GetX();

	/*
	* @brief Gets y-coordinate of the sprite
	*/
	int GetY();

	/*
	* @brief Gets height of the sprite
	*/
	int GetHeight();

	/*
	* @brief Gets width of the sprite
	*/
	int GetWidth();

	/*
	* @brief Gets a pointer to the sprite
	*/
	class Sprite* GetSprite();

	/*
	* @brief Sets x-coordinate of the sprite
	*/
	void SetX(int newX);

	/*
	* @brief Sets y-coordinate of the sprite
	*/
	void SetY(int newY);

protected:

	class Sprite* sprite;		// Sprite to draw
	int x, y;					// x and y coordinates of the sprite
	int width, height;			// Width and height of the sprite
	const double SAFE = 5;		// Safe pixels zone to avoid overlapping

};
