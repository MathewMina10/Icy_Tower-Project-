#include "player.h"
#include "Platforms.h"
#include<iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
using namespace std;
using namespace sf;


void playerinfo(player& player) {
	player.body.setSize(Vector2f(50.f, 50.f));
	player.body.setFillColor(Color::Red);
	player.body.setPosition(500.f, 300.f);
	player.velocity = Vector2f(0.f, 0.f);
	player.gravity = 0.3f;
	player.movespeed = 0.1f;
	player.jumppower = -11.f;
	player.isonground = false;
}

void playermovement(player& player) {
	if (Keyboard::isKeyPressed(Keyboard::D)) //right movement
		player.velocity.x += player.movespeed;
	else if (Keyboard::isKeyPressed(Keyboard::A)) // left movement
		player.velocity.x -= player.movespeed;
	else {
		player.velocity.x *= 0.3f; //friction force
	}
	if (Keyboard::isKeyPressed(Keyboard::Space) && player.isonground) {
		player.velocity.y = player.jumppower;
		player.isonground = false;
	}
}

void playerphysics(player& player) {
	if (player.velocity.x > 5)
		player.velocity.x = 5;
	if (player.velocity.x < -5)
		player.velocity.x = -5;
	if (player.velocity.y > 10)
		player.velocity.y = 10;
	player.velocity.y += player.gravity; //gravity
}

void playermove(player& player) {
	player.body.move(player.velocity);
}

void playerdraw(player& player, RenderWindow& window) {
	window.draw(player.body);
}

// collision
void walls(player& p, Platform platforms[]) {
	//left wall
	if (p.body.getPosition().x < 96.75)
		p.body.setPosition(96.75, p.body.getPosition().y);
	//right wall 
	if (p.body.getPosition().x + p.body.getGlobalBounds().width > 1820)
		p.body.setPosition(1820 - p.body.getGlobalBounds().width, p.body.getPosition().y);
	//bottom
	if (p.body.getPosition().y + p.body.getGlobalBounds().height > 1050) {
		p.body.setPosition(p.body.getPosition().x, 1050 - p.body.getGlobalBounds().height);
		p.velocity.y = 0;
		p.isonground = true;
	}




	for (int i = 0; i < PLATFORM_COUNT; i++)
	{
		if (p.velocity.y > 0 &&
			p.body.getGlobalBounds().intersects(platform[i].sprite.getGlobalBounds()))
		{
			p.body.setPosition(
				p.body.getPosition().x,
				platforms[i].sprite.getPosition().y - p.body.getSize().y
			);

			p.velocity.y = 0;
			p.isonground = true;

			std::cout << "Collision!\n";
		}
	}


}
//void collisionplatform(player& p) {
//	int PLATFORM_COUNT = 200;
//
//	for (int i = 0; i < PLATFORM_COUNT; i++) {
//
//		float playerLeft = p.body.getPosition().x;
//		float playerRight = playerLeft + p.body.getSize().x;
//		float playerBottom = p.body.getPosition().y + p.bodygetSize().y;
//
//		float platformLeft = platformX[i];
//		float platformRight = platformX[i] + 60;
//		float platformTop = platformY[i];
//
//		if (velocity.y > 0 && // نازل لتحت
//			playerBottom >= platformTop &&
//			playerBottom <= platformTop + 10 &&
//			playerRight > platformLeft &&
//			playerLeft < platformRight) {
//
//			// 👇 نقف فوق المنصة
//			player.setPosition(playerLeft, platformTop - player.getSize().y);
//
//			// نوقف السقوط
//			velocity.y = 0;
//		}
//	}

