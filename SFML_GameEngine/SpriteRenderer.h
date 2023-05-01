#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "PriorityQueue.h"
#include "Component.h"


class RenderingCore;


//스프라이트 렌더러 컴포넌트 클래스
/*
* 이 클래스는 스프라이트를 가지고 있고, 이 스프라이트는 렌더링 코어에 의해 화면에 렌더링 된다.
* 스프라이트는 다음과 같이 구성된다.
* 화면에 출력할 텍스쳐(이미지) -> ex ): png,jpg,bmp,jpeg 등등의 이미지 파일 
* 텍스쳐의 회전 정도 -> ex ) : 적을 바라보는 포탑
* 텍스쳐의 투명도 -> ex ) : 불러온 이미지를 얼마나 투명하게 할 지(케릭터가 은신하면 투명해진다.)
* 텍스쳐의 색상 가중치 -> ex) : 흰색 구슬 이미지가 있었는데, 빨강색(255,0,0)의 가중치를 텍스쳐에 적용하여, 빨간 구슬이 되었다.
* 텍스쳐의 크기 -> ex) : 텍스쳐를 x,y비율에 대하여 얼마나 확대 또는 축소 시킬지(이미지의 크기)
* 스프라이트는 이 5개의 요소를 결합하여 새로운 택스쳐를 생성하고, 이를 우리는 스프라이트라고 부를 수 있다.
*/
class SpriteRenderer : Component {
private:
	int sortOrder;//렌더링 중요도, 높을수록, 화면의 앞에 렌더링 된다.
	sf::Sprite sprite;//이 스프라이트 렌더러가 렌더링 할 스프라이트
	sf::Texture texture;//기본으로 할 이미지
	GameObject* gameObject;//이 렌더러를 포함하는 게임 오브젝트
	RenderingCore* rCore;//렌더링 코어 참조
public :
	float imageXPoint = 12.5;//이미지의 X,Y중심점
	float imageYPoint = 20;
	void setOrder(int i);//이 렌더러의 중요도를 설정한다.
	int getOrder();//이 렌더러의 중요도를 반환한다.
	~SpriteRenderer();//소멸자, 할당된 리소스들을 모두 해제한다.
	SpriteRenderer(GameObject * gameObejct);//생성자, 이 컴포넌트를 포함할 게임 오브젝트를 지정할 것
	GameObject * getGameObject();//이 렌더러를 포함하는 게임 오브젝트를 반환한다.
	void setTexture(const char * ptr);//이 렌더러가 렌더링 할 이미지를 로드하여 저장한다.
	sf::Sprite getSprite();//이 렌더러가 렌더링 할 스프라이트를 반환한다.
	const char * getType();//이 컴포넌트의 타입을 반환한다(SpriteRenderer)

};


