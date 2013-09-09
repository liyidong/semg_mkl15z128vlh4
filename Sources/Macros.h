/* ###################################################################
 **     THIS COMPONENT MODULE IS GENERATED BY USER.
 **     Filename    : Macros.h
 **     Project     : semg_mkl15z128vlh4
 **     Processor   : MKL15Z128VLH4
 **     Component   : 
 **     Version     : 
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2013-07-12, 12:30, # CodeGen: 0
 **     Author	    : Dong
 **     Abstract    :
 **          This file contains user macros used in this project.
 **
 **     
 **     mail      	: pzdongdong@163.com
 **     
 **     Revision    : No.  Name        Date/Time        Content
 ** ###################################################################*/
/*!
 * @file Macros.h
 * @version 01.00
 * @brief
 *      This file contains user macros used in this project.
 *          
 */
/*!
 *  @addtogroup UserMacros User Macros
 *      This module contains user macros used in this project.
 *  @{
 */

#ifndef MACROS_H_
#define MACROS_H_
/* MODULE USER MACROS */

#include "Settings.h"

/* 
 * ===================================================================
 * User Macros Definition
 * ===================================================================
 */

    /* 
     * ===================================================================
     * System Constants
     * ===================================================================
     */
    /*!
     * @addtogroup SysConst System Constants
     * @{
     */
#if USING_MKL15Z128VLH4
#define PROCESSOR_CLOCK              48U                                /*!< Processor clock frequence is 48MHz. */
#define MIN_SYSTICK_VALUE            0x01U                              /*!< Minimum value of the SysTick value register. */
#define MAX_SYSTICK_VALUE            0xFFFFFFU                          /*!< Maximum value of the SysTick value register. */
#define TICK_TO_US_PROCESSOR_CLOCK   48U                                /*!< 48 ticks equals to 1us, when using processor clock(48MHz). */
#define TICK_TO_US_EXTERNAL_CLOCK    3U                                 /*!< 3 ticks equals to 1us, when using external clock(3MHz). */
#define TICK_TO_MS_PROCESSOR_CLOCK   48000U                             /*!< 4800 ticks equals to 1ms, when using processor clock(48MHz). */
#define TICK_TO_MS_EXTERNAL_CLOCK    3000U                              /*!< 3000 ticks equals to 1ms, when using external clock(3MHz). */
#define SYSTICK_USE_PROCESSOR_CLOCK  SysTick_PDD_CORE_CLOCK             /*!< SysTick uses processor clock. */
#define SYSTICK_USE_EXTERNAL_CLOCK   SysTick_PDD_CORE_CLOCK_DIV16       /*!< SysTick uses external clock. */
#define MIN_DELAY_US                 5U                                 /*!< Minimum microseconds to delay when using SysTick. */
#define MIN_DELAY_TIME               1U                                 /*!< Minimum delay time is 1us/ms/s. */
#if PROCESSOR_CLOCK == 48U
#define MAX_DELAY_US_PROCESSOR_CLOCK 349525U                            /*!< Maximum delay microseconds of a 48MHz is 349525us. */
#define MAX_DELAY_MS_PROCESSOR_CLOCK 349U                               /*!< Maximum delay milliseconds of a 48MHz is 349ms. */
#define MAX_DELAY_MS_EXTERNAL_CLOCK  5592U                              /*!< Maximum delay milliseconds of a 3MHz is 5592ms. */
#endif  /* #if PROCESSOR_CLOCK ==48U */
#endif  /* #if USING_MKL15Z128VLH4 */
    /*!
     * @}
     */
    /*!
     * @addtogroup ADCConst ADC Constants
     * @{
     */
