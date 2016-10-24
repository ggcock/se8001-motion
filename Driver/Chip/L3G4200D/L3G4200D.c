/*---------------------------------------------------------------------*/
/*
* File name   : L3G3400D.c
* Author      : William.Guo
* Version     : 
* Date        : 2016-10-16
* Description : L3G3400D Çý¶¯
* others      :
* FunctionList:
* History     :
*   1. Date:
*      Reason:
*      Author:
*      Modification:
*/
/*---------------------------------------------------------------------*/

#include "L3G4200D.h"
#include "i2c.h"

/** Power on and prepare for general usage.
 * All values are defaults except for the power on bit in CTRL_REG_1
 * @see L3G4200D_RA_CTRL_REG1
 * @see L3G4200D_RA_CTRL_REG2
 * @see L3G4200D_RA_CTRL_REG3
 * @see L3G4200D_RA_CTRL_REG4
 * @see L3G4200D_RA_CTRL_REG5
 */
void L3G4200D_initialize(SE_L3G4200D_HandleTypeDef *hGS)
{
		//hGS->iCtrl_Reg1= L3G4200D_PD_ON | L3G4200D_ZEN | L3G4200D_YEN | L3G4200D_XEN ; 	//0b00001111
		//hGS->iCtrl_Reg2= L3G4200D_HPM_HRF | L3G4200D_HPCF1 ;														//0b00000000
		//hGS->iCtrl_Reg3= 0;
		//hGS->iCtrl_Reg4= 0;
		//hGS->iCtrl_Reg5= 0;

		hGS->iAV_X=0;
		hGS->iAV_Y=0;
		hGS->iAV_Z=0;
	
		if(hGS)
		{
			I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG1 , hGS->iCtrl_Reg1 );		
			I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG2 , hGS->iCtrl_Reg2 );		
			I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG3 , hGS->iCtrl_Reg3 );		
			I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG4 , hGS->iCtrl_Reg4 );		
			I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG5 , hGS->iCtrl_Reg5 );		
		}
}

/** Verify the I2C connection.
 * Make sure the device is connected and responds as expected.
 * @return True if connection is valid, false otherwise
 */
bool L3G4200D_testConnection(SE_L3G4200D_HandleTypeDef *hGS)
{		
		if(L3G4200D_getDeviceID(hGS)==0xD3)	
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}    
}


// WHO_AM_I register, read-only
/** Get the Device ID.
 * The WHO_AM_I register holds the device's id
 * @return Device ID (should be 0b11010011, 0xD3)
 * @see L3G4200D_RA_WHO_AM_I
 */
uint8_t L3G4200D_getDeviceID(SE_L3G4200D_HandleTypeDef *hGS) 
{

		hGS->iID = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_WHO_AM_I);
		
    return hGS->iID;
}



// CTRL_REG1 register, r/w

/** Set the output data rate
 * @param rate The new data output rate (can be 100, 200, 400, or 800)
 * @see L3G4200D_RA_CTRL_REG1
 * @see L3G4200D_ODR_BIT
 * @see L3G4200D_ODR_LENGTH
 * @see L3G4200D_RATE_100
 * @see L3G4200D_RATE_200
 * @see L3G4200D_RATE_400
 * @see L3G4200D_RATE_800
 */
void L3G4200D_setOutputDataRate(SE_L3G4200D_HandleTypeDef *hGS, uint16_t rate) 
{


	hGS->iCtrl_Reg1 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG1);
	
	hGS->iCtrl_Reg1 &= ~L3G4200D_RATE_MASK;
	
	if (rate == 100) 
	{
		hGS->iCtrl_Reg1 |= L3G4200D_RATE_100;
	} 
	else if (rate == 200) 
	{
		hGS->iCtrl_Reg1 |= L3G4200D_RATE_200;
	} 
	else if (rate == 400) 
	{
		hGS->iCtrl_Reg1 |= L3G4200D_RATE_400;
	} 
	else 
	{
		hGS->iCtrl_Reg1 |= L3G4200D_RATE_800;
	}
	
	I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG1 , hGS->iCtrl_Reg1 );		
}


/** Get the current output data rate
 * @return Current data output rate
 * @see L3G4200D_RA_CTRL_REG1
 * @see L3G4200D_ODR_BIT
 * @see L3G4200D_ODR_LENGTH
 * @see L3G4200D_RATE_100
 * @see L3G4200D_RATE_200
 * @see L3G4200D_RATE_400
 * @see L3G4200D_RATE_800
 */
uint16_t 	L3G4200D_getOutputDataRate(SE_L3G4200D_HandleTypeDef *hGS) {
	
	uint8_t rate =0;
	
	//I2Cdev::readBits(devAddr, L3G4200D_RA_CTRL_REG1, L3G4200D_ODR_BIT, L3G4200D_ODR_LENGTH, buffer);
	rate = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG1);
	
	rate &= L3G4200D_RATE_MASK;
	
	if (rate == L3G4200D_RATE_100) 
	{
		return 100;
	} 
	else if (rate == L3G4200D_RATE_200) 
	{
		return 200;
	} 
	else if (rate == L3G4200D_RATE_400) 
	{
		return 400;
	}
	else
	{
		return 800;
	}
}

/** Set the bandwidth cut-off mode
 * @param mode The new bandwidth cut-off mode
 * @see L3G4200D_RA_CTRL_REG1
 * @see L3G4200D_BW_BIT
 * @see L3G4200D_BW_LENGTH
 * @see L3G4200D_BW_LOW
 * @see L3G4200D_BW_MED_LOW
 * @see L3G4200D_BW_MED_HIGH
 * @see L3G4200D_BW_HIGH
 */
void L3G4200D_setBandwidthCutOffMode(SE_L3G4200D_HandleTypeDef *hGS, uint8_t mode) 
{
	//I2Cdev::writeBits(devAddr, L3G4200D_RA_CTRL_REG1, L3G4200D_BW_BIT, L3G4200D_BW_LENGTH, mode);
	if(hGS)
	{
		hGS->iCtrl_Reg1 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG1);
		
		hGS->iCtrl_Reg1 &= ~L3G4200D_BW_MASK;

		hGS->iCtrl_Reg1 |= mode;
		
		I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG1 , hGS->iCtrl_Reg1 );
	}
}

/** Get the current bandwidth cut-off mode
 * @return Current bandwidth cut off mode
 * @see L3G4200D_RA_CTRL_REG1
 * @see L3G4200D_BW_BIT
 * @see L3G4200D_BW_LENGTH
 * @see L3G4200D_BW_LOW
 * @see L3G4200D_BW_MED_LOW
 * @see L3G4200D_BW_MED_HIGH
 * @see L3G4200D_BW_HIGH
 */
uint8_t L3G4200D_getBandwidthCutOffMode(SE_L3G4200D_HandleTypeDef *hGS) 
{
	//I2Cdev::readBits(devAddr, L3G4200D_RA_CTRL_REG1, L3G4200D_BW_BIT, L3G4200D_BW_LENGTH, buffer);
	
	uint8_t iBW =0;
	if(hGS)
	{
		iBW = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG1);
		iBW &= L3G4200D_BW_MASK;
	}	
	return iBW;
}

/** Gets the current bandwidth cutoff based on ODR and BW
 * @return Float value of the bandwidth cut off
 * @see L3G4200D_RA_CTRL_REG1
 * @see L3G4200D_ODR_BIT
 * @see L3G4200D_ODR_LENGTH
 * @see L3G4200D_RATE_100
 * @see L3G4200D_RATE_200
 * @see L3G4200D_RATE_400
 * @see L3G4200D_RATE_800
 * @see L3G4200D_BW_BIT
 * @see L3G4200D_BW_LENGTH
 * @see L3G4200D_BW_LOW
 * @see L3G4200D_BW_MED_LOW
 * @see L3G4200D_BW_MED_HIGH
 * @see L3G4200D_BW_HIGH
 */
