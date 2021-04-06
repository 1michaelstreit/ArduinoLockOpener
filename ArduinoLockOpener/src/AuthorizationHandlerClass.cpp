/*****************************************************************************/
/*  Class      : AuthorizationHandlerClass                      Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   :                                    */
/*                                                                           */
/*                                                                           */
/*  Methodes   : AuthorizationHandlerClass()  ToDo                           */
/*              ~AuthorizationHandlerClass()  ToDo                           */
/*                                                                           */
/*  Author     : Michael Streit                                              */
/*                                                                           */
/*  History    : 30.03.2021  IO Created                                      */
/*                                                                           */
/*  File       : AuthorizationHandlerClass.cpp                               */
/*                                                                           */
/*****************************************************************************/
/* HTA Burgdorf                                                              */
/*****************************************************************************/

/* imports */
#include "Arduino.h"
#include "AuthorizationHandlerClass.h"
#include "EEPROM.h"



/* Class constant declaration  */
#define NR_OF_MATCHING_DIGITS 9

/* Class Type declaration      */

/* Class data declaration      */

/* Class procedure declaration */

/*****************************************************************************/
/*  Method      : AuthorizationHandlerClass                                  */
/*****************************************************************************/
/*                                                                           */
/*  Function    :                                                            */
/*                                                                           */
/*  Type        : Constructor                                                */
/*                                                                           */
/*  Input Para  :                                                            */
/*                                                                           */
/*  Output Para :                                                            */
/*                                                                           */
/*  Author      : Michael Streit                                             */
/*                                                                           */
/*  History     : 30.03.2021  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
AuthorizationHandlerClass::AuthorizationHandlerClass(GsmCommunicationClass *NewCommunication, EepromClass *NewEeprom1)
{
	GsmCommunication = NewCommunication;
	eeprom1 = NewEeprom1;
} //AuthorizationHandlerClass

// default destructor
AuthorizationHandlerClass::~AuthorizationHandlerClass()
{
} //~AuthorizationHandlerClass

/*****************************************************************************/
/*  Method      : 		                                     */
/*****************************************************************************/
/*                                                                           */
/*  Function    :                                                            */
/*                                                                           */
/*  Type        :			                                                */
/*                                                                           */
/*  Input Para  :                                                            */
/*                                                                           */
/*  Output Para :                                                            */
/*                                                                           */
/*  Author      : Michael Streit                                             */
/*                                                                           */
/*  History     : 30.03.2021  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/

void AuthorizationHandlerClass::handleReceivedCall(GPIOLedClass *LockLed){
	if(strstr(GsmCommunication->receiveBuffer, "RING") != NULL){ // if call received
		
		// check phone Number from caller
		GsmCommunication->sendAtCmd((char*)"AT+CLCC");	
		GsmCommunication->readSerial();
		
		
		
		if(checkAuthorization(GsmCommunication->receiveBuffer) == 1){	// if Nr of caller is authorized
			Serial.write("Number authorized -> OPEN LOCK \n\n");
			answerCall();
			delay(1000);		
			// open lock
			LockLed->On();
			delay(1000);
			LockLed->Off();
		}else{
			Serial.write("Number DECLINED \n\n");
		}
	}
}

int AuthorizationHandlerClass::checkAuthorization(char *nrToCheck){
	int i = 0;
	int v = 0;
	int nrOfMatchDigits = 0;
	int eepromAddress = eeprom1->getEepromAddress();
	
	Serial.write("CheckAuthorization\n");
	
	// check temporary numbers
	Serial.write("phone numbers in Contacts:\n");
	
	eeprom1->displayEeprom();
	
	// return 1 if minimum nr of digits matching
	for(i=0; i<eepromAddress;i++){								// until end of eeprom data reached
		for(v=0;nrToCheck[v]!='\0';v++){						// until string end
			if(nrToCheck[v]==EEPROM.read(i+nrOfMatchDigits)){	// compare single digits
				nrOfMatchDigits++;								// increase if matching Digit
				}else{
				nrOfMatchDigits = 0;					
			}
			if(nrOfMatchDigits>=NR_OF_MATCHING_DIGITS){			// return 1 if min matching digits reached
				return(1);
			}
			if((i+1)%9==0 && i!=0){
				nrOfMatchDigits = 0;
			}
		}
	}
	return(0);		// return 0 if no matching phone number was detected
}


void AuthorizationHandlerClass::answerCall(){
	
	// hang up incoming Call
	GsmCommunication->sendAtCmd("ATA");
	GsmCommunication->readSerial();
	GsmCommunication->sendAtCmd("AT+CVHU=0");
	GsmCommunication->readSerial();
	GsmCommunication->sendAtCmd("ATH");
	GsmCommunication->readSerial();
}