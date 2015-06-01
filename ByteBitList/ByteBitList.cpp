#include "Arduino.h"
#include "ByteBitList.h"

ByteBitList::ByteBitList(){
	_bitList = 0;
}

void ByteBitList::setValue(byte index, boolean value){
	bitWrite(_bitList, index, (value ? 1 : 0));
}

boolean ByteBitList::getValue(byte index){
	return (boolean)bitRead(_bitList, index);
}