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
	if (GsmSerial->available()==0){
		GsmSerial->println("AT+CREG?");		// ask if connected to cellular Network
	}
	readSerial();		// read Answer
	
	if(strstr(receiveBuffer, "+CREG: 0,1") != NULL){ // check if connection was successful
		gsmIsConnected = true;
		Serial.write("GSM Connected\n\n\n");
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
	while(GsmSerial->available()){
		receiveBuffer[i] = GsmSerial->read();
		i++;
	}
	
	// set end of string
	receiveBuffer[i] = '\0';
	
	// print receibed Buffer
	displayString(receiveBuffer);
}

void GsmCommunicationClass::displayString(char *dString){
	if(dString!=0){
		for(int i=0; dString[i]!='\0';i++){
			Serial.print(dString[i]);
		}
		Serial.print("\n");
	}
}

void GsmCommunicationClass::checkReceivedData(){
	
}

void GsmCommunicationClass::setUpSmsMode(){
	GsmSerial->println("AT+CMGF=1");	// Configure TEXT mode
	readSerial();
	
	GsmSerial->println("AT+CNMI=1,2,0,0,0");	// define how newly arrived SMS Msg. should be handled
	readSerial();
	// check Answer
	if(strstr(receiveBuffer, "OK") != NULL){ // check if configured
		Serial.write("SMS Mode is configured\n\n");
		gsmIsConnectedOld = gsmIsConnected;
	}else if(strstr(receiveBuffer, "ERROR")){
		Serial.write("ERROR in SMS mode configuration\n");
	}else{
		Serial.write("No response in SMS configuration\n");
	}
}