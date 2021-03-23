#ifndef __GSMCOMMUNICATIONCLASS_H__
#define __GSMCOMMUNICATIONCLASS_H__
/****************************************************************************/
/*  Header     : GsmCommunicationClass                          Version 1.0 */
/****************************************************************************/
/*                                                                          */
/*  Function   :          */
/*                                                                          */
/*                                                                          */
/*  Methodes   :                                                            */
/*                                                                          */
/*  Author     : M. Streit                                                  */
/*                                                                          */
/*  History    : 23.03.2021  IO Created                                     */
/*                                                                          */
/*  File       : GsmCommunicationClass.hpp                                  */
/*                                                                          */
/****************************************************************************/
/* HTA Burgdorf                                                             */
/****************************************************************************/

/* imports */
#include "SoftwareSerial.h"


/* Class constant declaration  */

// for software serial
#define RX	3 		// RX pin 3 on Arduino
#define TX	2 		// TX pin 2 on Arduino

/* Class Type declaration      */

/* Class data declaration      */

/* Class definition            */

class GsmCommunicationClass
{
// Data
public:

private:
SoftwareSerial *GsmSerialPtr;
static const int bufferSize = 256;
char receiveBuffer[bufferSize];	
bool gsmIsConnected = false;
bool gsmIsConnectedOld = false;
bool answerReceived = false;
 


// Methods
public:
	GsmCommunicationClass();
	~GsmCommunicationClass();
	
	void checkConnection();
	
private:

	void readSerial();
	void displayString(char *dString);
	void checkReceivedData();
	void setUpSmsMode();
};
/*****************************************************************************/
/*  End Header  : GsmCommunicationClass                                              */
/*****************************************************************************/
#endif //__GSMCOMMUNICATIONCLASS_H__