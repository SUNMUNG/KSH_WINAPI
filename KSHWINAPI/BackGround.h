#pragma once
#include "Actor.h"

class Background :public Actor
{
public:
	Background() = delete;
	Background(ResourceID InID);	// ������ ���� ��θ� �޾ƾ� ������ �� �ִ�.


	virtual void OnTick(float inDealtaTime) override;
	virtual void OnRender(Gdiplus::Graphics* InGraphics) override;

private:
	float ScrollSpeed = 50.0f;

	float Offset=0.0f;
};

