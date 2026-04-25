#include<iostream>
#include<vector>
#include "player.h"
#include "Platforms.h"
#include "Camera.h"
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
using namespace std;
using namespace sf;
int main()
{
    Camera camera;
    anim a;
    start(a);
    // window stuff
    RenderWindow window(VideoMode(1920, 1080), "Icy Tower", Style::Titlebar | Style::Close | Style::Resize);
    Event event;
    player p;
    camera.camera_stuff(1920.f, 1080.f);
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
    Clock clock;
    //game loop
    while (window.isOpen())
    {
        //deltatime
        p.dt = clock.restart().asSeconds();
        p.lastland += p.dt;

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
        playermovement(p, p.dt);
        playerphysics(p, p.dt);
        playermove(p, p.dt);
        collision(p, platformlist);
        update(a, p, p.dt);

        //camera stuff
        camera.camera_control(p.body.getPosition().y);

        //Render
        window.clear();
        window.setView(window.getDefaultView());
        //draw your game 
        window.draw(backgroundSprite);
        window.setView(camera.view);

        window.draw(leftWall);
        window.draw(rightWall);
        for (int i = 0; i < PLATFORM_COUNT; i++)
            window.draw(platformlist[i].sprite);
        window.draw(a.mary);
        window.display();
    }
    // end of application
    return 0;
}
