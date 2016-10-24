#ifndef _ADXL345_H_
#define _ADXL345_H_

#include "system.h"

#define ADXL345_ADDRESS_ALT_LOW     0x53 // alt address pin low (GND)
#define ADXL345_ADDRESS_ALT_HIGH    0x1D // alt address pin high (VCC)
#define ADXL345_DEFAULT_ADDRESS     ADXL345_ADDRESS_ALT_LOW

#define ADXL345_RA_DEVID            0x00
#define ADXL345_RA_RESERVED1        0x01
#define ADXL345_RA_THRESH_TAP       0x1D
#define ADXL345_RA_OFSX             0x1E
#define ADXL345_RA_OFSY             0x1F
#define ADXL345_RA_OFSZ             0x20
#define ADXL345_RA_DUR              0x21
#define ADXL345_RA_LATENT           0x22
#define ADXL345_RA_WINDOW           0x23
#define ADXL345_RA_THRESH_ACT       0x24
#define ADXL345_RA_THRESH_INACT     0x25
#define ADXL345_RA_TIME_INACT       0x26
#define ADXL345_RA_ACT_INACT_CTL    0x27
#define ADXL345_RA_THRESH_FF        0x28
#define ADXL345_RA_TIME_FF          0x29
#define ADXL345_RA_TAP_AXES         0x2A
#define ADXL345_RA_ACT_TAP_STATUS   0x2B
#define ADXL345_RA_BW_RATE          0x2C
#define ADXL345_RA_POWER_CTL        0x2D
#define ADXL345_RA_INT_ENABLE       0x2E
#define ADXL345_RA_INT_MAP          0x2F
#define ADXL345_RA_INT_SOURCE       0x30
#define ADXL345_RA_DATA_FORMAT      0x31
#define ADXL345_RA_DATAX0           0x32
#define ADXL345_RA_DATAX1           0x33
#define ADXL345_RA_DATAY0           0x34
#define ADXL345_RA_DATAY1           0x35
#define ADXL345_RA_DATAZ0           0x36
#define ADXL345_RA_DATAZ1           0x37
#define ADXL345_RA_FIFO_CTL         0x38
#define ADXL345_RA_FIFO_STATUS      0x39

#define ADXL345_AIC_ACT_AC_BIT      0x80
#define ADXL345_AIC_ACT_X_BIT       0x40
#define ADXL345_AIC_ACT_Y_BIT       0x20
#define ADXL345_AIC_ACT_Z_BIT       0x10
#define ADXL345_AIC_INACT_AC_BIT    0x08
#define ADXL345_AIC_INACT_X_BIT     0x04
#define ADXL345_AIC_INACT_Y_BIT     0x02
#define ADXL345_AIC_INACT_Z_BIT     0x01


#define ADXL345_TAPAXIS_SUP_BIT     0x08
#define ADXL345_TAPAXIS_X_BIT       0x04
#define ADXL345_TAPAXIS_Y_BIT       0x02
#define ADXL345_TAPAXIS_Z_BIT       0x01
#define ADXL345_TAPAXIS_MASK				0x0F

#define ADXL345_TAPSTAT_ACTX_BIT    0x40
#define ADXL345_TAPSTAT_ACTY_BIT    0x20
#define ADXL345_TAPSTAT_ACTZ_BIT    0x10
#define ADXL345_TAPSTAT_ASLEEP_BIT  0x08
#define ADXL345_TAPSTAT_TAPX_BIT    0x04
#define ADXL345_TAPSTAT_TAPY_BIT    0x02
#define ADXL345_TAPSTAT_TAPZ_BIT    0x01
#define ADXL345_TAPSTAT_MASK				0x7F

#define ADXL345_BW_LOWPOWER_BIT     0x10
#define ADXL345_BW_RATE_BIT         3
#define ADXL345_BW_RATE_LENGTH      4

#define ADXL345_RATE_3200           0x0F	//0b1111
#define ADXL345_RATE_1600           0x0E	//0b1110
#define ADXL345_RATE_800            0x0D	//0b1101
#define ADXL345_RATE_400            0x0C	//0b1100
#define ADXL345_RATE_200            0x0B	//0b1011
#define ADXL345_RATE_100            0x0A	//0b1010
#define ADXL345_RATE_50             0x09	//0b1001
#define ADXL345_RATE_25             0x08	//0b1000
#define ADXL345_RATE_12P5           0x07	//0b0111
#define ADXL345_RATE_6P25           0x06	//0b0110
#define ADXL345_RATE_3P13           0x05	//0b0101
#define ADXL345_RATE_1P56           0x04	//0b0100
#define ADXL345_RATE_0P78           0x03	//0b0011
#define ADXL345_RATE_0P39           0x02	//0b0010
#define ADXL345_RATE_0P20           0x01	//0b0001
#define ADXL345_RATE_0P10           0x00	//0b0000
#define ADXL345_RATE_MASK           0x0F	

