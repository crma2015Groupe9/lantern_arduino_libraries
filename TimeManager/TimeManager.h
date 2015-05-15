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
		unsigned int delta();
		
	private:
		unsigned long _time;
		unsigned long _previousTime;
};

#endif