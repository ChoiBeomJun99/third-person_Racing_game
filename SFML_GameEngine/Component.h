#pragma once
//컴포넌트 클래스는 기본적으로 게임 오브젝트에 여러개 붙을 수 있다.
//이 컴포넌트를 상속받아 다양한 컴포넌트를 구성할 수 있다.

class Component
{
protected:
	bool active;	//이 컴포넌트의 활성 여부
public :
	Component() {
		this->active = true;
	}
	//이 컴포넌트의 이름을 반환한다.
	virtual const char * getType() {
		return "Component";
	}

	//이 컴포넌트의 활성 상태를 설정한다.
	//이 클래스를 상속받을 경우 이 메소드를 오버라이딩 하여, 여러 리소스에 대한 처리를 해주어야 한다.
	virtual void setActive(bool isActive) {
		this->active = isActive;
	}

	bool isActive() {
		return active;
	}
	
};