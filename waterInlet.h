#ifndef WATER_INLET
#define WATER_INLET

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus*/

#include <vxWorks.h> 	/* Always include this as the first thing in every program */
#include <stdio.h> 		/* we use printf */
#include <taskLib.h> 	/* we use taskSpawn */
#include <sysLib.h> 	/* we use sysClk... */
#include <msgQLib.h> 	/* we use message queues */
#include <semLib.h>   	/* we use semaphores */
#include <time.h>		/* we use tickGet()  */

int waterIN(int, int, int, SEM_ID, MSG_Q_ID, MSG_Q_ID);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* WATER_INLET */
