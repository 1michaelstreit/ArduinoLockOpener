#ifndef LEDS_H_
#define LEDS_H_

/****************************************************************************/
/*  Header     : GpioPortClass									Version 1.0 */
/****************************************************************************/
/*                                                                          */
/*  Function   : This class describes the Leds                              */
/*                                                                          */
/*                                                                          */
/*  Methodes   : GpioPortClass()                                            */
/*              ~GpioPortClass()  ToDo                                      */
/*               SetLed()                                                   */
/*               ToggleLed()	                                            */
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

#define REP_TOGGLE_LED			1

/* Class Type declaration      */

/* Class data declaration      */

/* Class definition            */

class GpioPortClass
{
	// Data
	public:
		enum {MAX_LED = 8};
		enum LedState{ON = 1, OFF = 0};	
		int loopCntLed = 0;	
			
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

/****************************************************************************/
/*  Header     : LedClass										Version 1.0 */
/****************************************************************************/
/*                                                                          */
/*  Function   : This class describes the Leds                              */
/*                                                                          */
/*                                                                          */
/*  Methodes   : On()														*/
/*               Off()														*/
/*               Toggle()                                                   */
/*								                                            */
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
class LedClass
{
	// Data

	public:
	virtual void On() = 0;
	virtual void Off() = 0;
	virtual void Toggle() = 0;
};

/****************************************************************************/
/*  Header     : GPIOLedClass									Version 1.0 */
/****************************************************************************/
/*                                                                          */
/*  Function   : This class sets and clears the Leds                        */
/*                                                                          */
/*                                                                          */
/*  Methodes   : On()														*/
/*               Off()														*/
/*               Toggle()                                                   */
/*								                                            */
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

/****************************************************************************/
/*  Header     : LockOpenerClass								Version 1.0 */
/****************************************************************************/
/*                                                                          */
/*  Function   : This class sets and clears the Lock LED. Can be adapted    */
/*               to the real LockClass.                                     */
/*                                                                          */
/*  Methodes   : On()														*/
/*               Off()														*/
/*               Toggle()                                                   */
/*								                                            */
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
class LockOpenerClass : public LedClass
{
	GpioPortClass *MyParent;
	int MyLed;
	
	public:
	LockOpenerClass(GpioPortClass *Parent, int LedNumber) : MyParent(Parent), MyLed(LedNumber) {};
	void On()    {MyParent->SetLed(MyLed, GpioPortClass::ON);};
	void Off()   {MyParent->SetLed(MyLed, GpioPortClass::OFF);};
	void Toggle(){MyParent->ToggleLed(MyLed);};
	
};

/*****************************************************************************/
/*  End Header  :                                              */
/*****************************************************************************/
#endif /* LEDS_H_ */