#include "Arduino.h"
#include "Colors.h"

Colors::Colors(byte red, byte green, byte blue, float alpha){
	_red = red;
	_green = green;
	_blue = blue;
	_alpha = alpha < 0 ? 0 : (alpha > 1 ? 1 : alpha);
}

Colors::Colors(byte red, byte green, byte blue){
	_red = red;
	_green = green;
	_blue = blue;
	_alpha = 1.0;
}

void Colors::setColor(byte red, byte green, byte blue, float alpha){
	setRed(red);
	setGreen(green);
	setBlue(blue);
	setAlpha(alpha);
}
void Colors::setColor(byte red, byte green, byte blue){
	setColor(red, green, blue, 1.0);
}
void Colors::setRed(byte value){
	_red = value;
}
void Colors::setGreen(byte value){
	_green = value;
}
void Colors::setBlue(byte value){
	_blue = value;
}
void Colors::setAlpha(float value){
	_alpha = value < 0 ? 0 : (value > 1 ? 1 : value);
}

byte Colors::red(){
	return _red;
}
byte Colors::green(){
	return _green;
}
byte Colors::blue(){
	return _blue;
}
float Colors::alpha(){
	return _alpha;
}
float Colors::alphaMap(float min, float max){
	float temp;

	if (min > max)
	{
		temp = max;
		max = min;
		min = temp;
	}

	return min+((max - min)*_alpha);
}

float Colors::alphaMap(float max){
	return alphaMap(0, max);
}

Colors Colors::getGradientStep(double cursorPosition, Colors targetColor){
	double start, end, finalRed, finalGreen, finalBlue;
	float startAlpha, endAlpha, finalAlpha;

	startAlpha = alpha(); endAlpha = targetColor.alpha();
	finalAlpha = (float)((double)startAlpha+(((double)endAlpha - (double)startAlpha)*cursorPosition));

	start = (double)red(); end = (double)targetColor.red();
	finalRed = start+((end - start)*cursorPosition);
	finalRed = finalRed < 0 ? 0 : (finalRed > 255 ? 255 : finalRed);

	start = (double)green(); end = (double)targetColor.green();
	finalGreen = start+((end - start)*cursorPosition);
	finalGreen = finalGreen < 0 ? 0 : (finalGreen > 255 ? 255 : finalGreen);

	start = (double)blue(); end = (double)targetColor.blue();
	finalBlue = start+((end - start)*cursorPosition);
	finalBlue = finalBlue < 0 ? 0 : (finalBlue > 255 ? 255 : finalBlue);

	return Colors((byte)finalRed, (byte)finalGreen, (byte)finalBlue, finalAlpha);
}

