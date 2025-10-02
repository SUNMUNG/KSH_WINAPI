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
        delete pair.second; // �ε��� ��Ʈ�� ��� ����
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
        Gdiplus::Bitmap* Image = new Gdiplus::Bitmap(path); // �̹��� �ε�
        if (Image->GetLastStatus() != Gdiplus::Ok)
        {
            // ���������� ���� �ε��� �ȉ��.
            delete Image;       // ���������� ��� ����
            Image = nullptr;
            OutputDebugString(L"�̹��� �ε� ����");
            MessageBox(GameManager::Get().GetMainWindowHandle(),
                L"�̹��� �ε� ����", L"����", MB_OK | MB_ICONERROR);
        }
        else
        {
            Resources[InID] = Image;
            Result = true;
        }
    }

    return false;
}
