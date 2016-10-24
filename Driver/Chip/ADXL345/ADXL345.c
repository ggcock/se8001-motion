#include "ADXL345.h"
#include "i2c.h"
 
void 	ADXL345_initialize(SE_ADXL345_HandleTypeDef *hAS)
{
	
}
	
// WHO_AM_I register, read-only
uint8_t 	ADXL345_getDeviceID(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{
		return I2C_Read_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_DEVID);
	}
	else
	{
		return 0;
	}	
}

/** Verify the I2C connection.
 * Make sure the device is connected and responds as expected.
 * @return True if connection is valid, false otherwise
 */
bool ADXL345_testConnection(SE_ADXL345_HandleTypeDef *hAS)
{
	if(ADXL345_getDeviceID(hAS)==0xE5)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

// THRESH_TAP register
bool	 		ADXL345_getTapThreshold(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{
		hAS->iTap_Threshold = I2C_Read_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_THRESH_TAP);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
        
bool 			ADXL345_setTapThreshold(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{		
		I2C_Write_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_THRESH_TAP , hAS->iTap_Threshold );		
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}



// OFS* registers

/** Get axis offsets.
 * The OFSX, OFSY, and OFSZ registers are each eight bits and offer user-set
 * offset adjustments in twos complement format with a scale factor of 15.6
 * mg/LSB (that is, 0x7F = 2 g). The value stored in the offset registers is
 * automatically added to the acceleration data, and the resulting value is
 * stored in the output data registers. For additional information regarding
 * offset calibration and the use of the offset registers, refer to the Offset
 * Calibration section of the datasheet.
 * @param x X axis offset container
 * @param y Y axis offset container
 * @param z Z axis offset container
 * @see ADXL345_RA_OFSX
 * @see ADXL345_RA_OFSY
 * @see ADXL345_RA_OFSZ
 */

bool			ADXL345_getOffset(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{
		hAS->iOffset_X = I2C_Read_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_OFSX);
		hAS->iOffset_Y = I2C_Read_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_OFSY);
		hAS->iOffset_Z = I2C_Read_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_OFSZ);		
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/** Set axis offsets.
 * @param x X axis offset value
 * @param y Y axis offset value
 * @param z Z axis offset value
 * @see getOffset()
 * @see ADXL345_RA_OFSX
 * @see ADXL345_RA_OFSY
 * @see ADXL345_RA_OFSZ
 */
bool			ADXL345_setOffset(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{
		I2C_Write_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_OFSX, hAS->iOffset_X );
		I2C_Write_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_OFSY, hAS->iOffset_Y );
		I2C_Write_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_OFSZ, hAS->iOffset_Z );
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
				
// DUR register

/** Get tap duration.
 * The DUR register is eight bits and contains an unsigned time value
 * representing the maximum time that an event must be above the THRESH_TAP
 * threshold to qualify as a tap event. The scale factor is 625 us/LSB. A value
 * of 0 disables the single tap/ double tap functions.
 * @return Tap duration (scaled at 625 us/LSB)
 * @see ADXL345_RA_DUR
 */
bool			ADXL345_getTapDuration(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{			
		hAS->iTap_Duration = I2C_Read_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_DUR);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/** Set tap duration.
 * @param duration Tap duration (scaled at 625 us/LSB)
 * @see getTapDuration()
 * @see ADXL345_RA_DUR
 */
bool 			ADXL345_setTapDuration(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{
		I2C_Write_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_DUR, hAS->iTap_Duration );
		return TRUE;
	}
	else
	{
		return FALSE;
	}	
}
        
// LATENT register

/** Get tap duration.
 * The latent register is eight bits and contains an unsigned time value
 * representing the wait time from the detection of a tap event to the start of
 * the time window (defined by the window register) during which a possible
 * second tap event can be detected. The scale factor is 1.25 ms/LSB. A value of
 * 0 disables the double tap function.
 * @return Tap latency (scaled at 1.25 ms/LSB)
 * @see ADXL345_RA_LATENT
 */
bool			ADXL345_getDoubleTapLatency(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{		
		hAS->iTap_Latency = I2C_Read_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_LATENT);		
		return TRUE;
	}
	else
	{
		return FALSE;
	}	
}

