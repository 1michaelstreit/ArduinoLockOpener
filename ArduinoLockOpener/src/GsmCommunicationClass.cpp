/*****************************************************************************/
/*  Class      : GsmCommunicationClass                          Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : This Class manages the Communication between the the uP and */
/*               the GSM Moduel                                              */
/*                                                                           */
/*  Methodes   : GsmCommunicationClass()									 */
/*              ~GsmCommunicationClass()									 */
/*              checkConnection()                                            */
/*              setUpSmsMode()												 */
/*              sendAtCmd()                                                  */
/*              readSerial()                                                 */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/*  Author     : Michael Streit                                              */
/*                                                                           */
/*  History    : 23.03.2021  IO Created                                      */
/*                                                                           */
/*  File       : GsmCommunicationClass.cpp                                   */
/*                                                                           */
/*****************************************************************************/
/* HTA Burgdorf                                                              */
/*****************************************************************************/

/* imports */
#include <string.h>
#include "GsmCommunicationClass.h"
#include "Arduino.h"


/* Class constant declaration  */
#define BAUDRATE_DEBUG_SERIAL	( 9600 )
#define BAUDRATE_GSM_SERIAL		( 9600 )

/* Class Type declaration      */

/* Class data declaration      */

/* Class procedure declaration */

/*****************************************************************************/
/*  Method      : GsmCommunicationClass                                      */
/*****************************************************************************/
/*                                                                           */
/*  Function    : begin serial communications                                */
/*                                                                           */
/*  Type        : Constructor                                                */
/*                                                                           */
/*  Input Para  : NewGsmSerial: pointer to Gsm Serial Object                 */
/*                                                                           */
/*  Output Para : -                                                          */
/*                                                                           */
/*  Author      : Michael Streit                                             */
/*                                                                           */
/*  History     : 05.03.2021  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
GsmCommunicationClass::GsmCommunicationClass(SoftwareSerial *NewGsmSerial)
{
	GsmSerial = NewGsmSerial;
	
	// begin serial communication
	Serial.begin(BAUDRATE_DEBUG_SERIAL);		// for debugging with USB
	GsmSerial->begin(BAUDRATE_GSM_SERIAL);		// for GSM communication
	
	_delay_ms(1000);
	
	GsmSerial->println("AT");	// AT Handshake with GSM
	readSerial();
	
} //GsmCommunicationClass

// destructor
GsmCommunicationClass::~GsmCommunicationClass()
{
} //~GsmCommunicationClass

/*****************************************************************************/
/*  Method      : checkConnection		                                     */
/*****************************************************************************/
/*                                                                           */
/*  Function    : checks repetitively if GSM is connected to Network         */
/*                                                                           */
/*                                                                           */
/*  Input Para  : -                                                          */
/*                                                                           */
/*  Output Para : -                                                          */
/*                                                                           */
/*  Author      : Michael Streit                                             */
/*                                                                           */
/*  History     : 23.03.2021  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
void GsmCommunicationClass::checkConnection()
{	
	if(loopCntConnection >= REP_CHECK_CONNECTION){			// define repetition rate
		loopCntConnection = 0;
		
		if (GsmSerial->available()==0){
			GsmSerial->println("AT+CREG?");					// ask if connected to cellular Network
		}
		readSerial();										// read Answer
	
		if(strstr(receiveBuffer, "+CREG: 0,1") != NULL){	// check if connection was successful
			gsmIsConnected = true;
			Serial.write("GSM Connected\r\n\r\n\r\n");			// print that connection is successful
			if(gsmIsConnected == true && gsmIsConnectedOld == false){
				setUpSmsMode();								// set up Sms Mode if connected
			}
			gsmIsConnectedOld = gsmIsConnected;
			}else{
			gsmIsConnected = false;							// GSM is not connected
		}
	}else{
		loopCntConnection++;
	}
}
/*****************************************************************************/
/*  Method      : readSerial			                                     */
/*****************************************************************************/
/*                                                                           */
/*  Function    : Checks if something received from GSM Module, if yes       */
/*				  fill received data into Buffer and display it              */
/*                                                                           */
/*  Input Para  : -                                                          */
/*                                                                           */
/*  Output Para : -                                                          */
/*                                                                           */
/*  Author      : Michael Streit                                             */
/*                                                                           */
/*  History     : 23.03.2021  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
void GsmCommunicationClass::readSerial(){
	int i = 0;
	bool somethingReceived = false;
	
	_delay_ms(100);
	
	// clear Buffer
	for(int u=0; u<bufferSize; u++){
		receiveBuffer[u] = '\0';
	}
	
	// fill Buffer
	if(GsmSerial->available()){
		while(GsmSerial->available()){
		receiveBuffer[i] = GsmSerial->read();
		i++;
		}
	
	// set end of string
	receiveBuffer[i] = '\0';
	
	// print received Buffer
	Serial.write(receiveBuffer);
	}
}
	
/*****************************************************************************/
/*  Method      : setUpSmsMode			                                     */
/*****************************************************************************/
/*                                                                           */
/*  Function    : enable settings to receive SMS				             */
/*                                                                           */
/*  Input Para  : -                                                          */
/*                                                                           */
/*  Output Para : -                                                          */
/*                                                                           */
/*  Author      : Michael Streit                                             */
/*                                                                           */
/*  History     : 23.03.2021  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
void GsmCommunicationClass::setUpSmsMode(){
	GsmSerial->println("AT+CMGF=1");			// Configure TEXT mode
	readSerial();
	
	GsmSerial->println("AT+CNMI=1,2,0,0,0");	// define how newly arrived SMS Msg. should be handled
	readSerial();
	
	// check Answer
	if(strstr(receiveBuffer, "OK") != NULL){			// check if configured
		Serial.write("SMS Mode is configured\r\n\r\n");
		gsmIsConnectedOld = gsmIsConnected;
	}else if(strstr(receiveBuffer, "ERROR")){	
		Serial.write("ERROR in SMS mode configuration\r\n");
	}else{
		Serial.write("No response in SMS configuration\r\n");
	}
}

/*****************************************************************************/
/*  Method      : sendAtCmd				                                     */
/*****************************************************************************/
/*                                                                           */
/*  Function    : send At commands for extern classes			             */
/*                                                                           */
/*  Input Para  : atCmd: string which should be send                         */
/*                                                                           */
/*  Output Para : -                                                          */
/*                                                                           */
/*  Author      : Michael Streit                                             */
/*                                                                           */
/*  History     : 23.03.2021  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
void GsmCommunicationClass::sendAtCmd(char atCmd[256]){
	GsmSerial->println(atCmd);
}
