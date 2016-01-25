/*
 * errorHandler.h
 *
 *  Author: Ed Donovan
 */ 

#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include "conf_gpio.h"
#include <avr/eeprom.h>

void errorHandler_init(){
	DDRB |= (1<<DDB5); //initialize pin 13 to control LED
	DDRB |= (1<<DDB4); //initialize pin 12 to output, only use for debugging during development
	PORTB |= (1<<PINB4); //raise fail flag for oscilloscope trigger
}

void errorEEPROMWrite(uint32_t count ,uint8_t error){
	unsigned int init_addr = 0x0000;
	uint8_t error_intro = 0xfc;
	uint16_t next_addr = eeprom_read_word((uint16_t*)init_addr);
	if(next_addr == 0xffff || 0x0000){
	 next_addr = 0x0015;
	}
	else if(next_addr >= 0x03f0){
		next_addr = 0x0015;
	}
	else {
		next_addr = next_addr + 0x0015;
	}
	uint8_t err_addr = next_addr + 0x0004;
	eeprom_write_word((uint16_t*)init_addr, next_addr);
	eeprom_write_dword((uint32_t*)next_addr,count);
	eeprom_write_byte((uint8_t*)err_addr, error_intro);
	err_addr = err_addr + 1;
	eeprom_write_byte((uint8_t*)err_addr,error);
	
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