#pragma once
#include <unordered_map>
#include <Windows.h>
#include <gdiplus.h>
#include "enums.h"

// extern : 뒤에 있는 변수가 다른 파일에 선언이 되어 있다.
extern HWND g_hMainWindow; // g_hMainWindow가 다른 파일에 있다는 것을 알려줌
extern Gdiplus::Point g_ScreenSize;

using PointF = Gdiplus::PointF;
class BackGround
{
public:
	BackGround() = delete;
	BackGround(const wchar_t* InImagePath);	// 무조건 파일 경로를 받아야 생성할 수 있다.
	~BackGround()=default;

	void MapRender(Gdiplus::Graphics* InGraphics,int posX,int posY);
	int XMove = 5;
	int Mapwidth = 600;
	int MapHeight = 800;
	PointF PositionA = { 0.0f, 0.0f };
	PointF PositionB = { 0.0f, -800.0f };
private:
	Gdiplus::Bitmap* Image = nullptr;
	
	// 플레이어가 그려질 크기
	static constexpr int PixelSizeX = 650;
	static constexpr int PixelSizeY = 850;

};

