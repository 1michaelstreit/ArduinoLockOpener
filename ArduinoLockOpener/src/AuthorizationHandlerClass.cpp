/*****************************************************************************/
/*  Class      : AuthorizationHandlerClass                      Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Thies Class handles incomming Calls and checks the          */
/*				 Authorization                                               */
/*                                                                           */
/*  Methodes   : AuthorizationHandlerClass()	                             */
/*              ~AuthorizationHandlerClass()                                 */
/*              handleReceivedCall()                                         */
/*              checkAuthorization()                                         */
/*              answerCall()                                                 */
/*                                                                           */
/*  Author     : Michael Streit                                              */
/*                                                                           */
/*  History    : 30.03.2021  IO Created                                      */
/*                                                                           */
/*  File       : AuthorizationHandlerClass.cpp                               */
/*                                                                           */
/*****************************************************************************/
/* HTA Burgdorf                                                              */
/*****************************************************************************/

/* imports */
#include "Arduino.h"
#include "AuthorizationHandlerClass.h"
#include "EEPROM.h"

/* Class constant declaration  */
#define NR_OF_MATCHING_DIGITS 9

/* Class Type declaration      */

/* Class data declaration      */

/* Class procedure declaration */

/*****************************************************************************/
/*  Method      : AuthorizationHandlerClass                                  */
/*****************************************************************************/
/*                                                                           */
/*  Function    : Constructor                                                */
/*                                                                           */
/*  Type        : Constructor                                                */
/*                                                                           */
/*  Input Para  : NewCommunication: pointer to GSM communication             */
/*				  NewEeprom1: pointer to Eeprom Object						 */
/*                                                                           */
/*  Output Para : -                                                          */
/*                                                                           */
/*  Author      : Michael Streit                                             */
/*                                                                           */
/*  History     : 30.03.2021  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
AuthorizationHandlerClass::AuthorizationHandlerClass(GsmCommunicationClass *NewCommunication, EepromClass *NewEeprom1)
{
	GsmCommunication = NewCommunication;
	eeprom1 = NewEeprom1;
} //AuthorizationHandlerClass

// default destructor
AuthorizationHandlerClass::~AuthorizationHandlerClass()
{
} //~AuthorizationHandlerClass

/*****************************************************************************/
/*  Method      : handleReceivedCall	                                     */
/*****************************************************************************/
/*                                                                           */
/*  Function    : Checks if call is received. checks if caller is authorized.*/
/*				  open Lock if caller is authorized							 */
/*                                                                           */
/*                                                                           */
/*  Input Para  : Lock: Pointer to GPIO LED Class                            */
/*                                                                           */
/*  Output Para : -                                                          */
/*                                                                           */
/*  Author      : Michael Streit                                             */
/*                                                                           */
/*  History     : 30.03.2021  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
void AuthorizationHandlerClass::handleReceivedCall(LockOpenerClass *Lock){
	
	if(strstr(GsmCommunication->receiveBuffer, "RING") != NULL){		// check if call received
		
		GsmCommunication->sendAtCmd("AT+CLCC");			// read phone Number from caller
		GsmCommunication->readSerial();
		
		if(checkAuthorization(GsmCommunication->receiveBuffer) == 1){	// if Nr. of caller is authorized open Lock
			Serial.write("Number authorized -> OPEN LOCK \r\n\r\n");
			answerCall();		//hang up incoming call
			
			// open lock
			delay(1000);		
			Lock->On();
			delay(1000);
			Lock->Off();
		}else{
			Serial.write("Number DECLINED \r\n\r\n");		// if Nr. is declined
		}
	}
}

/*****************************************************************************/
/*  Method      : check Authorization	                                     */
/*****************************************************************************/
/*                                                                           */
/*  Function    : compares phone number to check with the contacts in the	 */
/*				  EEPROM, return 1 if one matches else return 0				 */
/*                                                                           */
/*                                                                           */
/*  Input Para  : nrToCheck: checkstring with phone number to check          */
/*                                                                           */
/*  Output Para : 1 if nr. matches else 0                                    */
/*                                                                           */
/*  Author      : Michael Streit                                             */
/*                                                                           */
/*  History     : 30.03.2021  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
int AuthorizationHandlerClass::checkAuthorization(char *nrToCheck){
	int i = 0;
	int v = 0;
	int nrOfMatchDigits = 0;
	int eepromAddress = eeprom1->getEepromAddress();
	
	Serial.write("CheckAuthorization...\r\n");
	//Serial.write("phone numbers in Contacts: \r\n");
	//eeprom1->displayEeprom();						// displays all contacts in Eeprom
	
	// return 1 if minimum nr of digits matching
	for(i=0; i<eepromAddress;i++){								// until end of eeprom data reached
		for(v=0;nrToCheck[v]!='\0';v++){						// until string end
			if(nrToCheck[v]==EEPROM.read(i+nrOfMatchDigits)){	// compare single digits
				nrOfMatchDigits++;								// increase if matching Digit
				}else{
				nrOfMatchDigits = 0;					
			}
			if(nrOfMatchDigits>=NR_OF_MATCHING_DIGITS){			// return 1 if min matching digits reached
				return(1);
			}
			if((i+1)%9==0 && i!=0){
				nrOfMatchDigits = 0;
			}
		}
	}
	return(0);		// return 0 if no matching phone number was detected
}

/*****************************************************************************/
/*  Method      : answerCall			                                     */
/*****************************************************************************/
/*                                                                           */
/*  Function    : hangs up the incoming Call								 */
/*                                                                           */
/*                                                                           */
/*  Input Para  : -													         */
/*                                                                           */
/*  Output Para : -                                                          */
/*                                                                           */
/*  Author      : Michael Streit                                             */
/*                                                                           */
/*  History     : 30.03.2021  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
void AuthorizationHandlerClass::answerCall(){
	
	// hang up incoming Call
	GsmCommunication->sendAtCmd("ATA");
	_delay_ms(400);
	GsmCommunication->readSerial();
	GsmCommunication->sendAtCmd("AT+CVHU=0");
	_delay_ms(400);
	GsmCommunication->readSerial();
	GsmCommunication->sendAtCmd("ATH");
	_delay_ms(400);
	GsmCommunication->readSerial();
}