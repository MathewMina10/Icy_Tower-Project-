#pragma once
#include<iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
using namespace std;
using namespace sf;
struct Platform;
struct player
{
    RectangleShape body;
    Vector2f velocity;
    float gravity;
    float movespeed;
    float jumppower;
    bool isonground;
    float dt;
};
void playerinfo(player& player);
void playermovement(player& player);
void playerphysics(player& player);
void playermove(player& player);
void playerdraw(player& player, RenderWindow& window);
void walls(player& p, Platform platformlist[]);