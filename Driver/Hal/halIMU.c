#//IMUÓ²¼þ³éÏó²ã
#include "halIMU.h"

bool	IMU_Init(SE_IMU_HandleTypeDef *pIMU)
{
		pIMU->tADXL345.iDeviceAddr_Main =ADXL345_DEFAULT_ADDRESS<<1;		//0x53 * 2 -> 0xA6;
		
		
		pIMU->tL3G4200D.iDeviceAddr_Main=L3G4200D_DEFAULT_ADDRESS<<1;		//0x69 * 2 -> 0xD2;
	
		return TRUE;
}

bool	IMU_GetAccData(SE_IMU_HandleTypeDef *pIMU)
{
		ADXL345_getAcceleration(&pIMU->tADXL345);
		return TRUE;
}

bool	IMU_GetGysData(SE_IMU_HandleTypeDef *pIMU)
{
		L3G4200D_getAngularVelocity(&pIMU->tL3G4200D);
		return TRUE;
}
