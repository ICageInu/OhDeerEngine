#pragma once

struct Rectf
{
	explicit Rectf(float left, float bottom, float width, float height):
		left(left),
		bottom(bottom),
		width(width),
		height(height)
	{

	};
	

	float left;
	float bottom;
	float width;
	float height;
};
