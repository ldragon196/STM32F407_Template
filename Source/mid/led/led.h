/*
 * led.h
 *
 *  Created on: November 18, 2020
 *      Author: LongHD
 */
 
/******************************************************************************/

#ifndef _SOURCE_MID_LED_LED_H_
#define _SOURCE_MID_LED_LED_H_

/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/

#include "config.h"

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/

typedef uint16_t LedMask;
enum {
	LED_OFF = 0,
	LED_GREEN = 1,
	LED_RED = 2,
	LED_ALL = 0xFFFF,
};

typedef struct {
	LedMask ledBlink;            // Led blink
	LedMask ledStable;           // Led after blink is completed
	uint16_t blinkTimes;         // Blink times
	uint16_t periods;            // Blink periods
} LedControl_t;


#define TIMES_BLINK_FOREVER                  200

#define TIME_LED_BLINK_FAST                  100
#define TIME_LED_BLINK_MEDIUM                300
#define TIME_LED_BLINK_SLOW                  500

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/



/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/



/******************************************************************************/
/*                                FUNCTIONS                                   */
/******************************************************************************/

void LED_Init(void);
void LED_Control(LedMask mask);
void LED_Toggle(LedMask mask);
void LED_Blink(LedMask ledBlink, uint32_t timeDelay, uint8_t timesBlink, LedMask ledStatble);

/******************************************************************************/

#endif /* _SOURCE_MID_LED_LED_H_ */
