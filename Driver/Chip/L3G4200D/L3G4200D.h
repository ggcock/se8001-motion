
#ifndef _L3G4200D_H_
#define _L3G4200D_H_

#include "system.h"

#define L3G4200D_ADDRESS           0x69
#define L3G4200D_DEFAULT_ADDRESS   0x69

#define L3G4200D_RA_WHO_AM_I       0x0F
#define L3G4200D_RA_CTRL_REG1      0x20
#define L3G4200D_RA_CTRL_REG2      0x21
#define L3G4200D_RA_CTRL_REG3      0x22
#define L3G4200D_RA_CTRL_REG4      0x23
#define L3G4200D_RA_CTRL_REG5      0x24
#define L3G4200D_RA_REFERENCE      0x25
#define L3G4200D_RA_OUT_TEMP       0x26
#define L3G4200D_RA_STATUS         0x27
#define L3G4200D_RA_OUT_X_L        0x28
#define L3G4200D_RA_OUT_X_H        0x29
#define L3G4200D_RA_OUT_Y_L        0x2A
#define L3G4200D_RA_OUT_Y_H        0x2B
#define L3G4200D_RA_OUT_Z_L        0x2C
#define L3G4200D_RA_OUT_Z_H        0x2D
#define L3G4200D_RA_FIFO_CTRL  	   0x2E
#define L3G4200D_RA_FIFO_SRC	   	 0x2F
#define L3G4200D_RA_INT1_CFG       0x30
#define L3G4200D_RA_INT1_SRC       0x31
#define L3G4200D_RA_INT1_THS_XH    0x32
#define L3G4200D_RA_INT1_THS_XL    0X33
#define L3G4200D_RA_INT1_THS_YH    0X34
#define L3G4200D_RA_INT1_THS_YL    0x35
#define L3G4200D_RA_INT1_THS_ZH    0X36
#define L3G4200D_RA_INT1_THS_ZL    0x37
#define L3G4200D_RA_INT1_DURATION  0X38

#define L3G4200D_ODR_BIT           7
#define L3G4200D_ODR_LENGTH        2
#define L3G4200D_BW_BIT            5
#define L3G4200D_BW_LENGTH         2
#define L3G4200D_PD_BIT            3
#define L3G4200D_ZEN_BIT           2
#define L3G4200D_YEN_BIT           1
#define L3G4200D_XEN_BIT           0

#define L3G4200D_RATE_100          0x0		//0b00000000
#define L3G4200D_RATE_200          0x4		//0b01000000
#define L3G4200D_RATE_400          0x8		//0b10000000
#define L3G4200D_RATE_800          0xc		//0b11000000
#define L3G4200D_RATE_MASK				 0xc		//0b11000000

#define L3G4200D_BW_LOW            0x00		//0b00000000
#define L3G4200D_BW_MED_LOW				 0x10		//0b00010000
#define L3G4200D_BW_MED_HIGH       0x20		//0b00100000
#define L3G4200D_BW_HIGH           0x30		//0b00110000
#define L3G4200D_BW_MASK           0x30		//0b00110000

#define L3G4200D_PD_ON						 0x08		//0b00001000
#define L3G4200D_ZEN							 0x04
#define L3G4200D_YEN							 0x02
#define L3G4200D_XEN							 0x01



#define L3G4200D_HPM_BIT           5
#define L3G4200D_HPM_LENGTH        2
#define L3G4200D_HPCF_BIT          3
#define L3G4200D_HPCF_LENGTH       4

#define L3G4200D_HPM_HRF           0x00
#define L3G4200D_HPM_REFERENCE     0x10
#define L3G4200D_HPM_NORMAL        0x20
#define L3G4200D_HPM_AUTORESET     0x30
#define L3G4200D_HPM_MASK					 0x30

#define L3G4200D_HPCF1             0x00
#define L3G4200D_HPCF2             0x01
#define L3G4200D_HPCF3             0x02
#define L3G4200D_HPCF4             0x03
#define L3G4200D_HPCF5             0x04
#define L3G4200D_HPCF6             0x05
#define L3G4200D_HPCF7             0x06
#define L3G4200D_HPCF8             0x07
#define L3G4200D_HPCF9             0x08
#define L3G4200D_HPCF10            0x09
#define L3G4200D_HPCF_MASK				 0x0F

