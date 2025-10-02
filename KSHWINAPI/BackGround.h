#pragma once
#include "Actor.h"

class Background :public Actor
{
public:
	Background() = delete;
	Background(ResourceID InID);	// 무조건 파일 경로를 받아야 생성할 수 있다.


	virtual void OnTick(float inDealtaTime) override;
	virtual void OnRender(Gdiplus::Graphics* InGraphics) override;

private:
	float ScrollSpeed = 50.0f;

	float Offset=0.0f;
};