/** Set tap duration.
 * @param latency Tap latency (scaled at 1.25 ms/LSB)
 * @see getDoubleTapLatency()
 * @see ADXL345_RA_LATENT
 */
bool			ADXL345_setDoubleTapLatency(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{
		I2C_Write_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_LATENT , hAS->iTap_Latency );
		return TRUE;
	}
	else
	{
		return FALSE;
	}		
}

// WINDOW register

/** Get double tap window.
 * The window register is eight bits and contains an unsigned time value
 * representing the amount of time after the expiration of the latency time
 * (determined by the latent register) during which a second valid tap can
 * begin. The scale factor is 1.25 ms/LSB. A value of 0 disables the double tap
 * function.
 * @return Double tap window (scaled at 1.25 ms/LSB)
 * @see ADXL345_RA_WINDOW
 */
bool 			ADXL345_getDoubleTapWindow(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{			
		hAS->iTap_Window = I2C_Read_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_WINDOW);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/** Set double tap window.
 * @param window Double tap window (scaled at 1.25 ms/LSB)
 * @see getDoubleTapWindow()
 * @see ADXL345_RA_WINDOW
 */
bool 			ADXL345_setDoubleTapWindow(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{
		I2C_Write_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_WINDOW , hAS->iTap_Window );
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}	



// THRESH_ACT register

/** Get activity threshold.
 * The THRESH_ACT register is eight bits and holds the threshold value for
 * detecting activity. The data format is unsigned, so the magnitude of the
 * activity event is compared with the value in the THRESH_ACT register. The
 * scale factor is 62.5 mg/LSB. A value of 0 may result in undesirable behavior
 * if the activity interrupt is enabled.
 * @return Activity threshold (scaled at 62.5 mg/LSB)
 * @see ADXL345_RA_THRESH_ACT
 */
bool 			ADXL345_getActivityThreshold(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{			
		hAS->iThres_Act = I2C_Read_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_THRESH_ACT);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/** Set activity threshold.
 * @param threshold Activity threshold (scaled at 62.5 mg/LSB)
 * @see getActivityThreshold()
 * @see ADXL345_RA_THRESH_ACT
 */
bool 			ADXL345_setActivityThreshold(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{
		I2C_Write_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_WINDOW , hAS->iThres_Act );
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}	
// THRESH_INACT register

/** Get inactivity threshold.
 * The THRESH_INACT register is eight bits and holds the threshold value for 
 * detecting inactivity. The data format is unsigned, so the magnitude of the
 * inactivity event is compared with the value in the THRESH_INACT register. The
 * scale factor is 62.5 mg/LSB. A value of 0 may result in undesirable behavior
 * if the inactivity interrupt is enabled.
 * @return Inactivity threshold (scaled at 62.5 mg/LSB)
 * @see ADXL345_RA_THRESH_INACT
 */
bool 			ADXL345_getInactivityThreshold(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{			
		hAS->iThres_InAct = I2C_Read_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_THRESH_INACT);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
/** Set inactivity threshold.
 * @param threshold Inctivity threshold (scaled at 62.5 mg/LSB)
 * @see getInctivityThreshold()
 * @see ADXL345_RA_THRESH_INACT
 */
bool 			ADXL345_setInactivityThreshold(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{
		I2C_Write_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_THRESH_INACT , hAS->iThres_InAct );
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}	

// TIME_INACT register

/** Set inactivity time.
 * The TIME_INACT register is eight bits and contains an unsigned time value
 * representing the amount of time that acceleration must be less than the value
 * in the THRESH_INACT register for inactivity to be declared. The scale factor
 * is 1 sec/LSB. Unlike the other interrupt functions, which use unfiltered data
 * (see the Threshold sectionof the datasheet), the inactivity function uses
 * filtered output data. At least one output sample must be generated for the
 * inactivity interrupt to be triggered. This results in the function appearing
 * unresponsive if the TIME_INACT register is set to a value less than the time
 * constant of the output data rate. A value of 0 results in an interrupt when
 * the output data is less than the value in the THRESH_INACT register.
 * @return Inactivity time (scaled at 1 sec/LSB)
 * @see ADXL345_RA_TIME_INACT
 */
bool 			ADXL345_getInactivityTime(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{			
		hAS->iTime_InAct = I2C_Read_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_TIME_INACT);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
/** Set inactivity time.
 * @param time Inactivity time (scaled at 1 sec/LSB)
 * @see getInctivityTime()
 * @see ADXL345_RA_TIME_INACT
 */
bool 			ADXL345_setInactivityTime(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{
		I2C_Write_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_TIME_INACT , hAS->iTime_InAct );
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}	

// ACT_INACT_CTL register

/** Get activity AC/DC coupling.
 * A setting of 0 selects dc-coupled operation, and a setting of 1 enables
 * ac-coupled operation. In dc-coupled operation, the current acceleration
 * magnitude is compared directly with THRESH_ACT and THRESH_INACT to determine
 * whether activity or inactivity is detected.
 *
 * In ac-coupled operation for activity detection, the acceleration value at the
 * start of activity detection is taken as a reference value. New samples of
 * acceleration are then compared to this reference value, and if the magnitude
 * of the difference exceeds the THRESH_ACT value, the device triggers an
 * activity interrupt.
 *
 * Similarly, in ac-coupled operation for inactivity detection, a reference
 * value is used for comparison and is updated whenever the device exceeds the
 * inactivity threshold. After the reference value is selected, the device
 * compares the magnitude of the difference between the reference value and the
 * current acceleration with THRESH_INACT. If the difference is less than the
 * value in THRESH_INACT for the time in TIME_INACT, the device is considered
 * inactive and the inactivity interrupt is triggered.
 *
 * @return Activity coupling (0 = DC, 1 = AC)
 * @see ADXL345_RA_ACT_INACT_CTL
 * @see ADXL345_AIC_ACT_AC_BIT			0x80
 * @see ADXL345_AIC_ACT_X_BIT       0x40
 * @see ADXL345_AIC_ACT_Y_BIT       0x20
 * @see ADXL345_AIC_ACT_Z_BIT       0x10
 * @see ADXL345_AIC_INACT_AC_BIT    0x08
 * @see ADXL345_AIC_INACT_X_BIT     0x04
 * @see ADXL345_AIC_INACT_Y_BIT     0x02
 * @see ADXL345_AIC_INACT_Z_BIT     0x01
 */
bool 			ADXL345_getActivityCtrl(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{			
		hAS->iTime_InAct = I2C_Read_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_TIME_INACT);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
/** Set activity AC/DC coupling.
 * @param enabled Activity AC/DC coupling (TRUE for AC, FALSE for DC)
 * @see getActivityAC()
 * @see ADXL345_RA_ACT_INACT_CTL
 * @see ADXL345_AIC_ACT_AC_BIT			0x80
 * @see ADXL345_AIC_ACT_X_BIT       0x40
 * @see ADXL345_AIC_ACT_Y_BIT       0x20
 * @see ADXL345_AIC_ACT_Z_BIT       0x10
 * @see ADXL345_AIC_INACT_AC_BIT    0x08
 * @see ADXL345_AIC_INACT_X_BIT     0x04
 * @see ADXL345_AIC_INACT_Y_BIT     0x02
 * @see ADXL345_AIC_INACT_Z_BIT     0x01
 */
bool 			ADXL345_setActivityCtrl(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{
		I2C_Write_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_ACT_INACT_CTL , hAS->iAct_InAct_Ctrl );
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}	


// THRESH_FF register

/** Get freefall threshold value.
 * The THRESH_FF register is eight bits and holds the threshold value, in
 * unsigned format, for free-fall detection. The acceleration on all axes is
 * compared with the value in THRESH_FF to determine if a free-fall event
 * occurred. The scale factor is 62.5 mg/LSB. Note that a value of 0 mg may
 * result in undesirable behavior if the free-fall interrupt is enabled. Values
 * between 300 mg and 600 mg (0x05 to 0x09) are recommended.
 * @return Freefall threshold value (scaled at 62.5 mg/LSB)
 * @see ADXL345_RA_THRESH_FF
 */
bool 			ADXL345_getFreefallThreshold(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{			
		hAS->iThres_FF = I2C_Read_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_THRESH_FF);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/** Set freefall threshold value.
 * @param threshold Freefall threshold value (scaled at 62.5 mg/LSB)
 * @see getFreefallThreshold()
 * @see ADXL345_RA_THRESH_FF
 */
bool 			ADXL345_setFreefallThreshold(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{
		I2C_Write_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_THRESH_FF , hAS->iThres_FF );
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}	
// TIME_FF register

/** Get freefall time value.
 * The TIME_FF register is eight bits and stores an unsigned time value
 * representing the minimum time that the value of all axes must be less than
 * THRESH_FF to generate a free-fall interrupt. The scale factor is 5 ms/LSB. A
 * value of 0 may result in undesirable behavior if the free-fall interrupt is
 * enabled. Values between 100 ms and 350 ms (0x14 to 0x46) are recommended.
 * @return Freefall time value (scaled at 5 ms/LSB)
 * @see getFreefallThreshold()
 * @see ADXL345_RA_TIME_FF
 */

bool 			ADXL345_getFreefallTime(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{			
		hAS->iTime_FF = I2C_Read_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_TIME_FF);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/** Set freefall time value.
 * @param threshold Freefall time value (scaled at 5 ms/LSB)
 * @see getFreefallTime()
 * @see ADXL345_RA_TIME_FF
 */
bool 			ADXL345_setFreefallTime(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{
		I2C_Write_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_TIME_FF , hAS->iTime_FF );
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}	

// TAP_AXES register

/** Get double-tap fast-movement suppression.
 * Setting the suppress bit suppresses double tap detection if acceleration
 * greater than the value in THRESH_TAP is present between taps. See the Tap
 * Detection section in the datasheet for more details.
 * @return Double-tap fast-movement suppression value
 * @see getTapThreshold()
 * @see ADXL345_RA_TAP_AXES
 * @see ADXL345_TAPAXIS_SUP_BIT     0x08
 * @see ADXL345_TAPAXIS_X_BIT       0x04
 * @see ADXL345_TAPAXIS_Y_BIT       0x02
 * @see ADXL345_TAPAXIS_Z_BIT       0x01
 */

bool ADXL345_getTapAxisEnable(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{			
		hAS->iTap_Axis_Enable = I2C_Read_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_TAP_AXES);
		hAS->iTap_Axis_Enable &= ADXL345_TAPAXIS_MASK;		
		return TRUE;
	}
	else
	{
		return FALSE;
	}	
}
				
/** Set double-tap fast-movement suppression.
 * @param enabled Double-tap fast-movement suppression value
 * @see getTapAxisSuppress()
 * @see ADXL345_RA_TAP_AXES
 * @see ADXL345_TAPAXIS_SUP_BIT
 */

bool ADXL345_setTapAxisEnable(SE_ADXL345_HandleTypeDef *hAS)
{	    
	if(hAS)
	{
		I2C_Write_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_TAP_AXES , hAS->iTap_Axis_Enable );
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


// ACT_TAP_STATUS register

/** Get X axis activity source flag.
 * These bits indicate the first axis involved in a tap or activity event. A
 * setting of 1 corresponds to involvement in the event, and a setting of 0
 * corresponds to no involvement. When new data is available, these bits are not
 * cleared but are overwritten by the new data. The ACT_TAP_STATUS register
 * should be read before clearing the interrupt. Disabling an axis from
 * participation clears the corresponding source bit when the next activity or
 * single tap/double tap event occurs.
 * @return X axis activity source flag
 * @see ADXL345_RA_ACT_TAP_STATUS
 * @see ADXL345_TAPSTAT_ACTX_BIT    0x40
 * @see ADXL345_TAPSTAT_ACTY_BIT    0x20
 * @see ADXL345_TAPSTAT_ACTZ_BIT    0x10
 * @see ADXL345_TAPSTAT_ASLEEP_BIT  0x08
 * @see ADXL345_TAPSTAT_TAPX_BIT    0x04
 * @see ADXL345_TAPSTAT_TAPY_BIT    0x02
 * @see ADXL345_TAPSTAT_TAPZ_BIT    0x01
 */

bool ADXL345_getTapStatus(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{
		hAS->iTap_Status = I2C_Read_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_ACT_TAP_STATUS);
		hAS->iTap_Status &= ADXL345_TAPSTAT_MASK;
		return TRUE;
	}
	else
	{
		return FALSE;
	}	
}

// BW_RATE register
/** Get low power enabled status and measurement data rate.
 * A setting of 0 in the LOW_POWER bit selects normal operation, and a setting
 * of 1 selects reduced power operation, which has somewhat higher noise (see
 * the Power Modes section of the datasheet for details).
 * These bits select the device bandwidth and output data rate (see Table 7 and
 * Table 8 in the datasheet for details). The default value is 0x0A, which
 * translates to a 100 Hz output data rate. An output data rate should be
 * selected that is appropriate for the communication protocol and frequency
 * selected. Selecting too high of an output data rate with a low communication
 * speed results in samples being discarded.
 * @return Low power enabled status
 * @see ADXL345_RA_BW_RATE
 * @see ADXL345_BW_LOWPOWER_BIT
 * @see ADXL345_BW_RATE_BIT
 */
bool	ADXL345_getBWRate(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{			
		hAS->iBW_Rate = I2C_Read_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_BW_RATE);
		
		return TRUE;
	}
	else
	{
		return FALSE;
	}	
}

bool	ADXL345_setBWRate(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{
		I2C_Write_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_BW_RATE , hAS->iBW_Rate );
		hAS->iTap_Status &= ADXL345_TAPSTAT_MASK;
		return TRUE;
	}
	else
	{
		return FALSE;
	}		
}
				
// POWER_CTL register
/** Get Power setting.
 * @see ADXL345_RA_POWER_CTL
 * @see ADXL345_PCTL_LINK_BIT       0x20
 * @see ADXL345_PCTL_AUTOSLEEP_BIT  0x10
 * @see ADXL345_PCTL_MEASURE_BIT    0x08
 * @see ADXL345_PCTL_SLEEP_BIT      0x04
 * @see ADXL345_WAKEUP_x						
 */
bool	ADXL345_getPWRCTL(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{			
		hAS->iPWR_Ctrl = I2C_Read_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_POWER_CTL );
		
		return TRUE;
	}
	else
	{
		return FALSE;
	}	
}

bool	ADXL345_setBWRCTL(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{
		I2C_Write_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_POWER_CTL,  hAS->iPWR_Ctrl );
		return TRUE;
	}
	else
	{
		return FALSE;
	}	
}


// INT_ENABLE register

/** Get interrupt enabled status.
 * Setting bits in this register to a value of 1 enables their respective
 * functions to generate interrupts, whereas a value of 0 prevents the functions
 * from generating interrupts. The DATA_READY, watermark, and overrun bits
 * enable only the interrupt output; the functions are always enabled. It is
 * recommended that interrupts be configured before enabling their outputs.
 * @return DATA_READY interrupt enabled status.
 * @see ADXL345_RA_INT_ENABLE
 * @see ADXL345_INT_DATA_READY_BIT  0x80
 * @see ADXL345_INT_SINGLE_TAP_BIT  0x40
 * @see ADXL345_INT_DOUBLE_TAP_BIT  0x20
 * @see ADXL345_INT_ACTIVITY_BIT    0x10
 * @see ADXL345_INT_INACTIVITY_BIT  0x08
 * @see ADXL345_INT_FREE_FALL_BIT   0x04
 * @see ADXL345_INT_WATERMARK_BIT   0x02
 * @see ADXL345_INT_OVERRUN_BIT     0x01
 */
bool			ADXL345_getINTEnable(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{			
		hAS->iINT_Enable = I2C_Read_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_INT_ENABLE );
		
		return TRUE;
	}
	else
	{
		return FALSE;
	}	
}

bool			ADXL345_setINTEnable(SE_ADXL345_HandleTypeDef *hAS)
{	
	if(hAS)
	{
		I2C_Write_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_INT_ENABLE,  hAS->iINT_Enable );
		return TRUE;
	}
	else
	{
		return FALSE;
	}		
}

