#include<iostream>
#include<vector>
#include "player.h"
#include "Platforms.h"
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
using namespace std;
using namespace sf;

int main()
{
    // window stuff
    RenderWindow window(VideoMode(1920, 1080), "Icy Tower", Style::Titlebar | Style::Close | Style::Resize);
    Event event;
    player p;
    playerinfo(p);

    // background
    Texture backgroundTexture;
    Sprite backgroundSprite;
    background(backgroundSprite, backgroundTexture, window);

    //walls
    Texture leftWallTexture, rightWallTexture;
    Sprite leftWall, rightWall;
    float wallWidth;
    wallssprite(leftWall, rightWall, leftWallTexture, rightWallTexture, window, wallWidth);


    //platforms 
    const int PLATFORM_COUNT = 200;
    Platform platformlist[PLATFORM_COUNT];
    Texture platformTexture;
    platformsTextures(platformlist, PLATFORM_COUNT, platformTexture, wallWidth, window);

    //game loop
    while (window.isOpen())
    {
        //Event
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape)
                    window.close();
            }
        }
        //Update
        playermovement(p);
        playerphysics(p);
        playermove(p);
        walls(p, platformlist);

        //Render
        window.clear();
        //draw your game 
        window.draw(backgroundSprite);
        window.draw(leftWall);
        window.draw(rightWall);
        for (int i = 0; i < PLATFORM_COUNT; i++)
            window.draw(platformlist[i].sprite);
        playerdraw(p, window);
        /*for (auto& p : platforms)
        {
            window.draw(p);
        }*/
        window.display();
    }
    // end of application
    return 0;
}
