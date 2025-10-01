#pragma once
#include "GameManager.h"
#include <gdiplus.h>
class ResourceManager
{
public:
	static ResourceManager& Get()
	{
		static ResourceManager instance;
		return instance;
	}

	inline Gdiplus::Bitmap* GetImage() { return Image; }
	void ImageInit(const wchar_t* InImagePath);
protected:
private:
	Gdiplus::Bitmap* Image = nullptr;

	ResourceManager() = default;
	virtual ~ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;	// 복사 생성자 삭제
	ResourceManager& operator=(const ResourceManager&) = delete; // 대입 연산자 삭제
	ResourceManager(const ResourceManager&&) = delete;	// 이동 생성자 삭제
	ResourceManager& operator=(const ResourceManager&&) = delete; // 이동 대입 연산자 삭제
};

