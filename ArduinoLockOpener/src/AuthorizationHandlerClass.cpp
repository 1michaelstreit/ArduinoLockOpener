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

void AuthorizationHandlerClass::handleReceivedCall(){
	if(strstr(GsmCommunication->receiveBuffer, "RING") != NULL){ // if call received
		// check phone Number from caller
		GsmCommunication->sendAtCmd("AT+CLCC");	
		GsmCommunication->readSerial();
		if(checkAuthorization(&GsmCommunication->receiveBuffer[0]) == 1){
			Serial.write("Number authorized -> OPEN LOCK \n\n");
			answerCall();		
			// open lock
		}else{
			Serial.write("Number DECLINED \n\n");
		}
	}
}

int AuthorizationHandlerClass::checkAuthorization(char *nrToCheck){
	Serial.write("CheckAuthorization\n");
	//displayString(nrToCheck);
	return(1);
}

void AuthorizationHandlerClass::answerCall(){
	GsmCommunication->sendAtCmd("ATA");
	GsmCommunication->readSerial();
	GsmCommunication->sendAtCmd("AT+CVHU=0");
	GsmCommunication->readSerial();
	GsmCommunication->sendAtCmd("ATH");
	GsmCommunication->readSerial();
}