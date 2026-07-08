#pragma once

#include "HD_Types.h"

struct HD_Color
{
	f32 myR = 0.f;
	f32 myG = 0.f;
	f32 myB = 0.f;
	f32 myA = 0.f;

	static const HD_Color Black;
	static const HD_Color White;
	static const HD_Color Red;
	static const HD_Color Green;
	static const HD_Color Blue;
	static const HD_Color Yellow;
	static const HD_Color Purple;
	static const HD_Color Teal;
};
