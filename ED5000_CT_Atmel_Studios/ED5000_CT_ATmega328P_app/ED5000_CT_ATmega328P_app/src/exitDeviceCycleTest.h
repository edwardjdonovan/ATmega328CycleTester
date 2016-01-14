#ifndef ED_CylceTest_H
#define ED_CylceTest_H

#include "conf_gpio.h"
#include "conf_clock.h"
#include <util/delay.h>

#define retractionTimeTimerMode 800
#define protractionTimeTimerMode 1000

enum switchStates{
	switch1Open = 0x01,
	switch2Open = 0x02,
	
	allSwitchesClosed = 0x00,
	allSwitchesOpen = switch1Open|switch2Open,
	};
	
void exitDeviceCycleTest_init(void){
	
	DDRB = 0x00; //initialize all pins on port B as inputs
	DDRB |= (1<<DDB2) | (1<<DDB3); //pins 10 and 11 are set to outputs
	
	PORTB &= ~(1<<PINB3); //initialize pin 11 as low, controls the external dry counter
	
	return;
}
	
int protractExitBar(void){
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

int retractExitBar(void){
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

void incrementCounter(uint8_t incrementValue){
	//increment counter-falling edge
}
	
int exitDeviceCycleTest(void){
	int result = 0;
	exitDeviceCycleTest_init();
	result = protractExitBar();
	if(result !=0) return result;
	while(true){
		retractExitBar();
		if(result!=0) break;
		protractExitBar();
		if(result!=0) break;
		incrementCounter(1);
	}
	return result;
}

#endif //ED_CycleTest_H