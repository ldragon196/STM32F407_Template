/*
 * gpio.c
 *
 *  Created on: November 18, 2020
 *      Author: LongHD
 */
 
/******************************************************************************/


/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/

#include "gpio.h"

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



/******************************************************************************/

/**
 * @brief  Initializes GPIO
 * @param  None
 * @retval None
 */

void GPIO_InitOutputPP(GPIO_Pin_t *gpio, uint32_t mode){
	GPIO_InitTypeDef GPIO_InitStruct;
	
	/*Configure GPIO pins */
	GPIO_InitStruct.Pin = gpio->pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = mode;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(gpio->port, &GPIO_InitStruct);
}











