#include "player.h"
#include "Platforms.h"
#include <cmath>
anim a;
//------------------------------------- Player -------------------------------------------------------//
void playerinfo(player& p) {
    p.body.setSize(Vector2f(50.f, 50.f));
    p.body.setFillColor(Color::Transparent);
    p.body.setOutlineThickness(0.25);
    p.body.setOutlineColor(Color::Green);
    p.body.setPosition(900.f, 1000.f);

    p.velocity = Vector2f(0.f, 0.f);
    p.gravity = 3500.f;
    p.movespeed = 2500.f;
    p.jumppower = -700.f;
    p.maxspeed = 850.f;
    p.friction = 0.97f;
    p.isonground = false;
    p.jumphold = false;
}

//--------------------------------

void playermovement(player& p, float dt)
{
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        p.velocity.x += p.movespeed * dt;
        a.ismoving = 1;
        p.body.setScale(1, 1);
    }
    else if (Keyboard::isKeyPressed(Keyboard::A)) {
        p.velocity.x -= p.movespeed * dt;
        a.ismoving = 1;
        p.body.setScale(-1, 1);
    }
    else {
        float slowdown = 1.f - (2.2f * dt);
        if (slowdown < 0) slowdown = 0;

        p.velocity.x *= slowdown;
    }

    // jump
    if (Keyboard::isKeyPressed(Keyboard::Space) && p.isonground)
    {
        float speedFactor = fabs(p.velocity.x) / p.maxspeed;
        speedFactor = min(speedFactor, 1.f);
        float jumpBoost = 1.f + speedFactor * 0.8f;
        if (p.lastland < 0.15f) {
            jumpBoost *= 2.f;     // jumpboost
        }
        p.velocity.y = p.jumppower * jumpBoost;
        p.isonground = false;
        p.justlanded = false;
        a.isjumping = true;
    }
}

//--------------------------------

void playerphysics(player& p, float dt)
{
    if (p.velocity.x > p.maxspeed) p.velocity.x = p.maxspeed;
    if (p.velocity.x < -p.maxspeed) p.velocity.x = -p.maxspeed;

    p.velocity.y += p.gravity * dt;

    if (p.velocity.y > 0)
        p.velocity.y += p.gravity * 1.2f * dt;

    if (p.velocity.y > 1200.f)
        p.velocity.y = 1200.f;
}

//--------------------------------

void playermove(player& p, float dt) {
    p.body.move(p.velocity.x * dt, p.velocity.y * dt);
}

//--------------------------------

void playerdraw(player& p, RenderWindow& window) {
    window.draw(p.body);
}

//--------------------------------collision----------------------------------------------------//

void collision(player& p, Platform platforms[]) {

    p.isonground = false;

    // walls
    if (p.body.getPosition().x < 190.5)
    {
        p.body.setPosition(190.5, p.body.getPosition().y);
        p.velocity.x *= -0.5f;
    }

    if (p.body.getPosition().x + p.body.getGlobalBounds().width > 1721)
    {
        p.body.setPosition(1721 - p.body.getGlobalBounds().width, p.body.getPosition().y);
        p.velocity.x *= -0.5f;
    }
    // ground
    if (p.body.getPosition().y + p.body.getGlobalBounds().height > 1050) {
        p.body.setPosition(p.body.getPosition().x, 1050 - p.body.getGlobalBounds().height);
        p.velocity.y = 0;
        p.isonground = true;
    }

    // platforms
    for (int i = 0; i < PLATFORM_COUNT; i++)
    {
        if (p.velocity.y > 0 && p.body.getGlobalBounds().intersects(platforms[i].sprite.getGlobalBounds()))
        {
            p.body.setPosition(
                p.body.getPosition().x, platforms[i].sprite.getPosition().y - p.body.getSize().y);
            p.justlanded = true;
            p.lastland = 0.f;

            p.velocity.y = 0;
            p.isonground = true;
        }
    }
}

//--------------------------------Animation---------------------------------------------------//

void start(anim& g) {

    g.idle.loadFromFile("idle.png");
    g.moving.loadFromFile("moving.png");
    g.jumping.loadFromFile("jump.png");
    g.Jumpbsss.loadFromFile("Jampbass.png");
    g.fall.loadFromFile("Falling.png");

    g.mary.setTexture(g.idle); // مهم

    g.mary.setOrigin(49.f / 2.f, 61.f);
    g.mary.setScale(2.f, 2.f);

    g.animTimer = 0;
    g.animSpeed = 0.12f;
    g.fallindex = 0;
    g.sakinindix = 0;
    g.movingindix = 0;
}

//--------------------------------

void update(anim& g, player& p, float dt) {

    g.animTimer += dt;

    g.ismoving = (abs(p.velocity.x) > 0.1f);
    g.isjumping = !p.isonground;


    if (g.animTimer >= g.animSpeed) {
        //falling
        if (p.velocity.y > 1.f) {
            g.mary.setTexture(g.fall);
            g.mary.setTextureRect(IntRect(g.fallindex * 57, 0, 57, 58));
            g.fallindex = (g.fallindex + 1) % 2;
        }
        // jumping
        else if (g.isjumping && g.ismoving) {
            g.mary.setTexture(g.jumping);
            g.mary.setTextureRect(IntRect(g.jumpingindix * 49, 0, 49, 61));
            g.jumpingindix = (g.jumpingindix + 1) % 3;

        }
        // jump upward
        else if (g.isjumping) {
            g.mary.setTexture(g.Jumpbsss);
            g.mary.setTextureRect(IntRect(0, 0, 49, 61));
        }
        //moving
        else if (g.ismoving) {
            g.mary.setTexture(g.moving);
            g.mary.setTextureRect(IntRect(g.movingindix * 50, 0, 50, 54));
            g.movingindix = (g.movingindix + 1) % 4;
        }
        //idle
        else {
            g.mary.setTexture(g.idle);
            g.mary.setTextureRect(IntRect(g.sakinindix * 49, 0, 49, 56));
            g.sakinindix = (g.sakinindix + 1) % 4;
        }

        g.animTimer = 0;
    }
    if (p.velocity.x < -0.1f) {
        g.mary.setScale(-2.f, 2.f); //وشه الناحية التانية
    }
    else if (p.velocity.x > 0.1f) {
        g.mary.setScale(2.f, 2.f);
    }
    g.mary.setPosition(p.body.getPosition().x + 25, p.body.getPosition().y + 48);
}