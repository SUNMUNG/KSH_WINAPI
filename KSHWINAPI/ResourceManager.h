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
	ResourceManager(const ResourceManager&) = delete;	// ���� ������ ����
	ResourceManager& operator=(const ResourceManager&) = delete; // ���� ������ ����
	ResourceManager(const ResourceManager&&) = delete;	// �̵� ������ ����
	ResourceManager& operator=(const ResourceManager&&) = delete; // �̵� ���� ������ ����
};

