/*****************************************************************************/
/*  Class      : SmsHandlerClass		                        Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   :                                    */
/*                                                                           */
/*                                                                           */
/*  Methodes   : TemplateClass()  ToDo                                       */
/*              ~TemplateClass()  ToDo                                       */
/*                                                                           */
/*  Author     : Michael Streit                                              */
/*                                                                           */
/*  History    : 30.03.2021  IO Created                                      */
/*                                                                           */
/*  File       : SmsHandlerClass.cpp                                         */
/*                                                                           */
/*****************************************************************************/
/* HTA Burgdorf                                                              */
/*****************************************************************************/


/* imports */
#include <string.h>
#include "Arduino.h"
#include "SmsHandlerClass.h"


/* Class constant declaration  */

/* Class Type declaration      */

/* Class data declaration      */

/* Class procedure declaration */

/*****************************************************************************/
/*  Method      : SmsHandlerClass		                                     */
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
SmsHandlerClass::SmsHandlerClass(GsmCommunicationClass *NewGsmCommunication, AuthorizationHandlerClass *NewAuthorizationHandler)
{
	GsmCommunication = NewGsmCommunication;
	AuthorizationHandler = NewAuthorizationHandler;
} //SmsHandlerClass

// default destructor
SmsHandlerClass::~SmsHandlerClass()
{
} //~SmsHandlerClass

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

void SmsHandlerClass::handleReceivedSms(ContactDirectoryClass *ContactDirectoryTemporary, ContactDirectoryClass *ContactDirectoryPermanent){
	
	if(strstr(GsmCommunication->receiveBuffer,"+CMT:") != NULL){	// if SMS received
		
		isolateSmsSenderPhoneNr(&(GsmCommunication->receiveBuffer[0]));	
		
		
		
		// check Authorization
		if(AuthorizationHandler->checkAuthorization((char*)&smsSenderNr,ContactDirectoryTemporary,ContactDirectoryPermanent) == 1){	// check if sms seder is authorized
			Serial.write("SMS sender AUTHORIZED !\n");
			
			// read sms Msg out of the receive Buffer
			readSms((char*)&GsmCommunication->receiveBuffer);
			newSmsReceived = true;
			// handle sms commands
			}else{
				Serial.write("SMS sender DECLINED \n");
				newSmsReceived = false;			// set flag for execute Comands
			}
		}else{
		newSmsReceived = false;
	}
}

void SmsHandlerClass::readSms(char *buffer){
	int textStart = 0;
	int i = 0;
	
	for(int u=0;(buffer[u]!='\0')||((buffer[u]=='A')&&(buffer[u+1]=='T')&&(buffer[u+2]=='+')); u++){
		// trigger start of SMS message
		if(((buffer[u-3]=='"')&&(buffer[u-2]==13)&&(buffer[u-1]==10))|| (textStart == 1)){
			textStart = 1;
			smsMsg[i]=buffer[u];
			i++;
		}
	}
	smsMsg[i]='\0';	
}

void SmsHandlerClass::isolateSmsSenderPhoneNr(char *buffer){
    char *retBuf;
    int u = 0;
    retBuf = strstr(buffer,"+CMT:");		// find beginning of sms sender
    if(retBuf != NULL){						// if SMS sender Nr received
        for(u=0; retBuf[u+7] !='\"';u++){	// fill Nr into variable until end of Nr reached
            smsSenderNr[u] = retBuf[u+7];
        }
        smsSenderNr[u]='\0';
    }else{
        smsSenderNr[u]='\0';
    }
	
	// Display SMS sender
	Serial.write("SMS sender: ");
	GsmCommunication->displayString(smsSenderNr);
	Serial.write("\n\n");	
}


