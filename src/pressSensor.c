#include "pressSensor.h"

void pressSensor(int sensor, int maxTemp, MSG_Q_ID msgQTemp, MSG_Q_ID msgQVolume) {
	
	if((wdPressure = wdCreate()) == NULL){ //create watchdog
		printf("Error creating Pressure Watchdog");
	}
	
	while(1) {
		
		//receive temp value
		if (msgQReceive(msgQTemp, msgBuf, 50, WAIT_FOREVER) == ERROR) {
							
			printf("Temp in pressSensor failed\n");
						
		}
		
		temp = atoi(msgBuf);
		
		//receive volume value
		if (msgQReceive(msgQVolume, msgBuf, 50, WAIT_FOREVER) == ERROR) {
					
			printf("Volume in pressSensor failed\n");
						
		}
		
		prevVolume = vol;
		vol = atoi(msgBuf);
		
		//start watchdog, if pressure sensor fails to read value, restart pressure sensor
		wdStart(wdPressure, sysClkRateGet(), (FUNCPTR) pressRestart, 0);
		
		if (pressure > 50) { //if critical pressure reached, kill the water sensors and send signal to sensors
			
			printf("Critical Pressure Reached! [%d ticks - %d secs]", tickGet(), tickGet() / sysClkRateGet());
			kill("waterLevelSensor", 30);
			
		} else {
			
			if (temp >= 90 && temp >= maxTemp) //if temp of water is high, increase pressure by two
				pressure += 2;
			if (vol >= sensor) // increase pressure if water is higher than the second sensor
				pressure++;
			if ((pressure != 0) && (vol < prevVolume)) //decrease pressure if the volume is decreasing
				pressure--;
			
		}
	}	
}

void pressRestart(void) {
	
	taskRestart("pressSensor");
	
}