#if USING_ADS1198
#define USING_CHANNEL_NUMBER         0x08U                                              /*!< Number of ADC channels used currently. */
#define MIN_CHANNEL_NUMBER           0x00U                                              /*!< Minimum number of ADC channels. */
#define MAX_CHANNEL_NUMBER           0x08U                                              /*!< Maximum number of ADC channels. */
#define MIN_REGISTER_READ_NUMBER     0x01U                                              /*!< Minimum number of registers to be read. */
#define MAX_REGISTER_READ_NUMBER     0x20U                                              /*!< Maxmimum number of registers to be read. */
#define RAW_DATA_HEAD_SIZE           0x03U                                              /*!< Head size of raw data from ADC. */
#define RAW_DATA_SIZE                RAW_DATA_HEAD_SIZE + USING_CHANNEL_NUMBER * 2      /*!< Size of raw data = 3Bytes + USING_CHANNEL_NUMBER * 2Bytes. */
#define RAW_DATA_HEAD                0x0CU                                              /*!< The first 4 bits of right ADC raw data is always 0b1100. */
#define BYTE_NUMBER_PER_CHANNEL      0x02U                                              /*!< The number of bytes per channel's data. */
#endif  /* #if USING_ADS1198 */
    /*!
     * @}
     */
    /* 
     * ===================================================================
     * ADC Commands and Registers Map
     * ===================================================================
     */
    /*!
     * @addtogroup ADCCmdReg ADC Commands and Registers Map 
     * @{
     */
        /*!
         * @addtogroup ADCCmd ADC Commands
         * @{
         */
#if USING_ADS1198

#define ADC_CMD_WAKEUP            0x02U 
#define ADC_CMD_STANDBY           0x04U
#define ADC_CMD_RESET             0x06U
#define ADC_CMD_START             0x08U
#define ADC_CMD_STOP              0x0aU
#define ADC_CMD_RDATAC            0x10U             /*!< ADC runs in Read Data Continuous mode. */
#define ADC_CMD_SDATAC            0x11U             /*!< Cancel RDATAC mode. */
#define ADC_CMD_RDATA             0x12U             /*!< If in SDATAC mode, read data from ADC when ~DRDY goes low. */
#define ADC_CMD_RREG(reg_addr)    0x20U + reg_addr  /*!< reg_addr - The starting address the registers to be read. */
#define ADC_CMD_WREG(reg_addr)    0x40U + reg_addr  /*!< reg_addr - The starting address the registers to be write. */
        /*!
         * @}
         */
        /*!
         * @addtogroup ADCReg ADC Registers 
         * @{
         */
            /*!
             * @addtogroup DevSet Device Settings 
             * @{
             */
#define ADC_REG_ID         0X00     /*!< Read-only register. */
            /*!
             * @}
             */
            /*!
             * @addtogroup GblSet Global Settings Across Channels 
             * @{
             */
#define ADC_REG_CONFIG1    0x01U
#define ADC_REG_CONFIG2    0x02U
#define ADC_REG_CONFIG3    0x03U
#define ADC_REG_LOFF       0x04U
            /*!
             * @}
             */
            /*!
             * @addtogroup  ChnSet Channel-Specific Settings
             * @{
             */
#define ADC_REG_CH1SET     0x05U
#define ADC_REG_CH2SET     0x06U
#define ADC_REG_CH3SET     0x07U
#define ADC_REG_CH4SET     0x08U
#define ADC_REG_CH5SET     0x09U    /*!< Not available for the ADS1194. */
#define ADC_REG_CH6SET     0x0AU    /*!< Not available for the ADS1194. */
#define ADC_REG_CH7SET     0x0BU    /*!< Not available for the ADS1194 and ADS1196. */
#define ADC_REG_CH8SET     0x0CU    /*!< Not available for the ADS1194 and ADS1196. */
#define ADC_REG_RLD_SENSP  0x0DU    /*!< Bits[7:4] are not available for the ADS1194. Bits[7:6] are not available for the ADS1196. */
#define ADC_REG_RLD_SENSN  0x0EU    /*!< Bits[7:4] are not available for the ADS1194. Bits[7:6] are not available for the ADS1196. */
#define ADC_REG_LOFF_SENSP 0x0FU    /*!< Bits[7:4] are not available for the ADS1194. Bits[7:6] are not available for the ADS1196. */
#define ADC_REG_LOFF_SENSN 0x10U    /*!< Bits[7:4] are not available for the ADS1194. Bits[7:6] are not available for the ADS1196. */
#define ADC_REG_LOFF_FLIP  0x11U
            /*!
             * @}
             */
            /*!
             * @addtogroup  LOFFStatReg Lead-Off Status Registers
             * @{
             */
