#ifndef __GSMCOMMUNICATIONCLASS_H__
#define __GSMCOMMUNICATIONCLASS_H__
/****************************************************************************/
/*  Header     : GsmCommunicationClass                          Version 1.0 */
/****************************************************************************/
/*                                                                          */
/*  Function   : This Class manages the Communication between the the uP and*/
/*               the GSM Moduel                                             */
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

// define Pins for software serial to GSM Modul
#define RX	3 		// RX pin 3 on Arduino
#define TX	2 		// TX pin 2 on Arduino

#define REP_CHECK_CONNECTION	50

/* Class Type declaration      */

/* Class data declaration      */

/* Class definition            */

class GsmCommunicationClass
{
// Data
public:
static const int bufferSize = 256;
char receiveBuffer[bufferSize] = {0};
int loopCntConnection = REP_CHECK_CONNECTION;

private:
SoftwareSerial *GsmSerial;
bool gsmIsConnected = false;
bool gsmIsConnectedOld = false;
bool answerReceived = false;


// Methods
public:
	GsmCommunicationClass(SoftwareSerial *NewGsmSerial);
	~GsmCommunicationClass();
	
	void checkConnection();
	void readSerial();
	void sendAtCmd(char atCmd[256]);
		
private:

	void setUpSmsMode();
		
};
/*****************************************************************************/
/*  End Header  : GsmCommunicationClass                                      */
/*****************************************************************************/
#endif //__GSMCOMMUNICATIONCLASS_H__
