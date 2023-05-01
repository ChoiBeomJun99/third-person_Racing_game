#pragma once
#include "GameObject.h"
#include "RigidBody.h"

class Ball : public GameObject{
private:
	

public :
	RigidBody * rb;
	Ball() {
		rb = new RigidBody(this);
		rb->boxX = 20;
		rb->boxY = 20;
		rb->eles = 1;
		rb->mass = 1;
		this->sprite->imageXPoint = 85;
		this->sprite->imageXPoint = 85;
		rb->addForce(45, 4);
		this->transform.x = 0;
		this->transform.y = 0;
		rb->isStatic = false;
	}

};