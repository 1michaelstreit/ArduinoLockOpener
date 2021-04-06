#ifndef __AUTHORIZATIONHANDLERCLASS_H__
#define __AUTHORIZATIONHANDLERCLASS_H__
/****************************************************************************/
/*  Header     : AuthorizationHandlerClass                      Version 1.0 */
/****************************************************************************/
/*                                                                          */
/*  Function   : Thies Class handles incomming Calls and checks the         */
/*				 Authorization                                              */
/*                                                                          */
/*  Methodes   : AuthorizationHandlerClass()	                            */
/*              ~AuthorizationHandlerClass()                                */
/*              handleReceivedCall()                                        */
/*              checkAuthorization()                                        */
/*              answerCall()                                                */
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
	protected:
	private:
	GsmCommunicationClass *GsmCommunication;
	EepromClass *eeprom1;

	// Methods
	public:
	AuthorizationHandlerClass(GsmCommunicationClass *NewCommunication, EepromClass *NewEeprom1);
	~AuthorizationHandlerClass();
	
	void handleReceivedCall(LockOpenerClass *Lock);
	int  checkAuthorization(char *nrToCheck);
	protected:
	private:
	void answerCall();
	
};
/*****************************************************************************/
/*  End Header  : AuthorizationHandlerClass                                  */
/*****************************************************************************/

#endif //__AUTHORIZATIONHANDLERCLASS_H__
