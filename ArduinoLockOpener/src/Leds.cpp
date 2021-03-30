/*****************************************************************************/
/*  Class      : TemplateClass                                  Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : This class describes ....                                   */
/*                                                                           */
/*                                                                           */
/*  Methodes   : TemplateClass()  ToDo                                       */
/*              ~TemplateClass()  ToDo                                       */
/*                                                                           */
/*  Author     : Michael Streit                                              */
/*                                                                           */
/*  History    : 05.03.2021  IO Created                                      */
/*                                                                           */
/*  File       : TemplateClass.cpp                                           */
/*                                                                           */
/*****************************************************************************/
/* HTA Burgdorf                                                              */
/*****************************************************************************/

/* imports */
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Leds.hpp"

//#include <iostream>

using namespace std;

/* Class constant declaration  */

/* Class Type declaration      */

/* Class data declaration      */

/* Class procedure declaration */

/*****************************************************************************/
/*  Method      :                                                   */
/*****************************************************************************/
/*                                                                           */
/*  Function    :                                                            */
/*                                                                           */
/*  Type        :                                                 */
/*                                                                           */
/*  Input Para  :                                                            */
/*                                                                           */
/*  Output Para :                                                            */
/*                                                                           */
/*  Author      : Michael Streit                                             */
/*                                                                           */
/*  History     : 10.11.2021  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/

GpioPortClass::GpioPortClass(uint8_t *NewBaseAdress)
{
	   LedBase = NewBaseAdress;
	   ShadowLedRegister = 0;

		// init GPIO
		DDRB	|=  (1 << LED_BUILTIN);	// set GPIO as Output
		PORTB	&= ~(1 << LED_BUILTIN);	// clear bit
		DDRB	|=  (1 << LED_STATE);	// set GPIO as Output
		PORTB	&= ~(1 << LED_STATE);	// clear bit
		
		DDRD	|= (1 << LOCK);			// set GPIO as Output
		PORTD	&= ~(1 << LOCK);		// clear bit

		
}

GpioPortClass::~GpioPortClass(void)
{
	   *LedBase = 0;
	   ShadowLedRegister = 0;
}

void GpioPortClass::SetLed(int LedNumber, LedState State)
{
   if ((LedNumber >= 0) && (LedNumber <= MAX_LED-1)) {

	   /* Find correct bitposition */
	  unsigned long  Mask = 1 << (LedNumber);

	   /* and clear or set bit according to State */
	   if (State != OFF) {
		   ShadowLedRegister |= Mask;
		   } else {
		   ShadowLedRegister  &= ~Mask; 
	   }
	   
	   *LedBase = ShadowLedRegister;
	}
   }

void GpioPortClass::ToggleLed(int LedNumber)
{
	if(toggleTime > 15){
		toggleTime = 0;
	if ((LedNumber >= 0) && (LedNumber <= MAX_LED-1)) {

	   /* Find correct bitposition */
		unsigned long  Mask = 1 << (LedNumber);

	   /* and clear or set bit according to State */
		ShadowLedRegister ^= Mask;
	   
	   *LedBase = ShadowLedRegister;
	}
	}else{
		toggleTime++;
	}
}
/*****************************************************************************/
/*  End Class   : TemplateClass                                              */
/*****************************************************************************/
