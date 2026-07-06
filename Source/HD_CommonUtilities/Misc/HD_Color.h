#pragma once

struct HD_Color
{
	float myR = 0.f;
	float myG = 0.f;
	float myB = 0.f;
	float myA = 0.f;

	static const HD_Color Black;
	static const HD_Color White;
	static const HD_Color Red;
	static const HD_Color Green;
	static const HD_Color Blue;
	static const HD_Color Yellow;
	static const HD_Color Purple;
	static const HD_Color Teal;
};

const HD_Color HD_Color::Black = { 0.f, 0.f, 0.f, 1.f };
const HD_Color HD_Color::White = { 1.f, 1.f, 1.f, 1.f };
const HD_Color HD_Color::Red = { 1.f, 0.f, 0.f, 1.f };
const HD_Color HD_Color::Green = { 0.f, 1.f, 0.f, 1.f };
const HD_Color HD_Color::Blue = { 0.f, 0.f, 1.f, 1.f };
const HD_Color HD_Color::Yellow = { 1.f, 1.f, 0.f, 1.f };
const HD_Color HD_Color::Purple = { 1.f, 0.f, 1.f, 1.f };
const HD_Color HD_Color::Teal = { 0.f, 1.f, 1.f, 1.f };
