#ifndef PRESS_SENSOR
#define PRESS_SENSOR

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
#include <sigLib.h>		/* we use Signals */
#include <wdLib.h>		/* we use a watchdog */

#define MAX_PRESSURE 50;
#define PRESSURE_DELAY (sysClkRateGet());

WDOG_ID wdPressure;

void pressSensor(int, int, MSG_Q_ID, MSG_Q_ID);
void pressRestart(void);

int temp = 0;
int vol = 0;
int pressure = 20;
int prevVolume;
char msgBuf[50];

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* PRESS_SENSOR */
