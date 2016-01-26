/*
 * debounceSwitch.h
 *
 * Created: 1/25/2016 4:02:54 PM
 *  Author: Edward Donovan
 */ 


#ifndef DEBOUNCESWITCH_H_
#define DEBOUNCESWITCH_H_

enum rawSwitchStates{
	rawSwitch1Open = 0x01,
	rawSwitch2Open = 0x02,
	
	allRawSwitchesClosed = 0x00,
	allRawSwitchesOpen = rawSwitch1Open|rawSwitch2Open,
};

extern rawKey1Pressed()
{
	if((PINB & rawSwitch1Open) == rawSwitch1Open) return false;
	else return true;
}
extern rawKey2Pressed()
{
	if((PINB & rawSwitch2Open) == rawSwitch2Open) return false;
	else return true;
}

//bool debouncedKey1Press = false;
//bool debouncedKey2Press = false;

bool debounceSwitch1()
{
	static uint16_t State = 0;
	State = (State<<1)| !rawKey1Pressed() | 0xe000;
	if(State == 0xf000) return true;
	return false;
}

bool debounceSwitch2()
{
	static uint16_t State = 0;
	State = (State<<1)|!rawKey2Pressed() | 0xe000;
	if(State == 0xf000) return true;
	return false;
}

#endif /* DEBOUNCESWITCH_H_ */