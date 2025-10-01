#include "ResourceManager.h"

void ResourceManager::ImageInit(const wchar_t* InImagePath)
{
	if (InImagePath)
    {
        Image = new Gdiplus::Bitmap(InImagePath); // 이미지 로딩
        if (Image->GetLastStatus() != Gdiplus::Ok)
        {
            // 정상적으로 파일 로딩이 안됬다.
            delete Image;       // 실패했으면 즉시 해제
            Image = nullptr;
            OutputDebugString(L"플레이어 이미지 로드 실패");
            MessageBox(GameManager::Get().GetMainWindowHandle(),
                L"이미지 로드 실패", L"오류", MB_OK | MB_ICONERROR);
        }
    }
}