#define ADC_REG_LOFF_STATP 0x12U    /*!< Read-only register. */
#define ADC_REG_LOFF_STATN 0x13U    /*!< Read-only register. */
            /*!
             * @}
             */
            /*!
             * @addtogroup  GPIO_Oth GPIO and OTHER Registers
             *      Address 16h is reserved.
             * @{
             */
#define ADC_REG_GPIO       0x14U
#define ADC_REG_PACE       0x15U
/* #define ADC_REG_RESERVED   0x16U */  /* Reserved. */
#define ADC_REG_CONFIG4    0x17U
#define ADC_REG_WCT1       0x18U
#define ADC_REG_WCT2       0x19U

#endif /* #if USING_ADS1198 */
            /*!
             * @}
             */
        /*!
         * @}
         */
    /*!
     * @}
     */

/* 
 * ===================================================================
 * User Type Definition
 * ===================================================================
 */
/*!
 * A structure of channel data from ADC. 
 * 
   @verbatim
   ---------------------------------------------------------------------------------------------------------
   |  Head   |   LOFF_STATP    |   LOFF_STATN    |GPIO[4:7]|                  CH[1-8] Data                 |
   ---------------------------------------------------------------------------------------------------------
   | 1 1 0 0 | x x x x x x x x | x x x x x x x x | x x x x | CH1 | CH2 | CH3 | CH4 | CH5 | CH6 | CH7 | CH8 |
   ---------------------------------------------------------------------------------------------------------
   |                        3Bytes                         |                  8*2=16Bytes                  |
   ---------------------------------------------------------------------------------------------------------
  
   -----------------------------------------------------------------
   | M |                       CHn Data                        | L |
   -----------------------------------------------------------------
   |1 5|1 4|1 3|1 2|1 1|1 0| 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
   -----------------------------------------------------------------
   | x | x | x | x | x | x | x | x | x | x | x | x | x | x | x | x |
   -----------------------------------------------------------------
   |             1Byte             |             1Byte             |
   -----------------------------------------------------------------
   @endverbatim
 */
struct TADCData
{
    byte  head;                                     /*!< The head bits of data should always be 0b00001100. */
    byte  loffStatP;                                /*!< The value of the register LOFF_STATP. */
    byte  loffStatN;                                /*!< The value of the register LOFF_STATN. */
    byte  regGPIOData;                              /*!< The value of bit[4-7] of the register GPIO. */
    byte  rawData[RAW_DATA_SIZE];                   /*!< The raw data from ADC, including status bytes. */
    int16 channelData[USING_CHANNEL_NUMBER];        /*!< The value of every channel's data, transformed from raw data. */
};
typedef struct TADCData TADCData;
typedef struct TADCData* TADCDataPtr; 

/* 
 * ===================================================================
 * Error Message
 * ===================================================================
 */

    /*!
     * @addtogroup ErrMsg Error Message
     * @{
     */
