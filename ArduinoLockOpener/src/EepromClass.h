#ifndef __EEPROMCLASS_H__
#define __EEPROMCLASS_H__
/****************************************************************************/
/*  Header     : EepromClass			                        Version 1.0 */
/****************************************************************************/
/*                                                                          */
/*  Function   : This Class manages the eeprom								*/
/*                                                                          */
/*                                                                          */
/*  Methodes   : EepromClass                                                */
/*				 ~EepromClass()												*/
/*               addContactToEeprom()                                       */
/*               clearEeprom()                                              */
/*               displayEeprom()                                            */
/*               getEepromAddress()                                         */
/*                                                                          */
/*                                                                          */
/*  Author     : M. Streit                                                  */
/*                                                                          */
/*  History    : 31.03.2021  IO Created                                     */
/*                                                                          */
/*  File       : EepromClass.hpp											*/
/*                                                                          */
/****************************************************************************/
/* HTA Burgdorf                                                             */
/****************************************************************************/

/* imports */

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
	//functions
	public:
	EepromClass();
	~EepromClass();
	void addContactToEeprom(char *newName, char *newPhoneNr);
	void clearEeprom();
	void displayEeprom();
	int getEepromAddress();
	protected:
	private:

};
/*****************************************************************************/
/*  End Header  : EepromClass												 */
/*****************************************************************************/
#endif //__EEPROMCLASS_H__
