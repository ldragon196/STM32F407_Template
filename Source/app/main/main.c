/*
 * main.c
 *
 *  Created on: November 18, 2020
 *      Author: LongHD
 */
 
/******************************************************************************/


/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/

#include "config.h"
#include "hard/event/event.h"
#include "mid/led/led.h"

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/



/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/



/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/



/******************************************************************************/
/*                                FUNCTIONS                                   */
/******************************************************************************/

static void MAIN_Init(void);

/******************************************************************************/

/**
 * @brief  Initializes all elements
 * @param  None
 * @retval None
 */

static void MAIN_Init(void){
	/* Configure the system clock */
	SystemClock_Config();
	
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();
	
	/* Hard initializations */
	EVENT_Init();
	
	/* Mid initializations */
	LED_Init();
}

/**
 * @brief  Main
 * @param  None
 * @retval None
 */

int main(void){
	/* Initialization */
	MAIN_Init();
	
	LED_Blink(LED_ALL, TIME_LED_BLINK_MEDIUM, 3, LED_GREEN);
	/* Main loop */
	while(1){
		EVENT_Task();
	}
}








