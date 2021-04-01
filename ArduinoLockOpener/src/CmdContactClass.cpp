/*****************************************************************************/
/*  Class      : CmdContactClass		                        Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   :                                    */
/*                                                                           */
/*                                                                           */
/*  Methodes   : CmdContactClass()  ToDo                                     */
/*              ~CmdContactClass()  ToDo                                     */
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
#include "CmdContactClass.h"
/* Class constant declaration  */

/* Class Type declaration      */

/* Class data declaration      */

/* Class procedure declaration */


/*****************************************************************************/
/*  Method      : CmdContactClass		                                     */
/*****************************************************************************/
/*                                                                           */
/*  Function    :                                                            */
/*                                                                           */
/*  Type        : Constructor                                                */
/*                                                                           */
/*  Input Para  :                                                            */
/*                                                                           */
/*  Output Para :                                                            */
/*                                                                           */
/*  Author      : Michael Streit                                             */
/*                                                                           */
/*  History     : 31.03.2021  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
CmdContactClass::CmdContactClass(GsmCommunicationClass *NewGsmCommunication, AuthorizationHandlerClass *NewAuthorizationHandler) :SmsHandlerClass(NewGsmCommunication,NewAuthorizationHandler)
{
} //CmdContactClass

// default destructor
CmdContactClass::~CmdContactClass()
{
} //~CmdContactClass

/*****************************************************************************/
/*  Method      : 		                                     */
/*****************************************************************************/
/*                                                                           */
/*  Function    :                                                            */
/*                                                                           */
/*  Type        :			                                                */
/*                                                                           */
/*  Input Para  :                                                            */
/*                                                                           */
/*  Output Para :                                                            */
/*                                                                           */
/*  Author      : Michael Streit                                             */
/*                                                                           */
/*  History     : 31.03.2021  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
void CmdContactClass::executeSmsCmd(ContactDirectoryClass *ContactDirectoryTemporary, ContactDirectoryClass *ContactDirectoryPermanent){
	
	if(newSmsReceived == true){
		char newPhoneNumber[10] = {0};
		char newName[NAME_SIZE] = {0};
			
		strcpy(newName,"Unknown");
		removePrefix((char*)&newPhoneNumber,(char*)&smsMsg);
		
		Serial.write("Number received: ");
		Serial.write(newPhoneNumber);
		Serial.write("\n");
			
			if(strstr(smsMsg,"Master:") != NULL){
				// add permament	
				Serial.write("Should add permanent.. \n");
				//ContactDirectoryPermanent->addContact(&newName[0],&newPhoneNumber[0],PERMANENT);
			}else{
				// add temporary
				Serial.write("Should add temporary.. \n");
				//ContactDirectoryTemporary->addContact(&newName[0],&newPhoneNumber[0],TEMPORARY);
			}
	}
	newSmsReceived == false;
}

void CmdContactClass::removePrefix(char *phoneNumber, char *smsMsg){

    int stringLength = strlen(smsMsg)-2; // string length 2 more
    //Serial.println(stringLength);		// for debugging

    // remove prefix
    if(stringLength>9){
        for(int u=0; u<9; u++){
            phoneNumber[u] = smsMsg[u+(stringLength-9)];
        }
    }
	phoneNumber[9] = '\0';
}