#define ADXL345_PCTL_LINK_BIT       0x20
#define ADXL345_PCTL_AUTOSLEEP_BIT  0x10
#define ADXL345_PCTL_MEASURE_BIT    0x08
#define ADXL345_PCTL_SLEEP_BIT      0x04

#define ADXL345_WAKEUP_MASK					0x03
#define ADXL345_WAKEUP_8HZ          0x00
#define ADXL345_WAKEUP_4HZ          0x01
#define ADXL345_WAKEUP_2HZ          0x02
#define ADXL345_WAKEUP_1HZ          0x03

#define ADXL345_INT_DATA_READY_BIT  0x80
#define ADXL345_INT_SINGLE_TAP_BIT  0x40
#define ADXL345_INT_DOUBLE_TAP_BIT  0x20
#define ADXL345_INT_ACTIVITY_BIT    0x10
#define ADXL345_INT_INACTIVITY_BIT  0x08
#define ADXL345_INT_FREE_FALL_BIT   0x04
#define ADXL345_INT_WATERMARK_BIT   0x02
#define ADXL345_INT_OVERRUN_BIT     0x01

#define ADXL345_FORMAT_SELFTEST_BIT 0x80
#define ADXL345_FORMAT_SPIMODE_BIT  0x40
#define ADXL345_FORMAT_INTMODE_BIT  0x20
#define ADXL345_FORMAT_FULL_RES_BIT 0x08
#define ADXL345_FORMAT_JUSTIFY_BIT  0x02
#define ADXL345_FORMAT_RANGE_BIT    1
#define ADXL345_FORMAT_RANGE_LENGTH 2

#define ADXL345_RANGE_2G            0x00
#define ADXL345_RANGE_4G            0x01
#define ADXL345_RANGE_8G            0x02
#define ADXL345_RANGE_16G           0x03
#define ADXL345_RANGE_MASK					0x03

#define ADXL345_FIFO_MODE_BIT       7
#define ADXL345_FIFO_MODE_LENGTH    2
#define ADXL345_FIFO_TRIGGER_BIT    5
#define ADXL345_FIFO_SAMPLES_BIT    4
#define ADXL345_FIFO_SAMPLES_LENGTH 5

#define ADXL345_FIFO_MODE_BYPASS    0x00
#define ADXL345_FIFO_MODE_FIFO      0x01
#define ADXL345_FIFO_MODE_STREAM    0x02
#define ADXL345_FIFO_MODE_TRIGGER   0x03

#define ADXL345_FIFOSTAT_TRIGGER_BIT        0x80
#define ADXL345_FIFOSTAT_DEPTH_MASK					0x3F

typedef struct 
{
	uint8_t		iDeviceAddr_Main;
	
	uint8_t		iOffset_X;			//X Axis Threshold
	uint8_t		iOffset_Y;			//Y Axis Threshold
	uint8_t		iOffset_Z;			//Z Axis Threshold
	
	uint8_t		iTap_Threshold;	//Tap Threshold
	uint8_t		iTap_Duration;	//Tap Duration
	uint8_t		iTap_Latency;		//Tap Latency
	uint8_t		iTap_Window;		//Tap Window
	
	uint8_t		iThres_Act;			//Threshold for activity
	uint8_t		iThres_InAct;
	uint8_t   iTime_InAct;
	uint8_t		iAct_InAct_Ctrl;
	
	uint8_t		iThres_FF;			//Threshold for free fall
	uint8_t		iTime_FF;
	uint8_t		iTap_Axis_Enable;
	uint8_t		iTap_Status;
	
	uint8_t		iBW_Rate;
	uint8_t		iPWR_Ctrl;
	
	uint8_t		iINT_Enable;
	uint8_t		iINT_Status;
	uint8_t		iINT_MAP;
	uint8_t		iDataFormat;

	uint8_t		iFifo_Ctrl;
	uint8_t		iFifo_Status;


	int16_t		iAcc_X;
	int16_t		iAcc_Y;
	int16_t		iAcc_Z;
	
}SE_ADXL345_HandleTypeDef;


				void 	ADXL345_initialize(SE_ADXL345_HandleTypeDef *hAS);
	
