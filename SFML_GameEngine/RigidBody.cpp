
#include "RigidBody.h"
#include "PhysicsSystem.h"


RigidBody::RigidBody(GameObject * obj) {
	this->gameObject = obj;
	this->pCore = PhysicsSystem::getInstance();
	(this->pCore)->enqueue(this);
}

RigidBody::~RigidBody() {
	(this->pCore)->removeTarget(this);
}


//이 강체에 힘을 가한다.
//파라미터 정보 (angle : 힘을 가할 방향(360도 법), power : 가할 힘의 크기)
void RigidBody::addForce(float angle, float power) {
	float calculatedPower = power / (this->mass);
	vX += sin(angle*0.017453)* calculatedPower;
	vY += cos(angle*0.017453)* calculatedPower;
}


//이 강체의 속도를 설정한다, 질량에 상관 없이 해당 속도로 셋팅된다.
//파라미터 정보 (angle : 방향, power : 속도)
void RigidBody::setForce(float angle, float power) {
	vX = sin(angle*0.017453)* power;
	vY = cos(angle*0.017453)* power;
}


//이 물체의 힘의 크기를 반환한다.
//파라미터 정보 ()
float RigidBody::getForece() {
	double sqare = (vX * vX) + (vY *vY);
	return sqrt(sqare);
}

//이 스프라이트 렌더러의 렌더링 중요도를 설정한다. 높을수록 앞에 렌더링 된다.
//파라미터 정보 (i : 재 설정할 우선순위)
float RigidBody::getDir() {
	return atan2(vY,vX);
}


//이 컴포넌트의 타입을 반환한다 : RigidBody.
//파라미터 정보 ()
const char * RigidBody::getType() {
	return "RigidBody";
}

//이 컴포넌트가 속한 오브젝트의 트렌스 폼을 반환한다.
Transform RigidBody::getTransform() {
	return this->gameObject->transform;
}


//이 강체와 다른 강체의 충돌 여부를 반환한다.
int RigidBody::isCollide(RigidBody * target) {
	if (target == nullptr) {
		return false;
	}
	Transform tPos = target->getTransform();
	Transform sPos = this->getTransform();
	float xGap, yGap;
	float xCol, yCol;
	xGap = abs(tPos.x - sPos.x);
	yGap = abs(tPos.y - sPos.y);
	xCol = target->boxX + this->boxX;
	yCol = target->boxY + this->boxY;
	if (xGap < xCol && yGap < yCol){
		float difX, difY;
		difX = xCol - xGap;//파뭍힌 정도
		difY = yCol - yGap;
		if (isStatic) {//충돌 객체의 좌표 보정
			difX /= target->vX;
			difY /= target->vY;
			difX = abs(difX);
			difY = abs(difY);
			if (difX < difY) {
				int dX;
				if (tPos.x > sPos.x) {
					dX = sPos.x + xCol + 1;
				}
				else {
					dX = sPos.x - xCol - 1;
				}
				target->setPos(dX, tPos.y);
				return 1;
			}
			else {
				int dY;
				if (tPos.y > sPos.y) {
					dY = sPos.y + yCol + 1;
				}
				else {
					dY = sPos.y - yCol - 1;
				}
				target->setPos(tPos.x, dY);
				return -1;
			}
		}
		else {
			difX /= this->vX;
			difY /= this->vY;
			difX = abs(difX);
			difY = abs(difY);
			if (difX < difY) {
				int dX;
				if (tPos.x < sPos.x) {
					dX = tPos.x + xCol + 1;
				}
				else {
					dX = tPos.x - xCol - 1;
				}
				this->setPos(dX, sPos.y);
				return -1;
			}
			else {
				int dY;
				if (tPos.y < sPos.y) {
					dY = tPos.y + yCol + 1;
				}
				else {
					dY = tPos.y - yCol - 1;
				}
				this->setPos(sPos.x, dY);
				return 1;
			}
		}
	}else {
		return 0;
	}
}

//이 강체와 벽의 충돌여부를 반환한다.
//파라미터 정보 (lX : x축 창의 길이, lY : y축 창의 길이)
int RigidBody::collisionWithWall(int lX, int lY) {
	Transform sPos = this->getTransform();
	int x, y;
	x = sPos.x;
	y = sPos.y;
	if (x < this->boxX) {
		this->gameObject->transform.x = this->boxX;
		return 1;
	}
	if (x > lX - this->boxX) {
		this->gameObject->transform.x = lX - this->boxX;
		return 1;
	}
	if (y < this->boxY) {
		this->gameObject->transform.y = this->boxY;
		return -1;
	}
	if (y > lY - this->boxY) {
		this->gameObject->transform.y = lY - this->boxY;
		return -1;
	}
	return 0;
}


void RigidBody::move() {
	this->gameObject->transform.x += this->vX;
	this->gameObject->transform.y += this->vY;
}


void RigidBody::setPos(float x,float y) {
	printf("좌표가 X : %f, Y : %f로 설정됨\n", x, y);
	this->gameObject->transform.x = x;
	this->gameObject->transform.y = y;
}