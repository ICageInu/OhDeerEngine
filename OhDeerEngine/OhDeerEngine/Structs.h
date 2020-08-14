#pragma once

struct Rectf
{
	Rectf() =default;
	explicit Rectf(float left, float bottom, float width, float height):
		left(left),
		bottom(bottom),
		width(width),
		height(height)
	{};

	float left;
	float bottom;
	float width;
	float height;

};
