#pragma once
#include "GameObject.h"
#include "ArrayList.h"

class Scene {
private:
	void callUpdate();
protected:
	sf::Window* window;
	virtual void update();
	virtual void start();
	ArrayList<GameObject> * gameObjects;
public:
	Scene(sf::Window& window);
	~Scene();
	void startView();
};