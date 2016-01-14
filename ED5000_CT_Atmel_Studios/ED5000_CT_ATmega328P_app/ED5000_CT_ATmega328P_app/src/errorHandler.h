#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include "conf_gpio.h"

void errorHandler_init(){
	DDRB |= (1<<DDB5); //initialize pin 13 to control LED
}

void errorHandler(uint8_t errorCode){
	
	errorHandler_init();
	
	//loop until MCU is reset manually
	while(true){
		
		for (uint8_t i = 0; i<errorCode;i++)
		{
			PORTB |= (1<<PINB5);
			_delay_ms(500);
			PORTB &= ~(1<<PINB5);
			_delay_ms(500);
		}
		
	_delay_ms(1500);
	
	}
	return; //should never reach this
}

#endif //ERROR_HANDLER_H