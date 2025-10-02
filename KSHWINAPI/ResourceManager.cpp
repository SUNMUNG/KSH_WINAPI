#include "ResourceManager.h"
#include "GameManager.h"

void ResourceManager::Initialize()
{
    Resources[ResourceID::None] = nullptr;
    LoadResourceFromFile(ResourceID::Player, L"./Images/ship.png");
    LoadResourceFromFile(ResourceID::Bomb, L"./Images/bomb.png");
    LoadResourceFromFile(ResourceID::Background, L"./Images/tile.png");
    LoadResourceFromFile(ResourceID::Number0, L"./Images/zero.png");
    LoadResourceFromFile(ResourceID::Number1, L"./Images/one.png");
    LoadResourceFromFile(ResourceID::Number2, L"./Images/two.png");
    LoadResourceFromFile(ResourceID::Number3, L"./Images/three.png");
    LoadResourceFromFile(ResourceID::Number4, L"./Images/four.png");
    LoadResourceFromFile(ResourceID::Number5, L"./Images/five.png");
    LoadResourceFromFile(ResourceID::Number6, L"./Images/six.png");
    LoadResourceFromFile(ResourceID::Number7, L"./Images/seven.png");
    LoadResourceFromFile(ResourceID::Number8, L"./Images/eight.png");
    LoadResourceFromFile(ResourceID::Number9, L"./Images/nine.png");
    LoadResourceFromFile(ResourceID::Dot, L"./Images/dot.png");

}

void ResourceManager::Destroy()
{
    for (auto& pair : Resources)
    {
        delete pair.second; // 로드한 비트맵 모두 지우
    }
    Resources.clear();
}

Gdiplus::Bitmap* ResourceManager::GetImage(ResourceID InID)
{
    auto iter = Resources.find(InID);
    if (iter != Resources.end()) {
        return iter->second;
    }

    return nullptr;
}

bool ResourceManager::LoadResourceFromFile(ResourceID InID, const wchar_t* path)
{
    bool Result = false;
    if (path)
    {
        Gdiplus::Bitmap* Image = new Gdiplus::Bitmap(path); // 이미지 로딩
        if (Image->GetLastStatus() != Gdiplus::Ok)
        {
            // 정상적으로 파일 로딩이 안됬다.
            delete Image;       // 실패했으면 즉시 해제
            Image = nullptr;
            OutputDebugString(L"이미지 로드 실패");
            MessageBox(GameManager::Get().GetMainWindowHandle(),
                L"이미지 로드 실패", L"오류", MB_OK | MB_ICONERROR);
        }
        else
        {
            Resources[InID] = Image;
            Result = true;
        }
    }

    return false;
}
