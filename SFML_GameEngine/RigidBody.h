#pragma once
#include "Component.h"
#include "GameObject.h"
#include "PriorityQueue.h"
#include <math.h>


class PhysicsSystem;



//리지드 바디 컴포넌트
/*
* 이 컴포넌트는 물리와 관련된 상수 및 설정값들을 가지고 있고, 자동으로 게임 엔진의 물리계에 등록되어, 물리연산을 적용 받는다.
* 구성 요소는 다음과 같다.
* 질량(힘을 받는 정도, 클 수록 힘을 덜 받는다.), 저항면적(공기 저항을 얼마나 받는지?), 탄성력(이 물체가 충돌했을 때 얼만큼 에너지를 보존할 지)
* x,y축 속도(물리계에서 이 물체를 각 축 방향으로 움직일 속도), x,y축 충돌판정 영역(충돌 판정을 할 히트박스의 크기)
* 고정체인가?(고정체인 경우, 힘을 받지 않으나, 다른 물체에게 영향을 줄 수는 있다.)
*/


class RigidBody : Component{
private:
	GameObject * gameObject;//이 컴포넌트를 가지는 게임 오브젝트.
	PhysicsSystem * pCore;//물리연산 코어
public :
	float mass = 1;//이 강체의 질량
	float area = 0.5f;//공기저항을 받는 면적
	float eles = 0;//탄성력 0~1사이에서 결정 1이면 완전 탄성 충돌,0이면 완전 비탄성 충돌
	float vX = 0;//x,y방향의 속도.
	float vY = 0;
	float boxX;//충돌판정 영역의 x,y축 크기
	float boxY;
	bool isStatic = false;//고정된 물체인가? 이 경우 이 물체와 충돌하면, 반작용을 그대로 받게 된다.
	const char * getType();//이 컴포넌트의 타입을 반환한다(RigidBody)
	RigidBody(GameObject * obj);
	~RigidBody();
	//방향으로 크기만큼 힘을 가한다.
	void addForce(float angle, float power);//이 물체에 힘을 가한다.
	void setForce(float angle, float power);//이 물체의 힘을 설정한다(초기화 한다.)
	float getForece();//이 물체의 힘의 크기
	float getDir();//이 물체의 힘의 방향
	int isCollide(RigidBody * target);//이 물체와 다른 물체가 충돌했는가??
	int collisionWithWall(int lX, int lY);//벽과의 충돌여부.
	void move();// 이 강체를 속도만큼 이동 시킨다.
	Transform getTransform();//이 강체가 속한 오브젝트의 트렌스폼 반환.
	void setPos(float x,float y);//이 강체가 속한 오브젝트의 좌표를 set한다.
};