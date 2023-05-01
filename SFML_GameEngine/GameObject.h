#pragma once
#include <SFML/Graphics.hpp>
#include "Transform.h"

class SpriteRenderer;

class GameObject {
public : 
	Transform transform;
	SpriteRenderer * sprite;
	GameObject();
	~GameObject();
	virtual void start();
	virtual void update();
	void operate();
};