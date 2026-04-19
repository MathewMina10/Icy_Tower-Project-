#include "Platforms.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <SFML/Audio.hpp>
#include <iomanip>
#include <cstdlib>   // for rand()
#include <ctime>
using namespace std;
using namespace sf;
void background(Sprite& backgroundSprite, Texture& backgroundTexture, RenderWindow& window) {
	backgroundTexture.loadFromFile("BackGround game1.png");
	backgroundSprite.setTexture(backgroundTexture);

	// Scale background to window size
	float backgroundscaleX = float(window.getSize().x) / backgroundTexture.getSize().x;
	float backgroundscaleY = float(window.getSize().y) / backgroundTexture.getSize().y;
	backgroundSprite.setScale(backgroundscaleX, backgroundscaleY);
}
void wallssprite(Sprite& leftWall, Sprite& rightWall, Texture& leftwalltexture, Texture& rightwallTexture, RenderWindow& window, float& wallWidth) {
	leftwalltexture.loadFromFile("wall11.png");
	rightwallTexture.loadFromFile("wall2.png");




	leftWall.setTexture(leftwalltexture);
	rightWall.setTexture(rightwallTexture);

	wallWidth = 200; // width of walls

	float scaleLeftX = wallWidth / leftwalltexture.getSize().x;
	float scaleRightX = wallWidth / rightwallTexture.getSize().x;
	float scaleY = float(window.getSize().y) / leftwalltexture.getSize().y;

	leftWall.setScale(scaleLeftX, scaleY);
	rightWall.setScale(scaleRightX, scaleY);

	leftWall.setPosition(0, 0);
	rightWall.setPosition(window.getSize().x - wallWidth, 0);
}
void platformsTextures(Platform platforms[], int count, Texture& platformTexture, float wallWidth, RenderWindow& window) {
	platformTexture.loadFromFile("Stair3.png");
	const float verticalSpacing = 80.0f;
	const float maxJumpX = 600.0f;
	float previousX = window.getSize().x / 2.0f;

	for (int i = 0; i < PLATFORM_COUNT; i++)
	{
		platforms[i].sprite.setTexture(platformTexture);

		// Random width scale
		float platformScaleX = 1.5f + static_cast<float>(rand()) / RAND_MAX; // 0.5 - 1.5
		platforms[i].sprite.setScale(platformScaleX, 1.0f);
		float platformWidth = platformTexture.getSize().x * platformScaleX;
		float center = window.getSize().x / 2.0f;
		previousX = previousX * 0.8f + center * 0.2f;
		// Random horizontal shift within max jump distance
		float dx = (static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f) * maxJumpX;
		float x = previousX + dx;
		float maragin = 20.0f;
		// Clamp X so platform stays inside walls
		x = max(wallWidth + maragin, min(x, window.getSize().x - wallWidth - platformWidth - maragin));
		// Random horizontal shift within max jump distance


		// place platforms upward with equal vertical spacing 
		float y = 1000 - i * verticalSpacing;

		platforms[i].sprite.setPosition(x, y);

		previousX = x;
	}
}
