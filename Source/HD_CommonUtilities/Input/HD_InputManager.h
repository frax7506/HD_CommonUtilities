#pragma once

#include "HD_Bitset.h"
#include "HD_Singleton.h"
#include "HD_Vector2.h"

#include "Windows.h"

class HD_InputManager : public HD_Singleton<HD_InputManager>
{
public:
	void Init(HWND aWindowHandle);

	void Update();
	bool UpdateEvents(UINT message, WPARAM wParam, LPARAM lParam);

	bool GetIsKeyHeld(s32 aKeyCode) const;
	bool GetIsKeyPressed(s32 aKeyCode) const;
	bool GetIsKeyReleased(s32 aKeyCode) const;

	HD_Vector2_f32 GetMouseDelta() const;
	HD_Vector2_f32 GetMousePosition() const;

	void ShowMouse() const;
	void HideMouse() const;

	void CaptureMouse() const;
	void ReleaseMouse() const;

private:
	// The "tentative" state holds the state that is
	// being updated by the message pump thread. It
	// can be used in place of the current state but
	// depending on how the game is threaded it might
	// be nice to keep them separate.
	HD_Bitset<256> myTentativeState;
	HD_Bitset<256> myCurrentState;
	HD_Bitset<256> myPreviousState;

	HWND myOwnerHWND;

	HD_Vector2_s32 myTentativeMousePosition;
	HD_Vector2_s32 myCurrentMousePosition;
	HD_Vector2_s32 myPreviousMousePosition;

	HD_Vector2_s32 myTentativeMouseDelta;
	HD_Vector2_s32 myMouseDelta;

	f32 myTentativeMouseWheelDelta;
	f32 myMouseWheelDelta;
};