// WHO_AM_I register, read-only
				uint8_t 	ADXL345_getDeviceID(SE_ADXL345_HandleTypeDef *hAS);
				bool 			ADXL345_testConnection(SE_ADXL345_HandleTypeDef *hAS);

// THRESH_TAP register
				bool	 		ADXL345_getTapThreshold(SE_ADXL345_HandleTypeDef *hAS);
        bool 			ADXL345_setTapThreshold(SE_ADXL345_HandleTypeDef *hAS);

// OFFSET register
				bool			ADXL345_getOffset(SE_ADXL345_HandleTypeDef *hAS);
				bool			ADXL345_setOffset(SE_ADXL345_HandleTypeDef *hAS);
        
// DUR register
        bool			ADXL345_getTapDuration(SE_ADXL345_HandleTypeDef *hAS);
        bool 			ADXL345_setTapDuration(SE_ADXL345_HandleTypeDef *hAS);
        
// LATENT register
        bool			ADXL345_getDoubleTapLatency(SE_ADXL345_HandleTypeDef *hAS);
        bool			ADXL345_setDoubleTapLatency(SE_ADXL345_HandleTypeDef *hAS);
        
        // WINDOW register
        bool 			ADXL345_getDoubleTapWindow(SE_ADXL345_HandleTypeDef *hAS);
        bool 			ADXL345_setDoubleTapWindow(SE_ADXL345_HandleTypeDef *hAS);
        
        // THRESH_ACT register
        bool 			ADXL345_getActivityThreshold(SE_ADXL345_HandleTypeDef *hAS);
        bool 			ADXL345_setActivityThreshold(SE_ADXL345_HandleTypeDef *hAS);
        
        // THRESH_INACT register
        bool			ADXL345_getInactivityThreshold(SE_ADXL345_HandleTypeDef *hAS);
        bool			ADXL345_setInactivityThreshold(SE_ADXL345_HandleTypeDef *hAS);

        // TIME_INACT register
        bool			ADXL345_getInactivityTime(SE_ADXL345_HandleTypeDef *hAS);
        bool			ADXL345_setInactivityTime(SE_ADXL345_HandleTypeDef *hAS);
				
				// ACT_INACT register
				bool			ADXL345_getActivityCtrl(SE_ADXL345_HandleTypeDef *hAS);
				bool			ADXL345_setActivityCtrl(SE_ADXL345_HandleTypeDef *hAS);
				
				// Free fall register
				bool 			ADXL345_getFreefallThreshold(SE_ADXL345_HandleTypeDef *hAS);
				bool 			ADXL345_setFreefallThreshold(SE_ADXL345_HandleTypeDef *hAS);
					
				// Free fall time register
				bool 			ADXL345_getFreefallTime(SE_ADXL345_HandleTypeDef *hAS);
				bool 			ADXL345_setFreefallTime(SE_ADXL345_HandleTypeDef *hAS);
				
				// TAP_AXES register
				bool 			ADXL345_getTapAxisEnable(SE_ADXL345_HandleTypeDef *hAS);
				bool 			ADXL345_setTapAxisEnable(SE_ADXL345_HandleTypeDef *hAS);
				
				// ACT_TAP_STATUS register
				bool 			ADXL345_getTapStatus(SE_ADXL345_HandleTypeDef *hAS);
				
				// BW_RATE register
				bool			ADXL345_getBWRate(SE_ADXL345_HandleTypeDef *hAS);
				bool			ADXL345_setBWRate(SE_ADXL345_HandleTypeDef *hAS);
        // BW_RATE register
        //bool getLowPowerEnabled();
        //void setLowPowerEnabled(bool enabled);
        //uint8_t getRate();
        //void setRate(uint8_t rate);
				
				// POWER_CTL register
				bool			ADXL345_getPWRCTL(SE_ADXL345_HandleTypeDef *hAS);
				bool			ADXL345_setBWRCTL(SE_ADXL345_HandleTypeDef *hAS);
				
				// POWER_CTL register
        //bool getLinkEnabled();
        //void setLinkEnabled(bool enabled);
        //bool getAutoSleepEnabled();
        //void setAutoSleepEnabled(bool enabled);
        //bool getMeasureEnabled();
        //void setMeasureEnabled(bool enabled);
        //bool getSleepEnabled();
        //void setSleepEnabled(bool enabled);
        //uint8_t getWakeupFrequency();
        //void setWakeupFrequency(uint8_t frequency);

				// INT_ENABLE register
				bool			ADXL345_getINTEnable(SE_ADXL345_HandleTypeDef *hAS);
				bool			ADXL345_setINTEnable(SE_ADXL345_HandleTypeDef *hAS);
				
        // INT_ENABLE register
        //bool getIntDataReadyEnabled();
        //void setIntDataReadyEnabled(bool enabled);
        //bool getIntSingleTapEnabled();
        //void setIntSingleTapEnabled(bool enabled);
        //bool getIntDoubleTapEnabled();
        //void setIntDoubleTapEnabled(bool enabled);
        //bool getIntActivityEnabled();
        //void setIntActivityEnabled(bool enabled);
        //bool getIntInactivityEnabled();
        //void setIntInactivityEnabled(bool enabled);
        //bool getIntFreefallEnabled();
        //void setIntFreefallEnabled(bool enabled);
        //bool getIntWatermarkEnabled();
        //void setIntWatermarkEnabled(bool enabled);
        //bool getIntOverrunEnabled();
        //void setIntOverrunEnabled(bool enabled);
				
				// INT_MAP register
				bool			ADXL345_getINTMAP(SE_ADXL345_HandleTypeDef *hAS);
				bool			ADXL345_setINTMAP(SE_ADXL345_HandleTypeDef *hAS);				
				// INT_MAP register
        //uint8_t getIntDataReadyPin();
        //void setIntDataReadyPin(uint8_t pin);
        //uint8_t getIntSingleTapPin();
        //void setIntSingleTapPin(uint8_t pin);
        //uint8_t getIntDoubleTapPin();
        //void setIntDoubleTapPin(uint8_t pin);
        //uint8_t getIntActivityPin();
        //void setIntActivityPin(uint8_t pin);
        //uint8_t getIntInactivityPin();
        //void setIntInactivityPin(uint8_t pin);
        //uint8_t getIntFreefallPin();
        //void setIntFreefallPin(uint8_t pin);
        //uint8_t getIntWatermarkPin();
        //void setIntWatermarkPin(uint8_t pin);
        //uint8_t getIntOverrunPin();
        //void setIntOverrunPin(uint8_t pin);
				
				// INT_SOURCE register
				bool 			ADXL345_getIntStatus(SE_ADXL345_HandleTypeDef *hAS);
				// INT_SOURCE register
        //uint8_t getIntDataReadySource();
        //uint8_t getIntSingleTapSource();
        //uint8_t getIntDoubleTapSource();
        //uint8_t getIntActivitySource();
        //uint8_t getIntInactivitySource();
        //uint8_t getIntFreefallSource();
        //uint8_t getIntWatermarkSource();
        //uint8_t getIntOverrunSource();
				
				
				// DATA_FORMAT register
				bool			ADXL345_getFORMAT(SE_ADXL345_HandleTypeDef *hAS);
				bool			ADXL345_setFORMAT(SE_ADXL345_HandleTypeDef *hAS);
        //uint8_t getSelfTestEnabled();
        //void setSelfTestEnabled(uint8_t enabled);
        //uint8_t getSPIMode();
        //void setSPIMode(uint8_t mode);
        //uint8_t getInterruptMode();
        //void setInterruptMode(uint8_t mode);
        //uint8_t getFullResolution();
        //void setFullResolution(uint8_t resolution);
        //uint8_t getDataJustification();
        //void setDataJustification(uint8_t justification);
        //uint8_t getRange();
        //void setRange(uint8_t range);
				
        // DATA* registers
				bool			ADXL345_getAcceleration(SE_ADXL345_HandleTypeDef *hAS);				
        //void getAcceleration(int16_t* x, int16_t* y, int16_t* z);
        //int16_t getAccelerationX();
        //int16_t getAccelerationY();
        //int16_t getAccelerationZ();
				
				
        // FIFO_CTL register
				bool			ADXL_getFIFOCtrl(SE_ADXL345_HandleTypeDef *hAS);	
				bool			ADXL_setFIFOCtrl(SE_ADXL345_HandleTypeDef *hAS);	
        //uint8_t getFIFOMode();
        //void setFIFOMode(uint8_t mode);
        //uint8_t getFIFOTriggerInterruptPin();
        //void setFIFOTriggerInterruptPin(uint8_t interrupt);
        //uint8_t getFIFOSamples();
        //void setFIFOSamples(uint8_t size);
        
        // FIFO_STATUS register
				bool			ADXL_getFIFOTriggerOccured(SE_ADXL345_HandleTypeDef *hAS);
				uint8_t		ADXL_getFIFODepth(SE_ADXL345_HandleTypeDef *hAS);				
				//bool getFIFOTriggerOccurred();
        //uint8_t getFIFOLength();

#endif /* _ADXL345_H_ */
