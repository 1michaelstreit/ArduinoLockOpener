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

void EepromClass::eepromToContactDirectory(ContactDirectoryClass *ContactDirectory){
	
	eepromAddress = getEepromAddress();
	char tempNumber[PHONE_NR_SIZE]={0};
	char tempName[NAME_SIZE]={0};
	int v = 0;
	int state = 0;
	
	for(int i=0; i<eepromAddress;i++){	// until end of Eeprom data reached	
		if(EEPROM.read(i) == ','){			// change state if number or name ended
			v=0;
			if(state == 0){					// toggle between states
				tempNumber[i] = '\0';		// end number string
				state = 1;
			}else{
				tempName[i] = '\0';			// end name string
				
				// add contact readed out of eeprom to contact
				ContactDirectory->addContact((char*)&tempName,(char*)&tempNumber,TEMPORARY);	
				state = 0;
			}
		}else{
			switch(state){
				case 0:	// read number
					tempNumber[v]=EEPROM.read(i);						
				break;
		
				case 1: // read name
					tempName[v] = EEPROM.read(i);	
				break;
			}
			v++;
		}
	}
}

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
	eepromAddress = getEepromAddress();
	for(int i= 0; i<eepromAddress; i++){
		Serial.write(EEPROM.read(i));
	}
	
}