float L3G4200D_getBandwidthCutOff(SE_L3G4200D_HandleTypeDef *hGS) 
{
	uint16_t dataRate 		= 0;
	uint8_t bandwidthMode = 0;

	if(hGS)
	{
		dataRate 			= L3G4200D_getOutputDataRate(hGS);
		bandwidthMode = L3G4200D_getBandwidthCutOffMode(hGS);
		
		if (dataRate == 100) 
		{
			if (bandwidthMode == L3G4200D_BW_LOW) 
			{
				return 12.5;
			} 
			else 
			{
				return 25.0;
			}
		} 
		else if (dataRate == 200) 
		{
			if (bandwidthMode == L3G4200D_BW_LOW) 
			{
				return 12.5;
			} 
			else if (bandwidthMode == L3G4200D_BW_MED_LOW) 
			{
				return 25.0;
			} 
			else if (bandwidthMode == L3G4200D_BW_MED_HIGH) 
			{
				return 50.0;
			} 
			else 
			{
				return 70.0;
			}
		} 
		else if (dataRate == 400) 
		{
			if (bandwidthMode == L3G4200D_BW_LOW) 
			{
				return 20.0;
			} 
			else if (bandwidthMode == L3G4200D_BW_MED_LOW) 
			{
				return 25.0;
			} 
			else if (bandwidthMode == L3G4200D_BW_MED_HIGH) 
			{
				return 50.0;
			} 
			else 
			{
				return 110.0;
			}
		} 
		else 
		{
			if (bandwidthMode == L3G4200D_BW_LOW) 
			{
				return 30.0;
			} 
			else if (bandwidthMode == L3G4200D_BW_MED_LOW) 
			{
				return 35.0;
			} 
			else if (bandwidthMode == L3G4200D_BW_MED_HIGH) 
			{
				return 50.0;
			} 
			else 
			{
				return 110.0;
			}
		}		
	}
	else	// hGS invalid;
	{
		return 0.0;
	}
}

/** Set power on or off
 * @param enabled The new power setting (true for on, false for off)
 * @see L3G4200D_RA_CTRL_REG1
 * @see L3G4200D_PD_BIT
 */
void L3G4200D_setPowerOn(SE_L3G4200D_HandleTypeDef *hGS, bool on) 
{
	//I2Cdev::writeBit(devAddr, L3G4200D_RA_CTRL_REG1, L3G4200D_PD_BIT, on);
	
	if(hGS)
	{
		hGS->iCtrl_Reg1 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG1);
		
		if(on)
		{
			hGS->iCtrl_Reg1 |= L3G4200D_PD_ON;
		}
		else
		{
			hGS->iCtrl_Reg1 &= ~L3G4200D_PD_ON;			
		}
		
		I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG1 , hGS->iCtrl_Reg1 );		
	}
}

/** Get the current power state
 * @return Powered on state (true for on, false for off)
 * @see L3G4200D_RA_CTRL_REG1
 * @see L3G4200D_PD_BIT
 */
bool L3G4200D_getPowerOn(SE_L3G4200D_HandleTypeDef *hGS) 
{
	uint8_t	iPD =FALSE;
	//I2Cdev::readBit(devAddr, L3G4200D_RA_CTRL_REG1, L3G4200D_PD_BIT, buffer);
	//return buffer[0];
	
	if(hGS)
	{
		iPD = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG1);
		iPD &= L3G4200D_PD_ON;
		if(iPD)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}	
	else
	{
		return FALSE;
	}
}

/** Enables or disables the ability to get Z data
 * @param enabled The new enabled state of the Z axis
 * @see L3G4200D_RA_CTRL_REG1
 * @see L3G4200D_ZEN_BIT
 */
void L3G4200D_setZEnabled(SE_L3G4200D_HandleTypeDef *hGS,bool enabled) 
{
	//I2Cdev::writeBit(devAddr, L3G4200D_RA_CTRL_REG1, L3G4200D_ZEN_BIT, enabled);
	if(hGS)
	{
		hGS->iCtrl_Reg1 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG1);
		
		if(enabled)
		{
			hGS->iCtrl_Reg1 |= L3G4200D_ZEN;
		}
		else
		{
			hGS->iCtrl_Reg1 &= ~L3G4200D_ZEN;			
		}
		
		I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG1 , hGS->iCtrl_Reg1 );		
	}	
}

/** Get whether Z axis data is enabled
 * @return True if the Z axis is enabled, false otherwise
 * @see L3G4200D_RA_CTRL_REG1
 * @see L3G4200D_ZEN_BIT
 */
bool L3G4200D_getZEnabled(SE_L3G4200D_HandleTypeDef *hGS) 
{
	uint8_t	iXYZ_EN =FALSE;
	
	if(hGS)
	{
		iXYZ_EN = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG1);
		iXYZ_EN &= L3G4200D_ZEN;
		if(iXYZ_EN)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}	
	else
	{
		return FALSE;
	}
}


/** Enables or disables the ability to get Y data
 * @param enabled The new enabled state of the Y axis
 * @see L3G4200D_RA_CTRL_REG1
 * @see L3G4200D_YEN_BIT
 */
void L3G4200D_setYEnabled(SE_L3G4200D_HandleTypeDef *hGS,bool enabled) 
{	
	if(hGS)
	{
		hGS->iCtrl_Reg1 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG1);
		
		if(enabled)
		{
			hGS->iCtrl_Reg1 |= L3G4200D_YEN;
		}
		else
		{
			hGS->iCtrl_Reg1 &= ~L3G4200D_YEN;			
		}
		
		I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG1 , hGS->iCtrl_Reg1 );		
	}		
}

/** Get whether Y axis data is enabled
 * @return True if the Y axis is enabled, false otherwise
 * @see L3G4200D_RA_CTRL_REG1
 * @see L3G4200D_YEN_BIT
 */
bool L3G4200D_getYEnabled(SE_L3G4200D_HandleTypeDef *hGS) 
{
	uint8_t	iXYZ_EN =FALSE;
	
	if(hGS)
	{
		iXYZ_EN = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG1);
		iXYZ_EN &= L3G4200D_YEN;
		if(iXYZ_EN)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}	
	else
	{
		return FALSE;
	}
}

/** Enables or disables the ability to get X data
 * @param enabled The new enabled state of the X axis
 * @see L3G4200D_RA_CTRL_REG1
 * @see L3G4200D_XEN_BIT
 */
void L3G4200D_setXEnabled(SE_L3G4200D_HandleTypeDef *hGS, bool enabled) 
{
	if(hGS)
	{
		hGS->iCtrl_Reg1 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG1);
		
		if(enabled)
		{
			hGS->iCtrl_Reg1 |= L3G4200D_XEN;
		}
		else
		{
			hGS->iCtrl_Reg1 &= ~L3G4200D_XEN;			
		}
		
		I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG1 , hGS->iCtrl_Reg1 );		
	}			
}

/** Get whether X axis data is enabled
 * @return True if the X axis is enabled, false otherwise
 * @see L3G4200D_RA_CTRL_REG1
 * @see L3G4200D_XEN_BIT
 */
bool L3G4200D_getXEnabled(SE_L3G4200D_HandleTypeDef *hGS) 
{
	uint8_t	iXYZ_EN =FALSE;
	
	if(hGS)
	{
		iXYZ_EN = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG1);
		iXYZ_EN &= L3G4200D_XEN;
		if(iXYZ_EN)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}	
	else
	{
		return FALSE;
	}
}

// CTRL_REG2 register, r/w

/** Set the high pass mode
 * @param mode The new high pass mode
 * @see L3G4200D_RA_CTRL_REG2
 * @see L3G4200D_HPM_BIT
 * @see L3G4200D_HPM_LENGTH
 * @see L3G4200D_HPM_HRF
 * @see L3G4200D_HPM_REFERENCE
 * @see L3G4200D_HPM_NORMAL
 * @see L3G4200D_HPM_AUTORESET
 */