// INT_MAP register

/** Get DATA_READY interrupt pin.
 * Any bits set to 0 in this register send their respective interrupts to the
 * INT1 pin, whereas bits set to 1 send their respective interrupts to the INT2
 * pin. All selected interrupts for a given pin are OR'ed.
 * @return Interrupt pin setting
 * @see ADXL345_RA_INT_MAP
 * @see ADXL345_INT_DATA_READY_BIT  0x80
 * @see ADXL345_INT_SINGLE_TAP_BIT  0x40
 * @see ADXL345_INT_DOUBLE_TAP_BIT  0x20
 * @see ADXL345_INT_ACTIVITY_BIT    0x10
 * @see ADXL345_INT_INACTIVITY_BIT  0x08
 * @see ADXL345_INT_FREE_FALL_BIT   0x04
 * @see ADXL345_INT_WATERMARK_BIT   0x02
 * @see ADXL345_INT_OVERRUN_BIT     0x01
 */
bool			ADXL345_getINTMAP(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{			
		hAS->iINT_MAP = I2C_Read_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_INT_MAP);
		
		return TRUE;
	}
	else
	{
		return FALSE;
	}	
}

bool			ADXL345_setINTMAP(SE_ADXL345_HandleTypeDef *hAS)
{	
	if(hAS)
	{
		I2C_Write_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_INT_MAP,  hAS->iINT_MAP );
		return TRUE;
	}
	else
	{
		return FALSE;
	}		
}