#define L3G4200D_I1_INT1_EN        0x80
#define L3G4200D_I1_BOOT_EN        0x40
#define L3G4200D_H_LACTIVE_EN      0x20
#define L3G4200D_PP_OD_EN          0x10
#define L3G4200D_I2_DRDY_EN        0x08
#define L3G4200D_I2_WTM_EN         0x04
#define L3G4200D_I2_ORUN_EN        0x02
#define L3G4200D_I2_EMPTY_EN       0x01

#define L3G4200D_PUSH_PULL         1
#define L3G4200D_OPEN_DRAIN        0

#define L3G4200D_BDU_EN            0x80

#define L3G4200D_BLE_EN	         	 0x40	
#define L3G4200D_BLE_BIG				   0x40
#define L3G4200D_BLE_LITTLE			   0x00

#define L3G4200D_SIM_4W         	 0x01

#define L3G4200D_FS_250            0x00
#define L3G4200D_FS_500            0x10
#define L3G4200D_FS_2000           0x20
#define L3G4200D_FS_MASK           0x30

#define L3G4200D_SELF_TEST_NORMAL  0x00
#define L3G4200D_SELF_TEST_0       0x02
#define L3G4200D_SELF_TEST_1       0x06
#define L3G4200D_SELF_TEST_MASK    0x06

#define L3G4200D_SPI_4_WIRE        0x00
#define L3G4200D_SPI_3_WIRE        0x01

#define L3G4200D_BOOT_BIT          7
#define L3G4200D_FIFO_EN_BIT       6
#define L3G4200D_HPEN_BIT          4
#define L3G4200D_INT1_SEL_BIT      3
#define L3G4200D_INT1_SEL_LENGTH   2
#define L3G4200D_OUT_SEL_BIT       1
#define L3G4200D_OUT_SEL_LENGTH    2

#define L3G4200D_BOOT_EN					 0x80
#define L3G4200D_FIFO_EN					 0x40
#define L3G4200D_HP_EN						 0x10

#define L3G4200D_INT1_SEL_NONE		 0x00
#define L3G4200D_INT1_SEL_HP			 0x04
#define L3G4200D_INT1_SEL_LP			 0x08
#define L3G4200D_INT1_SEL_BP			 0x0C			//Bandpass=HP+LP
#define L3G4200D_INT1_SEL_MASK		 0x0C

#define L3G4200D_OUT_SEL_NONE			 0x00
#define L3G4200D_OUT_SEL_HP			 	 0x01
#define L3G4200D_OUT_SEL_LP			 	 0x02
#define L3G4200D_OUT_SEL_BP			 	 0x03			//Bandpass=HP+LP
#define L3G4200D_OUT_SEL_MASK		 	 0x03


#define L3G4200D_STA_ZYXOR				 0x80
#define L3G4200D_STA_ZOR					 0x40
#define L3G4200D_STA_YOR					 0x20
#define L3G4200D_STA_XOR					 0x10
#define L3G4200D_STA_ZYXDA				 0x08
#define L3G4200D_STA_ZDA					 0x04
#define L3G4200D_STA_YDA					 0x02
#define L3G4200D_STA_XDA					 0x01

#define L3G4200D_FIFO_MODE_BIT     7
#define L3G4200D_FIFO_MODE_LENGTH  3
#define L3G4200D_FIFO_WTM_BIT      4
#define L3G4200D_FIFO_WTM_LENGTH   5

#define L3G4200D_FM_BYPASS         0x00
#define L3G4200D_FM_FIFO           0x20
#define L3G4200D_FM_STREAM         0x40
#define L3G4200D_FM_STREAM_FIFO    0x60
#define L3G4200D_FM_BYPASS_STREAM  0x80
#define L3G4200D_FM_MASK					 0xE0

#define L3G4200D_WTM_MASK					 0x1F

