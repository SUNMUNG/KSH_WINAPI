#pragma once
#include "Common.h"
class Actor
{
public:
	Actor() = delete;
	Actor(const wchar_t* InImagePath);	// ������ ���� ��θ� �޾ƾ� ������ �� �ִ�.
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

	// �߽���
	PointF Pivot = { 0.5f, 0.5f }; // Pivot �⺻ ���� �Ѱ��

	// ��ġ
	PointF Position = { 0.0f, 0.0f };

	// �̹����� ������� ��Ʈ��
	Gdiplus::Bitmap* Image = nullptr;   // �÷��̾ �׷��� ����		

};

