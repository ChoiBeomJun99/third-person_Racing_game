#include "GameObject.h"
#include "SpriteRenderer.h"

GameObject::GameObject() {
	this->sprite = new SpriteRenderer(this);
}

GameObject::~GameObject() {
	delete this->sprite;
}

void GameObject::start() {
	return;
}

void GameObject::update() {
	return;
}