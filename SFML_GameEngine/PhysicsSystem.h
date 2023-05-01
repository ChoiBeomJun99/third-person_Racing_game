#pragma once
#include "PriorityQueue.h"
#include <iostream>

class RigidBody;


class PhysicsSystem {
private:
	PriorityQueue<RigidBody*> pq;
	PhysicsSystem() {}
	static PhysicsSystem* instance;

public:
	//물리계 상수들을 정의한다.
	float gravityConstant = 9.8f;//중력상수, 0일 경우 무중력
	float airResistance = 0.3f;//공기저항 상수, 작을수록 공기 저항이 줄어들고, 0일 경우 공기저항이 없어진다.
	bool collisionWithWall = true; //벽과 충돌 판정을 하는가?
	static PhysicsSystem* getInstance() {
		if (PhysicsSystem::instance == NULL) {
			PhysicsSystem::instance = new PhysicsSystem();
		}
		return PhysicsSystem::instance;
	}
	void XENGINE_Begine_PhySics_Thread();
	void enqueue(RigidBody* target);
	void removeTarget(RigidBody* target);
	void attachCollision(RigidBody* r1,RigidBody * r2,int xOrY);
	void justBounce(RigidBody* r1, int xOrY);
	void attatchAirResistance(RigidBody* r1);
	float getCollsionSpeed(float vS,float vT,float mS,float mT,float tE);
};