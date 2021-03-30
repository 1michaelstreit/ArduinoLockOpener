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
#include "GsmCommunicationClass.h"


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
SmsHandlerClass::SmsHandlerClass(GsmCommunicationClass *NewGsmCommunication)
{
	GsmCommunication = NewGsmCommunication;
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

void SmsHandlerClass::handleReceivedSms(){
	if(strstr(GsmCommunication->receiveBuffer,"+CMT:") != NULL){	// if SMS received
		
		isolateSmsSenderPhoneNr(&(GsmCommunication->receiveBuffer[0]));
		
		// check Authorization
		if(GsmCommunication->checkAuthorization(&smsSenderNr[0]) == 1){
			Serial.write("SMS sender AUTHORIZED !\n");
			
			// read sms Msg out of the receive Buffer
			readSms(&(GsmCommunication->receiveBuffer[0]));
			
			// handle sms commands
			//GsmCommunication->displayString(smsMsg);		// for debbuging
			if(strstr(smsMsg,"Globi 18") != NULL){
				Serial.write("Msg Globi received\n");
			}
		}
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