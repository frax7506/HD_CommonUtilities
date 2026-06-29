#include "HD_InputManager.h"

#include "HD_Unused.h"

HD_InputManager::HD_InputManager()
{
}

HD_InputManager& HD_InputManager::GetInstance()
{
	static HD_InputManager ourInstance;
	return ourInstance;
}

void HD_InputManager::Init(HWND aWindowHandle)
{
	HD_Unused(aWindowHandle);
}

void HD_InputManager::Update()
{

}

bool HD_InputManager::UpdateEvents(UINT message, WPARAM wParam, LPARAM lParam)
{
	HD_Unused(message);
	HD_Unused(wParam);
	HD_Unused(lParam);

	return false;
}

bool HD_InputManager::GetIsKeyHeld(int aKeyCode) const
{
	HD_Unused(aKeyCode);

	return false;
}

bool HD_InputManager::GetIsKeyPressed(int aKeyCode) const
{
	HD_Unused(aKeyCode);

	return false;
}

bool HD_InputManager::GetIsKeyReleased(int aKeyCode) const
{
	HD_Unused(aKeyCode);

	return false;
}

HD_Vector2f HD_InputManager::GetMouseDelta() const
{
	return HD_Vector2f::Zero;
}

HD_Vector2f HD_InputManager::GetMousePosition() const
{
	return HD_Vector2f::Zero;
}

void HD_InputManager::ShowMouse() const
{

}

void HD_InputManager::HideMouse() const
{

}

void HD_InputManager::CaptureMouse() const
{

}

void HD_InputManager::ReleaseMouse() const
{

}
