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
#include "hard/event/event.h"
#include "led.h"

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/



/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/

EventControl ledBlinkEventControl;

static GPIO_Pin_t LED_Pins[LED_COUNT] = LED_PINS_CONFIG;
static LedControl_t ledControlled;

/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/



/******************************************************************************/
/*                                FUNCTIONS                                   */
/******************************************************************************/

void ledBlinkEventFunction(void);

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
	memset(&ledControlled, 0, sizeof(ledControlled));
	
	/* Turn off all led */
	LED_Control(LED_OFF);
	
	/* Creat event for blink */
	EVENT_Creat(&ledBlinkEventControl, ledBlinkEventFunction);
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

/**
 * @brief  Toggle led (bit = 1: Toggle, bit = 0: No toggle)
 * @param  Led mask
 * @retval None
 */

void LED_Toggle(LedMask mask){
	for(uint8_t i = 0; i < LED_COUNT; i++){
		if( ((mask >> i) & 0x01) == 1){
			HAL_GPIO_TogglePin(LED_Pins[i].port, LED_Pins[i].pin);
		}
	}
}

/**
 * @function :  LED_BlinkLed
 * @brief    :  blink led
 * @parameter:  ledBlink: Led controlled blinky
 *              timeDelay: time delay between 2 times blinks
 *              timesBlink: times blinks
*               ledStatble: led mask will be showed after blink complete
 * @retVal   :  None
 */

void LED_Blink(LedMask ledBlink, uint32_t timeDelay, uint8_t timesBlink, LedMask ledStatble){
	ledControlled.ledBlink = ledBlink;
	ledControlled.periods = timeDelay;
	ledControlled.blinkTimes = 2 * timesBlink;
	ledControlled.ledStable = ledStatble;
	
	/* If times blink >= TIMES_BLINK_FOREVER, blink led forever */
	if (timesBlink > TIMES_BLINK_FOREVER){
		timesBlink = TIMES_BLINK_FOREVER;
	}
	
	/* Turn on led for a moment before blink */
	LED_Control(LED_OFF);
	EVENT_SetDelayMS(ledBlinkEventControl, TIME_LED_BLINK_FAST);
}

/**
 * @brief    :  Determine time and blinks led
 * @parameter:  None
 * @retVal   :  None
 */

void ledBlinkEventFunction(void){
	EVENT_SetInactive(ledBlinkEventControl);
	
	if(ledControlled.blinkTimes > 0){
		/* Toggle led */
		LED_Toggle(ledControlled.ledBlink);
		if(ledControlled.blinkTimes != TIMES_BLINK_FOREVER){
			ledControlled.blinkTimes--;
		}
		
		/* Active event again after time delay */
		EVENT_SetDelayMS(ledBlinkEventControl, ledControlled.periods);
	}
	else{
		/* Control led stable */
		LED_Control(ledControlled.ledStable);
	}
}









