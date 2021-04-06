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
	
	delay(2000);
	
	SoftwareSerial GsmSerial(RX, TX); // RX TX
	
	// creat Contact directories
	//ContactDirectoryClass ContactDirectoryTemporary("Temporary");
	//ContactDirectoryClass ContactDirectoryPermanent("Permanent");
	
	// create eeprom object
	EepromClass Eeprom1;
	
	GsmCommunicationClass GsmCommunication(&GsmSerial);
	AuthorizationHandlerClass AuthorizationHandler(&GsmCommunication,&Eeprom1);
	CmdContactClass SmsHandler(&GsmCommunication,&AuthorizationHandler);

	Eeprom1.clearEeprom();
	
	//Eeprom1.eepromToContactDirectory(&ContactDirectoryPermanent); // make permanent List out of Eeprom
	
	Eeprom1.addContactToEeprom("Michael Streit","786750902");
	//Eeprom1.addContactToEeprom("Hans","564418910");
	//Eeprom1.addContactToEeprom("Anna","564418784");
	
	
    //DDRB = 0b00100000; // configure pin 7 of PORTB as output (digital pin 13 on the Arduino Mega2560) 
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
		SmsHandler.handleReceivedSms();
		SmsHandler.executeSmsCmd();
		AuthorizationHandler.handleReceivedCall(&LockLed);
		
		
		//LockLed.Toggle();	// makes error on PORTD for Serial communication
		
		LedState.Toggle();
		LedBuiltIn.Toggle();
		_delay_ms(100);		
	}
}
