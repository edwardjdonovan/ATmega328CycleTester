/*
 * exitDeviceCycleTest.h
 *
 *  Author: Ed Donovan
 */ 

#ifndef ED_CylceTest_H
#define ED_CylceTest_H

#include "conf_gpio.h"
#include "conf_clock.h"
#include <util/delay.h>

#include "counter.h"
#include "errorHandler.h"

#define timerPosPin	

#define retractionTimeTimerMode 2000
#define protractionTimeTimerMode 2000

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
	return;
}
	
int protractExitBar(){
	
	PORTB |= (1<<PINB2);  //allow bar to protract
		
	_delay_ms(protractionTimeTimerMode);
		
	if((PINB & switch1Open) == switch1Open){
		return 1;
		//if switch1 is closed, continue, if its open, break out of main loop
	}
	if((PINB & switch2Open) != switch2Open){
		return 4;
		//if switch2 is closed, contiue; if closed, break
	}		
	return 0;
}

int retractExitBar(){
	
	PORTB &= ~(1<<PINB2); //trigger bar retract
		
	_delay_ms(retractionTimeTimerMode); //wait 800 milliseconds
		
	if((PINB & switch2Open) == switch2Open){
		return 2;
		//if switch2 is closed, contiue; if closed, break
	}
	if((PINB & switch1Open) != switch1Open){
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
	result = protractExitBar();
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
		result = retractExitBar();
		if(result!=0) {
			errorEEPROMWrite(counter, result);
			return result;
		}
		result = protractExitBar();
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