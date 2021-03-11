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

/* Class Type declaration      */

/* Class data declaration      */

/* Class definition            */

class LedManagerClass
{
	// Data
	public:
		enum {MAX_LED = 8};
		enum {PORTB_BASE = 0x25};
		enum LedState{ON = 1, OFF = 0};		
			
	private:
	      volatile uint8_t *LedBase;
	      unsigned long  ShadowLedRegister;
		  
	// Methods
	public:
			LedManagerClass(uint8_t BaseAdress = PORTB_BASE);
	        ~LedManagerClass();
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

class PortClass : public LedClass
{
	   LedManagerClass *MyParent;
	   int MyLed;
	   
	   public:
      PortClass(LedManagerClass *Parent, int LedNumber) : MyParent(Parent), MyLed(LedNumber) {};
      void On()    {MyParent->SetLed(MyLed, LedManagerClass::ON);};
      void Off()   {MyParent->SetLed(MyLed, LedManagerClass::OFF);};
      void Toggle(){MyParent->ToggleLed(MyLed);};
	
};

/*****************************************************************************/
/*  End Header  :                                              */
/*****************************************************************************/
#endif /* LEDS_H_ */