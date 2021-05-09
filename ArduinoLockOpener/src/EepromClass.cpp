/*****************************************************************************/
/*  Class      : EepromClass									Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : This Class manages the eeprom                               */
/*                                                                           */
/*                                                                           */
/*  Methodes   : EepromClass                                                 */
/*				 ~EepromClass()												 */
/*               addContactToEeprom()                                        */
/*               clearEeprom()                                               */
/*               displayEeprom()                                             */
/*               getEepromAddress()                                          */
/*                                                                           */
/*  Author     : Michael Streit                                              */
/*                                                                           */
/*  History    : 31.03.2021  IO Created                                      */
/*                                                                           */
/*  File       : EepromClass.cpp											 */
/*                                                                           */
/*****************************************************************************/
/* HTA Burgdorf                                                              */
/*****************************************************************************/

/* imports */
#include "Arduino.h"
#include "EepromClass.h"
#include "EEPROM.h"

/* Class constant declaration  */

/* Class Type declaration      */

/* Class data declaration      */

/* Class procedure declaration */

/****************************************************************************/
/*  Method      : EepromClass									Version 1.0 */
/****************************************************************************/
/*																			*/
/*  Function   : Constructor				                                */
/*                                                                          */
/*                                                                          */
/*  Type        : Constructor                                               */
/*                                                                          */
/*  Input Para  : -                                                         */
/*                                                                          */
/*  Output Para : -                                                         */
/*                                                                          */
/*                                                                          */
/*  Author     : Michael Streit                                             */
/*                                                                          */
/*  History    : 31.03.2021  IO Created                                     */
/*                                                                          */
/*  File       : EepromClass.cpp											*/
/*                                                                          */
/****************************************************************************/
EepromClass::EepromClass()
{
} //EepromClass

// default destructor
EepromClass::~EepromClass()
{
} //~EepromClass

/****************************************************************************/
/*  Method      : addContactToEeprom							Version 1.0 */
/****************************************************************************/
/*																			*/
/*  Function   : add new Contact to EEPROM	                                */
/*                                                                          */
/*               stores contacts like this in the Eeprom:                   */
/*				 <Phone_Number0>,<Name0>,<Phone_Number1>,<Name1>,...		*/
/*               comma is used as delemiter                                 */
/*                                                                          */
/*  Input Para  : newName: new name of new Contact                          */
/*                newPhoneNr: new Number of new Contact                     */
/*                                                                          */
/*  Output Para : -                                                         */
/*                                                                          */
/*                                                                          */
/*  Author     : Michael Streit                                             */
/*                                                                          */
/*  History    : 31.03.2021  IO Created                                     */
/*                                                                          */
/*  File       : EepromClass.cpp											*/
/*                                                                          */
/****************************************************************************/
void EepromClass::addContactToEeprom(char *newName, char *newPhoneNr){
	char cBuffer[50];
	int eepromAddress;
	
	eepromAddress = getEepromAddress();							// get the eeprom index
	
	// write phone number into eeprom
	for(int i=0; newPhoneNr[i]!= NULL ; i++, eepromAddress++){	// until end of phone number is not reached
		if(eepromAddress < (EEPROM.length())){					// error if eeprom full
			EEPROM.write(eepromAddress, newPhoneNr[i]);			
			}else{
			Serial.print("ERROR EEPROM is full");
		}
	}
	// write delimiter into eeprom
	EEPROM.write(eepromAddress, ',');							
	eepromAddress++;
	
	// write Name into eeprom
	for(int i=0; newName[i] != NULL; i++, eepromAddress++){
		if(eepromAddress < (EEPROM.length())){					// error if eeprom full
			EEPROM.write(eepromAddress, newName[i]);			
			}else{
			Serial.print("ERROR EEPROM is full");
		}
	}
	EEPROM.write(eepromAddress, ',');							// write delimiter
	
	sprintf(cBuffer,"Added: %s, %s	to EEPROM \r\n\r\n",newPhoneNr,newName );
	Serial.write(cBuffer);
}

/****************************************************************************/
/*  Method      : getEepromAddress								Version 1.0 */
/****************************************************************************/
/*																			*/
/*  Function   : findes the index of the rearmost data in EEPROM			*/
/*                                                                          */
/*                                                                          */
/*  Input Para  : -															*/
/*                                                                          */
/*  Output Para : offset of the rearmost data in EEPROM                     */
/*                                                                          */
/*                                                                          */
/*  Author     : Michael Streit                                             */
/*                                                                          */
/*  History    : 31.03.2021  IO Created                                     */
/*                                                                          */
/*  File       : EepromClass.cpp											*/
/*                                                                          */
/****************************************************************************/
int EepromClass::getEepromAddress(){
	for(int address=0; address < EEPROM.length();address++){
		if(EEPROM.read(address)== 0){
			return(address);
		}
	}
	return(EEPROM.length());
}

/****************************************************************************/
/*  Method      : clearEeprom									Version 1.0 */
/****************************************************************************/
/*																			*/
/*  Function   : clears the EEPROM											*/
/*                                                                          */
/*                                                                          */
/*  Input Para  : -															*/
/*                                                                          */
/*  Output Para : -										                    */
/*                                                                          */
/*                                                                          */
/*  Author     : Michael Streit                                             */
/*                                                                          */
/*  History    : 31.03.2021  IO Created                                     */
/*                                                                          */
/*  File       : EepromClass.cpp											*/
/*                                                                          */
/****************************************************************************/
void EepromClass::clearEeprom(){
	for (int i = 0 ; i < EEPROM.length() ; i++) {
		EEPROM.write(i, 0);
	}
	Serial.write("EEPROM cleared \r\n\r\n");
}
/****************************************************************************/
/*  Method      : displayEeprom									Version 1.0 */
/****************************************************************************/
/*																			*/
/*  Function   : displays everything in EEPROM								*/
/*                                                                          */
/*                                                                          */
/*  Input Para  : -															*/
/*                                                                          */
/*  Output Para : -										                    */
/*                                                                          */
/*                                                                          */
/*  Author     : Michael Streit                                             */
/*                                                                          */
/*  History    : 31.03.2021  IO Created                                     */
/*                                                                          */
/*  File       : EepromClass.cpp											*/
/*                                                                          */
/****************************************************************************/
void EepromClass::displayEeprom(){
	int delimiterCnt = 0;
	int eepromAddress;
	
	eepromAddress = getEepromAddress();
	for(int i= 0; i<eepromAddress; i++){	// display contact until end of eepromdata reached
		if(EEPROM.read(i)==','){			// check if Name or Number ended
			delimiterCnt++;
		}
		if(delimiterCnt>1){					// make new line for new contact
			Serial.write("\r\n");
			delimiterCnt = 0;
			}else{
			Serial.write(EEPROM.read(i));	// display Contact
		}
	}
}