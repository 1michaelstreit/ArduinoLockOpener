#ifndef __AUTHORIZATIONHANDLERCLASS_H__
#define __AUTHORIZATIONHANDLERCLASS_H__
/****************************************************************************/
/*  Header     : AuthorizationHandlerClass                      Version 1.0 */
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
/*  File       : AuthorizationHandlerClass.hpp								*/
/*                                                                          */
/****************************************************************************/
/* HTA Burgdorf                                                             */
/****************************************************************************/

/* imports */
#include "AuthorizationHandlerClass.h"
#include "GsmCommunicationClass.h"
#include "ContactDirectoryClass.h"
#include "Leds.hpp"



/* Class constant declaration  */
#define MATCHING_DIGITS	9
/* Class Type declaration      */

/* Class data declaration      */

/* Class definition            */

class AuthorizationHandlerClass
{
// Data
public:
GsmCommunicationClass *GsmCommunication;

protected:
private:

// Methods
public:
	AuthorizationHandlerClass(GsmCommunicationClass *NewCommunication);
	~AuthorizationHandlerClass();
	
	void handleReceivedCall( ContactDirectoryClass *ContactDirectoryTemporary, ContactDirectoryClass *ContactDirectoryPermanent,  GPIOLedClass *LockLed);
	int  checkAuthorization(char *nrToCheck,ContactDirectoryClass *ContactDirectoryTemporary, ContactDirectoryClass *ContactDirectoryPermanent);
	void answerCall();
protected:
private:
	
};
/*****************************************************************************/
/*  End Header  : AuthorizationHandlerClass                                  */
/*****************************************************************************/

#endif //__AUTHORIZATIONHANDLERCLASS_H__