void L3G4200D_setHighPassMode(SE_L3G4200D_HandleTypeDef *hGS, uint8_t mode) 
{
	
	if(hGS)
	{
		hGS->iCtrl_Reg2 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG2);
		hGS->iCtrl_Reg2 &= ~L3G4200D_HPM_MASK;
		
		hGS->iCtrl_Reg2 |= mode;
		
		I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG2 , hGS->iCtrl_Reg2 );
		
	}
}

/** Get the high pass mode
 * @return High pass mode
 * @see L3G4200D_RA_CTRL_REG2
 * @see L3G4200D_HPM_BIT
 * @see L3G4200D_HPM_LENGTH
 * @see L3G4200D_HPM_HRF
 * @see L3G4200D_HPM_REFERENCE
 * @see L3G4200D_HPM_NORMAL
 * @see L3G4200D_HPM_AUTORESET
 */
uint8_t L3G4200D_getHighPassMode(SE_L3G4200D_HandleTypeDef *hGS) 
{
	uint8_t	iHPM_mode=0;
	
	if(hGS)
	{
		iHPM_mode = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG2);
		iHPM_mode &= L3G4200D_HPM_MASK;				
	}	

	return iHPM_mode;
}

/** Set the high pass filter cut off frequency level (1 - 10)
 * @param level The new level for the hpcf, using one of the defined levels
 * @see L3G4200D_RA_CTRL_REG2
 * @see L3G4200D_HPCF_BIT
 * @see L3G4200D_HPCF_LENGTH
 * @see L3G4200D_HPCF1
 * @see L3G4200D_HPCF2
 * @see L3G4200D_HPCF3
 * @see L3G4200D_HPCF4
 * @see L3G4200D_HPCF5
 * @see L3G4200D_HPCF6
 * @see L3G4200D_HPCF7
 * @see L3G4200D_HPCF8
 * @see L3G4200D_HPCF9
 * @see L3G4200D_HPCF10
 */
void L3G4200D_setHighPassFilterCutOffFrequencyLevel(SE_L3G4200D_HandleTypeDef *hGS, uint8_t level) 
{
	//I2Cdev::writeBits(devAddr, L3G4200D_RA_CTRL_REG2, L3G4200D_HPCF_BIT, L3G4200D_HPCF_LENGTH, level);
	if(hGS)
	{
		hGS->iCtrl_Reg2 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG2);
		hGS->iCtrl_Reg2 &= ~L3G4200D_HPCF_MASK;
		
		hGS->iCtrl_Reg2 |= level;
		
		I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG2 , hGS->iCtrl_Reg2 );	
	}	
}

/** Get the high pass filter cut off frequency level (1 - 10)
 * @return High pass filter cut off frequency level
 * @see L3G4200D_RA_CTRL_REG2
 * @see L3G4200D_HPCF_BIT
 * @see L3G4200D_HPCF_LENGTH
 * @see L3G4200D_HPCF1
 * @see L3G4200D_HPCF2
 * @see L3G4200D_HPCF3
 * @see L3G4200D_HPCF4
 * @see L3G4200D_HPCF5
 * @see L3G4200D_HPCF6
 * @see L3G4200D_HPCF7
 * @see L3G4200D_HPCF8
 * @see L3G4200D_HPCF9
 * @see L3G4200D_HPCF10
 */
uint8_t L3G4200D_getHighPassFilterCutOffFrequencyLevel(SE_L3G4200D_HandleTypeDef *hGS) 
{
	uint8_t	iHPCF=0;
	
	if(hGS)
	{
		iHPCF = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG2);
		iHPCF &= L3G4200D_HPCF_MASK;				
	}	

	return iHPCF;
}




// CTRL_REG3 register, r/w

/** Set the INT1 interrupt enabled state
 * @param enabled New enabled state for the INT1 interrupt
 * @see L3G4200D_RA_CTRL_REG3
 * @see L3G4200D_I1_INT1_BIT
 */
void L3G4200D_setINT1InterruptEnabled(SE_L3G4200D_HandleTypeDef *hGS, bool enabled) 
{
	
	if(hGS)
	{
		hGS->iCtrl_Reg3 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG3);
		
		if(enabled)
		{
			hGS->iCtrl_Reg3 |= L3G4200D_I1_INT1_EN;
		}
		else
		{
			hGS->iCtrl_Reg3 &= ~L3G4200D_I1_INT1_EN;
		}
		
		I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG3 , hGS->iCtrl_Reg3 );	
	}		
}

/** Get the INT1 interrupt enabled state
 * @return True if the INT1 interrupt is enabled, false otherwise
 * @see L3G4200D_RA_CTRL_REG3
 * @see L3G4200D_I1_INT1_BIT
 */

bool L3G4200D_getINT1InterruptEnabled(SE_L3G4200D_HandleTypeDef *hGS) 
{
	uint8_t	iResult=0;
	
	if(hGS)
	{
		hGS->iCtrl_Reg3 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG3);		
		iResult = hGS->iCtrl_Reg3 & L3G4200D_I1_INT1_EN;				
		
		if(iResult)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}	

	return FALSE;
}

/** Set the INT1 boot status enabled state
 * @param enabled New enabled state for the INT1 boot status
 * @see L3G4200D_RA_CTRL_REG3
 * @see L3G4200D_I1_BOOT_BIT
 */
void L3G4200D_setINT1BootStatusEnabled(SE_L3G4200D_HandleTypeDef *hGS, bool enabled) 
{
	
	if(hGS)
	{
		hGS->iCtrl_Reg3 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG3);
		
		if(enabled)
		{
			hGS->iCtrl_Reg3 |= L3G4200D_I1_BOOT_EN;
		}
		else
		{
			hGS->iCtrl_Reg3 &= ~L3G4200D_I1_BOOT_EN;
		}
		
		I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG3 , hGS->iCtrl_Reg3 );	
	}	
}

/** Get the INT1 boot status enabled state
 * @return INT1 boot status status
 * @see L3G4200D_RA_CTRL_REG3
 * @see L3G4200D_I1_BOOT_BIT
 */

bool L3G4200D_getINT1BootStatusEnabled(SE_L3G4200D_HandleTypeDef *hGS) 
{
	uint8_t	iResult=0;
	
	if(hGS)
	{
		hGS->iCtrl_Reg3 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG3);		
		iResult = hGS->iCtrl_Reg3 & L3G4200D_I1_BOOT_EN;				
		
		if(iResult)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}	

	return FALSE;
}
/** Interrupts the active INT1 configuration
 * @see L3G4200D_RA_CTRL_REG3
 * @see L3G4200D_H_LACTIVE_BIT
 */
void L3G4200D_interruptActiveINT1Config(SE_L3G4200D_HandleTypeDef *hGS,bool active_h) 
{
	//I2Cdev::writeBit(devAddr, L3G4200D_RA_CTRL_REG3, L3G4200D_H_LACTIVE_BIT, 1);
	if(hGS)
	{
		hGS->iCtrl_Reg3 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG3);
		
		if(active_h)
		{
			hGS->iCtrl_Reg3 &= ~L3G4200D_H_LACTIVE_EN;
		}
		else
		{
			hGS->iCtrl_Reg3 |= L3G4200D_H_LACTIVE_EN;
		}
		
		I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG3 , hGS->iCtrl_Reg3 );	
	}	
}

/** Set output mode to push-pull or open-drain
 * @param mode New output mode
 * @see L3G4200D_RA_CTRL_REG3
 * @see L3G4200D_PP_OD_BIT
 * @see L3G4200D_PUSH_PULL
 * @see L3G4200D_OPEN_DRAIN
 */
