#ifndef WATER_LVL_SENSOR
#define WATER_LVL_SENSOR

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus*/

#include <vxWorks.h> 	/* Always include this as the first thing in every program */
#include <stdio.h> 		/* we use printf */
#include <stdlib.h>		/* we use atoi() */
#include <taskLib.h> 	/* we use taskSpawn */
#include <sysLib.h> 	/* we use sysClk... */
#include <msgQLib.h> 	/* we use message queues */
#include <semLib.h>   	/* we use semaphores */
#include <tickLib.h>	/* we use tickGet() */

void waterSensor (int, int, int, int, SEM_ID, SEM_ID, MSG_Q_ID, MSG_Q_ID, MSG_Q_ID);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* WATER_LVL_SENSOR */
