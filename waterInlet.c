#include "waterInlet.h"

int waterIN(int flow, int volume, int numOfValves, SEM_ID semBinWaterIN, MSG_Q_ID msgQWaterIN, MSG_Q_ID msgQWaterVol) {
	
	char msgBuf[50];
	
	//printf("CHICKEN LEGS : %d\n", flow);
	flow = flow * numOfValves; //calculate flow rate 
	//printf("CHICKEN LEGS B4 WHILE");
	
	while (1) {
		
		//take the semaphore, receive the volume value
		semTake(semBinWaterIN, WAIT_FOREVER);
		msgQReceive(msgQWaterVol, msgBuf, 50, NO_WAIT); 
		volume = atoi(msgBuf);
		
		//printf("CHICKEN LEGS 3 : %d\n", flow);
		volume += flow; //increment the volume value
		//printf("CHICKEN LEGS 4 : %d\n", volume);
		
		//send
		sprintf(msgBuf,"%d", volume);
		if((msgQSend(msgQWaterIN, msgBuf, 50, WAIT_FOREVER,MSG_PRI_NORMAL))== ERROR) {
			
			printf("msgQwater in waterIN failed\n");
			
		}
		
		msgQSend(msgQWaterVol, msgBuf, 50, WAIT_FOREVER,MSG_PRI_NORMAL);		
		semGive(semBinWaterIN);
		taskDelay(sysClkRateGet());
		
	}
	
	return volume;
	
}
