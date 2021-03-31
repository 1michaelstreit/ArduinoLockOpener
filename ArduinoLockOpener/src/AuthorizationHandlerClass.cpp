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


/* Class constant declaration  */

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
AuthorizationHandlerClass::AuthorizationHandlerClass(GsmCommunicationClass *NewCommunication)
{
	GsmCommunication = NewCommunication;
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

void AuthorizationHandlerClass::handleReceivedCall(ContactDirectoryClass *ContactDirectoryTemporary, ContactDirectoryClass* ContactDirectoryPermanent){
	if(strstr(GsmCommunication->receiveBuffer, "RING") != NULL){ // if call received
		// check phone Number from caller
		GsmCommunication->sendAtCmd((char*)"AT+CLCC");	
		GsmCommunication->readSerial();
		if(checkAuthorization((char*)&GsmCommunication->receiveBuffer, ContactDirectoryTemporary) == 1		// check all contacts
		|| checkAuthorization((char*)&GsmCommunication->receiveBuffer, ContactDirectoryPermanent) == 1){
			Serial.write("Number authorized -> OPEN LOCK \n\n");
			answerCall();		
			// open lock
		}else{
			Serial.write("Number DECLINED \n\n");
		}
	}
}

int AuthorizationHandlerClass::checkAuthorization(char *nrToCheck, ContactDirectoryClass *ContactDirectory){
	char displayString[100] = {0};
	
	Serial.write("CheckAuthorization\n");
	
	ContactClass *currentContact = ContactDirectory->head;
	int numberOfMatchingDigits = 0;
	
	// check temporary numbers
	Serial.write("phone numbers in Contacts:\n");
	while(currentContact != NULL){		// until end of list reached
		sprintf(displayString,"phone number: %s		Name: %s \n", currentContact->phoneNumber, currentContact->Name);
		Serial.write(displayString);	// display current phone nr
		
		_delay_ms(100);		// for debug
		
		for(int u=0; nrToCheck[u] != '\0'; u++){
			if(nrToCheck[u] == currentContact->phoneNumber[numberOfMatchingDigits]){ // compare the single digits
				numberOfMatchingDigits++;
			}else{
				numberOfMatchingDigits = 0;
			}
			if(numberOfMatchingDigits >= MATCHING_DIGITS){	// return 1 if Number matches
				return(1);
			}
		}
		currentContact = currentContact->next;	// rearch in next contact in the list
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