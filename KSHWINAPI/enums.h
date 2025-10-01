#pragma once
#include <cstdint>
#include <Windows.h>

enum class InputDirection : uint8_t
{
	None=0,
	Up = VK_UP,
	Down = VK_DOWN,
	Left = VK_LEFT,
	Right = VK_RIGHT
};