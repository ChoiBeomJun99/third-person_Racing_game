#pragma once
class Transform {
public:
	float x;//x,y좌표
	float y;
	float xSize;//x,y축 크기
	float ySize;
	float angle;//이미지의 각도
	Transform() {//디폴트 생성자
		x = 0;
		y = 0;
		xSize = 1;
		ySize = 1;
		angle = 0;
	}
	void setPos(float x, float y) {
		this->x = x;
		this->y = y;
	}
};