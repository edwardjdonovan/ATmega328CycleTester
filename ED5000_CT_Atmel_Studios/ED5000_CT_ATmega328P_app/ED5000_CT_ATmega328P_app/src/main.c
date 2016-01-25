/**
 * \file
 *
 * \brief 
 *
 */

 /**
 * \mainpage
 * \section intro Introduction
 * 
 *
 * \section files Files:
 * - main.c:
 * - asf.h:
 * - exitDeviceCycleTest:
 * - errorHandler:
 * - conf_gpio.h: 
 * - conf_clock.h: 
 *
 * \section setup Setup
 * This application firmware is made for ATmega328P-UP with four cables in the following
 * strap configuration:
 * - PORTB
 * - - PIN0 - INPUT FROM SWITCH 1 
 * - - PIN1 - INPUT FROM SWITCH 2 
 * - - PIN2 - OUTPUT TO TIMER+ 
 * - - PIN3 - OUTPUT TO EXTERNAL COUNTER
 *
 * \section description Description
 * The example will utilize different registers for setting and reading port
 * and pin GPIOs. These GPIOs are connected to switches, the Timer+ on the ED5000, and an external counter.
 *
 *
 *
 * \section compinfo Compilation Info
 * This software was written for the <A href="http://gcc.gnu.org/">GNU GCC</A>
 * for AVR. \n
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * Edward Donovan <A href="ed.donovan@assaabloy.com">Ed Donovan Email</A>. \n"
 * 
 */
#include "compiler.h"
#include <avr/interrupt.h>

#include "exitDeviceCycleTest.h"
#include "errorHandler.h"

/**
 * \brief Main routine
 */
int main(void)
{ 
	uint8_t error = 0;
	
	error = exitDeviceCycleTest();
	
	//only enter this loop if there is a failure
	errorHandler(error);
}