void L3G4200D_setOutputMode(SE_L3G4200D_HandleTypeDef *hGS,bool mode) 
{
	if(hGS)
	{
		hGS->iCtrl_Reg3 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG3);
		
		if(mode)
		{
			hGS->iCtrl_Reg3 |= L3G4200D_PP_OD_EN;
		}
		else
		{
			hGS->iCtrl_Reg3 &= ~L3G4200D_PP_OD_EN;
		}
		
		I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG3 , hGS->iCtrl_Reg3 );	
	}	
}

/** Get whether mode is push-pull or open drain
 * @return Output mode (TRUE for push-pull, FALSE for open-drain)
 * @see L3G4200D_RA_CTRL_REG3
 * @see L3G4200D_PP_OD_BIT
 * @see L3G4200D_PUSH_PULL
 * @see L3G4200D_OPEN_DRAIN
 */
bool L3G4200D_getOutputMode(SE_L3G4200D_HandleTypeDef *hGS) 
{
	uint8_t	iResult=0;
	
	if(hGS)
	{
		hGS->iCtrl_Reg3 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG3);		
		iResult = hGS->iCtrl_Reg3 & L3G4200D_PP_OD_EN;
		
		if(iResult)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}	

	return FALSE;
}

/** Set data ready interrupt enabled state on INT2 pin
 * @param enabled New INT2 data ready interrupt enabled state
 * @see L3G4200D_RA_CTRL_REG3
 * @see L3G4200D_I2_DRDY_BIT
 */
void L3G4200D_setINT2DataReadyEnabled(SE_L3G4200D_HandleTypeDef *hGS,bool enabled) 
{
	if(hGS)
	{
		hGS->iCtrl_Reg3 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG3);
		
		if(enabled)
		{
			hGS->iCtrl_Reg3 |= L3G4200D_I2_DRDY_EN;
		}
		else
		{
			hGS->iCtrl_Reg3 &= ~L3G4200D_I2_DRDY_EN;
		}
		
		I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG3 , hGS->iCtrl_Reg3 );	
	}	
}

/** Get whether the data ready interrupt is enabled on the INT2 pin
 * @return True if the INT2 data ready interrupt is enabled, false otherwise
 * @see L3G4200D_RA_CTRL_REG3
 * @see L3G4200D_I2_DRDY_BIT
 */
bool L3G4200D_getINT2DataReadyEnabled(SE_L3G4200D_HandleTypeDef *hGS) 
{
	uint8_t	iResult=0;
	
	if(hGS)
	{
		hGS->iCtrl_Reg3 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG3);		
		iResult = hGS->iCtrl_Reg3 & L3G4200D_I2_DRDY_EN;				
		
		if(iResult)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}	

	return FALSE;
}

/** Set whether the INT2 FIFO watermark interrupt is enabled
 * The sensor contains a 32-slot FIFO buffer for storing data so that it may be 
 * read later. If enabled, the sensor will generate an interrupt on the 
 * INT2/DRDY pin when the watermark has been reached. The watermark can be 
 * configured through the setFIFOWatermark function.
 * @param enabled New enabled state of the INT2 FIFO watermark
 * @see L3G4200D_RA_CTRL_REG3
 * @see L3G4200D_I2_WTM_BIT
 */
void L3G4200D_setINT2FIFOWatermarkInterruptEnabled(SE_L3G4200D_HandleTypeDef *hGS,bool enabled) 
{
	if(hGS)
	{
		hGS->iCtrl_Reg3 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG3);
		
		if(enabled)
		{
			hGS->iCtrl_Reg3 |= L3G4200D_I2_WTM_EN;
		}
		else
		{
			hGS->iCtrl_Reg3 &= ~L3G4200D_I2_WTM_EN;
		}
		
		I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG3 , hGS->iCtrl_Reg3 );	
	}	
}

/** Get the INT2 FIFO watermark interrupt enabled state
 * @return true if the FIFO watermark is enabled, false otherwise
 * @see L3G4200D_RA_CTRL_REG3
 * @see L3G4200D_I2_WTM_BIT
 */ 
bool L3G4200D_getINT2FIFOWatermarkInterruptEnabled(SE_L3G4200D_HandleTypeDef *hGS) 
{
	uint8_t	iResult=0;
	
	if(hGS)
	{
		hGS->iCtrl_Reg3 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG3);		
		iResult = hGS->iCtrl_Reg3 & L3G4200D_I2_WTM_EN;				
		
		if(iResult)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}	

	return FALSE;
}


/** Set whether an interrupt is triggered on INT2 when the FIFO is overrun
 * @param enabled New FIFO overrun interrupt enabled state
 * @see L3G4200D_RA_CTRL_REG3
 * @see L3G4200D_I2_ORUN_BIT
 */
void L3G4200D_setINT2FIFOOverrunInterruptEnabled(SE_L3G4200D_HandleTypeDef *hGS,bool enabled) 
{
	if(hGS)
	{
		hGS->iCtrl_Reg3 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG3);
		
		if(enabled)
		{
			hGS->iCtrl_Reg3 |= L3G4200D_I2_ORUN_EN;
		}
		else
		{
			hGS->iCtrl_Reg3 &= ~L3G4200D_I2_ORUN_EN;
		}
		
		I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG3 , hGS->iCtrl_Reg3 );	
	}	
}

/** Get whether an interrupt is triggered on INT2 when the FIFO is overrun
 * @return True if the INT2 FIFO overrun interrupt is enabled, false otherwise
 * @see L3G4200D_RA_CTRL_REG3
 * @see L3G4200D_I2_ORUN_BIT
 */
bool L3G4200D_getINT2FIFOOverrunInterruptEnabled(SE_L3G4200D_HandleTypeDef *hGS) 
{
	uint8_t	iResult=0;
	
	if(hGS)
	{
		hGS->iCtrl_Reg3 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG3);		
		iResult = hGS->iCtrl_Reg3 & L3G4200D_I2_ORUN_EN;				
		
		if(iResult)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}	

	return FALSE;
}

/** Set whether an interrupt is triggered on INT2 when the FIFO buffer is empty
 * @param enabled New INT2 FIFO empty interrupt state
 * @see L3G4200D_RA_CTRL_REG3
 * @see L3G4200D_I2_EMPTY_BIT
 */
void L3G4200D_setINT2FIFOEmptyInterruptEnabled(SE_L3G4200D_HandleTypeDef *hGS,bool enabled) 
{
	if(hGS)
	{
		hGS->iCtrl_Reg3 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG3);
		
		if(enabled)
		{
			hGS->iCtrl_Reg3 |= L3G4200D_I2_EMPTY_EN;
		}
		else
		{
			hGS->iCtrl_Reg3 &= ~L3G4200D_I2_EMPTY_EN;
		}
		
		I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG3 , hGS->iCtrl_Reg3 );	
	}	
}

/** Get whether the INT2 FIFO empty interrupt is enabled
 * @returns Trur if the INT2 FIFO empty interrupt is enabled, false otherwise
 * @see L3G4200D_RA_CTRL_REG3
 * @see L3G4200D_I2_EMPTY_BIT
 */
bool L3G4200D_getINT2FIFOEmptyInterruptEnabled(SE_L3G4200D_HandleTypeDef *hGS) 
{
	uint8_t	iResult=0;
	
	if(hGS)
	{
		iResult = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG3);		
		iResult &= L3G4200D_I2_EMPTY_EN;				
		
		if(iResult)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}	

	return FALSE;
}



// CTRL_REG4 register, r/w

/** Set the Block Data Update (BDU) enabled state
 * @param enabled New BDU enabled state
 * @see L3G4200D_RA_CTRL_REG4
 * @see L3G4200D_BDU_BIT
 */
void L3G4200D_setBlockDataUpdateEnabled(SE_L3G4200D_HandleTypeDef *hGS, bool enabled) {
	//I2Cdev::writeBit(devAddr, L3G4200D_RA_CTRL_REG4, L3G4200D_BDU_BIT, enabled);
	if(hGS)
	{
		hGS->iCtrl_Reg4 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG4);
		
		if(enabled)
		{
			hGS->iCtrl_Reg4 |= L3G4200D_BDU_EN;
		}
		else
		{
			hGS->iCtrl_Reg4 &= ~L3G4200D_BDU_EN;
		}
		
		I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG4 , hGS->iCtrl_Reg4 );	
	}		
}