#define L3G4200D_FIFO_STATUS_BIT   7
#define L3G4200D_FIFO_OVRN_BIT     6
#define L3G4200D_FIFO_EMPTY_BIT    5
#define L3G4200D_FIFO_FSS_BIT      4
#define L3G4200D_FIFO_FSS_LENGTH   5

#define L3G4200D_FIFO_STA_WTM			 0x80
#define L3G4200D_FIFO_STA_OVR			 0x40
#define L3G4200D_FIFO_STA_EMPTY		 0x20
#define L3G4200D_FIFO_DEPTH_MASK	 0x1F

#define L3G4200D_INT1_AND_OR_BIT   0x80
#define L3G4200D_INT1_LIR_BIT      0x40
#define L3G4200D_ZHIE_BIT          0x20
#define L3G4200D_ZLIE_BIT          0x10
#define L3G4200D_YHIE_BIT          0x08
#define L3G4200D_YLIE_BIT          0x04
#define L3G4200D_XHIE_BIT          0x02
#define L3G4200D_XLIE_BIT          0x01

#define L3G4200D_INT1_OR           0
#define L3G4200D_INT1_AND          1

#define L3G4200D_INT1_IA_BIT       0x40
#define L3G4200D_INT1_ZH_BIT       0x20
#define L3G4200D_INT1_ZL_BIT       0x10
#define L3G4200D_INT1_YH_BIT       0x08
#define L3G4200D_INT1_YL_BIT       0x04
#define L3G4200D_INT1_XH_BIT       0x02
#define L3G4200D_INT1_XL_BIT       0x01

#define L3G4200D_INT1_WAIT_BIT     0x80
#define L3G4200D_INT1_DUR_BIT      6
#define L3G4200D_INT1_DUR_LENGTH   7

#define L3G4200D_INT1_DUR_MASK		0x7F