/** Get DATA_READY interrupt source flag.
 * Bits set to 1 in this register indicate that their respective functions have
 * triggered an event, whereas a value of 0 indicates that the corresponding
 * event has not occurred. The DATA_READY, watermark, and overrun bits are
 * always set if the corresponding events occur, regardless of the INT_ENABLE
 * register settings, and are cleared by reading data from the DATAX, DATAY, and
 * DATAZ registers. The DATA_READY and watermark bits may require multiple
 * reads, as indicated in the FIFO mode descriptions in the FIFO section. Other
 * bits, and the corresponding interrupts, are cleared by reading the INT_SOURCE
 * register.
 * @return Interrupt source flag
 * @see ADXL345_RA_INT_SOURCE
 * @see ADXL345_INT_DATA_READY_BIT  0x80
 * @see ADXL345_INT_SINGLE_TAP_BIT  0x40
 * @see ADXL345_INT_DOUBLE_TAP_BIT  0x20
 * @see ADXL345_INT_ACTIVITY_BIT    0x10
 * @see ADXL345_INT_INACTIVITY_BIT  0x08
 * @see ADXL345_INT_FREE_FALL_BIT   0x04
 * @see ADXL345_INT_WATERMARK_BIT   0x02
 * @see ADXL345_INT_OVERRUN_BIT     0x01
 */
