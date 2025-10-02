#pragma once
#include "Actor.h"
class TestGridActor : public Actor
{
public:
	TestGridActor(ResourceID _);
	virtual ~TestGridActor();

	virtual void OnRender(Gdiplus::Graphics* InGraphics) override;
private:
	int WindowHeight = 0;
	int WindowWidth = 0;
	Gdiplus::SolidBrush* BlueBrush=nullptr;
	int interval = 50;
	int HalfSize = 0;
};

