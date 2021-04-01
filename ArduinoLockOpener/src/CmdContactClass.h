#ifndef __CMDCONTACTCLASS_H__
#define __CMDCONTACTCLASS_H__
/****************************************************************************/
/*  Header     : CmdContactClass                                Version 1.0 */
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
/*  File       : CmdContactClass.hpp										*/
/*                                                                          */
/****************************************************************************/
/* HTA Burgdorf                                                             */
/****************************************************************************/

/* imports */
#include "SmsHandlerClass.h"

/* Class constant declaration  */

/* Class Type declaration      */

/* Class data declaration      */

/* Class procedure declaration */

class CmdContactClass : public SmsHandlerClass
{
//variables
public:
protected:
private:

//functions
public:
	CmdContactClass(GsmCommunicationClass *NewGsmCommunication, AuthorizationHandlerClass *NewAuthorizationHandler);
	~CmdContactClass();
	void executeSmsCmd(ContactDirectoryClass *ContactDirectoryTemporary, ContactDirectoryClass *ContactDirectoryPermanent);
	void removePrefix(char *phoneNumber, char *smsMsg);	
protected:
private:


};
/*****************************************************************************/
/*  End Header  : CmdContactClass		                                     */
/*****************************************************************************/

#endif //__CMDCONTACTCLASS_H__