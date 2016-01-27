/*
 * exitDeviceCycleTest.h
 *
 *  Author: Ed Donovan
 */ 

#ifndef ED_CylceTest_H
#define ED_CylceTest_H

#include "conf_gpio.h"
#include "conf_clock.h"
#include "debounceSwitch.h"
#include <util/delay.h>

#include "counter.h"
#include "errorHandler.h"

#define timerPosPin	

#define retractionTimeTimerMode 2000
#define protractionTimeTimerMode 2000

#define minAssertTimeMS 500

enum switchStates{
	switch1Open = 0x01,
	switch2Open = 0x02,
	
	allSwitchesClosed = 0x00,
	allSwitchesOpen = switch1Open|switch2Open,
	};
	
void exitDeviceCycleTest_init(void){
	
	DDRB = 0x00; //initialize all pins on port B as inputs
	DDRB |= (1<<DDB2) ; //pins 10 is set to output
	PORTB |= (1<<PINB0) | (1<<PINB1);  //enable internal pullups on pins 8 and 9
	PORTB |= (1<<PINB2);  //allow bar to protract
	return;
}

void assertRetraction(void){
	PORTB &= ~(1<<PINB2); //assert bar retract
	_delay_ms(minAssertTimeMS);
	PORTB |= (1<<PINB2); //allow bar protract
}
	
int checkProtractExitBar(){
	
	bool debouncedSwitch2State;
	bool debouncedSwitch1State;	
	
	for (int i = 0; i < 200; i++) {
		debouncedSwitch1State = debounceSwitch1();
		if(debouncedSwitch1State) break;
		_delay_ms(5);
	}
		

	if(!debouncedSwitch1State){
		return 1;
		//if switch1 is closed, continue, if its open, break out of main loop
	}
	
	for (int h = 0; h < 10; h++) {
		debouncedSwitch2State = debounceSwitch2();
		if(debouncedSwitch2State) break;
		_delay_ms(5);
		}
	

	if(debouncedSwitch2State){
		return 4;
		//if switch2 is closed, contiue; if closed, break
	}		
	return 0;
}

int checkRetractExitBar(){
	
	//new code
	
	bool debouncedSwitch2State; 
	bool debouncedSwitch1State;

	
	for (int j = 0; j < 200; j++){ 
		debouncedSwitch2State = debounceSwitch2();
		if(debouncedSwitch2State) break;
		_delay_ms(5);
	}	

	if(!debouncedSwitch2State){
		return 2;
		//if switch2 is closed, contiue; if closed, break
	}

	
	for (int k = 0; k < 10; k++) {
		debouncedSwitch1State = debounceSwitch1();
		if(debouncedSwitch1State) break;
		_delay_ms(5);
	}
	
	if(debouncedSwitch1State){
		return 3;
		//if switch1 is closed, continue, if its open, break out of main loop
	}	
	return 0;
}

	
int exitDeviceCycleTest(void){
	uint32_t counter = 0;
	int result = 0;
	exitDeviceCycleTest_init();
	counter_init();
	//need to protract exit bar and evaluate state
	result = checkProtractExitBar();
	if(result !=0) {
		if (result == 1){
			errorEEPROMWrite(counter, 5);
			return 5;
			 }
		else if(result == 4) {
			errorEEPROMWrite(counter, 6);
			return 6;
			}
		else{
			errorEEPROMWrite(counter, result);
			return result;	//retvalue are 5 and 6 to differentiate initialization failure from bar protraction failure
		}
	}
	
	while(true){

		/*new code*/
		//assertRetraction();
		/*end new code*/	
	
		result = checkRetractExitBar();
		if(result!=0) {
			errorEEPROMWrite(counter, result);
			return result;
		}
		
		_delay_ms(500); //needs to be at least 400mS
		
		result = checkProtractExitBar();
		if(result!=0){
			errorEEPROMWrite(counter, result);
			return result;
		}
		incrementCounter(1);	//costs 200ms
		counter = counter+1;
	}
	return result;
}

#endif //ED_CycleTest_H