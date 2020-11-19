/*
 * gpio.h
 *
 *  Created on: November 19, 2020
 *      Author: LongHD
 */
 
/******************************************************************************/

#ifndef _SOURCE_HARD_EVENT_EVENT_H_
#define _SOURCE_HARD_EVENT_EVENT_H_

/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/

#include "config.h"

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/

typedef void (*EventFunction)(void);       // Event fired callback
typedef uint8_t EventControl;              // Event identify

/* Event status */
typedef uint8_t EventStatus;
enum{
    EVENT_INACTIVE = 0x00,
    EVENT_ACTIVE = 0x01,
};

typedef struct{
    EventStatus status;                    // Event status
    uint32_t timeStart;                    // Time start active event
    uint32_t timeExcute;                   // Active event after timeExcute (ms)
    EventFunction eventHandler;            // Callback function is invoked when timeout
} EventParam_t;




#define CURRENT_TIME_MS()                  HAL_GetTick()           
#define TIME_ELAPSED_MS(start)             ((CURRENT_TIME_MS() - (start)) & MAX_UINT32_T)


/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/



/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/



/******************************************************************************/
/*                                FUNCTIONS                                   */
/******************************************************************************/

void EVENT_Init(void);
void EVENT_Creat(EventControl *eventId, EventFunction callbackFunc);
void EVENT_Task(void);

void EVENT_SetActive(EventControl eventId);
void EVENT_SetInactive(EventControl eventId);
void EVENT_SetDelayMS(EventControl eventId, uint32_t delay);
uint32_t EVENT_GetTimeRemain(EventControl eventId);

/******************************************************************************/

#endif /* _SOURCE_HARD_EVENT_EVENT_H_ */
