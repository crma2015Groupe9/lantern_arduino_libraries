#include "Arduino.h"
#include "Colors.h"

Colors::Colors(){
	_red = 0;
	_green = 0;
	_blue = 0;
}

Colors::Colors(byte red, byte green, byte blue){
	_red = red;
	_green = green;
	_blue = blue;
}

void Colors::setColor(byte red, byte green, byte blue){
	setRed(red);
	setGreen(green);
	setBlue(blue);
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

byte Colors::red(){
	return _red;
}
byte Colors::green(){
	return _green;
}
byte Colors::blue(){
	return _blue;
}

Colors Colors::getGradientStep(double cursorPosition, Colors targetColor){
	double start, end, finalRed, finalGreen, finalBlue;

	start = (double)red(); end = (double)targetColor.red();
	finalRed = start+((end - start)*cursorPosition);
	finalRed = finalRed < 0 ? 0 : (finalRed > 255 ? 255 : finalRed);

	start = (double)green(); end = (double)targetColor.green();
	finalGreen = start+((end - start)*cursorPosition);
	finalGreen = finalGreen < 0 ? 0 : (finalGreen > 255 ? 255 : finalGreen);

	start = (double)blue(); end = (double)targetColor.blue();
	finalBlue = start+((end - start)*cursorPosition);
	finalBlue = finalBlue < 0 ? 0 : (finalBlue > 255 ? 255 : finalBlue);

	return Colors((byte)finalRed, (byte)finalGreen, (byte)finalBlue);
}

Colors Colors::getColorWithAlpha(float alpha){
	double start, finalRed, finalGreen, finalBlue;
	float opacity = 1.0 - alpha;

	start = (double)red();
	finalRed = start * (double)opacity;
	finalRed = finalRed < 0 ? 0 : (finalRed > 255 ? 255 : finalRed);

	start = (double)green();
	finalGreen = start * (double)opacity;
	finalGreen = finalGreen < 0 ? 0 : (finalGreen > 255 ? 255 : finalGreen);

	start = (double)blue();
	finalBlue = start * (double)opacity;
	finalBlue = finalBlue < 0 ? 0 : (finalBlue > 255 ? 255 : finalBlue);

	return Colors((byte)finalRed, (byte)finalGreen, (byte)finalBlue);
}

