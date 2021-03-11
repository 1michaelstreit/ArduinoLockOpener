/****************************************************************************/
/*  Module     : Main                                           Version 1.0 */
/****************************************************************************/
/*																			*/
/*  Function   :														    */
/*                                                                          */
/*                                                                          */
/*  Procedures: main()                                                      */
/*                                                                          */
/*  Author     : Michael Streit												*/
/*                                                                          */
/*  History    : 10.03.2021  IO Created                                     */
/*                                                                          */
/*  File       : Main_LockOpener.cpp                                        */
/*                                                                          */
/****************************************************************************/
/*			                                                                */
/****************************************************************************/

/* imports */
#include <Arduino.h>
#include "Leds.hpp"
#include <stdint.h>
#include <SoftwareSerial.h>



// the loop function runs over and over again forever
void main_ArduinoLockOpener() {
	
	Serial.begin(9600);
	
	

    DDRB = 0b00100000; // configure pin 7 of PORTB as output (digital pin 13 on the Arduino Mega2560)
    
	LedManagerClass LedManager;
	PortClass Led1(&LedManager,6);
	
	
    for(;;)
    {
		//Serial.print("Hello World");
	    //PORTB = 0b00100000; // set 5th bit to HIGH
	    Led1.On();
		_delay_ms(500);
	    Led1.Off();
		//PORTB = 0b00000000; // set 5th bit to LOW
	    _delay_ms(500);
    }
}
