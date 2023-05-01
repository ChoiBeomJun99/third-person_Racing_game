#pragma once
#include <SFML/Graphics.hpp>
#include "PriorityQueue.h"
#include "Options.h"


class SpriteRenderer;

class RenderingCore {
private:
	sf::RenderWindow * window;
	PriorityQueue<SpriteRenderer *> pq;
	RenderingCore() {}
	static RenderingCore* instance;

public:
	static RenderingCore* getInstance() {
		if (RenderingCore::instance == NULL) {
			RenderingCore::instance = new RenderingCore();
		}
		return RenderingCore::instance;
	}
	void XENGINE_Begine_Rendering_Thread(sf::RenderWindow * window);
	void enqueue(SpriteRenderer* target);
	void removeTarget(SpriteRenderer* target);
};

