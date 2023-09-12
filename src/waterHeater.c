#include "waterHeater.h"

/*
 * Could rewrite file. Use a bool value ON/OFF to decide how to change temp value.
 */

void waterHeater(int startTemp, SEM_ID semBinWaterTEMP, MSG_Q_ID waterTemp) {
	
	sprintf(msgBuf,"%d", startTemp);
	msgQSend(waterTemp, msgBuf, 50, WAIT_FOREVER,MSG_PRI_NORMAL);
	
	while(1) {
		
		//take the semaphore, and set the temp value
		semTake(semBinWaterTEMP, WAIT_FOREVER);
		temp = atoi(msgBuf);
		
		temp += 2; //increment temp value
		
		//send temp value to msgQ for use by Sensor
		sprintf(msgBuf,"%d", temp);
		if((msgQSend(waterTemp, msgBuf, 50, WAIT_FOREVER,MSG_PRI_NORMAL))== ERROR) {
		
			printf("waterTemp in waterHeater failed\n");
		
		}
		
		//give up the semaphore, delay task by 1 second
		semGive(semBinWaterTEMP);
		taskDelay(sysClkRateGet());
		
		
	}
	
}

void waterCooler(SEM_ID semBinWaterTEMPC, MSG_Q_ID waterTemp) {
	
	while(1) {
			
		semTake(semBinWaterTEMPC, WAIT_FOREVER);
		temp = atoi(msgBuf);
		
		temp -= 1;
		
		sprintf(msgBuf,"%d", temp);
				
		if((msgQSend(waterTemp, msgBuf, 50, WAIT_FOREVER,MSG_PRI_NORMAL))== ERROR) {
		
			printf("waterTemp in waterHeater failed\n");
		
		}
		
		semGive(semBinWaterTEMPC);
		taskDelay(sysClkRateGet());
			
			
	}
	
}