#if DEBUG
#define ERR_MSG_OK                   "OK.\n"
#define ERR_MSG_SPEED                "This device does not work in the active speed mode.\n"
#define ERR_MSG_RANGE                "Parameter out of range.\n"
#define ERR_MSG_VALUE                "Parameter of incorrect value.\n"
#define ERR_MSG_OVERFLOW             "Timer overflow.\n"
#define ERR_MSG_MATH                 "Overflow during evaluation.\n"
#define ERR_MSG_ENABLED              "Device is enabled.\n"
#define ERR_MSG_DISABLED             "Device is disabled.\n"
#define ERR_MSG_BUSY                 "Device is busy.\n"
#define ERR_MSG_NOTAVAIL             "Requested value or method not available.\n"
#define ERR_MSG_RXEMPTY              "No data in receiver.\n"
#define ERR_MSG_TXFULL               "Transmitter is full.\n"
#define ERR_MSG_BUSOFF               "Bus not available.\n"
#define ERR_MSG_OVERRUN              "Overrun error is detected.\n"
#define ERR_MSG_FRAMING              "Framing error is detected.\n"
#define ERR_MSG_PARITY               "Parity error is detected.\n"
#define ERR_MSG_NOISE                "Noise error is detected.\n"
#define ERR_MSG_IDLE                 "Idle error is detected.\n"
#define ERR_MSG_FAULT                "Fault error is detected.\n"
#define ERR_MSG_BREAK                "Break char is received during communication.\n"
#define ERR_MSG_CRC                  "CRC error is detected.\n"
#define ERR_MSG_ARBITR               "A node losts arbitration. This error occurs if two nodes start transmission at the same time.\n"
#define ERR_MSG_PROTECT              "Protection error is detected.\n"
#define ERR_MSG_UNDERFLOW            "Underflow error is detected.\n"
#define ERR_MSG_UNDERRUN             "Underrun error is detected.\n"
#define ERR_MSG_COMMON               "Common error of a device.\n"
#define ERR_MSG_LINSYNC              "LIN synchronization error is detected.\n"
#define ERR_MSG_FAILED               "Requested functionality or process failed.\n"
#define ERR_MSG_QFULL                "Queue is full.\n"
#define ERR_MSG_WRITE_FAILED         "Fail to write data.\n"
#define ERR_MSG_PARAM_MASK           "Invalid mask.\n"
#define ERR_MSG_PARAM_MODE           "Invalid mode.\n"
#define ERR_MSG_PARAM_INDEX          "Invalid index.\n"
#define ERR_MSG_PARAM_DATA           "Invalid data.\n"
#define ERR_MSG_PARAM_SIZE           "Invalid size.\n"
#define ERR_MSG_PARAM_VALUE          "Invalid value.\n"
#define ERR_MSG_PARAM_RANGE          "Invalid parameter's range or parameters' combination.\n"
#define ERR_MSG_PARAM_LOW_VALUE      "Invalid value (LOW part).\n"
#define ERR_MSG_PARAM_HIGH_VALUE     "Invalid value (HIGH part).\n"
#define ERR_MSG_PARAM_ADDRESS        "Invalid address.\n"
#define ERR_MSG_PARAM_PARITY         "Invalid parity.\n"
#define ERR_MSG_PARAM_WIDTH          "Invalid width.\n"
#define ERR_MSG_PARAM_LENGTH         "Invalid length.\n"
#define ERR_MSG_PARAM_ADDRESS_TYPE   "Invalid address type.\n"
#define ERR_MSG_PARAM_COMMAND_TYPE   "Invalid command type.\n"
#define ERR_MSG_PARAM_COMMAND        "Invalid command.\n"
#define ERR_MSG_PARAM_RECIPIENT      "Invalid recipient.\n"
#define ERR_MSG_PARAM_BUFFER_COUNT   "Invalid buffer count.\n"
#define ERR_MSG_PARAM_ID             "Invalid ID.\n"
#define ERR_MSG_PARAM_GROUP          "Invalid group.\n"
#define ERR_MSG_PARAM_CHIP_SELECT    "Invalid chip select.\n"
#define ERR_MSG_PARAM_ATTRIBUTE_SET  "Invalid set of attributes.\n"
#define ERR_MSG_PARAM_SAMPLE_COUNT   "Invalid sample count.\n"
#define ERR_MSG_PARAM_CONDITION      "Invalid condition.\n"
#define ERR_MSG_PARAM_TICKS          "Invalid ticks parameter.\n"
#define ERR_MSG_UNKNOWN              "Unknown error.\n"
#endif  /* #if DEBUG */
    /*!
     * @}
     */

    /* END Macros. */

#endif
/* #ifndef MACROS_H_ */

/*!
 * @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Dong
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
