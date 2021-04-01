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
#include "ContactDirectoryClass.h"
#include "EepromClass.h"
#include "CmdContactClass.h"



// the loop function runs over and over again forever
void main_ArduinoLockOpener() {
	
	delay(2000);
	
	SoftwareSerial GsmSerial(RX, TX); // RX TX
	
	// creat Contact directories
	ContactDirectoryClass ContactDirectoryTemporary("Temporary");
	ContactDirectoryClass ContactDirectoryPermanent("Permanent");
	
	GsmCommunicationClass GsmCommunication(&GsmSerial);
	AuthorizationHandlerClass AuthorizationHandler(&GsmCommunication);
	CmdContactClass SmsHandler(&GsmCommunication,&AuthorizationHandler);
	

	
	EepromClass Eeprom1;
	Eeprom1.clearEeprom();
	
	Eeprom1.eepromToContactDirectory(&ContactDirectoryPermanent); // make permanent List out of Eeprom
	
	ContactDirectoryPermanent.addContact("Michael Streit","786750902",PERMANENT);
	

	
	//ContactDirectoryTemporary.addContact("Martin Streit","564418910",TEMPORARY);
	
	
    DDRB = 0b00100000; // configure pin 7 of PORTB as output (digital pin 13 on the Arduino Mega2560) 
	GpioPortClass GpioPortB((uint8_t*)0x25);
	GpioPortClass GpioPortD((uint8_t*)0x2B);
	GPIOLedClass LedBuiltIn(&GpioPortB,LED_BUILTIN);
	GPIOLedClass LedState(&GpioPortB,LED_STATE);
	GPIOLedClass LockLed(&GpioPortD,LOCK);
	
	_delay_ms(1000);
	Serial.write("Start\n");
	_delay_ms(1000);
	

    for(;;){
		GsmCommunication.checkConnection();	
		GsmCommunication.readSerial();	
		SmsHandler.handleReceivedSms(&ContactDirectoryTemporary, &ContactDirectoryPermanent);
		SmsHandler.executeSmsCmd(&ContactDirectoryTemporary,&ContactDirectoryPermanent);
		AuthorizationHandler.handleReceivedCall(&ContactDirectoryTemporary,&ContactDirectoryPermanent);
		
		
		//LockLed.Toggle();	// makes error on PORTD for Serial communication
		
		//LedState.Toggle();
		//LedBuiltIn.Toggle();
		_delay_ms(100);		
	}
}
