/*****************************************************************************/
/*  Class      : SmsHandlerClass		                        Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : This class handles the incoming SMS                         */
/*                                                                           */
/*                                                                           */
/*  Methodes   : TemplateClass()											 */
/*              ~TemplateClass()											 */
/*              readSms()                                                    */
/*              isolateSmsSenderPhoneNr()                                    */
/*              handleReceivedSms()                                          */
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
/*  Function    : Constructor                                                */
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
/*  Method      : handleReceivedSms		                                     */
/*****************************************************************************/
/*                                                                           */
/*  Function    : If a new sms was received, it will be checked the phone    */
/*                number of the sender and checks his authorization          */
/*                if the number is ok, commands can be executed				 */
/*                                                                           */
/*                                                                           */
/*  Input Para  : -                                                          */
/*                                                                           */
/*  Output Para : -                                                          */
/*                                                                           */
/*  Author      : Michael Streit                                             */
/*                                                                           */
/*  History     : 30.03.2021  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
void SmsHandlerClass::handleReceivedSms(){
	
	if(strstr(GsmCommunication->receiveBuffer,"+CMT:") != NULL){	// if SMS received
		
		isolateSmsSenderPhoneNr(smsSenderNr, GsmCommunication->receiveBuffer);
		
		if(AuthorizationHandler->checkAuthorization(smsSenderNr) == 1){	// check if sms seder is authorized
			Serial.write("SMS sender AUTHORIZED !\n");
			
			
			readSms(smsMsg, GsmCommunication->receiveBuffer);			// read sms Msg out of the receive Buffer
			newSmsReceived = true;						// set flag for execute sms CMDs
			// handle sms commands
			}else{
			Serial.write("SMS sender DECLINED \n");
			newSmsReceived = false;			// set flag for execute Comands
		}
		}else{
		newSmsReceived = false;
	}
}

/*****************************************************************************/
/*  Method      : readSms				                                     */
/*****************************************************************************/
/*                                                                           */
/*  Function    : reads sms message out of buffer and stores it in the target*/
/*                                                                           */
/*                                                                           */
/*  Input Para  : target: pointer where to write in result                   */
/*                buffer: reads sms msg out of this buffer                   */
/*                                                                           */
/*  Output Para : -                                                          */
/*                                                                           */
/*  Author      : Michael Streit                                             */
/*                                                                           */
/*  History     : 30.03.2021  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
void SmsHandlerClass::readSms(char *target, char *buffer){
	int textStart = 0;
	int i = 0;
	
	for(int u=0;(buffer[u]!='\0')||((buffer[u]=='A')&&(buffer[u+1]=='T')&&(buffer[u+2]=='+')); u++){
		
		if(((buffer[u-3]=='"')&&(buffer[u-2]==13)&&(buffer[u-1]==10))|| (textStart == 1)){ // trigger start of SMS message
			textStart = 1;
			target[i]=buffer[u];		// copy sms msg into target
			i++;
		}
	}
	target[i]='\0';
	
	Serial.write("Readed SMS MSG: ");
	Serial.write(target);
	Serial.write("\n");
}

/*****************************************************************************/
/*  Method      : isolateSmsSenderPhoneNr	                                 */
/*****************************************************************************/
/*                                                                           */
/*  Function    : reads out sms number from buffer and stores it in target   */
/*                                                                           */
/*                                                                           */
/*  Input Para  : target: pointer where to write in result                   */
/*                buffer: reads sms msg out of this buffer                   */
/*                                                                           */
/*  Output Para : -                                                          */
/*                                                                           */
/*  Author      : Michael Streit                                             */
/*                                                                           */
/*  History     : 30.03.2021  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
void SmsHandlerClass::isolateSmsSenderPhoneNr(char* target, char *buffer){
	char *retBuf;
	int u = 0;
	retBuf = strstr(buffer,"+CMT:");		// find beginning of sms sender phone number
	if(retBuf != NULL){
		for(u=0; retBuf[u+7] !='\"';u++){	// fill Nr into variable until end of Nr reached
			target[u] = retBuf[u+7];
		}
		target[u]='\0';
		}else{
		target[u]='\0';
	}
	
	// Display SMS sender
	Serial.write("SMS sender: ");
	Serial.write(smsSenderNr);
	Serial.write("\n\n");
}


