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
#include "SmsHandlerClass.h"
#include "AuthorizationHandlerClass.h"
#include "EepromClass.h"
#include "CmdContactClass.h"

/* Class constant declaration  */

/* Class Type declaration      */

/* Class data declaration      */

/* Class procedure declaration */


// the loop function runs over and over again forever
void main_ArduinoLockOpener() {
	
	// create gsmSerial 
	SoftwareSerial GsmSerial(RX, TX); // RX TX
	
	// create eeprom object
	EepromClass Eeprom1;
	
	GsmCommunicationClass GsmCommunication(&GsmSerial);
	AuthorizationHandlerClass AuthorizationHandler(&GsmCommunication,&Eeprom1);
	CmdContactClass SmsHandler(&Eeprom1, &GsmCommunication, &AuthorizationHandler);

	// clear EEPROM and add standard contacts
	Eeprom1.clearEeprom();
	
	Eeprom1.addContactToEeprom("Michael Streit","786750902");
	
	
    //DDRB = 0b00100000; // configure pin 7 of PORTB as output (digital pin 13 on the Arduino Mega2560) 
	GpioPortClass GpioPortB((uint8_t*)0x25);
	GpioPortClass GpioPortD((uint8_t*)0x2B);
	GPIOLedClass LedBuiltIn(&GpioPortB,LED_BUILTIN);// bult in LED
	LockOpenerClass LockRepresentationLed(&GpioPortB,LED_STATE);	// Lock repesentation LED
	LockOpenerClass Lock(&GpioPortD,LOCK);							// real Lock Port unused
	
	Serial.write("Start \r\n");
	_delay_ms(1000);
	

    for(;;){
		GsmCommunication.checkConnection();	
		GsmCommunication.readSerial();	
		SmsHandler.handleReceivedSms();
		SmsHandler.executeSmsCmd();
		AuthorizationHandler.handleReceivedCall(&LockRepresentationLed);
		
		LedBuiltIn.Toggle();
	}
}