/** Get the BDU enabled state
 * @return True if Block Data Update is enabled, false otherwise
 * @see L3G4200D_RA_CTRL_REG4
 * @see L3G4200D_BDU_BIT
 */
bool L3G4200D_getBlockDataUpdateEnabled(SE_L3G4200D_HandleTypeDef *hGS) 
{
	uint8_t	iResult=0;
	
	if(hGS)
	{
		hGS->iCtrl_Reg4 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG4);		
		iResult = hGS->iCtrl_Reg4 & L3G4200D_BDU_EN;				
		
		if(iResult)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}	

	return FALSE;
}

/** Set the data endian modes
 * In Big Endian mode, the Most Significat Byte (MSB) is on the lower address, 
 * and the Least Significant Byte (LSB) is on the higher address. Little Endian 
 * mode reverses this order. Little Endian is the default mode.
 * @param endianness New endian mode
 * @see L3G4200D_RA_CTRL_REG4
 * @see L3G4200D_BLE_BIT
 * @see L3G4200D_BIG_ENDIAN
 * @see L3G4200D_LITTLE_ENDIAN
 */
void L3G4200D_setEndianMode(SE_L3G4200D_HandleTypeDef *hGS, bool endianness) {
	
	if(hGS)
	{
		hGS->iCtrl_Reg4 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG4);
		
		if(endianness)
		{
			// 1 big endian
			hGS->iCtrl_Reg4 |= L3G4200D_BLE_EN;
		}
		else
		{ // 0 little endian
			hGS->iCtrl_Reg4 &= ~L3G4200D_BLE_EN;
		}
		
		I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG4 , hGS->iCtrl_Reg4 );	
	}			
}

/** Get the data endian mode
 * @return Current endian mode
 * @see L3G4200D_RA_CTRL_REG4
 * @see L3G4200D_BLE_BIT
 * @see L3G4200D_BIG_ENDIAN
 * @see L3G4200D_LITTLE_ENDIAN
 */
uint8_t L3G4200D_getEndianMode(SE_L3G4200D_HandleTypeDef *hGS) {
	uint8_t	iResult=0;
	
	if(hGS)
	{
		hGS->iCtrl_Reg4 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG4);		
		iResult	= hGS->iCtrl_Reg4 & L3G4200D_BLE_EN;				
		
		
	}			
	return iResult;
}

/** Set the full scale of the data output (in dps)
 * @param scale The new scale of the data output (250, 500, 2000)
 * @see L3G4200D_RA_CTRL_REG4
 * @see L3G4200D_FS_BIT
 * @see L3G4200D_FS_LENGTH
 * @see L3G4200D_FS_250
 * @see L3G4200D_FS_500
 * @see L3G4200D_FS_2000
 */
void L3G4200D_setFullScale(SE_L3G4200D_HandleTypeDef *hGS,uint16_t scale) {
	
	if(hGS)
	{
		hGS->iCtrl_Reg4 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG4);

		hGS->iCtrl_Reg4 &= ~L3G4200D_FS_MASK;
		
		if (scale == 250) 
		{
			hGS->iCtrl_Reg4 |= L3G4200D_FS_250;
		} 
		else if (scale == 500) 
		{
			hGS->iCtrl_Reg4 |= L3G4200D_FS_500;
		} 
		else 
		{
			hGS->iCtrl_Reg4 |= L3G4200D_FS_2000;
		}
			
		I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG4 , hGS->iCtrl_Reg4 );	
	}			
}

/** Get the current full scale of the output data (in dps)
 * @return Current scale of the output data
 * @see L3G4200D_RA_CTRL_REG4
 * @see L3G4200D_FS_BIT
 * @see L3G4200D_FS_LENGTH
 * @see L3G4200D_FS_250
 * @see L3G4200D_FS_500
 * @see L3G4200D_FS_2000
 */
uint16_t L3G4200D_getFullScale(SE_L3G4200D_HandleTypeDef *hGS) {
	uint8_t readBits = 0;	

	if(hGS)
	{
		hGS->iCtrl_Reg4 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG4);		
		readBits = hGS->iCtrl_Reg4 & L3G4200D_FS_MASK;				
		
		if (readBits == L3G4200D_FS_250) 
		{
			return 250;
		} 
		else if (readBits == L3G4200D_FS_500) 
		{
			return 500;
		} 
		else 
		{
			return 2000;
		}
	}	

	return 0;	
}

/** Set the self test mode
 * @param mode New self test mode (Normal, 0, 1)
 * @see L3G4200D_RA_CTRL_REG4
 * @see L3G4200D_ST_BIT
 * @see L3G4200D_ST_LENGTH
 * @see L3G4200D_SELF_TEST_NORMAL
 * @see L3G4200D_SELF_TEST_0
 * @see L3G4200D_SELF_TEST_1
 */
void L3G4200D_setSelfTestMode(SE_L3G4200D_HandleTypeDef *hGS,uint8_t mode) {
	
	if(hGS)
	{
		hGS->iCtrl_Reg4 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG4);
		hGS->iCtrl_Reg4 &= ~L3G4200D_SELF_TEST_MASK;		
		mode 						&= ~L3G4200D_SELF_TEST_MASK;		
		hGS->iCtrl_Reg4 |= mode;	
			
		I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG4 , hGS->iCtrl_Reg4 );	
	}			
}

/** Get the current self test mode
 * @return Current self test mode
 * @see L3G4200D_RA_CTRL_REG4
 * @see L3G4200D_ST_BIT
 * @see L3G4200D_ST_LENGTH
 * @see L3G4200D_SELF_TEST_NORMAL
 * @see L3G4200D_SELF_TEST_0
 * @see L3G4200D_SELF_TEST_1
 */
uint8_t L3G4200D_getSelfTestMode(SE_L3G4200D_HandleTypeDef *hGS) {

	uint8_t readBits = 0;	

	if(hGS)
	{
		hGS->iCtrl_Reg4 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG4);		
		readBits = hGS->iCtrl_Reg4 & L3G4200D_SELF_TEST_MASK;				
	}	
	return readBits;		
}

/** Set the SPI mode
 * @param mode New SPI mode
 * @see L3G4200D_RA_CTRL_REG4
 * @see L3G4200D_SIM_BIT
 * @see L3G4200D_SPI_4_WIRE
 * @see L3G4200D_SPI_3_WIRE
 */
void L3G4200D_setSPIMode(SE_L3G4200D_HandleTypeDef *hGS, bool mode)
{
	if(hGS)
	{
		hGS->iCtrl_Reg4 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG4);
		
		if(mode)
		{
			// 1 big endian
			hGS->iCtrl_Reg4 |= L3G4200D_SPI_4_WIRE;
		}
		else
		{ // 0 little endian
			hGS->iCtrl_Reg4 |= L3G4200D_SPI_3_WIRE;
		}
		
		I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG4 , hGS->iCtrl_Reg4 );	
	}	
}

/** Get the SPI mode
 * @return Current SPI mode
 * @see L3G4200D_RA_CTRL_REG4
 * @see L3G4200D_SIM_BIT
 * @see L3G4200D_SPI_4_WIRE
 * @see L3G4200D_SPI_3_WIRE
 */
bool L3G4200D_getSPIMode(SE_L3G4200D_HandleTypeDef *hGS) {
	uint8_t	iResult=0;
	
	if(hGS)
	{
		hGS->iCtrl_Reg4 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG4);		
		iResult	= hGS->iCtrl_Reg4 & L3G4200D_SPI_3_WIRE;				
		
		if(iResult==L3G4200D_SPI_3_WIRE)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}	

	return FALSE;
}


