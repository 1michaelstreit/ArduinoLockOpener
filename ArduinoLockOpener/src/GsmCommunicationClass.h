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
SoftwareSerial *GsmSerial;
int checkConnectionTime;

private:
static const int bufferSize = 256;
char receiveBuffer[bufferSize];	
bool gsmIsConnected = false;
bool gsmIsConnectedOld = false;
bool answerReceived = false;
char smsSenderNr[20] = {0};
 


// Methods
public:
	GsmCommunicationClass(SoftwareSerial *NewGsmSerial);
	~GsmCommunicationClass();
	
	void checkConnection();
	void readSerial();
	void handleReceivedSms();
	
private:


	void displayString(char *dString);
	void checkReceivedData();
	int  checkAuthorzation(char *nrToCheck);
	void isolateSmsSenderPhoneNr();
	void setUpSmsMode();
	
	
};
/*****************************************************************************/
/*  End Header  : GsmCommunicationClass                                              */
/*****************************************************************************/
#endif //__GSMCOMMUNICATIONCLASS_H__
