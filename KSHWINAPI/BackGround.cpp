#include "BackGround.h"

BackGround::BackGround(const wchar_t* InImagePath)
{
    Image = new Gdiplus::Bitmap(InImagePath);
}

void BackGround::MapRender(Gdiplus::Graphics* InGraphics, int posX, int posY)
{
    if (Image)
    {
        // g_PlayerImage�� �ε��Ǿ� �ִ�.
        InGraphics->DrawImage(
            Image,          // �׷��� �̹�
            static_cast<int>(posX),    // �׷��� ��ġ
            static_cast<int>(posY),
            PixelSizeX, PixelSizeY);  // �׷��� ������
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
