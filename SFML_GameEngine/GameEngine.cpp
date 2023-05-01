// GameEngine.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <ctime>
#include <cstdlib>
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "RenderingCore.h"
#include "PhysicsSystem.h"
#include "Box.h"
#include "Cart.h"

Cart player;
Box box;

void renderingThread(sf::RenderWindow * window) {
	RenderingCore * rc = RenderingCore::getInstance();
	window->setActive(true);
	while (window->isOpen()) {
		rc->XENGINE_Begine_Rendering_Thread(window);
		sf::sleep(sf::milliseconds(16));
	}
}

void physicsThread(sf::RenderWindow * window) {
	PhysicsSystem * ps = PhysicsSystem::getInstance();
	while (window->isOpen()) {
		ps->XENGINE_Begine_PhySics_Thread();
		sf::sleep(sf::milliseconds(16));
		player.update();
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_X, SCREEN_Y), "SFML작동!");
	window.setActive(false);

	RenderingCore * rc = RenderingCore::getInstance();
	box.sprite->setTexture("box.png");
	player.sprite->setTexture("DarkKnight.png");
	box.transform.x = SCREEN_X * 0.5;
	box.transform.y = SCREEN_Y * 0.5;
	sf::Thread threadR(&renderingThread,&window);
	sf::Thread threadP(&physicsThread, &window);
	threadR.launch();
	threadP.launch();
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
	}
	return 0;
}


