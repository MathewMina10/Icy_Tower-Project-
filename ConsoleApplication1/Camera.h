#pragma once
#include<iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
using namespace std;
using namespace sf;
struct Camera
{
    View view;

    float highestY;
    float offsetY;
    float cameraSpeed;
    float deadZone;

    void camera_stuff(float width, float height);

    void camera_control(float playerY);
};