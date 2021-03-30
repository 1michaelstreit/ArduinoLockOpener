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

/* Class constant declaration  */

/* Class Type declaration      */

/* Class data declaration      */

/* Class definition            */

class SmsHandlerClass
{
// Data
public:
GsmCommunicationClass *GsmCommunication;
protected:
private:
static const int bufferSize = 256;
char smsSenderNr[20] = {0};
char smsMsg[bufferSize] = {0};

// Methods
public:
	SmsHandlerClass(GsmCommunicationClass *GsmCommunication);
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
