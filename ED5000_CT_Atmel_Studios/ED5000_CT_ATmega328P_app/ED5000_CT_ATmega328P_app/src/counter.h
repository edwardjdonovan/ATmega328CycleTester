/*
 * counter.h
 *
 * Created: 1/15/2016 3:16:12 PM
 *  Author: Ed Donovan
 */ 


#ifndef COUNTER_H_
#define COUNTER_H_

#include "conf_gpio.h"
#include "conf_clock.h"
#include <util/delay.h>

void counter_init(void){
	DDRB |= (1<<DDB3);
	PORTB |= (1<<PINB3); //initialize pin 11 as high (pin11 is counter)
	//PORTB &= ~(1<<PINB3); //initialize pin 11 as low, controls the external dry counter
}


void incrementCounter(uint8_t incrementValue){
		for(int i = 0; i < incrementValue; i++){
		PORTB &= ~(1<<PINB3); 
		_delay_ms(100);
		PORTB |= (1<<PINB3);
		_delay_ms(100);
	}
}


#endif /* COUNTER_H_ */