#ifndef __CONTACTCLASS_H__
#define __CONTACTCLASS_H__
/****************************************************************************/
/*  Header     : ContactClass                          Version 1.0 */
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
/*  File       : ContactClass.hpp											*/
/*                                                                          */
/****************************************************************************/
/* HTA Burgdorf                                                             */
/****************************************************************************/
/* imports */
//#include <string>
#include <Arduino.h>

/* Class constant declaration  */
#define TEMPORARY	1
#define PERMANENT	2

/* Class Type declaration      */

/* Class data declaration      */

/* Class definition            */

class ContactClass
{
//Data
public:
char Name[50];
char phoneNumber[20]; 
ContactClass *next;
ContactClass *prev;
protected:
private:



//Methods
public:
	ContactClass(char *NewName, char *NewphoneNumber);
	~ContactClass();
protected:
private:

}; 

/*****************************************************************************/
/*  End Header  : ContactClass												 */
/*****************************************************************************/

#endif //__CONTACTCLASS_H__
