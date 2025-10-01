#include "BackGround.h"

BackGround::BackGround(const wchar_t* InImagePath)
{
    Image = new Gdiplus::Bitmap(InImagePath);
}

void BackGround::MapRender(Gdiplus::Graphics* InGraphics, int posX, int posY)
{
    if (Image)
    {
        // g_PlayerImage가 로딩되어 있다.
        InGraphics->DrawImage(
            Image,          // 그려질 이미
            static_cast<int>(posX),    // 그려질 위치
            static_cast<int>(posY),
            PixelSizeX, PixelSizeY);  // 그려질 사이즈
    }
    else
    {
        Gdiplus::SolidBrush RedBrush(Gdiplus::Color(255, 255, 0, 0));
        InGraphics->FillEllipse(
            &RedBrush,
            100, 100,
            PixelSizeX, PixelSizeY);
    }
}
