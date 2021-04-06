#ifndef __CMDCONTACTCLASS_H__
#define __CMDCONTACTCLASS_H__
/****************************************************************************/
/*  Header     : CmdContactClass                                Version 1.0 */
/****************************************************************************/
/*                                                                          */
/*  Function   : This Class executes received messages                      */
/*                                                                          */
/*  Methodes   : CmdContactClass()											*/
/*              ~CmdContactClass()											*/
/*              executeSmsCmd()									            */
/*              removePrefix()                                              */
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
#define NAME_SIZE	50

/* Class Type declaration      */

/* Class data declaration      */

/* Class procedure declaration */

class CmdContactClass : public SmsHandlerClass
{
//variables
public:
protected:
private:
EepromClass *eeprom1;

//functions
public:
	CmdContactClass(EepromClass *NewEeprom1,GsmCommunicationClass *NewGsmCommunication, AuthorizationHandlerClass *NewAuthorizationHandler);
	~CmdContactClass();
	void executeSmsCmd();
	void removePrefix(char *phoneNumber, char *smsMsg);	
protected:
private:


};
/*****************************************************************************/
/*  End Header  : CmdContactClass		                                     */
/*****************************************************************************/

#endif //__CMDCONTACTCLASS_H__
