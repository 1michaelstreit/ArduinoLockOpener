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


/* Class constant declaration  */

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
	AuthorizationHandlerClass(GsmCommunicationClass *NewGsmCommunication);
	~AuthorizationHandlerClass();
	
	void handleReceivedCall();
	int  checkAuthorization(char *nrToCheck);
	void answerCall();
protected:
private:
	
};
/*****************************************************************************/
/*  End Header  : AuthorizationHandlerClass                                  */
/*****************************************************************************/

#endif //__AUTHORIZATIONHANDLERCLASS_H__
