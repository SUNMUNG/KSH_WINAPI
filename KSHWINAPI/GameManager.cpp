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



    Player* MainPlayer = new Player(L"./Images/ship.png");
    MainPlayer->SetRenderLayer(RenderLayer::Player);
    AddActor(MainPlayer);
    AddActor2(MainPlayer, RenderLayer::Player);
    TestGridActor* testGrid = new TestGridActor();
    testGrid->SetRenderLayer(RenderLayer::Test);
    AddActor(testGrid);
    AddActor2(testGrid, RenderLayer::Test);

    Background* background = new Background(L"./Images/tile.png");
    background->SetRenderLayer(RenderLayer::Background);
    AddActor(background);
    AddActor2(background, RenderLayer::Background);



    std::sort(Actors.begin(), Actors.end(), [](Actor* left, Actor* Right) {
        return static_cast<int>(left->GetRenderLayer()) < static_cast<int>(Right->GetRenderLayer());
        }
    );
}

void GameManager::Destroy()
{
    delete BackBufferGraphics;
    BackBufferGraphics = nullptr;
    delete BackBuffer;
    BackBuffer = nullptr;
}

void GameManager::Tick(float InDeltaTime)
{
    for (Actor* Actor : Actors)
    {
        Actor->OnTick(InDeltaTime);
    }
}

void GameManager::Render()
{
    if (BackBufferGraphics)   // g_BackBufferGraphics 필수
    {
        BackBufferGraphics->Clear(Gdiplus::Color(255, 0, 0, 0));

        
        for (Actor* Actor : Actors)
        {
            Actor->OnRender(BackBufferGraphics);
        }

        //for (Actor* Actor : Actors)
        //{
        //   

        //    for (auto& pair : Actors2)
        //    {
        //        Actor* actor = pair.first;
        //        // Actor를 사용하여 필요한 작업 수행
        //        Actor->OnRender(BackBufferGraphics);
        //    }
        //    Actor->OnRender(BackBufferGraphics);
        //}
        
        
    }
}

void GameManager::HandleKeyState(WPARAM InKey, bool InIsPressed)
{
    MainPlayer->HandleKeyState(InKey, InIsPressed);
}