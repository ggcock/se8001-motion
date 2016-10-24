
#ifndef __HALIMU_H
#define __HALIMU_H

#include "system.h"

#define	IMU_USE_L3G4200D
#define IMU_USE_ADXL345


#ifdef IMU_USE_L3G4200D
	#include "../Driver/Chip/L3G4200D/L3G4200D.h"
#endif


#ifdef IMU_USE_ADXL345
	#include "../Driver/Chip/ADXL345/ADXL345.h"
#endif

typedef struct 	
{
	SE_ADXL345_HandleTypeDef		tADXL345;
	SE_L3G4200D_HandleTypeDef		tL3G4200D;
}SE_IMU_HandleTypeDef;

bool	IMU_Init(SE_IMU_HandleTypeDef *pIMU);
bool	IMU_GetAccData(SE_IMU_HandleTypeDef *pIMU);
bool	IMU_GetGysData(SE_IMU_HandleTypeDef *pIMU);
#endif
