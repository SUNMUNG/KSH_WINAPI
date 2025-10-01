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
        // Ȥ�� �ȸ�������� ���� ����� ���� ���
        MessageBox(hMainWindow, L"�� ���� �׷��Ƚ� ���� ����", L"����", MB_OK | MB_ICONERROR);
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
    if (BackBufferGraphics)   // g_BackBufferGraphics �ʼ�
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
        //        // Actor�� ����Ͽ� �ʿ��� �۾� ����
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