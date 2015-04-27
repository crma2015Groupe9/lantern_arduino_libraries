#ifndef Colors_h
#define Colors_h

#include "Arduino.h"

class Colors
{
	public:
		Colors(byte red, byte green, byte blue, float alpha);
		Colors(byte red, byte green, byte blue);

		void setColor(byte red, byte green, byte blue, float alpha);
		void setColor(byte red, byte green, byte blue);
		void setRed(byte value);
		void setGreen(byte value);
		void setBlue(byte value);
		void setAlpha(float value);

		byte red();
		byte green();
		byte blue();
		float alpha();
		float alphaMap(float min, float max);
		float alphaMap(float max);

		Colors getGradientStep(double cursorPosition, Colors targetColor);

	private:
		byte _red;
		byte _green;
		byte _blue;
		float _alpha;
};

#endif