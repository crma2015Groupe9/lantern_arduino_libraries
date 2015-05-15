#ifndef Colors_h
#define Colors_h

#include "Arduino.h"

class Colors
{
	public:
		Colors();
		Colors(byte red, byte green, byte blue);

		void setColor(byte red, byte green, byte blue);
		void setRed(byte value);
		void setGreen(byte value);
		void setBlue(byte value);

		byte red();
		byte green();
		byte blue();

		Colors getGradientStep(float cursorPosition, Colors targetColor);
		Colors getColorWithAlpha(float alpha);

	private:
		byte _red;
		byte _green;
		byte _blue;
};

#endif