bool 			ADXL345_getIntStatus(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{			
		hAS->iINT_Status = I2C_Read_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_INT_SOURCE);
		
		return TRUE;
	}
	else
	{
		return FALSE;
	}	
}

// DATA_FORMAT register

/** Get self-test force enabled.
 * A setting of 1 in the SELF_TEST bit applies a self-test force to the sensor,
 * causing a shift in the output data. A value of 0 disables the self-test
 * force.
 * @see ADXL345_RA_DATA_FORMAT
 * @see ADXL345_FORMAT_SELFTEST_BIT 0x80
 * @see ADXL345_FORMAT_SPIMODE_BIT  0x40
 * @see ADXL345_FORMAT_INTMODE_BIT  0x20
 * @see ADXL345_FORMAT_FULL_RES_BIT 0x08
 * @see ADXL345_FORMAT_JUSTIFY_BIT  0x02
 */
bool			ADXL345_getFORMAT(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{			
		hAS->iDataFormat = I2C_Read_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_DATA_FORMAT);
		
		return TRUE;
	}
	else
	{
		return FALSE;
	}	
}

bool			ADXL345_setFORMAT(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{
		I2C_Write_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_DATA_FORMAT,  hAS->iDataFormat );
		return TRUE;
	}
	else
	{
		return FALSE;
	}		
}

