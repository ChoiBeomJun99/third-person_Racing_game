#pragma once
#include "GameObject.h"
#include "RigidBody.h"

class Cart : public GameObject {
protected:
	float carMass = 1;
	float carAccelate = 0.02;
	float carCollisionDefence = 0.2;
	float carBoostAccelate = 0.06;
	float carBoostCapacity = 120;
	float carBoostRecovery = 5;
	float carHandling = 30.0;
	float currentBooster = 0;
	bool boosterUsed = false;

public:
	RigidBody * rb;
	Cart() {
		rb = new RigidBody(this);
		rb->boxX = 20;
		rb->boxY = 20;
		rb->eles = carCollisionDefence;
		rb->mass = carMass;
		this->transform.x = 0;
		this->transform.y = 0;
		this->transform.xSize = 1;
		this->transform.ySize = 1;
		rb->isStatic = false;
	}
	~Cart() {
		delete rb;
	}
	void rotate() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			transform.angle += carHandling / 60;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			transform.angle -= carHandling / 60;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			boosterUsed = false;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (currentBooster > 30||boosterUsed)) {
				rb->addForce(transform.angle, carBoostAccelate);
				currentBooster -= 1;
				boosterUsed = true;
			}
			rb->addForce(transform.angle, carAccelate);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			rb->addForce(transform.angle, -0.5 * carAccelate);
		}
	}
	void front();
	void start() {
		currentBooster = 0;
	}

	void update() {
		if (currentBooster + ((carBoostCapacity / carBoostRecovery)/60) > carBoostCapacity) {
			currentBooster = carBoostCapacity;
		}
		else {
			currentBooster += ((carBoostCapacity/carBoostRecovery)/60);
		}
		rotate();
	}
};