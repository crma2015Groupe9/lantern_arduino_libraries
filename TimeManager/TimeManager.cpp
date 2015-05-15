#include "Arduino.h"
#include "TimeManager.h"

TimeManager::TimeManager(){
}

void TimeManager::init(){
	_time = millis();
	_previousTime = _time;
}

void TimeManager::loopStart(){
	_time = millis();
}

void TimeManager::loopEnd(){
	_previousTime = _time;
}

unsigned long TimeManager::total(){
	return _time;
}

unsigned int TimeManager::delta(){
	if(_time >= _previousTime){
		return (unsigned int)(_time - _previousTime);
	}

	return (unsigned int)(ULONG_MAX - _previousTime + _time);
}