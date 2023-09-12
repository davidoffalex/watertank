#include "waterLvlSensor.h"

int isFull = 0;

void waterSensor (int sensor1, int sensor2, int sensor3, int sensor4, SEM_ID semBinWaterIN, SEM_ID semBinWaterOUT, MSG_Q_ID waterIN, MSG_Q_ID waterOUT, MSG_Q_ID waterVolPRESS) {
	
	char msgBuf[50];
	while (1) {
		
		if (isFull == 0) {
			
			if (msgQReceive(waterIN, msgBuf, 50, WAIT_FOREVER) == ERROR) { //read msgQ value
				
				printf("waterIN in WaterSensor failed\n");
				
			} else {
				
				msgQSend(waterVolPRESS, msgBuf, 50, WAIT_FOREVER, MSG_PRI_NORMAL);
				
				//detect volume per each sensor value
				if (atoi(msgBuf) >= sensor1) {
					
					printf("Water Sensor #1 has been reached at %dL at [%d ticks - %d secs]\n", atoi(msgBuf), tickGet(), tickGet() / sysClkRateGet());
										
				} 
				if (atoi(msgBuf) >= sensor2) {
					
					printf("Water Sensor #2 has been reached at %dL at [%d ticks - %d secs]\n", atoi(msgBuf), tickGet(), tickGet() / sysClkRateGet());
										
				}
				if (atoi(msgBuf) >= sensor3) {
					
					printf("Water Sensor #3 has been reached at %dL at [%d ticks - %d secs]\n", atoi(msgBuf), tickGet(), tickGet() / sysClkRateGet());
					
				}
				if (atoi(msgBuf) >= sensor4) {
					
					//turn off water IN, turn on water OUT
					printf("Water Sensor #4 has been reached at %dL at [%d ticks - %d secs]\n", atoi(msgBuf), tickGet(), tickGet() / sysClkRateGet());
					isFull = 1;
					semTake(semBinWaterIN, WAIT_FOREVER);
					semGive(semBinWaterOUT);
					

				}
				
			}
			
		} 
		
		if (isFull == 1) {
			
			if (msgQReceive(waterOUT, msgBuf, 50, WAIT_FOREVER) == ERROR) { //read msgQ value
							
				printf("waterOUT in WaterSensor failed\n");
				
			} else {
				
				msgQSend(waterVolPRESS, msgBuf, 50, WAIT_FOREVER, MSG_PRI_NORMAL);
				
				if (atoi(msgBuf) < sensor1) {
					
					//turn off water OUT, turn on water IN
					isFull = 0;
					semTake(semBinWaterOUT, WAIT_FOREVER);
					semGive(semBinWaterIN);
					
				}
				if (atoi(msgBuf) >= sensor1) {
					
					printf("Water Sensor #1 has been reached at %dL at [%d ticks - %d secs]\n", atoi(msgBuf), tickGet(), tickGet() / sysClkRateGet());
										
				}
				if (atoi(msgBuf) >= sensor2) {
					
					printf("Water Sensor #2 has been reached at %dL at [%d ticks - %d secs]\n", atoi(msgBuf), tickGet(), tickGet() / sysClkRateGet());
										
				}
				if (atoi(msgBuf) >= sensor3) {
					
					printf("Water Sensor #3 has been reached at %dL at [%d ticks - %d secs]\n", atoi(msgBuf), tickGet(), tickGet() / sysClkRateGet());
										
				}
				if (atoi(msgBuf) >= sensor4) {
					
					printf("Water Sensor #4 has been reached at %dL at [%d ticks - %d secs]\n", atoi(msgBuf), tickGet(), tickGet() / sysClkRateGet()); 
										
				}
				
			}
			
		}
		
	}
	
}

void sigHandler (int sigNo){
	
	switch(sigNo)
	case(30):
				//if pressure sensor goes off, turn off water IN, turn on water OUT
				isFull = 1;
				printf("Critical Pressure hit - Inlet valves closed. Outlet valves open. Occurred at [%d ticks - %d secs]\n", tickGet(), tickGet() / sysClkRateGet());
}

