/*
 * gpio.c
 *
 *  Created on: November 19, 2020
 *      Author: LongHD
 */
 
/******************************************************************************/


/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/

#include "utility/utility.h"
#include "event.h"

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/



/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/

static EventParam_t eventControls[EVENT_MAX_CONTROL];
static uint32_t eventCounter;

/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/



/******************************************************************************/
/*                                FUNCTIONS                                   */
/******************************************************************************/

uint8_t EVENT_IsExpiredTime(uint8_t eventID);

/******************************************************************************/

/**
 * @brief  Initializes GPIO
 * @param  None
 * @retval None
 */

void EVENT_Init(void){
	/* Initializes timer if necessary */
	
	/* Set event control default value */
	eventCounter = 0;
    memset((uint8_t*) eventControls, 0, sizeof(eventControls));
}

/**
 * @brief  Register event to schedule
 * @param  eventId output to store event id
 *         callbackFunc function handler when event excute
 * @retval None
 */

void EVENT_Creat(EventControl *eventId, EventFunction callbackFunc){
	if(eventCounter < EVENT_MAX_CONTROL){
		eventControls[eventCounter].status = EVENT_INACTIVE;
		eventControls[eventCounter].eventHandler = callbackFunc;
		*eventId = eventCounter;
		eventCounter++;
		return;
    }
	/* Invalid ieventIdnput*/
	*eventId = EVENT_MAX_CONTROL;
}

/**
 * @brief  Active event now
 * @param  eventId
 * @retval None
 */

void EVENT_SetActive(EventControl eventId){
    if(eventId < eventCounter){
        eventControls[eventId].timeStart = CURRENT_TIME_MS();
        eventControls[eventId].timeExcute = 0;
        eventControls[eventId].status = EVENT_ACTIVE;
    }
}

/**
 * @brief  Inactive event now
 * @param  eventId
 * @retval None
 */

void EVENT_SetInactive(EventControl eventId){
    if(eventId < eventCounter){
        eventControls[eventId].status = EVENT_INACTIVE;
    }
}

/**
 * @brief  Schedule active timer after delay ms
 * @param  eventControl
 *         delay time (milliseconds)
 * @retval None
 */

void EVENT_SetDelayMS(EventControl eventId, uint32_t delay){
    if(eventId < eventCounter){
        eventControls[eventId].timeStart = CURRENT_TIME_MS();
        eventControls[eventId].timeExcute = delay;
        eventControls[eventId].status = EVENT_ACTIVE;
    }
}

/**
 * @brief  Get time remaining before event is excuted
 * @param  Event index
 * @retval Time remaining
 *         If event is not active, return 0xFFFFFFFF
 */

uint32_t EVENT_GetTimeRemain(EventControl eventId){
    uint32_t start, timeElapse;
	
    if(eventControls[eventId].status == EVENT_ACTIVE){
		// Get time remaining
		start = eventControls[eventId].timeStart;
		timeElapse = TIME_ELAPSED_MS(start);
		
		if(eventControls[eventId].timeExcute > timeElapse){
			return eventControls[eventId].timeExcute - timeElapse;
		}
    }
    return MAX_UINT32_T;
}

/**
 * @func   EVENT_Task
 * @brief  Task to schedule event
 * @param  None
 * @retval None
 */

void EVENT_Task(void){
    uint32_t i;
    for(i = 0; i < eventCounter; i++){
        if(eventControls[i].status == EVENT_ACTIVE){
            if(EVENT_IsExpiredTime(i)){
				if(eventControls[i].eventHandler != NULL){
					eventControls[i].eventHandler();
				}
            }
        }
    }
}

/**
 * @brief  Check time expired of event
 * @param  Event id to check
 * @retval true if time is expired
 */

uint8_t EVENT_IsExpiredTime(uint8_t eventID){
    uint32_t timeElapse, timeStart;

    // Get time elapse
    timeStart = eventControls[eventID].timeStart;
    timeElapse = TIME_ELAPSED_MS(timeStart);

    if(timeElapse >= eventControls[eventID].timeExcute){
        return 1;
    }
    return 0;
}






