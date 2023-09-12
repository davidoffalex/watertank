#ifndef WATER_TANK
#define WATER_TANK

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus*/

#include <vxWorks.h> 	/* Always include this as the first thing in every program */
#include <stdio.h> 		/* we use printf */
#include <taskLib.h> 	/* we use taskSpawn */
#include <sysLib.h> 	/* we use sysClk... */
#include <msgQLib.h> 	/* we use message queues */
#include <semLib.h>   	/* we use semaphores */

#include "waterInlet.h"
#include "waterLvlSensor.h"
#include "waterOutput.h"
#include "tempSensor.h"
#include "waterHeater.h"
#include "pressSensor.h"

#define MAX_VOL 50 //1 Liter per 1000
#define FLOWRATE 1 //Lpt
#define MAX_MESSAGES 100
#define MAX_MESSAGE_LENGTH 50

int volume = 0; //L
int lowSensor = 10; //L
int mid1Sensor = 20; //L
int mid2Sensor = 30; //L
int hiSensor = 40; //L
int minTemp = 10; //*C
int maxTemp = 100; //*C

SEM_ID semBinWaterIN;
SEM_ID semBinWaterOUT;
SEM_ID semBinWaterTEMP;
SEM_ID semBinWaterTEMPC;

MSG_Q_ID msgQWaterIN;
MSG_Q_ID msgQWaterOUT;
MSG_Q_ID msgQWaterVol;
MSG_Q_ID msgQWaterTemp;
MSG_Q_ID msgQWaterTempPRESS;
MSG_Q_ID msgQWaterVolPRESS;

void startSys();

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* WATER_TANK */
