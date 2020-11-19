/*
 * config.h
 *
 *  Created on: November 18, 2020
 *      Author: LongHD
 */
 
/******************************************************************************/

#ifndef _SOURCE_CONFIG_H_
#define _SOURCE_CONFIG_H_

/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "app/board/board.h"

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/

/* LED */

#define LED_COUNT                               2
#define LED_1_PORT                              GPIOD
#define LED_1_PIN                               GPIO_PIN_12
#define LED_2_PORT                              GPIOD
#define LED_2_PIN                               GPIO_PIN_13

#define LED_PINS_CONFIG                         \
{                                               \
	{LED_1_PORT, LED_1_PIN},                    \
	{LED_2_PORT, LED_2_PIN},                    \
}

#define LED_ON_LEVEL                            GPIO_PIN_SET
#define LED_OFF_LEVEL                           GPIO_PIN_RESET
#define LED_PIN_PP_MODE                         GPIO_PULLDOWN
#define LED_GPIO_CLK_ENABLE()                   __HAL_RCC_GPIOD_CLK_ENABLE()



/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/



/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/



/******************************************************************************/
/*                                FUNCTIONS                                   */
/******************************************************************************/



/******************************************************************************/

#endif /* _SOURCE_CONFIG_H_ */
