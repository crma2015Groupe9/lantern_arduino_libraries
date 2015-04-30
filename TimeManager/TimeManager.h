#ifndef TimeManager_h
#define TimeManager_h

#include <limits.h>
#include "Arduino.h"

class TimeManager
{
	public:
		TimeManager();
		void init();
		void loopStart();
		void loopEnd();

		unsigned long total();
		unsigned long delta();
		int maxTimeCount();
		
	private:
		unsigned long _time;
		unsigned long _previousTime;
		unsigned long _deltaTime;
		int _maxTimeCount;
};

#endif