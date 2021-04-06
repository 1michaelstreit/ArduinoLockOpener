#ifndef __SMSHANDLERCLASS_H__
#define __SMSHANDLERCLASS_H__
/****************************************************************************/
/*  Header     : SmsHandlerClass                                Version 1.0 */
/****************************************************************************/
/*                                                                          */
/*  Function   :          */
/*                                                                          */
/*                                                                          */
/*  Methodes   :                                                            */
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
GsmCommunicationClass *GsmCommunication;
AuthorizationHandlerClass *AuthorizationHandler;

char smsMsg[BUFFER_SIZE] = {0};
protected:
bool newSmsReceived = false;
private:
char smsSenderNr[20] = {0};


// Methods
public:
	SmsHandlerClass(GsmCommunicationClass *NewGsmCommunication, AuthorizationHandlerClass *NewAuthorizationHandler);
	~SmsHandlerClass();
	
	void readSms(char *buffer);
	void isolateSmsSenderPhoneNr(char *buffer);
	void handleReceivedSms();
	

protected:
private:
	

};
/*****************************************************************************/
/*  End Header  : SmsHandlerClass		                                     */
/*****************************************************************************/

#endif //__SMSHANDLERCLASS_H__