// CTRL_REG5 register, r/w

/** Reboots the FIFO memory content
 * @see L3G4200D_RA_CTRL_REG5
 * @see L3G4200D_BOOT_BIT
 */
void L3G4200D_rebootMemoryContent(SE_L3G4200D_HandleTypeDef *hGS) 
{
	if(hGS)
	{
		hGS->iCtrl_Reg5 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG5);
		
		hGS->iCtrl_Reg5 |= L3G4200D_BOOT_EN;
		I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG5 , hGS->iCtrl_Reg5 );			
	}
}

/** Set whether the FIFO buffer is enabled
 * @param enabled New enabled state of the FIFO buffer
 * @see L3G4200D_RA_CTRL_REG5
 * @see L3G4200D_FIFO_EN_BIT
 */
void L3G4200D_setFIFOEnabled(SE_L3G4200D_HandleTypeDef *hGS, bool enabled) {
	
	if(hGS)
	{
		hGS->iCtrl_Reg5 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG5);
		
		hGS->iCtrl_Reg5 &= ~L3G4200D_FIFO_EN;
		
		if(enabled)
		{
			hGS->iCtrl_Reg5 |= L3G4200D_FIFO_EN;
		}
		
		I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG5 , hGS->iCtrl_Reg5 );			
	}
}

/** Get whether the FIFO buffer is enabled
 * @return True if the FIFO buffer is enabled, false otherwise
 * @see L3G4200D_RA_CTRL_REG5
 * @see L3G4200D_FIFO_EN_BIT
 */
bool L3G4200D_getFIFOEnabled(SE_L3G4200D_HandleTypeDef *hGS) {
	uint8_t	iResult=0;
	
	if(hGS)
	{
		hGS->iCtrl_Reg5 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG5);
		iResult	= hGS->iCtrl_Reg5 & L3G4200D_FIFO_EN;				
		
		if(iResult==L3G4200D_FIFO_EN)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}	

	return FALSE;
}

/** Set the high pass filter enabled state
 * @param enabled New high pass filter enabled state
 * @see L3G4200D_RA_CTRL_REG5
 * @see L3G4200D_HPEN_BIT
 */
void L3G4200D_setHighPassFilterEnabled(SE_L3G4200D_HandleTypeDef *hGS, bool enabled) {
	if(hGS)
	{
		hGS->iCtrl_Reg5 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG5);
		
		hGS->iCtrl_Reg5 &= ~L3G4200D_HP_EN;
		
		if(enabled)
		{
			hGS->iCtrl_Reg5 |= L3G4200D_HP_EN;
		}
		
		I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG5 , hGS->iCtrl_Reg5 );			
	}
}

/** Get whether the high pass filter is enabled
 * @return True if the high pass filter is enabled, false otherwise
 * @see L3G4200D_RA_CTRL_REG5
 * @see L3G4200D_HPEN_BIT
 */
bool L3G4200D_getHighPassFilterEnabled(SE_L3G4200D_HandleTypeDef *hGS) {
	uint8_t	iResult=0;
	
	if(hGS)
	{
		hGS->iCtrl_Reg5 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG5);
		iResult	= hGS->iCtrl_Reg5 & L3G4200D_HP_EN;				
		
		if(iResult==L3G4200D_HP_EN)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}	

	return FALSE;
}

/** Sets the filter mode to one of the four provided.
 * This function also uses the setHighPassFilterEnabled function in order to set
 * the mode. That function does not haved to be called in addition to this one. 
 * In addition to setting the filter for the data in the FIFO buffer 
 * (controlled by the bits written to OUT_SEL), this function also sets the
 * filter used for interrupt generation (the bits written to INT1_SEL) to be the
 * same as the filter used for the FIFO buffer.
 * @param filter New method to be used when filtering data
 * @see L3G4200D_RA_CTRL_REG5
 * @see L3G4200D_INT1_SEL_BIT
 * @see L3G4200D_INT1_SEL_LENGTH
 * @see L3G4200D_OUT_SEL_BIT
 * @see L3G4200D_OUT_SEL_LENGTH
 * @see L3G4200D_NON_HIGH_PASS
 * @see L3G4200D_HIGH_PASS
 * @see L3G4200D_LOW_PASS
 * @see L3G4200D_LOW_HIGH_PASS
 */
void L3G4200D_setDataFilter(SE_L3G4200D_HandleTypeDef *hGS, uint8_t filter) {
	
	uint8_t iTemp1=0,iTemp2=0;
	
	if(hGS)
	{
		hGS->iCtrl_Reg5 = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG5);
		
		hGS->iCtrl_Reg5 &= ~(L3G4200D_HP_EN | L3G4200D_INT1_SEL_MASK | L3G4200D_OUT_SEL_MASK);
		
		iTemp1 = filter & L3G4200D_INT1_SEL_MASK ;
		iTemp2 = filter & L3G4200D_OUT_SEL_MASK ; 
		if(iTemp1 == L3G4200D_INT1_SEL_HP || iTemp1 == L3G4200D_INT1_SEL_BP || iTemp2 == L3G4200D_OUT_SEL_HP || iTemp2 == L3G4200D_OUT_SEL_LP )
		{
				hGS->iCtrl_Reg5 |= L3G4200D_HP_EN ;
		}
	
		hGS->iCtrl_Reg5 |= iTemp1;
		hGS->iCtrl_Reg5 |= iTemp2;
		
		I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_CTRL_REG5 , hGS->iCtrl_Reg5 );
	}
}


// REFERENCE/DATACAPTURE register, r/w

/** Set the reference value for interrupt generation
 * @param reference New reference value for interrupt generation
 * @see L3G4200D_RA_REFERENCE
 */
void L3G4200D_setInterruptReference(SE_L3G4200D_HandleTypeDef *hGS, uint8_t reference) {
	
	if(hGS)
	{	
		hGS->iReference = reference;
		I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_REFERENCE , hGS->iReference );
	}	
}

/** Get the 8-bit reference value for interrupt generation
 * @return 8-bit reference value for interrupt generation
 * @see L3G4200D_RA_REFERENCE
 */
uint8_t L3G4200D_getInterruptReference(SE_L3G4200D_HandleTypeDef *hGS) {
	if(hGS)
	{
		hGS->iReference = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_REFERENCE);
	}

	return hGS->iReference;
}

// OUT_TEMP register, read-only

/** Gets the current temperature reading from the sensor
 * @return Current temperature
 * @see L3G4200D_RA_OUT_TEMP
 */
uint8_t L3G4200D_getTemperature(SE_L3G4200D_HandleTypeDef *hGS) {
	
	if(hGS)
	{
		hGS->iTemperature = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_OUT_TEMP);
	}

	return hGS->iTemperature;
}


/** Gets the current status reading from the sensor
 * @return TRUE   hGS->iStatus is updated;
 *         FALSE  hGS->iStatus read failed;
 * @see L3G4200D_RA_STATUS
 */
bool			L3G4200D_getStatus(SE_L3G4200D_HandleTypeDef *hGS)
{
	 if(hGS)
	 {
		 hGS->iStatus_Reg = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_STATUS);
		 return TRUE;
	 }
	 else
	 {
		 return FALSE;
	 }
}



// OUT_* registers, read-only

/** Get the angular velocity for all 3 axes
 * Due to the fact that this device supports two difference Endian modes, both 
 * must be accounted for when reading data. In Little Endian mode, the first 
 * byte (lowest address) is the least significant and in Big Endian mode the 
 * first byte is the most significant.
 * @param x 16-bit integer container for the X-axis angular velocity
 * @param y 16-bit integer container for the Y-axis angular velocity
 * @param z 16-bit integer container for the Z-axis angular velocity
 */
void L3G4200D_getAngularVelocity(SE_L3G4200D_HandleTypeDef *hGS) {
	L3G4200D_getAngularVelocityX(hGS);
	L3G4200D_getAngularVelocityY(hGS);
	L3G4200D_getAngularVelocityZ(hGS);
}

