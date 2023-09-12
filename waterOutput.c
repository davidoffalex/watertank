#include "waterOutput.h"

/*
 * function to control the outlet flow of the tank.
 */

int waterOUT(int flow, int volume, SEM_ID semBinWaterOUT, MSG_Q_ID msgQWaterOUT, MSG_Q_ID msgQWaterVol) {
	
	char msgBuf[50];
	
	while (1) {
		
		//take the semaphore, receive the volume value
		semTake(semBinWaterOUT, WAIT_FOREVER);	
		msgQReceive(msgQWaterVol, msgBuf, 50, WAIT_FOREVER); 
		volume = atoi(msgBuf); 
		
		//printf("CHICKEN LEGS VOLUME: %d\n", volume);
		volume -= flow; //decrease volume value
		
		//send volume value to sensors
		sprintf(msgBuf,"%d", volume);
		if((msgQSend(msgQWaterOUT, msgBuf, 50, WAIT_FOREVER,MSG_PRI_NORMAL))== ERROR) {
		
			printf("msgQwater in waterIN failed\n");
		
		}

		msgQSend(msgQWaterVol, msgBuf, 50, WAIT_FOREVER,MSG_PRI_NORMAL);
		
		//give the semaphore up, delay task by 1 second
		semGive(semBinWaterOUT);
		taskDelay(sysClkRateGet());
		
	}
	
	return volume;
	
}