// DATA* registers

/** Get 3-axis accleration measurements.
 * These six bytes (Register 0x32 to Register 0x37) are eight bits each and hold
 * the output data for each axis. Register 0x32 and Register 0x33 hold the
 * output data for the x-axis, Register 0x34 and Register 0x35 hold the output
 * data for the y-axis, and Register 0x36 and Register 0x37 hold the output data
 * for the z-axis. The output data is twos complement, with DATAx0 as the least
 * significant byte and DATAx1 as the most significant byte, where x represent
 * X, Y, or Z. The DATA_FORMAT register (Address 0x31) controls the format of
 * the data. It is recommended that a multiple-byte read of all registers be
 * performed to prevent a change in data between reads of sequential registers.
 * 
 * The DATA_FORMAT register controls the presentation of data to Register 0x32
 * through Register 0x37. All data, except that for the +/-16 g range, must be
 * clipped to avoid rollover.
 *
 * @param x 16-bit signed integer container for X-axis acceleration
 * @param y 16-bit signed integer container for Y-axis acceleration
 * @param z 16-bit signed integer container for Z-axis acceleration
 * @see ADXL345_RA_DATAX0
 */
bool 			ADXL345_getAcceleration(SE_ADXL345_HandleTypeDef *hAS)
{
	uint8_t	iDataBuf[6];
	
	if(hAS)
	{			
		if(	I2C_Read_Multi_Bytes(hAS->iDeviceAddr_Main, ADXL345_RA_DATAX0, 6, iDataBuf) )
		{
			hAS->iAcc_X = (((int16_t)iDataBuf[1]) << 8) | iDataBuf[0];
			hAS->iAcc_Y = (((int16_t)iDataBuf[3]) << 8) | iDataBuf[2];
			hAS->iAcc_Z = (((int16_t)iDataBuf[5]) << 8) | iDataBuf[4];	
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

bool			ADXL_getFIFOCtrl(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{			
		hAS->iFifo_Ctrl = I2C_Read_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_FIFO_CTL);
		
		return TRUE;
	}
	else
	{
		return FALSE;
	}	
}

bool			ADXL_setFIFOCtrl(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{
		I2C_Write_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_FIFO_CTL, hAS->iFifo_Ctrl);
		return TRUE;
	}
	else
	{
		return FALSE;
	}	
}
/** Get FIFO trigger occurred status.
 * A 1 in the FIFO_TRIG bit corresponds to a trigger event occurring, and a 0
 * means that a FIFO trigger event has not occurred.
 * @return FIFO trigger occurred status
 * @see ADXL345_RA_FIFO_STATUS
 * @see ADXL345_FIFOSTAT_TRIGGER_BIT
 */
bool			ADXL_getFIFOTriggerOccured(SE_ADXL345_HandleTypeDef *hAS)
{	
	if(hAS)
	{			
		hAS->iFifo_Status = I2C_Read_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_FIFO_STATUS);
		
		if(hAS->iFifo_Status&ADXL345_FIFOSTAT_TRIGGER_BIT)
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
/** Get FIFO length.
 * These bits report how many data values are stored in FIFO. Access to collect
 * the data from FIFO is provided through the DATAX, DATAY, and DATAZ registers.
 * FIFO reads must be done in burst or multiple-byte mode because each FIFO
 * level is cleared after any read (single- or multiple-byte) of FIFO. FIFO
 * stores a maximum of 32 entries, which equates to a maximum of 33 entries
 * available at any given time because an additional entry is available at the
 * output filter of the I2Cdev::
 * @return Current FIFO length
 * @see ADXL345_RA_FIFO_STATUS
 * @see ADXL345_FIFOSTAT_LENGTH_BIT
 * @see ADXL345_FIFOSTAT_LENGTH_LENGTH
 */
uint8_t		ADXL_getFIFODepth(SE_ADXL345_HandleTypeDef *hAS)
{
	if(hAS)
	{			
		hAS->iFifo_Status = I2C_Read_One_Byte(hAS->iDeviceAddr_Main, ADXL345_RA_FIFO_STATUS);
		
		return (hAS->iFifo_Status&ADXL345_FIFOSTAT_DEPTH_MASK) ;
	}
	else
	{
		return 0;
	}			
}
 


