#include "waterTank.h"


void createSems() { //Function to create all Semaphores used for the Program. Semaphores used to control water valves and temperature heater.
	semBinWaterIN = semBCreate(SEM_Q_FIFO, SEM_FULL);
	semBinWaterOUT = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
	semBinWaterTEMP = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
	semBinWaterTEMPC = semBCreate(SEM_Q_FIFO, SEM_FULL);
}

void createMsgQs() { //Function to Create all message Queues used for the Program. Used to pass values between functions.
	if ((msgQWaterIN = msgQCreate(MAX_MESSAGES,MAX_MESSAGE_LENGTH,MSG_Q_FIFO)) == NULL)
		printf("msgQWaterIN in createMsgQs failed\n");
	if ((msgQWaterOUT = msgQCreate(MAX_MESSAGES,MAX_MESSAGE_LENGTH,MSG_Q_FIFO)) == NULL)
		printf("msgQWaterOUT in createMsgQs failed\n");
	if ((msgQWaterVol = msgQCreate(MAX_MESSAGES,MAX_MESSAGE_LENGTH,MSG_Q_FIFO)) == NULL)
		printf("msgQWaterVol in createMsgQs failed\n");
	if ((msgQWaterTemp = msgQCreate(MAX_MESSAGES,MAX_MESSAGE_LENGTH,MSG_Q_FIFO)) == NULL)
		printf("msgQWaterTemp in createMsgQs failed\n");
	if ((msgQWaterTempPRESS = msgQCreate(MAX_MESSAGES,MAX_MESSAGE_LENGTH,MSG_Q_FIFO)) == NULL)
		printf("msgQWaterTempPRESS in createMsgQs failed\n");
	if ((msgQWaterVolPRESS = msgQCreate(MAX_MESSAGES,MAX_MESSAGE_LENGTH,MSG_Q_FIFO)) == NULL)
		printf("msgQWaterVolPRESS in createMsgQs failed\n");
}

void startSys() {

	// Ask user for Sensor placements within the tank.
	printf("Enter lowest Water Level Sensor height:\n");
	scanf("%d", &lowSensor);
	
	printf("Enter middle Water Level Sensor height:\n");
	scanf("%d", &mid1Sensor);
		
	printf("Enter second highest Water Level Sensor height:\n");
	scanf("%d", &mid2Sensor);
	
	printf("Enter highest Water Level Sensor height:\n");
	scanf("%d", &hiSensor);
				
	printf("Enter minimum Temperature:\n");
	scanf("%d", &minTemp);
	
	printf("Enter maxmimum Temperature:\n");
	scanf("%d", &maxTemp);
	
	createSems(); 	//Create Semaphores
	createMsgQs();	//Create Message Queues
	
	//Spawn all tasks 
	taskSpawn("waterIN", 100, 0x100, 2000, (FUNCPTR) waterIN, FLOWRATE, volume, 2, semBinWaterIN, msgQWaterIN, msgQWaterVol, msgQWaterVol, 0, 0, 0);
	taskSpawn("waterLevelSensor", 100, 0x100, 2000, (FUNCPTR) waterSensor, lowSensor, mid1Sensor, mid2Sensor, hiSensor, semBinWaterIN, semBinWaterOUT, msgQWaterIN, msgQWaterOUT, msgQWaterVolPRESS, 0);
	taskSpawn("waterOUT", 100, 0x100, 2000, (FUNCPTR) waterOUT, FLOWRATE, volume, semBinWaterOUT, msgQWaterOUT, msgQWaterVol, 0, 0, 0, 0, 0);
	taskSpawn("tempSensor", 100, 0x100, 2000, (FUNCPTR) tempSensor, maxTemp, minTemp, semBinWaterTEMP, semBinWaterTEMPC, msgQWaterTemp, msgQWaterTempPRESS, 0, 0, 0, 0);
	taskSpawn("waterHeater", 100, 0x100, 2000, (FUNCPTR) waterHeater, 11, semBinWaterTEMP, msgQWaterTemp, 0, 0, 0, 0, 0, 0, 0);
	taskSpawn("waterCooler", 100, 0x100, 2000, (FUNCPTR) waterCooler, semBinWaterTEMPC, msgQWaterTemp, 0, 0, 0, 0, 0, 0, 0, 0);
	taskSpawn("pressSensor", 100, 0x100, 2000, (FUNCPTR) pressSensor, mid2Sensor, maxTemp, msgQWaterTempPRESS, msgQWaterVolPRESS, 0, 0, 0, 0, 0, 0);

}

