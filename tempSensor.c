#include "tempSensor.h"

void tempSensor(int maxTemp, int minTemp, SEM_ID semBinWaterTEMP, SEM_ID semBinWaterTEMPC, MSG_Q_ID waterTemp, MSG_Q_ID waterTempPRESS) {
	
	char msgBuf[50];
	
	while(1) {
		
		if (msgQReceive(waterTemp, msgBuf, 50, WAIT_FOREVER) == ERROR) { //read msgQ value
						
			printf("waterTemp in tempSensor failed\n");
						
		} else {
			
			msgQSend(waterTempPRESS, msgBuf, 50, WAIT_FOREVER, MSG_PRI_NORMAL); //send temp to pressSensor
			
			if (atoi(msgBuf) >= (maxTemp - 10)) { //if temp is greater than MAX TEMP, stop increasing temp
				
				printf("Water Temp exceeded MAX TEMP of %d at [%d ticks - %d secs]\n", maxTemp, tickGet(), tickGet() / sysClkRateGet());
				semTake(semBinWaterTEMP, WAIT_FOREVER);
				semGive(semBinWaterTEMPC);
				
			}
			if (atoi(msgBuf) <= minTemp) { //if temp is less than MIN TEMP, heat up water
				
				printf("Water Temp exceeded MIN TEMP of %d at [%d ticks - %d secs]\n", minTemp, tickGet(), tickGet() / sysClkRateGet());
				semGive(semBinWaterTEMP);
				semTake(semBinWaterTEMPC, WAIT_FOREVER);
				
			}
		}
	}
}
