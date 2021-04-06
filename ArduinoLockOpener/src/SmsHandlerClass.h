#ifndef __SMSHANDLERCLASS_H__
#define __SMSHANDLERCLASS_H__
/****************************************************************************/
/*  Header     : SmsHandlerClass                                Version 1.0 */
/****************************************************************************/
/*                                                                          */
/*  Function   : This class handles the incoming SMS                        */
/*                                                                          */
/*                                                                          */
/*  Methodes   : TemplateClass()											*/
/*              ~TemplateClass()											*/
/*              readSms()                                                   */
/*              isolateSmsSenderPhoneNr()                                   */
/*              handleReceivedSms()                                         */
/*                                                                          */
/*  Author     : M. Streit                                                  */
/*                                                                          */
/*  History    : 30.03.2021  IO Created                                     */
/*                                                                          */
/*  File       : SmsHandlerClass.hpp										*/
/*                                                                          */
/****************************************************************************/
/* HTA Burgdorf                                                             */
/****************************************************************************/

/* imports */
#include "GsmCommunicationClass.h"
#include "AuthorizationHandlerClass.h"

/* Class constant declaration  */
#define BUFFER_SIZE 256

/* Class Type declaration      */

/* Class data declaration      */

/* Class definition            */

class SmsHandlerClass
{
	// Data
	public:

	char smsMsg[BUFFER_SIZE] = {0};

	protected:
	bool newSmsReceived = false;
	private:
	char smsSenderNr[20] = {0};
	GsmCommunicationClass *GsmCommunication;
	AuthorizationHandlerClass *AuthorizationHandler;

	// Methods
	public:
	SmsHandlerClass(GsmCommunicationClass *NewGsmCommunication, AuthorizationHandlerClass *NewAuthorizationHandler);
	~SmsHandlerClass();
	
	void readSms(char *target, char *buffer);
	void isolateSmsSenderPhoneNr(char *target, char *buffer);
	void handleReceivedSms();
	
	protected:
	private:

};
/*****************************************************************************/
/*  End Header  : SmsHandlerClass		                                     */
/*****************************************************************************/

#endif //__SMSHANDLERCLASS_H__
