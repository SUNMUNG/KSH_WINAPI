#include "ResourceManager.h"

void ResourceManager::ImageInit(const wchar_t* InImagePath)
{
	if (InImagePath)
    {
        Image = new Gdiplus::Bitmap(InImagePath); // �̹��� �ε�
        if (Image->GetLastStatus() != Gdiplus::Ok)
        {
            // ���������� ���� �ε��� �ȉ��.
            delete Image;       // ���������� ��� ����
            Image = nullptr;
            OutputDebugString(L"�÷��̾� �̹��� �ε� ����");
            MessageBox(GameManager::Get().GetMainWindowHandle(),
                L"�̹��� �ε� ����", L"����", MB_OK | MB_ICONERROR);
        }
    }
}
