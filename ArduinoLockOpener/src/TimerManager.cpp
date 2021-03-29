/*****************************************************************************/
/*  Class      : TimerManager                                  Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   :                                    */
/*                                                                           */
/*                                                                           */
/*  Methodes   :                                       */
/*                                                                           */
/*  Author     : Michael Streit                                              */
/*                                                                           */
/*  History    : 29.03.2021  IO Created                                      */
/*                                                                           */
/*  File       : TimerManager.cpp                                           */
/*                                                                           */
/*****************************************************************************/
/* HTA Burgdorf                                                              */
/*****************************************************************************/

/* imports */
#include "TimerManager.h"

using namespace std;

/* Class constant declaration  */

/* Class Type declaration      */

/* Class data declaration      */

/* Class procedure declaration */

/*****************************************************************************/
/*  Method      : TimerManagerClass                                                  */
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
/*  History     : 29.03.2021  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
TimerManager::TimerManager()
{
	// initialize Timer
	/*
	TCCR1A = 0;		// set entire Register to 0
	TCCR1B = 0;		
	TCNT1  = 0;
	
	OCR1A = 15625;            // compare match register 16MHz/256/4Hz
	TCCR1B |= (1 << WGM12);   // CTC mode
	TCCR1B |= (1 << CS12);    // 256 prescaler
	TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
	interrupts();             // enable all interrupts
	*/
} //TimerManager

// default destructor
TimerManager::~TimerManager()
{
} //~TimerManager
