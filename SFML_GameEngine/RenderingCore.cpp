#include "SpriteRenderer.h"
#include "RenderingCore.h"
#include <vector>



using namespace std;

RenderingCore* RenderingCore::instance;

//렌더링 쓰레드를 가동한다.
void RenderingCore::XENGINE_Begine_Rendering_Thread(sf::RenderWindow * window) {
		this->window = window;
		PriorityQueue<SpriteRenderer *> temp;
		this->window->clear();//창을 백지로 만들고
		while (!pq.isEmpty()) {//큐에 남아있는 스프라이트들을 모두 창에 그린다.
			SpriteRenderer * target = pq.pop();//큐에서 스프라이트를 뽑고
			temp.push(target, target->getOrder());//뽑은 스프라이트를 백업하고
			this->window->draw(target->getSprite());
		}
		while (!temp.isEmpty()) {//큐에 남아있는 스프라이트들을 모두 창에 그린다.
			SpriteRenderer * target = temp.pop();//큐에서 스프라이트를 뽑고
			pq.push(target, target->getOrder());//뽑은 스프라이트를 백업하고
		}
		window->display();
}

//렌더링 큐에 스프라이트 렌더러를 등록한다.
void RenderingCore::enqueue(SpriteRenderer* target) {
	if (target != nullptr) {
		pq.push(target, target->getOrder());
	}
}

//렌더링 큐에서 주소에 해당하는 스프라이트 렌더러를 제외시킨다
void RenderingCore::removeTarget(SpriteRenderer* target) {
	pq.removeAt(target);
}