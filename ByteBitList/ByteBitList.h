#ifndef ByteBitList_h
#define ByteBitList_h

#include "Arduino.h"

class ByteBitList
{
	public:
		ByteBitList();

		void setValue(byte index, boolean value);
		boolean getValue(byte index);

	private:
		byte _bitList;
};

#endif