#ifndef __EEPROMCLASS_H__
#define __EEPROMCLASS_H__
/****************************************************************************/
/*  Header     : EepromClass			                        Version 1.0 */
/****************************************************************************/
/*                                                                          */
/*  Function   :          */
/*                                                                          */
/*                                                                          */
/*  Methodes   :                                                            */
/*                                                                          */
/*  Author     : M. Streit                                                  */
/*                                                                          */
/*  History    : 31.03.2021  IO Created                                     */
/*                                                                          */
/*  File       : EepromClass.hpp									*/
/*                                                                          */
/****************************************************************************/
/* HTA Burgdorf                                                             */
/****************************************************************************/

/* imports */
#include "ContactDirectoryClass.h"

/* Class constant declaration  */

/* Class Type declaration      */

/* Class data declaration      */

/* Class definition            */

class EepromClass
{
//variables
public:
protected:
private:
	int eepromAddress;
//functions
public:
	EepromClass();
	~EepromClass();
	void addContactToEeprom(char *newName, char *newPhoneNr);
	void eepromToContactDirectory(ContactDirectoryClass *ContactDirectory);
	void clearEeprom();
	void displayEeprom();
protected:
private:
	int getEepromAddress();
	
	

};
/*****************************************************************************/
/*  End Header  : EepromClass												 */
/*****************************************************************************/
#endif //__EEPROMCLASS_H__
