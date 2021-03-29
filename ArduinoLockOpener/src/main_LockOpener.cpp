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
#include <stdint.h>
#include <SoftwareSerial.h>
#include "Leds.hpp"
#include "GsmCommunicationClass.h"





// the loop function runs over and over again forever
void main_ArduinoLockOpener() {
	
	SoftwareSerial GsmSerial(RX, TX); // RX TX
	
	GsmCommunicationClass GsmCommunication(&GsmSerial);
	
    DDRB = 0b00100000; // configure pin 7 of PORTB as output (digital pin 13 on the Arduino Mega2560) 
	LedManagerClass LedManager;
	PortClass Led1(&LedManager,6);
	
	_delay_ms(1000);
	Serial.write("Start\n");
	_delay_ms(1000);
	

    for(;;){
		_delay_ms(1500);
		GsmCommunication.checkConnection();		
	}
}
