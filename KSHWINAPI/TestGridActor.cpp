#include "TestGridActor.h"

TestGridActor::TestGridActor()
    :Actor(nullptr)
{
    WindowWidth = g_ScreenSize.X;
    WindowHeight = g_ScreenSize.Y;

    Size = 5;
    HalfSize = Size / 2;

    BlueBrush = new Gdiplus::SolidBrush(Gdiplus::Color(255, 0, 0, 255));
}

TestGridActor::~TestGridActor()
{
    delete BlueBrush;
    BlueBrush = nullptr;
}

void TestGridActor::OnRender(Gdiplus::Graphics* InGraphics)
{	
    if (!InGraphics || !BlueBrush)return;

    for (int y = 0; y <= WindowHeight; y+= interval)
    {
        for (int x = 0; x <= WindowWidth; x+= interval)
        {
            InGraphics->FillRectangle(BlueBrush, x, y, Size, Size);
        }
    }
}