/** Get the angular velocity about the X-axis
 * @return Angular velocity about the X-axis
 * @see L3G4200D_RA_OUT_X_L
 * @see L3G4200D_RA_OUT_X_H
 */
int16_t L3G4200D_getAngularVelocityX(SE_L3G4200D_HandleTypeDef *hGS)
{
		uint8_t iBufL;
		uint8_t iBufH;

		if(hGS)
		{
		 iBufL  = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_OUT_X_L);
		 iBufH  = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_OUT_X_H);
		 
		 if (L3G4200D_getEndianMode(hGS) == L3G4200D_BLE_BIG) 
		 {
			hGS->iAV_X = (((int16_t) iBufL) << 8) | iBufH;
		 } 
		 else 
		 {
			hGS->iAV_X = (((int16_t) iBufH) << 8) | iBufL;
		 }
		 return hGS->iAV_X;
	 }
	 else
	 {
		 return 0;
	 }
}
	
/** Get the angular velocity about the Y-axis
 * @return Angular velocity about the Y-axis
 * @see L3G4200D_RA_OUT_Y_L
 * @see L3G4200D_RA_OUT_Y_H
 */
int16_t L3G4200D_getAngularVelocityY(SE_L3G4200D_HandleTypeDef *hGS) {
		uint8_t iBufL;
		uint8_t iBufH;

		if(hGS)
		{
		 iBufL  = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_OUT_Y_L);
		 iBufH  = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_OUT_Y_H);
		 
		 if (L3G4200D_getEndianMode(hGS) == L3G4200D_BLE_BIG) 
		 {
			hGS->iAV_Y = (((int16_t) iBufL) << 8) | iBufH;
		 } 
		 else 
		 {
			hGS->iAV_Y = (((int16_t) iBufH) << 8) | iBufL;
		 }
		 return hGS->iAV_Y;
	 }
	 else
	 {
		 return 0;
	 }
}

/** Get the angular velocity about the Z-axis
 * @return Angular velocity about the Z-axis
 * @see L3G4200D_RA_OUT_Z_L
 * @see L3G4200D_RA_OUT_Z_H
 */
int16_t L3G4200D_getAngularVelocityZ(SE_L3G4200D_HandleTypeDef *hGS) {
		uint8_t iBufL;
		uint8_t iBufH;

		if(hGS)
		{
		 iBufL  = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_OUT_Z_L);
		 iBufH  = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_OUT_Z_H);
		 
		 if (L3G4200D_getEndianMode(hGS) == L3G4200D_BLE_BIG) 
		 {
			hGS->iAV_Z = (((int16_t) iBufL) << 8) | iBufH;
		 } 
		 else 
		 {
			hGS->iAV_Z = (((int16_t) iBufH) << 8) | iBufL;
		 }
		 return hGS->iAV_Z;
	 }
	 else
	 {
		 return 0;
	 }
}




// FIFO_CTRL register, r/w

/** Set the FIFO mode to one of the defined modes
 * @param mode New FIFO mode
 * @see L3G4200D_RA_FIFO_CTRL
 * @see L3G4200D_FIFO_MODE_BIT
 * @see L3G4200D_FIFO_MODE_LENGTH
 * @see L3G4200D_FM_BYPASS
 * @see L3G4200D_FM_FIFO
 * @see L3G4200D_FM_STREAM
 * @see L3G4200D_FM_STREAM_FIFO
 * @see L3G4200D_FM_BYPASS_STREAM
 */
void L3G4200D_setFIFOMode(SE_L3G4200D_HandleTypeDef *hGS,uint8_t mode) {

	if(hGS)
	{
		hGS->iFIFO_Ctrl_Reg = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_FIFO_CTRL);
		
		hGS->iFIFO_Ctrl_Reg &= ~L3G4200D_FM_MASK;
		mode &= L3G4200D_FM_MASK;		
    hGS->iFIFO_Ctrl_Reg |= mode;
		
		I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_FIFO_CTRL , hGS->iFIFO_Ctrl_Reg );
	}
}

/** Get the FIFO mode to one of the defined modes
 * @return Current FIFO mode
 * @see L3G4200D_RA_FIFO_CTRL
 * @see L3G4200D_FIFO_MODE_BIT
 * @see L3G4200D_FIFO_MODE_LENGTH
 * @see L3G4200D_FM_BYPASS
 * @see L3G4200D_FM_FIFO
 * @see L3G4200D_FM_STREAM
 * @see L3G4200D_FM_STREAM_FIFO
 * @see L3G4200D_FM_BYPASS_STREAM
 */
uint8_t L3G4200D_getFIFOMode(SE_L3G4200D_HandleTypeDef *hGS)
{
	
	uint8_t iResult=0;
	
	if(hGS)
	{
		hGS->iFIFO_Ctrl_Reg = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_FIFO_CTRL);
		
		iResult = hGS->iFIFO_Ctrl_Reg & L3G4200D_FM_MASK;
	}
	return iResult;
}

/** Set the FIFO watermark threshold
 * @param wtm New FIFO watermark threshold
 * @see L3G4200D_RA_FIFO_CTRL
 * @see L3G4200D_FIFO_WTM_BIT
 * @see L3G4200D_FIFO_WTM_LENGTH
 */
void L3G4200D_setFIFOThreshold(SE_L3G4200D_HandleTypeDef *hGS,uint8_t wtm) {
	if(hGS)
	{
		hGS->iFIFO_Ctrl_Reg = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_FIFO_CTRL);
		
		hGS->iFIFO_Ctrl_Reg &= ~L3G4200D_FM_MASK;
		wtm &= L3G4200D_WTM_MASK;		
    hGS->iFIFO_Ctrl_Reg |= wtm;
		
		I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_FIFO_CTRL , hGS->iFIFO_Ctrl_Reg );
	}
}

/** Get the FIFO watermark threshold
 * @return FIFO watermark threshold
 * @see L3G4200D_RA_FIFO_CTRL
 * @see L3G4200D_FIFO_WTM_BIT
 * @see L3G4200D_FIFO_WTM_LENGTH
 */
uint8_t L3G4200D_getFIFOThreshold(SE_L3G4200D_HandleTypeDef *hGS) {
	uint8_t iResult=0;
	
	if(hGS)
	{
		hGS->iFIFO_Ctrl_Reg = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_FIFO_CTRL);
		
		iResult = hGS->iFIFO_Ctrl_Reg & L3G4200D_WTM_MASK;
	}
	return iResult;
}


// FIFO_SRC register, read-only

/** Get whether the number of data sets in the FIFO buffer is less than the 
 * watermark
 * @return True if the number of data sets in the FIFO buffer is more than or 
 * equal to the watermark, false otherwise.
 * @see L3G4200D_RA_FIFO_SRC
 * @see L3G4200D_FIFO_STATUS_BIT
 */
bool 			L3G4200D_isFIFOAtWatermark(SE_L3G4200D_HandleTypeDef *hGS)
{
		uint8_t	iResult=0;
	
		if(hGS)
		{
				iResult = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_FIFO_SRC);
			
				if(iResult&L3G4200D_FIFO_STA_WTM)
				{
					return TRUE;
				}
				else
				{
					return FALSE;
				}
		}
   	
		return FALSE;
}

/** Get whether the FIFO buffer is full
 * @return True if the FIFO buffer is full, false otherwise
 * @see L3G4200D_RA_FIFO_SRC
 * @see L3G4200D_FIFO_OVRN_BIT
 */
bool L3G4200D_isFIFOOverrun(SE_L3G4200D_HandleTypeDef *hGS)
{
		uint8_t	iResult=0;
	
		if(hGS)
		{
				iResult = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_FIFO_SRC);
			
				if(iResult&L3G4200D_FIFO_STA_OVR)
				{
					return TRUE;
				}
				else
				{
					return FALSE;
				}
		}
   	
		return FALSE;
}

