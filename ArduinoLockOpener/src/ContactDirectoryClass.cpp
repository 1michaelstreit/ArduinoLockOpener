/*****************************************************************************/
/*  Class      : ContactDirectoryClass	                        Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   :                                    */
/*                                                                           */
/*                                                                           */
/*  Methodes   : ContactDirectoryClass()  ToDo                                       */
/*              ~ContactDirectoryClass()  ToDo                                       */
/*                                                                           */
/*  Author     : Michael Streit                                              */
/*                                                                           */
/*  History    : 31.03.2021  IO Created                                      */
/*                                                                           */
/*  File       : ContactDirectoryClass.cpp                                         */
/*                                                                           */
/*****************************************************************************/
/* HTA Burgdorf                                                              */
/*****************************************************************************/

/* imports */
#include "ContactDirectoryClass.h"
#include "EepromClass.h"

/* Class constant declaration  */

/* Class Type declaration      */

/* Class data declaration      */

/* Class procedure declaration */

// default constructor
ContactDirectoryClass::ContactDirectoryClass()
{
} //ContactDirectoryClass

// default destructor
ContactDirectoryClass::~ContactDirectoryClass()
{
} //~ContactDirectoryClass

void ContactDirectoryClass::addContact(char *newName, char *newPhoneNr, int priority){
	
	// add temporary data until power off
	if(priority == TEMPORARY){
		ContactClass *newContact;		// pointer to new Contact
		newContact = new ContactClass(newName, newPhoneNr);	// new Contact
	
		/*
		for(int i=0; i<10; i++){	// store 10 digits from phone Nr
		newContact->phoneNumber[i] = newPhoneNr[i];
		}
		*/
		pushFront(newContact);	// add to List
		
		Serial.write("Added...\"");
		Serial.write(newPhoneNr);
		Serial.write("\" to Contact \n\n");

	}
	
	// add to EEPROM
	
	if(priority == PERMANENT){
		EepromClass tempEeprom;
		tempEeprom.addContactToEeprom(newName, newPhoneNr);
		
		tempEeprom.eepromToContactDirectory(this);
	}
}

void ContactDirectoryClass::pushFront(ContactClass *newContact){
	if(head == NULL){
		tail = newContact;
	}else{
		head->prev = newContact;
	}
	newContact->next = head;
	head = newContact;
	newContact->prev = NULL;
}
