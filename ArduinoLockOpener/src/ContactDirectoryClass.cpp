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
ContactDirectoryClass::ContactDirectoryClass(char newListName[NAME_SIZE])
{
	head = NULL;
	tail = NULL;
	strcpy(listName,newListName);
} //ContactDirectoryClass

// default destructor
ContactDirectoryClass::~ContactDirectoryClass()
{
} //~ContactDirectoryClass

void ContactDirectoryClass::addContact(char *newName, char *newPhoneNr, int priority){
			

	
	// add temporary data into List until power off
	if(priority == TEMPORARY){
			
			ContactClass *newContact = new ContactClass(newName, newPhoneNr);	// new Contact
			
			pushFront(newContact);	// add to List
			
			Serial.write("Added...\"");
			Serial.write(newPhoneNr);
			Serial.write("\" to Contact List \n\n");	
	}
	
	// add Permanent
	
	if(priority == PERMANENT){
		EepromClass tempEeprom;
		tempEeprom.addContactToEeprom(newName, newPhoneNr);	// add new Contact to Eeprom
		
		addContact(newName,newPhoneNr,TEMPORARY);			// add new Contact to Contact List Permenant
		
		//tempEeprom.eepromToContactDirectory(this);
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

void ContactDirectoryClass::showContactList(){
	ContactClass *currentContact = tail;
	
	char displayString1[100] = {0};
	char displayString2[100] = {0};
		
		//sprintf(displayString2,"Displays Contacts from Contact Directory List: %s \n", this->listName);
		//Serial.write(displayString2);
		
		Serial.write(this->listName);
		Serial.write("\n");

	
		while(currentContact != NULL){
			sprintf(displayString1,"phone number: %s		Name: %s \n", currentContact->phoneNumber, currentContact->Name);
			Serial.write(displayString1);
		
			currentContact = currentContact->next;
		}
}