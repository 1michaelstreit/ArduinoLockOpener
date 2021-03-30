#ifndef LEDS_H_
#define LEDS_H_

/****************************************************************************/
/*  Header     : LedClass										Version 1.0 */
/****************************************************************************/
/*                                                                          */
/*  Function   :           */
/*                                                                          */
/*                                                                          */
/*  Methodes   :                                                            */
/*                                                                          */
/*  Author     : M. Streit                                                  */
/*                                                                          */
/*  History    : 10.03.2021  IO Created                                     */
/*                                                                          */
/*  File       : Leds.hpp													*/
/*                                                                          */
/****************************************************************************/
/* HTA Burgdorf                                                             */
/****************************************************************************/

/* imports */
#include <stdint.h>


/* Class constant declaration  */
#define LED_STATE		0
#define LED_BUILTIN		5
#define LOCK			5

/* Class Type declaration      */

/* Class data declaration      */

/* Class definition            */

class GpioPortClass
{
	// Data
	public:
		enum {MAX_LED = 8};
		//enum {PORTB_BASE = 0x25};
		uint8_t port_base;
		enum LedState{ON = 1, OFF = 0};	
		int toggleTime = 0;	
			
	private:
	      volatile uint8_t *LedBase;
	      unsigned long  ShadowLedRegister;
		  
	// Methods
	public:
			GpioPortClass(uint8_t *NewBaseAdress);
	        ~GpioPortClass();
	        void SetLed(int Number, LedState State);
	        void ToggleLed(int Number);

};


class LedClass
{
	// Data

	public:
	virtual void On() = 0;
	virtual void Off() = 0;
	virtual void Toggle() = 0;
};

class GPIOLedClass : public LedClass
{
	   GpioPortClass *MyParent;
	   int MyLed;
	   
	   public:
      GPIOLedClass(GpioPortClass *Parent, int LedNumber) : MyParent(Parent), MyLed(LedNumber) {};
      void On()    {MyParent->SetLed(MyLed, GpioPortClass::ON);};
      void Off()   {MyParent->SetLed(MyLed, GpioPortClass::OFF);};
      void Toggle(){MyParent->ToggleLed(MyLed);};
	
};

/*****************************************************************************/
/*  End Header  :                                              */
/*****************************************************************************/
#endif /* LEDS_H_ */