/*
 * led.c
 *
 *  Created on: November 18, 2020
 *      Author: LongHD
 */
 
/******************************************************************************/


/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/

#include "hard/gpio/gpio.h"

#include "led.h"

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/



/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/

static GPIO_Pin_t LED_Pins[LED_COUNT] = LED_PINS_CONFIG;

/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/



/******************************************************************************/
/*                                FUNCTIONS                                   */
/******************************************************************************/



/******************************************************************************/

/**
 * @brief  Initializes led
 * @param  None
 * @retval None
 */

void LED_Init(void){
	/* GPIO Ports Clock Enable */
	LED_GPIO_CLK_ENABLE();
	
	/*Configure GPIO pins */
	for(uint8_t i = 0; i < LED_COUNT; i++){
		GPIO_InitOutputPP(&LED_Pins[i], LED_PIN_PP_MODE);
	}
	
	LED_Control(LED_OFF);
}

/**
 * @brief  Control led
 * @param  Enum led mask, bit 1 ~ led on, bit 0 ~ led off
 * @retval None
 */

void LED_Control(LedMask mask){
	for(uint8_t i = 0; i < LED_COUNT; i++){
		if( (mask >> i) & 0x01 ){
			HAL_GPIO_WritePin(LED_Pins[i].port, LED_Pins[i].pin, LED_ON_LEVEL);
		}
		else{
			HAL_GPIO_WritePin(LED_Pins[i].port, LED_Pins[i].pin, LED_OFF_LEVEL);
		}
	}
}











