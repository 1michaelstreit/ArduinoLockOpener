/*****************************************************************************/
/*  Class      : EepromClass									Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   :                                    */
/*                                                                           */
/*                                                                           */
/*  Methodes   : EepromClass()  ToDo                                       */
/*              ~EepromClass()  ToDo                                       */
/*                                                                           */
/*  Author     : Michael Streit                                              */
/*                                                                           */
/*  History    : 31.03.2021  IO Created                                      */
/*                                                                           */
/*  File       : EepromClass.cpp                                         */
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

// default constructor
EepromClass::EepromClass()
{
} //EepromClass

// default destructor
EepromClass::~EepromClass()
{
} //~EepromClass

void EepromClass::addContactToEeprom(char *newName, char *newPhoneNr){
	
	eepromAddress = getEepromAddress();							// "Phone_Number0","Name0","Phone_Number1","Name1",...
	
	for(int i=0; newPhoneNr[i]!= NULL ; i++, eepromAddress++){	// until end of phone number is not reached
		if(eepromAddress < (EEPROM.length())){					// error if eeprom full
			EEPROM.write(eepromAddress, newPhoneNr[i]);			// write phone number into eeprom
			}else{
			Serial.print("ERROR EEPROM is full");
		}
	}
	EEPROM.write(eepromAddress, ',');							// write delimiter
	eepromAddress++;
	
	for(int i=0; newName[i] != NULL; i++, eepromAddress++){
		if(eepromAddress < (EEPROM.length())){					// error if eeprom full
			EEPROM.write(eepromAddress, newName[i]);			// write Name into eeprom
			}else{
			Serial.print("ERROR EEPROM is full");
		}
	}
	EEPROM.write(eepromAddress, ',');							// write delimiter
	
	Serial.write("Added...\"");
	Serial.write(newPhoneNr);
	Serial.write("\" to EEPROM \n\n");
}

int EepromClass::getEepromAddress(){
	for(int address=0; address < EEPROM.length();address++){
		if(EEPROM.read(address)== 0){
			return(address);
		}
	}
	return(EEPROM.length());
}

void EepromClass::clearEeprom(){
	for (int i = 0 ; i < EEPROM.length() ; i++) {
		EEPROM.write(i, 0);
	}
	Serial.write("EEPROM cleared\n\n");
}

void EepromClass::displayEeprom(){
	int delimiterCnt = 0;
	
	eepromAddress = getEepromAddress();
	for(int i= 0; i<eepromAddress; i++){	// display contact until end of eepromdata reached
		if(EEPROM.read(i)==','){			// check if Name or Number ended
			delimiterCnt++;
		}
		if(delimiterCnt>1){				// make new line for new contact
				Serial.write("\n");
				delimiterCnt = 0;
				}else{
				Serial.write(EEPROM.read(i));	// display Contact
		}		
	}
}