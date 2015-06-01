#include "Arduino.h"
#include "TimeManager.h"

TimeManager::TimeManager(){
}

void TimeManager::init(){
	_time = millis();
	_previousTime = _time;
	_deltaTime = 0;
	_maxTimeCount = 0;
}

void TimeManager::loopStart(){
	_time = millis();
	if(_time >= _previousTime){
		_deltaTime = (unsigned int)(_time - _previousTime);
	}
	else{
		_deltaTime = (unsigned int)(ULONG_MAX - _previousTime + _time);
		_maxTimeCount++;
	}
}

void TimeManager::loopEnd(){
	_previousTime = _time;
}

unsigned long TimeManager::total(){
	return _time;
}

unsigned int TimeManager::delta(){
	return _deltaTime;
}

byte TimeManager::maxTimeCount(){
	return _maxTimeCount;
}