#pragma once
#include <unordered_map>
#include "enums.h"
#include "Actor.h"

// extern : 뒤에 있는 변수가 다른 파일에 선언이 되어 있다.
extern HWND g_hMainWindow; // g_hMainWindow가 다른 파일에 있다는 것을 알려줌
extern Gdiplus::Point g_ScreenSize;

using PointF = Gdiplus::PointF;
class Player : public Actor
{
	/*
		키보드 입력으로 좌우 이동
		플레이어가 화면을 벗어나지 않게 하기
	*/
public:
	Player() = delete;
	Player(ResourceID InID);	// 무조건 파일 경로를 받아야 생성할 수 있다.


	virtual void OnTick(float inDeltaTime) override;
	virtual void OnRender(Gdiplus::Graphics* InGraphics) override;

	void HandleKeyState(WPARAM InKey, bool InIsPressed);


	inline float GetSpeed() const { return Speed; }
	inline void SetSpeed(float InSpeed) { Speed = InSpeed; }
private:
	// 플레이어 키 입력 상태
	std::unordered_map<InputDirection, bool> KeyWasPressedMap;

	// 플레이어의 이동 속도
	float Speed = 200.0f;
};