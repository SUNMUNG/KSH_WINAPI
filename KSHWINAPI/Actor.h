#pragma once
#include "Common.h"
class Actor
{
public:
	Actor() = delete;
	Actor(const wchar_t* InImagePath);	// 무조건 파일 경로를 받아야 생성할 수 있다.
	virtual ~Actor();


	virtual void OnTick(float inDealtaTime);
	virtual void OnRender(Gdiplus::Graphics* InGraphics);


	inline const Gdiplus::PointF& GetPivot() { return this->Pivot; };
	inline const Gdiplus::PointF& GetPos() { return this->Position; }
	inline const int GetSize() { return this->Size; }
	
	inline void SetPosition(float InX, float InY) { Position.X = InX; Position.Y = InY; }
	inline void SetSize(int InSize) { Size = InSize; }
	inline void SetPivot(float InX, float InY) { Pivot.X = InX; Pivot.Y = InY; }
	inline void SetRenderLayer(RenderLayer InLayer) { TargetRenderLayer = InLayer; }

protected:
	int Size = 64;

	// 중심점
	PointF Pivot = { 0.5f, 0.5f }; // Pivot 기본 값은 한가운데

	// 위치
	PointF Position = { 0.0f, 0.0f };

	// 이미지가 들어있을 비트맵
	Gdiplus::Bitmap* Image = nullptr;   // 플레이어가 그려질 종이		

};

