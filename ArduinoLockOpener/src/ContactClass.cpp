/*****************************************************************************/
/*  Class      : ContactClass									Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   :                                    */
/*                                                                           */
/*                                                                           */
/*  Methodes   : ContactClass()  ToDo                                        */
/*              ~ContactClass()  ToDo										 */
/*                                                                           */
/*  Author     : Michael Streit                                              */
/*                                                                           */
/*  History    : 31.03.2021  IO Created                                      */
/*                                                                           */
/*  File       : ContactClass.cpp											 */
/*                                                                           */
/*****************************************************************************/
/* HTA Burgdorf                                                              */
/*****************************************************************************/

/* imports */
#include "ContactClass.h"

/* Class constant declaration  */

/* Class Type declaration      */

/* Class data declaration      */

/* Class procedure declaration */

// default constructor
ContactClass::ContactClass(char *NewName, char *NewphoneNumber)
{
	next = NULL;
	prev = NULL;
	strcpy(Name, NewName);
	strcpy(phoneNumber,NewphoneNumber);
} //ContactClass

// default destructor
ContactClass::~ContactClass()
{
} //~ContactClass