/** Get whether the FIFO buffer is empty
 * @return True if the FIFO buffer is empty, false otherwise
 * @see L3G4200D_RA_FIFO_SRC
 * @see L3G4200D_FIFO_EMPTY_BIT
 */
bool L3G4200D_isFIFOEmpty(SE_L3G4200D_HandleTypeDef *hGS)
{
		uint8_t	iResult=0;
	
		if(hGS)
		{
				iResult = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_FIFO_SRC);
			
				if(iResult&L3G4200D_FIFO_STA_EMPTY)
				{
					return TRUE;
				}
				else
				{
					return FALSE;
				}
		}
   	
		return FALSE;
}

/** Get the number of filled FIFO buffer slots
 * @return Number of filled slots in the FIFO buffer
 * @see L3G4200D_RA_FIFO_SRC
 * @see L3G4200D_FIFO_FSS_BIT
 * @see L3G4200D_FIFO_FSS_LENGTH
 */ 
uint8_t L3G4200D_getFIFOStoredDataLevel(SE_L3G4200D_HandleTypeDef *hGS)
{
		uint8_t	iResult=0;
	
		if(hGS)
		{
				iResult = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_FIFO_SRC);
			
				iResult &= L3G4200D_FIFO_DEPTH_MASK;
							
		}
   	
		return iResult;
}

/** Set the interrupt events
 * @param combination New combination mode for interrupt events. 
 * L3G4200D_INT1_OR for OR and L3G4200D_INT1_AND for AND
 * @see L3G4200D_RA_INT1_CFG
 * @see L3G4200D_INT1_AND_OR_BIT
 * @see L3G4200D_INT1_OR
 * @see L3G4200D_INT1_AND
 */
bool			L3G4200D_SetInterruptCFG(SE_L3G4200D_HandleTypeDef *hGS, uint8_t iIntCfg)
{
	
		if(hGS)
		{
			hGS->iINT1_Cfg_Reg	=	iIntCfg;
			I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_INT1_CFG, hGS->iINT1_Cfg_Reg );
			
			return TRUE;
		}
		else
		{
			return FALSE;
		}
}


// INT1_SRC register, read-only

/** Get whether an interrupt has been generated
 * @return True if one or more interrupts has been generated, false otherwise
 * @see L3G4200D_RA_INT1_SRC
 */

uint8_t		L3G4200D_getIntStatus(SE_L3G4200D_HandleTypeDef *hGS)
{
		uint8_t	iResult=0;
		if(hGS)
		{
			iResult = I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_FIFO_SRC);			
		}
		
		return iResult;
}		


// INT1_THS_* registers, r/w

/** Set the threshold for a high interrupt on the X Y Z axis
 * @param threshold New threshold for a high interrupt on the X Y Z axis
@  @param hGS->iTH_X  hGS->iTH_Y  hGS->iTH_Z
 * @see L3G4200D_INT1_THS_XH XL YH YL 
 */

bool			L3G4200D_setXYZThreshold(SE_L3G4200D_HandleTypeDef *hGS)
{
		uint8_t	iTH_H=0;
		uint8_t	iTH_L=0;
	
		if(hGS)
		{
				hGS->iTH_X	&=	0x7F;
				hGS->iTH_Y	&=	0x7F;
				hGS->iTH_Z	&=	0x7F;
				
				iTH_H = (hGS->iTH_X>>8) & 0x00FF;
				iTH_L = hGS->iTH_X & 0x00FF;			
				I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_INT1_THS_XH, iTH_H);
				I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_INT1_THS_XL, iTH_L);

				iTH_H = (hGS->iTH_Y>>8) & 0x00FF;
				iTH_L = hGS->iTH_Y & 0x00FF;
				I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_INT1_THS_YH, iTH_H);
				I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_INT1_THS_YL, iTH_L);

				iTH_H = (hGS->iTH_Z>>8) & 0x00FF;
				iTH_L = hGS->iTH_Z & 0x00FF;			
				I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_INT1_THS_ZH, iTH_H);
				I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_INT1_THS_ZL, iTH_L);

				return TRUE;
		}
		else
		{
				return FALSE;
		}
}


bool			L3G4200D_getXYZThreshold(SE_L3G4200D_HandleTypeDef *hGS)
{
		uint8_t	iTH_H=0;
		uint8_t	iTH_L=0;
	
		if(hGS)
		{
				
				iTH_H	=	I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_INT1_THS_XH);	
				iTH_L	=	I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_INT1_THS_XL);	
				hGS->iTH_X = (((int16_t) iTH_H) << 8) | iTH_L;
			
				iTH_H	=	I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_INT1_THS_YH);	
				iTH_L	=	I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_INT1_THS_YL);	
				hGS->iTH_Y = (((int16_t) iTH_H) << 8) | iTH_L;

				iTH_H	=	I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_INT1_THS_ZH);	
				iTH_L	=	I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_INT1_THS_ZL);	
				hGS->iTH_Z = (((int16_t) iTH_H) << 8) | iTH_L;			
				return TRUE;
			
		}
		else
		{
				return FALSE;
		}		
}

// INT1_DURATION register, r/w

/* Set the minimum duration for an interrupt event to be recognized
 * This depends on the chosen output data rate
 * @param duration New duration necessary for an interrupt event to be 
 * recognized
 * @see L3G4200D_RA_INT1_DURATION
 * @see L3G4200D_INT1_DUR_BIT
 * @see L3G4200D_INT1_DUR_LENGTH
 */
void L3G4200D_setDuration(SE_L3G4200D_HandleTypeDef *hGS, uint8_t iDuration) {
	
	if(hGS)
	{
		hGS->iINT1_Dra_Reg	=	I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_INT1_DURATION);

		hGS->iINT1_Dra_Reg  &= ~L3G4200D_INT1_DUR_MASK;
		iDuration 					&= L3G4200D_INT1_DUR_MASK;
		
		hGS->iINT1_Dra_Reg	|= iDuration	;			
		
		I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_INT1_DURATION, hGS->iINT1_Dra_Reg);
	}

}

/** Get the minimum duration for an interrupt event to be recognized
 * @return Duration necessary for an interrupt event to be recognized
 * @see L3G4200D_RA_INT1_DURATION
 * @see L3G4200D_INT1_DUR_BIT
 * @see L3G4200D_INT1_DUR_LENGTH
 */
uint8_t L3G4200D_getDuration(SE_L3G4200D_HandleTypeDef *hGS)
{
		if(hGS)
		{				
				hGS->iINT1_Dra_Reg	=	I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_INT1_DURATION);	

				return hGS->iINT1_Dra_Reg & L3G4200D_INT1_DUR_MASK;
			
		}
		else
		{
				return 0;
		}		
}

/** Set whether the interrupt wait feature is enabled
 * If false, the interrupt falls immediately if signal crosses the selected 
 * threshold. Otherwise, if signal crosses the selected threshold, the interrupt
 * falls only after the duration has counted number of samples at the selected 
 * data rate, written into the duration counter register.
 * @param enabled New enabled state of the interrupt wait
 * @see L3G4200D_RA_INT1_DURATION
 * @see L3G4200D_INT1_WAIT_BIT
 */
void L3G4200D_setWaitEnabled(SE_L3G4200D_HandleTypeDef *hGS, bool enabled) 
{
	
	if(hGS)
	{
		hGS->iINT1_Dra_Reg	=	I2C_Read_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_INT1_DURATION);

		hGS->iINT1_Dra_Reg  &= ~L3G4200D_INT1_WAIT_BIT;
		
		if(enabled)
		{
			hGS->iINT1_Dra_Reg	|= L3G4200D_INT1_WAIT_BIT	;
		}
		
		I2C_Write_One_Byte(hGS->iDeviceAddr_Main, L3G4200D_RA_INT1_DURATION, hGS->iINT1_Dra_Reg);
		
	}
	
}


		
