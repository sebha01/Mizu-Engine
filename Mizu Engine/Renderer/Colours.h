#pragma once
#include "Config.h"

class Colour
{
	private:
		float r;
		float g;
		float b;
		float a;
	public:
		Colour(float red, float green, float blue, float alpha)
		{
			this->r = red;
			this->g = green;
			this->b = blue;
			this->a = alpha;
		}
};


const Colour red(1.0f, 0.0f, 0.0f, 1.0f);
const Colour green(0.0f, 1.0f, 0.0f, 1.0f);
const Colour blue(0.0f, 0.0f, 1.0f, 1.0f);
const Colour white(1.0f, 1.0f, 1.0f, 1.0f);
const Colour black(0.0f, 0.0f, 0.0f, 1.0f);
const Colour purple(1.0f, 0.0f, 1.0f, 1.0f);
const Colour yellow(1.0f, 1.0f, 0.0f, 1.0f);
const Colour orange(1.0f, 0.5f, 0.0f, 1.0f);
