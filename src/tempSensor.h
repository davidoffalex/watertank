#ifndef TEMP_SENSOR
#define TEMP_SENSOR

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
#include <logLib.h>   	/* we use logMsg rather than printf */
#include <tickLib.h>	/* we use getTick() */

void tempSensor (int, int, SEM_ID, SEM_ID, MSG_Q_ID, MSG_Q_ID);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* TEMP_SENSOR */
