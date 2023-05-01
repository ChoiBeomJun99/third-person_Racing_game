//SpriteRenderer의 함수들에 대한 Implementation
#include "SpriteRenderer.h"
#include "RenderingCore.h"



//이 스프라이트 렌더러의 렌더링 중요도를 설정한다. 높을수록 앞에 렌더링 된다.
//파라미터 정보 (i : 재 설정할 우선순위)
void SpriteRenderer::setOrder(int i) {
	(this->rCore)->removeTarget(this);
	sortOrder = i;
	(this->rCore)->enqueue(this);
}

//이 스프라이트 렌더러의 렌더링 중요도를 반환한다.
//파라미터 정보 ()
int SpriteRenderer::getOrder() {
	return sortOrder;
}

SpriteRenderer::~SpriteRenderer() {
	(this->rCore)->removeTarget(this);//이 컴포넌트를 매니저에서 제거할 것을 요청.

}

SpriteRenderer::SpriteRenderer(GameObject * gameObejct) {
	this->gameObject = gameObejct;
	this->sortOrder = 0;
	this->rCore = RenderingCore::getInstance();
	(this->rCore)->enqueue(this);
}

GameObject * SpriteRenderer::getGameObject() {
	return this->gameObject;
}

//이 렌더러가 렌더링 할 텍스쳐를 설정한다.
void SpriteRenderer::setTexture(const char * ptr) {
	sf::Texture temp;
	if (!temp.loadFromFile(ptr)) {
		printf("Log::SpriteRenderer::%p - ImageLoadFailError( %s )", this, ptr);
	}
	else {
		this->texture = temp;
	}
}

sf::Sprite SpriteRenderer::getSprite() {
	this->sprite.setTexture(this->texture);
	this->sprite.setOrigin(sf::Vector2f(this->imageXPoint, this->imageYPoint));
	this->sprite.setPosition(sf::Vector2f(this->gameObject->transform.x,SCREEN_Y - (this->gameObject->transform.y)));
	this->sprite.setRotation(this->gameObject->transform.angle);
	this->sprite.setScale(sf::Vector2f(this->gameObject->transform.xSize, this->gameObject->transform.ySize));
	return (this->sprite);
}

const char * SpriteRenderer::getType() {
	return "SpriteRenderer";
}
