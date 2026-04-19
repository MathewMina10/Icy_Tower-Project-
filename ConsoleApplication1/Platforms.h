#pragma once
#include<iostream>
#include<vector>
#include "player.h"
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
using namespace std;
using namespace sf;
const int PLATFORM_COUNT = 200;
struct Platform
{
	Sprite sprite;
};
extern Platform platform[PLATFORM_COUNT];
void background(Sprite& backgroundSprite, Texture& backgroundTexture, RenderWindow& window);
void wallssprite(Sprite& leftWall, Sprite& rightWall, Texture& leftwalltexture, Texture& rightwallTexture, RenderWindow& window, float& widthWall);
void platformsTextures(Platform platforms[], int count, Texture& platformTexture, float wallWidth, RenderWindow& window);