#include "RigidBody.h"
#include "PhysicsSystem.h"
#include "Options.h"

PhysicsSystem* PhysicsSystem::instance;

// 쓰레드를 가동한다.
void PhysicsSystem::XENGINE_Begine_PhySics_Thread() {
	PriorityQueue<RigidBody *> temp;
	PriorityQueue<RigidBody *> used;
	while (!pq.isEmpty()) {//큐에 남아있는 강체를 하나씩 인출.
		RigidBody * subject = pq.pop();//큐에서 스프라이트를 뽑고 주체로 설정한다,
		if (!(subject->isStatic)) {
			subject->move();
		}
		else {
			subject->vX = 0;
			subject->vY = 0;
		}
		attatchAirResistance(subject);
		int collideWithWall = subject->collisionWithWall(SCREEN_X, SCREEN_Y);
		if ( collideWithWall!= 0&&this->collisionWithWall) {
			justBounce(subject, collideWithWall);
			if (!(subject->isStatic)) {
				subject->move();
			}
		}
		int i = 0;
		while (!pq.isEmpty()) {//나머지 강체를 하나씩 큐로
			RigidBody * target = pq.pop();//큐에서 강체를 뽑고 주체로 설정한다,
			int collideType = subject->isCollide(target);
			if (collideType) {
				attachCollision(subject,target,collideType);
				if (!(subject->isStatic)) {
					subject->move();
				}
				else {
					target->move();
				}
			}
			temp.push(target, i);
			i++;
		}
		i = 0;
		while (!temp.isEmpty()) {//나머지 강체를 하나씩 큐로
			RigidBody * target = temp.pop();//큐에서 강체를 뽑고 주체로 설정한다,
			pq.push(target, i);
			i++;
		}
		used.push(subject, 0);
	}
	int i = 0;
	while (!used.isEmpty()) {//큐를 원상 복귀시킨다.
		RigidBody * target = used.pop();//큐에서 뽑고
		pq.push(target, i);//돌려놓는다.
		i++;
	}
}

//물리연산 큐에 강체를 등록한다.
void PhysicsSystem::enqueue(RigidBody* target) {
	if (target != nullptr) {
		pq.push(target, 0);
	}
}

//물리연산 큐에서 오브젝트를 제거한다.
void PhysicsSystem::removeTarget(RigidBody* target) {
	pq.removeAt(target);
}

//두 강체에게 충돌처리를 한다.
void PhysicsSystem::attachCollision(RigidBody * r1, RigidBody * r2,int xOrY) {
	float te = (r1->eles + r2->eles) / 2;
	float vX1, vY1, vX2, vY2;
	float vXC1, vYC1, vXC2, vYC2;
	float m1, m2;
	vX1 = r1->vX;
	vX2 = r2->vX;
	vY1 = r1->vY;
	vY2 = r2->vY;
	m1 = r1->mass;
	m2 = r2->mass;
	vXC1 = getCollsionSpeed(vX1, vX2, m1, m2, te);
	vXC2 = getCollsionSpeed(vX2, vX1, m2, m1, te);
	vYC1 = getCollsionSpeed(vY1, vY2, m1, m2, te);
	vYC2 = getCollsionSpeed(vY2, vY1, m2, m1, te);
	if (!(r1->isStatic)) {
		r1->vX = vXC1;
		r1->vY = vYC1;
	}
	else {
		this->justBounce(r2, xOrY);
		return;
	}
	if (!(r2->isStatic)) {
		r2->vX = vXC2;
		r2->vY = vYC2;
	}
	else {
		this->justBounce(r1, xOrY);
		return;
	}
}

//충돌 직후의 속도를 계산한다.
float PhysicsSystem::getCollsionSpeed(float vs,float vt,float ms,float mt,float te) {
	double massSum = ms + mt;
	double upperSeg = ((1 + te) * (mt * vt)) + (vs * (ms - (te * mt)));
	return (float)(upperSeg / massSum);
}


//단순히 오브젝트를 튕긴다, 예를 들어 벽과 충돌하는 경우에 이 메소드를 호출한다.
void PhysicsSystem::justBounce(RigidBody* r1,int xOrY) {
	float te = r1->eles;
	float vX1, vY1;
	vX1 = r1->vX;
	vY1 = r1->vY;
	if (!r1->isStatic) {
		if (xOrY == 1) {
			r1->vX = -vX1 * te;
			r1->vY *= te;
		}
		else {
			r1->vY = -vY1 * te;
			r1->vX *= te;
		}
	}
}

//공기 저항을 적용한다.
void PhysicsSystem::attatchAirResistance(RigidBody* r1) {
	r1->vX -= (abs(r1->vX) * (r1->vX) * (0.01)) / r1->mass;
	r1->vY -= (abs(r1->vY) * (r1->vY) * (0.01)) / r1->mass;
}