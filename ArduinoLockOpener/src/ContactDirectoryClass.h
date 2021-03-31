#ifndef __CONTACTDIRECTORYCLASS_H__
#define __CONTACTDIRECTORYCLASS_H__
/****************************************************************************/
/*  Header     : ContactDirectoryClass                          Version 1.0 */
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
/*  File       : ContactDirectoryClass.hpp									*/
/*                                                                          */
/****************************************************************************/
/* HTA Burgdorf                                                             */
/****************************************************************************/

/* imports */
//#include <C:/Qt/Tools/mingw730_64/lib/gcc/x86_64-w64-mingw32/7.3.0/include/c++/list>
//#include <list.h>
#include "ContactClass.h"

/* Class constant declaration  */

/* Class Type declaration      */

/* Class data declaration      */

/* Class definition            */

class ContactDirectoryClass
{
	
	
//Data
public:
// list elements
	ContactClass *head = NULL;
	ContactClass *tail = NULL;
protected:
private:


//Methods
public:
	ContactDirectoryClass();
	~ContactDirectoryClass();
	void addContact(char *NewName, char *NewPhoneNr, int priority);
	
protected:
private:
	void pushFront(ContactClass *NewContact);

}; 
/*****************************************************************************/
/*  End Header  : ContactDirectoryClass		                                 */
/*****************************************************************************/
#endif //__CONTACTDIRECTORYCLASS_H__
