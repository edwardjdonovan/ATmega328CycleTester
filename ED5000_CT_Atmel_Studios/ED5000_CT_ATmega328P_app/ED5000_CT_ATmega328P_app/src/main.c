/**
 * \file
 *
 * \brief megaAVR STK600 GPIO Example
 *
 * Copyright (c) 2014-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

 /**
 * \mainpage
 * \section intro Introduction
 * This example demonstrates GPIO port access, pin access, pin interrupt and
 * pin pull up configuration.
 *
 * \section files Files:
 * - mega_gpio_example.c: megaAVR GPIO example application
 * - conf_example.h: Example configuration
 *
 * \section setup Setup
 * This example is made for STK600 with two 10-pin cables in the following
 * strap configuration:
 * - PORTB <-> SWITCHES
 * - PORTD <-> LEDS
 *
 * \section description Description
 * The example will utilize different registers for setting and reading port
 * and pin GPIOs. These GPIOs are connected to switches and LEDs on the STK600.
 *
 * In the end of the example pin change interrupts are enabled and can be
 * tested with STK600 SW0. This will toggle LED0 from the interrupt handler.
 * Not all megaAVR devices supports pin change interrupts, so for those this
 * is disabled.
 *
 * For the best demonstration it's recommended to run this in a debug session
 * and single step through the different operations.
 *
 * \section compinfo Compilation Info
 * This software was written for the <A href="http://gcc.gnu.org/">GNU GCC</A>
 * for AVR. \n
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.atmel.com/">Atmel</A>.\n
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include "compiler.h"
#include <avr/interrupt.h>
//#include "conf_gpio.h"
//#include "conf_clock.h"
//#include <util/delay.h>

#include "exitDeviceCycleTest.h"
#include "errorHandler.h"

// Only use Pin Change Interrupt handler for devices supporting this.
#ifdef EXAMPLE_PCINT_vect

/**
 * \brief Pin change interrupt handler for PB0
 *
 * Create breakpoint here and then run. Press SW0 in order to test
 * this.
 */
ISR(EXAMPLE_PCINT_vect)
{

}

#endif

//#define retractionTimeTimerMode 800
//#define protractionTimeTimerMode 1000

//switch states bitmasks
/*enum switchStates{
	switch1Open = 0x01,
	switch2Open = 0x02,
	
	allSwitchesClosed = 0x00,
	allSwitchesOpen = switch1Open|switch2Open,
	};*/

/**
 * \brief Main routine
 */
int main(void)
{ 

	/*uint8_t error = 0;
	uint8_t fail = 0;
	
	DDRB = 0x00; //initialize all pins on port B as inputs
	DDRB |= (1<<DDB2) | (1<<DDB3); //pins 10 and 11 are set to outputs
	
	PORTB |= (1<<PINB2); //initialize pin 10 as high to protract bar
	PORTB &= ~(1<<PINB3); //initialize pin 11 as low, controls the external dry counter
	
	//check to see if switch 1 is closed
	if((PINB & switch1Open) == switch1Open){
		error = 5;
		//if switch1 is closed, continue, if its open, break out of main loop
		fail = 1;
	}
	
	while(!fail){
		
		PORTB &= ~(1<<PINB2); //trigger bar retract
		
		_delay_ms(retractionTimeTimerMode); //wait 800 milliseconds
		
		if((PINB & switch2Open) == switch2Open){
			error = 2;
			//if switch2 is closed, contiue; if closed, break
			break;
		}
		if((PINB & switch1Open) != switch1Open){
			error = 3;
			//if switch1 is closed, continue, if its open, break out of main loop
			break;
		}		
		
		
		PORTB |= (1<<PINB2);  //allow bar to protract
		
		_delay_ms(protractionTimeTimerMode);
		
		if((PINB & switch1Open) == switch1Open){
			error = 1;
			//if switch1 is closed, continue, if its open, break out of main loop
			break;
		}
		if((PINB & switch2Open) != switch2Open){
			error = 4;
			//if switch2 is closed, contiue; if closed, break
			break;
		}		
		 //increment counter
	}*/
	
	uint8_t error = 0;
	error = exitDeviceCycleTest();
	
	DDRB |= (1<<DDB5); //set pin 13 to output to control LED
	
	//only enter this loop if there is a failure
	
	errorHandler(error);
	
	/*while(true){
		
		for (uint8_t i = 0; i<error;i++)
		{
			PORTB |= (1<<PINB5);
			_delay_ms(500);
			PORTB &= ~(1<<PINB5);
			_delay_ms(500);
		}
		_delay_ms(1500);
	}*/
	
}
