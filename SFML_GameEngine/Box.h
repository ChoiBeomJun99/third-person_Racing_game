#pragma once
#include "GameObject.h"
#include "RigidBody.h"
#include "SpriteRenderer.h"

class Box : public GameObject {
private:

public:
	RigidBody * rb;
	Box() {
		rb = new RigidBody(this);
		rb->boxX = 85;
		rb->boxY = 85;
		rb->eles = 1;
		rb->mass = 1;
		this->transform.x = 0;
		this->transform.y = 0;
		this->transform.xSize = 1;
		this->transform.ySize = 1;
		rb->isStatic = true;
		this->sprite->imageXPoint = 85;
		this->sprite->imageYPoint = 85;
	}
	void rotate() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			transform.angle += 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			transform.angle -= 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				rb->addForce(transform.angle, 0.24);
			}
			rb->addForce(transform.angle, 0.08);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			rb->addForce(transform.angle, -0.08);
		}
	}
	void front();
};