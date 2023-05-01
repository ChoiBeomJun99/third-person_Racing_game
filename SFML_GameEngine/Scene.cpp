#include "Scene.h"

Scene::Scene(sf::Window& window) {
	this->window = &window;
	gameObjects = new ArrayList<GameObject>();
}

Scene::~Scene() {
	for (int i = 0; i < gameObjects->getSize(); i++) {
		delete gameObjects->get(i);
	}
	delete gameObjects;
}

void Scene::startView() {
	this->start();
	sf::Thread loop(&Scene::callUpdate,this);
	loop.launch();
}

void Scene::callUpdate() {
	while (window->isOpen()) {
		this->update();
	}
}



void Scene::start() {

}

void Scene::update() {

}