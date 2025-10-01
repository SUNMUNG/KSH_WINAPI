#pragma once
#include <unordered_map>
#include <Windows.h>
#include <gdiplus.h>
#include "enums.h"

// extern : �ڿ� �ִ� ������ �ٸ� ���Ͽ� ������ �Ǿ� �ִ�.
extern HWND g_hMainWindow; // g_hMainWindow�� �ٸ� ���Ͽ� �ִٴ� ���� �˷���
extern Gdiplus::Point g_ScreenSize;

using PointF = Gdiplus::PointF;
class BackGround
{
public:
	BackGround() = delete;
	BackGround(const wchar_t* InImagePath);	// ������ ���� ��θ� �޾ƾ� ������ �� �ִ�.
	~BackGround()=default;

	void MapRender(Gdiplus::Graphics* InGraphics,int posX,int posY);
	int XMove = 5;
	int Mapwidth = 600;
	int MapHeight = 800;
	PointF PositionA = { 0.0f, 0.0f };
	PointF PositionB = { 0.0f, -800.0f };
private:
	Gdiplus::Bitmap* Image = nullptr;
	
	// �÷��̾ �׷��� ũ��
	static constexpr int PixelSizeX = 650;
	static constexpr int PixelSizeY = 850;

};

