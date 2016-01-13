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
#include "conf_gpio.h"
#include <util/delay.h>

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


/**
 * \brief Main routine
 */
int main(void)
{
	// Variable to put switch input into
	uint8_t switch1;
	uint8_t switch2;
	
	DDRB = 0x00; //initialize all pins on port B as inputs
	DDRB |= (1<<DDB2) | (1<<DDB3); //pins 10 and 11 are set to outputs
	
	switch1 = PINB0;	//pin 8 is limit switch 1
	switch2 = PINB1;	//pin 9 is limit switch 2
	
	PORTB |= (1<<PINB2); //initialize pin 10 as high to protract bar
	PORTB &= ~(1<<PINB3); //initialize pin 11 as low, controls the external dry counter
	
	//check to see if switch 1 is closed
	if(switch1 == 0){
		//break out of main loop
	}
	
	while(true){
		
		PORTB &= ~(1<<PINB2); //trigger bar retract
		
		_delay_ms(1000); //wait 1 second
		
		if(switch2 == 0){
			//if switch2 is closed, contiue; if closed, break
			break;
		}
		PORTB |= (1<<PINB2);
		_delay_ms(1000);
		
		if(switch1 == 0){
			//check state of switch1
			break;
		}
		
		PORTB = 1; //increment counter
	}
}
