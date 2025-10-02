#pragma once

template<typename T>
class Singleton
{
public:
	static T& Get()
	{
		static T instance;
		return instance;
	}

protected:
	Singleton() = default;
	virtual ~Singleton() = default;

	// Singleton : Ŭ������ �ν��Ͻ��� 1���� �ִ� Ŭ����. 
	// private�� �����ڸ� �־ �ۿ��� �ν��Ͻ�ȭ �ϴ� ���� ��õ������ ����
	Singleton(const Singleton&) = delete;	// ���� ������ ����
	Singleton& operator=(const Singleton&) = delete; // ���� ������ ����
	Singleton(const Singleton&&) = delete;	// �̵� ������ ����
	Singleton& operator=(const Singleton&&) = delete; // �̵� ���� ������ ����
};