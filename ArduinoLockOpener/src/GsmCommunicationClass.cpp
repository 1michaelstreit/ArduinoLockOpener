/*****************************************************************************/
/*  Class      : GsmCommunicationClass                          Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   :                                    */
/*                                                                           */
/*                                                                           */
/*  Methodes   : TemplateClass()  ToDo                                       */
/*              ~TemplateClass()  ToDo                                       */
/*                                                                           */
/*  Author     : Michael Streit                                              */
/*                                                                           */
/*  History    : 23.03.2021  IO Created                                      */
/*                                                                           */
/*  File       : GsmCommunicationClass.cpp                                           */
/*                                                                           */
/*****************************************************************************/
/* HTA Burgdorf                                                              */
/*****************************************************************************/

/* imports */
#include <string.h>
#include "GsmCommunicationClass.h"
#include "Arduino.h"
#include "SoftwareSerial.h"


using namespace std;

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
/*  Function    :                                                            */
/*                                                                           */
/*  Type        : Constructor                                                */
/*                                                                           */
/*  Input Para  :                                                            */
/*                                                                           */
/*  Output Para :                                                            */
/*                                                                           */
/*  Author      : Michael Streit                                             */
/*                                                                           */
/*  History     : 05.03.2021  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
GsmCommunicationClass::GsmCommunicationClass()
{
	SoftwareSerial GsmSerial(RX, TX); // RX TX
	GsmSerialPtr = &GsmSerial;
	
	// begin serial communication
	Serial.begin(BAUDRATE_DEBUG_SERIAL);		// for debugging with USB
	GsmSerialPtr->begin(BAUDRATE_GSM_SERIAL);	// for GSM communication
	_delay_ms(1000);
	
	GsmSerialPtr->println("AT");	// AT Handshake with GSM
	readSerial();
	
} //GsmCommunicationClass

// destructor
GsmCommunicationClass::~GsmCommunicationClass()
{
} //~GsmCommunicationClass

/*****************************************************************************/
/*  Method      : InitCommunication		                                     */
/*****************************************************************************/
/*                                                                           */
/*  Function    :                                                            */
/*                                                                           */
/*  Type        :			                                                */
/*                                                                           */
/*  Input Para  :                                                            */
/*                                                                           */
/*  Output Para :                                                            */
/*                                                                           */
/*  Author      : Michael Streit                                             */
/*                                                                           */
/*  History     : 23.03.2021  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
void GsmCommunicationClass::checkConnection()
{
	
	if (GsmSerialPtr->available()==0){
		GsmSerialPtr->println("AT+CREG?");		// ask if connected to cellular Network
	}
	
	readSerial();		// read Answer
	if(strstr(receiveBuffer, "+CREG: 0,1") != NULL){ // check if connection was successful
		gsmIsConnected = true;
		
		if(gsmIsConnected == true && gsmIsConnectedOld == false){
			setUpSmsMode();
		}
		gsmIsConnectedOld = gsmIsConnected;
		}else{
		gsmIsConnected = false;
	}
	
}

void GsmCommunicationClass::readSerial(){
	int i = 0;
	
	_delay_ms(500);
	
	// clear Buffer
	for(int u=0; u<bufferSize; u++){
		receiveBuffer[u] = '\0';
	}
	
	// fill Buffer
	while(GsmSerialPtr->available()){
		receiveBuffer[i] = GsmSerialPtr->read();
		i++;
	}
	
	// set end of string
	receiveBuffer[i] = '\0';
	
	if(receiveBuffer!=0){
		displayString(receiveBuffer);
		Serial.print("\n");
	}
}

void GsmCommunicationClass::displayString(char *dString){
	for(int i=0; dString[i]!='\0';i++){
		Serial.print(dString[i]);
	}
}

void GsmCommunicationClass::checkReceivedData(){
	
}

void GsmCommunicationClass::setUpSmsMode(){
	GsmSerialPtr->println("AT+CMGF=1");	// Configure TEXT mode
	readSerial();
	
	GsmSerialPtr->println("AT+CNMI=1,2,0,0,0");	// define how newly arrived SMS Msg. should be handled
	readSerial();
	// check Answer
	if(strstr(receiveBuffer, "OK") != NULL){ // check if configured
		Serial.write("SMS Mode is configured");
		gsmIsConnectedOld = gsmIsConnected;
	}else if(strstr(receiveBuffer, "ERROR")){
		Serial.write("ERROR in SMS mode configuration");
	}else{
		Serial.write("No response in SMS configuration");
	}
}