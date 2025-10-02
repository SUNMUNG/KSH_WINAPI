#include "GameManager.h"
#include "Background.h"
#include "Player.h"
#include "TestGridActor.h"

void GameManager::Initialize()
{
    BackBuffer = new Gdiplus::Bitmap(
        GameManager::ScreenWidth, GameManager::ScreenHeight, PixelFormat32bppARGB);
    BackBufferGraphics = Gdiplus::Graphics::FromImage(BackBuffer);
    if (!BackBufferGraphics)
    {
        // 혹시 안만들어졌을 때를 대비한 에러 출력
        MessageBox(hMainWindow, L"백 버퍼 그래픽스 생성 실패", L"오류", MB_OK | MB_ICONERROR);
    }

    Background* background = new Background(ResourceID::Background);
    Player* MainPlayer = new Player(ResourceID::Player);
    AddActor(RenderLayer::Background, background);
    AddActor(RenderLayer::Player,MainPlayer);
    AddActor(RenderLayer::Test,new TestGridActor());
}

void GameManager::Destroy()
{
    for (auto pair : Actors) {
        for (Actor* actor : pair.second) {
            delete actor;
        }
        pair.second.clear();
    }
    Actors.clear();

    delete BackBufferGraphics;
    BackBufferGraphics = nullptr;
    delete BackBuffer;
    BackBuffer = nullptr;
}

void GameManager::Tick(float InDeltaTime)
{
    for (auto pair : Actors) {
        for (Actor* Actor : pair.second)
        {
            Actor->OnTick(InDeltaTime);
        }
    }
    
}

void GameManager::Render()
{
    if (BackBufferGraphics)   // g_BackBufferGraphics 필수
    {
        BackBufferGraphics->Clear(Gdiplus::Color(255, 0, 0, 0));


        for (auto pair : Actors) {
            for (Actor* Actor : pair.second)
            {
                Actor->OnRender(BackBufferGraphics);
            }
        }
        
    }
}

void GameManager::HandleKeyState(WPARAM InKey, bool InIsPressed)
{
    MainPlayer->HandleKeyState(InKey, InIsPressed);
}