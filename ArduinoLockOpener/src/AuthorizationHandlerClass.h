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
#include "Leds.hpp"
#include "EepromClass.h"



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
EepromClass *eeprom1;

protected:
private:

// Methods
public:
	AuthorizationHandlerClass(GsmCommunicationClass *NewCommunication, EepromClass *NewEeprom1);
	~AuthorizationHandlerClass();
	
	void handleReceivedCall(GPIOLedClass *LockLed);
	int  checkAuthorization(char *nrToCheck);
	void answerCall();
protected:
private:

	
};
/*****************************************************************************/
/*  End Header  : AuthorizationHandlerClass                                  */
/*****************************************************************************/

#endif //__AUTHORIZATIONHANDLERCLASS_H__