typedef struct 
{
	uint8_t		iDeviceAddr_Main;
	uint8_t		iDeviceAddr_Sub;
	
	uint8_t		iID;
	uint8_t		iCtrl_Reg1;
	uint8_t		iCtrl_Reg2;
	uint8_t		iCtrl_Reg3;
	uint8_t		iCtrl_Reg4;
	uint8_t		iCtrl_Reg5;
	
	uint8_t		iReference;
	uint8_t		iTemperature;
	uint8_t		iStatus_Reg;

	uint8_t		iFIFO_Ctrl_Reg;
	uint8_t		iFIFO_Src_Reg;
	
	uint8_t		iINT1_Cfg_Reg;	
	uint8_t		iINT1_Dra_Reg;
	
	
	//uint16_t	iAV_X_buf[10];
	//uint16_t	iAV_Y_buf[10];
	//uint16_t	iAV_Z_buf[10];	

	uint16_t	iAV_X;
	uint16_t	iAV_Y;
	uint16_t	iAV_Z;	
	

	
	uint16_t	iTH_X;
	uint16_t	iTH_Y;
	uint16_t	iTH_Z;
	
}SE_L3G4200D_HandleTypeDef;


     //L3G4200D();
     //   L3G4200D(uint8_t address);

    void 			L3G4200D_initialize(SE_L3G4200D_HandleTypeDef *hGS);
     // bool testConnection();

		
		// WHO_AM_I register, read-only
    uint8_t 	L3G4200D_getDeviceID(SE_L3G4200D_HandleTypeDef *hGS);
		
		// CTRL_REG1 register, r/w
		void 			L3G4200D_setOutputDataRate(SE_L3G4200D_HandleTypeDef *hGS, uint16_t rate);
		uint16_t 	L3G4200D_getOutputDataRate(SE_L3G4200D_HandleTypeDef *hGS);
		void 			L3G4200D_setBandwidthCutOffMode(SE_L3G4200D_HandleTypeDef *hGS, uint8_t mode);
		uint8_t		L3G4200D_getBandwidthCutOffMode(SE_L3G4200D_HandleTypeDef *hGS);
		float 		L3G4200D_getBandwidthCutOff(SE_L3G4200D_HandleTypeDef *hGS);
		void 			L3G4200D_setPowerOn(SE_L3G4200D_HandleTypeDef *hGS,bool on);
		bool 			L3G4200D_getPowerOn(SE_L3G4200D_HandleTypeDef *hGS);
		void 			L3G4200D_setZEnabled(SE_L3G4200D_HandleTypeDef *hGS,bool enabled);
		bool 			L3G4200D_getZEnabled(SE_L3G4200D_HandleTypeDef *hGS);
		void 			L3G4200D_setYEnabled(SE_L3G4200D_HandleTypeDef *hGS,bool enabled);
		bool 			L3G4200D_getYEnabled(SE_L3G4200D_HandleTypeDef *hGS);
		void 			L3G4200D_setXEnabled(SE_L3G4200D_HandleTypeDef *hGS,bool enabled);
		bool 			L3G4200D_getXEnabled(SE_L3G4200D_HandleTypeDef *hGS);

		// CTRL_REG2 register, r/w
		void 			L3G4200D_setHighPassMode(SE_L3G4200D_HandleTypeDef *hGS,uint8_t mode);
		uint8_t 	L3G4200D_getHighPassMode(SE_L3G4200D_HandleTypeDef *hGS);
		void 			L3G4200D_setHighPassFilterCutOffFrequencyLevel(SE_L3G4200D_HandleTypeDef *hGS,uint8_t level);
		uint8_t 	L3G4200D_getHighPassFilterCutOffFrequencyLevel(SE_L3G4200D_HandleTypeDef *hGS);

		// CTRL_REG3 register, r/w
		void 			L3G4200D_setINT1InterruptEnabled(SE_L3G4200D_HandleTypeDef *hGS,bool enabled);
		bool 			L3G4200D_getINT1InterruptEnabled(SE_L3G4200D_HandleTypeDef *hGS);
		void 			L3G4200D_setINT1BootStatusEnabled(SE_L3G4200D_HandleTypeDef *hGS,bool enabled);
		bool 			L3G4200D_getINT1BootStatusEnabled(SE_L3G4200D_HandleTypeDef *hGS);
		void 			L3G4200D_interruptActiveINT1Config(SE_L3G4200D_HandleTypeDef *hGS,bool active_h);
		void 			L3G4200D_setOutputMode(SE_L3G4200D_HandleTypeDef *hGS,bool mode);
		bool 			L3G4200D_getOutputMode(SE_L3G4200D_HandleTypeDef *hGS);
		void 			L3G4200D_setINT2DataReadyEnabled(SE_L3G4200D_HandleTypeDef *hGS,bool enabled);
		bool 			L3G4200D_getINT2DataReadyEnabled(SE_L3G4200D_HandleTypeDef *hGS);
		void 			L3G4200D_setINT2FIFOWatermarkInterruptEnabled(SE_L3G4200D_HandleTypeDef *hGS,bool enabled);
		bool 			L3G4200D_getINT2FIFOWatermarkInterruptEnabled(SE_L3G4200D_HandleTypeDef *hGS);
		void 			L3G4200D_setINT2FIFOOverrunInterruptEnabled(SE_L3G4200D_HandleTypeDef *hGS,bool enabled);
		bool 			L3G4200D_getINT2FIFOOverrunInterruptEnabled(SE_L3G4200D_HandleTypeDef *hGS);
		void 			L3G4200D_setINT2FIFOEmptyInterruptEnabled(SE_L3G4200D_HandleTypeDef *hGS,bool enabled);
		bool 			L3G4200D_getINT2FIFOEmptyInterruptEnabled(SE_L3G4200D_HandleTypeDef *hGS);
		
		// CTRL_REG4 register, r/w
		void 			L3G4200D_setBlockDataUpdateEnabled(SE_L3G4200D_HandleTypeDef *hGS,bool enabled);
		bool 			L3G4200D_getBlockDataUpdateEnabled(SE_L3G4200D_HandleTypeDef *hGS);
		void 			L3G4200D_setEndianMode(SE_L3G4200D_HandleTypeDef *hGS,bool endianness);
		uint8_t		L3G4200D_getEndianMode(SE_L3G4200D_HandleTypeDef *hGS);
		void 			L3G4200D_setFullScale(SE_L3G4200D_HandleTypeDef *hGS,uint16_t scale);
		uint16_t 	L3G4200D_getFullScale(SE_L3G4200D_HandleTypeDef *hGS);
		void 			L3G4200D_setSelfTestMode(SE_L3G4200D_HandleTypeDef *hGS,uint8_t mode);
		uint8_t 	L3G4200D_getSelfTestMode(SE_L3G4200D_HandleTypeDef *hGS);
		void 			L3G4200D_setSPIMode(SE_L3G4200D_HandleTypeDef *hGS,bool mode);
		bool 			L3G4200D_getSPIMode(SE_L3G4200D_HandleTypeDef *hGS);

		// CTRL_REG5 register, r/w
		void 			L3G4200D_rebootMemoryContent(SE_L3G4200D_HandleTypeDef *hGS);
		void 			L3G4200D_setFIFOEnabled(SE_L3G4200D_HandleTypeDef *hGS,bool enabled);
		bool 			L3G4200D_getFIFOEnabled(SE_L3G4200D_HandleTypeDef *hGS);
		void 			L3G4200D_setHighPassFilterEnabled(SE_L3G4200D_HandleTypeDef *hGS,bool enabled);
		bool 			L3G4200D_getHighPassFilterEnabled(SE_L3G4200D_HandleTypeDef *hGS);
		void 			L3G4200D_setDataFilter(SE_L3G4200D_HandleTypeDef *hGS,uint8_t filter);
		uint8_t 	L3G4200D_getDataFilter(SE_L3G4200D_HandleTypeDef *hGS);
		
		// REFERENCE/DATACAPTURE register, r/w
		void 			L3G4200D_setInterruptReference(SE_L3G4200D_HandleTypeDef *hGS, uint8_t reference);
		uint8_t 	L3G4200D_getInterruptReference(SE_L3G4200D_HandleTypeDef *hGS);
		
		// OUT_TEMP register, read-only
		uint8_t 	L3G4200D_getTemperature(SE_L3G4200D_HandleTypeDef *hGS);

		// STATUS register, read-only
		bool			L3G4200D_getStatus(SE_L3G4200D_HandleTypeDef *hGS);
		
		//bool 			L3G4200D_getXYZOverrun(void);
		//bool 			L3G4200D_getZOverrun(void);
		//bool 			L3G4200D_getYOverrun(void);
		//bool 			L3G4200D_getXOverrun(void);
		//bool 			L3G4200D_getXYZDataAvailable(void);
		//bool 			L3G4200D_getZDataAvailable(void);
		//bool 			L3G4200D_getYDataAvailable(void);
		//bool 			L3G4200D_getXDataAvailable(void);

    // OUT_* registers, read-only
		void 			L3G4200D_getAngularVelocity(SE_L3G4200D_HandleTypeDef *hGS);
    int16_t 	L3G4200D_getAngularVelocityX(SE_L3G4200D_HandleTypeDef *hGS);
		int16_t 	L3G4200D_getAngularVelocityY(SE_L3G4200D_HandleTypeDef *hGS);
		int16_t 	L3G4200D_getAngularVelocityZ(SE_L3G4200D_HandleTypeDef *hGS);
		
		// FIFO_CTRL register, r/w
		void 			L3G4200D_setFIFOMode(SE_L3G4200D_HandleTypeDef *hGS,uint8_t mode);
		uint8_t 	L3G4200D_getFIFOMode(SE_L3G4200D_HandleTypeDef *hGS);
		void 			L3G4200D_setFIFOThreshold(SE_L3G4200D_HandleTypeDef *hGS,uint8_t wtm);
		uint8_t 	L3G4200D_getFIFOThreshold(SE_L3G4200D_HandleTypeDef *hGS);
		
		// FIFO_SRC register, read-only
		bool 			L3G4200D_isFIFOAtWatermark(SE_L3G4200D_HandleTypeDef *hGS);
		bool 			L3G4200D_isFIFOOverrun(SE_L3G4200D_HandleTypeDef *hGS);
		bool 			L3G4200D_isFIFOEmpty(SE_L3G4200D_HandleTypeDef *hGS);
		uint8_t 	L3G4200D_getFIFOStoredDataLevel(SE_L3G4200D_HandleTypeDef *hGS);
		
		// INT1_CFG register, r/w
		bool			L3G4200D_SetInterruptCFG(SE_L3G4200D_HandleTypeDef *hGS, uint8_t iIntCfg);
		//void 			L3G4200D_setInterruptCombination(bool combination);
		//bool 			L3G4200D_getInterruptCombination(void);
		//void 			L3G4200D_setInterruptRequestLatched(bool latched);
		//bool 			L3G4200D_getInterruptRequestLatched(void);
		//void 			L3G4200D_setZHighInterruptEnabled(bool enabled);
		//bool 			L3G4200D_getZHighInterruptEnabled(void);
		//void 			L3G4200D_setYHighInterruptEnabled(bool enabled);
		//bool 			L3G4200D_getYHighInterruptEnabled(void);
		//void 			L3G4200D_setXHighInterruptEnabled(bool enabled);
		//bool 			L3G4200D_getXHighInterruptEnabled(void);
		//void 			L3G4200D_setZLowInterruptEnabled(bool enabled);
		//bool 			L3G4200D_getZLowInterruptEnabled(void);
		//void 			L3G4200D_setYLowInterruptEnabled(bool enabled);
		//bool 			L3G4200D_getYLowInterruptEnabled(void);
		//void 			L3G4200D_setXLowInterruptEnabled(bool enabled);
		//bool 			L3G4200D_getXLowInterruptEnabled(void);

		// INT1_SRC register, read-only
		
		uint8_t		L3G4200D_getIntStatus(SE_L3G4200D_HandleTypeDef *hGS);
		
		//bool 			L3G4200D_getInterruptActive(void);
		//bool 			L3G4200D_getZHigh(void);
		//bool 			L3G4200D_getZLow(void);
		//bool 			L3G4200D_getYHigh(void);
		//bool 			L3G4200D_getYLow(void);
		//bool 			L3G4200D_getXHigh(void);
		//bool 			L3G4200D_getXLow(void);
		
		// INT1_THS_* registers, r/w
		bool			L3G4200D_setXYZThreshold(SE_L3G4200D_HandleTypeDef *hGS);
		bool			L3G4200D_getXYZThreshold(SE_L3G4200D_HandleTypeDef *hGS);
		
		//void 			L3G4200D_setXHighThreshold(uint8_t threshold);
		//uint8_t 	L3G4200D_getXHighThreshold(void);
		//void 			L3G4200D_setXLowThreshold(uint8_t threshold);
		//uint8_t 	L3G4200D_getXLowThreshold(void);
		//void 			L3G4200D_setYHighThreshold(uint8_t threshold);
		//uint8_t 	L3G4200D_getYHighThreshold(void);
		//void 			L3G4200D_setYLowThreshold(uint8_t threshold);
		//uint8_t 	L3G4200D_getYLowThreshold(void);
		//void 			L3G4200D_setZHighThreshold(uint8_t threshold);
		//uint8_t 	L3G4200D_getZHighThreshold(void);
		//void 			L3G4200D_setZLowThreshold(uint8_t threshold);
		//uint8_t 	L3G4200D_getZLowThreshold(void);

		// INT1_DURATION register, r/w
		void 			L3G4200D_setDuration(SE_L3G4200D_HandleTypeDef *hGS, uint8_t duration);
		uint8_t 	L3G4200D_getDuration(SE_L3G4200D_HandleTypeDef *hGS);
		void 			L3G4200D_setWaitEnabled(SE_L3G4200D_HandleTypeDef *hGS, bool enabled);
		bool 			L3G4200D_getWaitEnabled(SE_L3G4200D_HandleTypeDef *hGS);

#endif /* _L3G4200D_H_ */
