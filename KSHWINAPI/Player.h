#pragma once
#include <unordered_map>
#include "enums.h"
#include "Actor.h"

// extern : �ڿ� �ִ� ������ �ٸ� ���Ͽ� ������ �Ǿ� �ִ�.
extern HWND g_hMainWindow; // g_hMainWindow�� �ٸ� ���Ͽ� �ִٴ� ���� �˷���
extern Gdiplus::Point g_ScreenSize;

using PointF = Gdiplus::PointF;
class Player : public Actor
{
	/*
		Ű���� �Է����� �¿� �̵�
		�÷��̾ ȭ���� ����� �ʰ� �ϱ�
	*/
public:
	Player() = delete;
	Player(ResourceID InID);	// ������ ���� ��θ� �޾ƾ� ������ �� �ִ�.


	virtual void OnTick(float inDeltaTime) override;
	virtual void OnRender(Gdiplus::Graphics* InGraphics) override;

	void HandleKeyState(WPARAM InKey, bool InIsPressed);


	inline float GetSpeed() const { return Speed; }
	inline void SetSpeed(float InSpeed) { Speed = InSpeed; }
private:
	// �÷��̾� Ű �Է� ����
	std::unordered_map<InputDirection, bool> KeyWasPressedMap;

	// �÷��̾��� �̵� �ӵ�
	float Speed = 200.0f;
};