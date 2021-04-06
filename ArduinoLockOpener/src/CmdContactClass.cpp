/*****************************************************************************/
/*  Class      : CmdContactClass		                        Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : This Class executes received messages                       */
/*                                                                           */
/*                                                                           */
/*  Methodes   : CmdContactClass()											 */
/*              ~CmdContactClass()											 */
/*              executeSmsCmd()									             */
/*              removePrefix()                                               */
/*                                                                           */
/*  Author     : Michael Streit                                              */
/*                                                                           */
/*  History    : 31.03.2021  IO Created                                      */
/*                                                                           */
/*  File       : CmdContactClass.cpp                                         */
/*                                                                           */
/*****************************************************************************/
/* HTA Burgdorf                                                              */
/*****************************************************************************/

/* imports */
#include <string.h>
#include "Arduino.h"
#include "CmdContactClass.h"
/* Class constant declaration  */

/* Class Type declaration      */

/* Class data declaration      */

/* Class procedure declaration */

/*****************************************************************************/
/*  Method      : CmdContactClass		                                     */
/*****************************************************************************/
/*                                                                           */
/*  Function    : Constructor							                     */
/*                                                                           */
/*  Type        : Constructor                                                */
/*                                                                           */
/*  Input Para  : newEeprom1: pointer to eeprom1                             */
/*                NewGsmCommunication: pointer to GsmCommunication           */
/*                NewAuthorizationHandler: pointer to Authorization handler  */
/*                                                                           */
/*  Output Para :  -                                                         */
/*                                                                           */
/*  Author      : Michael Streit                                             */
/*                                                                           */
/*  History     : 31.03.2021  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
CmdContactClass::CmdContactClass(EepromClass *newEeprom1, GsmCommunicationClass *NewGsmCommunication, AuthorizationHandlerClass *NewAuthorizationHandler) :SmsHandlerClass(NewGsmCommunication,NewAuthorizationHandler)
{
	eeprom1 = newEeprom1;
} //CmdContactClass

// default destructor
CmdContactClass::~CmdContactClass()
{
} //~CmdContactClass

/*****************************************************************************/
/*  Method      : executeSmsCmd			                                     */
/*****************************************************************************/
/*                                                                           */
/*  Function    : Finds command in sms message and executes the cmd			 */
/*                                                                           */
/*  Commands	:                                                            */
/*				CMD_Add_Nr:		adds a new number to eeprom					 */
/*				CMD_clear:		clears the eeprom and adds standard contact	 */
/*				CMD_contacts:	displays all stored contacts				 */
/*                                                                           */
/*                                                                           */
/*  Input Para  : -                                                          */
/*                                                                           */
/*  Output Para : -                                                          */
/*                                                                           */
/*  Author      : Michael Streit                                             */
/*                                                                           */
/*  History     : 31.03.2021  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
void CmdContactClass::executeSmsCmd(){
	char cBuffer[50];
	
	if(newSmsReceived == true){
		char newPhoneNumber[10] = {0};
		char newName[NAME_SIZE] = {0};
		
		// add new Contact
		if(strstr(smsMsg,"CMD_Add_Nr:") != NULL){		
			
			removePrefix(newPhoneNumber,smsMsg);		// removes prefix from nr. 
			strcpy(newName,"Unknown");					// define standard name for new nr.
			
			sprintf(cBuffer,"Number received: %s \n",newPhoneNumber );
			Serial.write(cBuffer);
			
			eeprom1->addContactToEeprom(newName,newPhoneNumber);	// store new contact
		}else
		
		// clear eeprom
		if(strstr(smsMsg,"CMD_clear") != NULL){
			eeprom1->clearEeprom();										// clear eeprom
			eeprom1->addContactToEeprom("Michael Streit", "786750902");	// add standard contact
		}else
		
		// display contacts
		if(strstr(smsMsg,"CMD_contacts") != NULL){
			Serial.write("Displays all Contacts: \n");				// display all contacts
			eeprom1->displayEeprom();
			}else{
			Serial.write("No Command received \n");					// if no cmd was received
		}
	}
	newSmsReceived == false;
}

/*****************************************************************************/
/*  Method      : removePrefix			                                     */
/*****************************************************************************/
/*                                                                           */
/*  Function    : get the 9 last character of the smsMsg and stores			 */
/*                them into phoneNumber                                      */
/*                                                                           */
/*  Input Para  : phoneNumber: pointer where nr. needs to be stored          */
/*                smsMsg: string with sms msg                                */
/*                                                                           */
/*  Output Para : -                                                          */
/*                                                                           */
/*  Author      : Michael Streit                                             */
/*                                                                           */
/*  History     : 31.03.2021  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
void CmdContactClass::removePrefix(char *phoneNumber, char *smsMsg){

	int stringLength = strlen(smsMsg)-2; // get the sting length

	// remove prefix
	if(stringLength>9){
		for(int u=0; u<9; u++){
			phoneNumber[u] = smsMsg[u+(stringLength-9)];
		}
	}
	phoneNumber[9] = '\0';
}