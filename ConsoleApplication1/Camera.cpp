#include "Camera.h"
#include<iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
void Camera::camera_stuff(float width, float height)
{
    view.setSize(width, height);
    view.setCenter(width / 2.f, height / 2.f);

    highestY = 0.f;
    offsetY = 180.f;
    cameraSpeed = 0.12f;
    deadZone = 50.f;
}

void Camera::camera_control(float playerY)
{
    float currentY = view.getCenter().y;

    // Track highest reached position
    if (playerY < highestY)
        highestY = playerY;

    float triggerLine = currentY - deadZone;

    if (playerY < triggerLine)
    {
        float targetY = highestY + offsetY;

        // Only move camera UP (Icy Tower behavior)
        if (targetY < currentY)
        {
            float newY = currentY + (targetY - currentY) * cameraSpeed;
            view.setCenter(view.getCenter().x, newY);
        }
    }
}
