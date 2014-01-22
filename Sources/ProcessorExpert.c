/* ###################################################################
 **     Filename    : ProcessorExpert.c
 **     Project     : semg_mkl15z128vlh4
 **     Processor   : MKL15Z128VLH4
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2013-07-11, 23:27, # CodeGen: 0
 **     Abstract    :
 **         Main module.
 **         This module contains user's application code.
 **     Settings    :
 **     Contents    :
 **         No public methods
 **
 **     Mail        : pzdongdong@163.com
 **
 **     Revision    : No.  Name        Date/Time        Content
 ** ###################################################################*/
/*!
 ** @file ProcessorExpert.c
 ** @version 01.01
 ** @brief
 **         Main module.
 **         This module contains user's application code.
 */
/*!
 **  @addtogroup ProcessorExpert_module ProcessorExpert module documentation
 **  @{
 */
/* MODULE ProcessorExpert */

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "SM_SPI1.h"
#include "SS_SPI0.h"
#include "CsIO_UART2.h"
#include "IO2.h"
#include "SysTick.h"
#include "BitIO_NOT_PWDN.h"
#include "BitIO_NOT_RESET.h"
#include "BitIO_START.h"
#include "BitIO_DAISY_IN.h"
#include "BitIO_CLKSEL.h"
#include "EINT_NOT_DRDY.h"
#include "EINT_SYNC_INT.h"
#include "DMAT_M_SPI_TX.h"
#include "DMA_CTRL.h"
#include "DMAT_M_SPI_RX.h"
#include "DMAT_S_SPI_TX.h"
#include "DMAT_S_SPI_RX.h"
#include "BitIO_UPRDY.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#include "SPI_PDD.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "MyHeaders.h"

/*
 * ===================================================================
 * Macros
 * ===================================================================
 */
//const int MSG_SIZE = 2000;

/*
 * ===================================================================
 * Global Variables
 * ===================================================================
 */
//volatile byte* uploadBufferPtr = NULL;
//volatile byte msg[MSG_SIZE] = {0};
//volatile byte msg2[MSG_SIZE] = {0};

/*
 * ===================================================================
 * Main Function
 * ===================================================================
 */
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
    /* Write your local variable definition here */
    extern TADCPtr tADCPtr[USING_ADC_COUNT];
    extern TMCUPtr tMCUPtr;
    extern TARMPtr tARMPtr;
    byte cmd;
    //byte reg;
    byte regVal[25] = {0};
    //byte dummy[MSG_SIZE];
    bool flag1 = TRUE;
    uint16 i;

    /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
    PE_low_level_init();
    /*** End of Processor Expert internal initialization.                    ***/

    /* Write your code here */
    /* For example: for(;;) { } */

    /* Initialize on-chip and peripheral devices */
#if DEBUG
    GPIOTest();
    printf("+UserInit begins...\n");
#endif
    UserInit();
#if DEBUG
    printf("-UserInit finished.\n");
#endif

#if DEBUG
    GPIOTest();
#endif

//    for(i = 0; i < MSG_SIZE; i++)
//    {
//        msg[i] = 0xAAU;
//        msg2[i] = 0xBBU;
//    }
//    msg[MSG_SIZE - 1] = 0x01U;
//    msg2[MSG_SIZE - 1] = 0x20U;



    cmd = ADC_CMD_SDATAC;
    ADCSendCommand(&cmd);
    while(!tMCUPtr->mcuStatus.isSPI1RxDMATransCompleted && !tMCUPtr->mcuStatus.isSPI1TxDMATransCompleted);
    tMCUPtr->mcuStatus.isSPI1TxDMATransCompleted = FALSE;
    tMCUPtr->mcuStatus.isSPI1RxDMATransCompleted = FALSE;

    for(;;)
    {
        cmd = ADC_REG_ID;
        ADCReadRegister(cmd, regVal, 1);
        while(!tMCUPtr->mcuStatus.isSPI1RxDMATransCompleted && !tMCUPtr->mcuStatus.isSPI1TxDMATransCompleted);
        tMCUPtr->mcuStatus.isSPI1TxDMATransCompleted = FALSE;
        tMCUPtr->mcuStatus.isSPI1RxDMATransCompleted = FALSE;
        printf("ID: %#x\t", regVal[0]);

        cmd = ADC_REG_CONFIG3;
        regVal[0] = 0x60U;
        ADCWriteRegister(cmd, regVal, 1);
        while(!tMCUPtr->mcuStatus.isSPI1RxDMATransCompleted && !tMCUPtr->mcuStatus.isSPI1TxDMATransCompleted);
        tMCUPtr->mcuStatus.isSPI1TxDMATransCompleted = FALSE;
        tMCUPtr->mcuStatus.isSPI1RxDMATransCompleted = FALSE;
        ADCReadRegister(cmd, regVal, 1);
        while(!tMCUPtr->mcuStatus.isSPI1RxDMATransCompleted && !tMCUPtr->mcuStatus.isSPI1TxDMATransCompleted);
        tMCUPtr->mcuStatus.isSPI1TxDMATransCompleted = FALSE;
        tMCUPtr->mcuStatus.isSPI1RxDMATransCompleted = FALSE;
        printf("CONFIG3: %#x\n", regVal[0]);
    }
    for(;;);

//
//    regVal[0] = 0x10U;
//    regVal[1] = 0x10U;
//    regVal[2] = 0x10U;
//    regVal[3] = 0x10U;
//    regVal[4] = 0x10U;
//    regVal[5] = 0x10U;
//    regVal[6] = 0x10U;
//    regVal[7] = 0x10U;
//    ADCWriteRegister(ADC_REG_CH1SET, regVal, 8);
//    for(i = 0; i < 8; i++)
//    {
//        regVal[i] = 0x00U;
//    }
////    for(;;)
//    ADCReadRegister(ADC_REG_CH1SET, regVal, 8);
//    printf("%#x, %#x, %#x, %#x, %#x, %#x, %#x, %#x\n", regVal[0], regVal[1], regVal[2], regVal[3], regVal[4], regVal[5], regVal[6], regVal[7]);


    cmd = ADC_CMD_RDATAC;
    ADCSendCommand(&cmd);

    EIntNotReadyEnable(EINT_NOT_DRDY);
    EIntSyncInterruptEnable(EINT_SYNC_INT);

    cmd = ADC_CMD_START;
    ADCSendCommand(&cmd);

    for(;;)
    {
        /* If data of ADC is ready, read it. */
        if(tADCPtr[0]->adcStatus.isDataReady)
        {
            if(!tMCUPtr->mcuStatus.isReceivingADCData && tMCUPtr->mcuStatus.isSPI1RxDMATransCompleted)
            {
                ADCReadContinuousData(tADCPtr[0]->adcData.rawData, RAW_DATA_SIZE);
                tMCUPtr->mcuStatus.isReceivingADCData = TRUE;
                tMCUPtr->mcuStatus.isSPI1RxDMATransCompleted = FALSE;
            }
            if(tMCUPtr->mcuStatus.isSPI1RxDMATransCompleted)
            {
                tMCUPtr->mcuStatus.isReceivingADCData = FALSE;
                SplitRawData(&(tADCPtr[0]->adcData));
                printf("%#x %#x %#x %#x | %#x %#x %#x %#x %#x %#x %#x %#x\n", tADCPtr[0]->adcData.head, tADCPtr[0]->adcData.loffStatP,
                                                                                tADCPtr[0]->adcData.loffStatN, tADCPtr[0]->adcData.regGPIOData,
                                                                                tADCPtr[0]->adcData.channelData[0], tADCPtr[0]->adcData.channelData[1],
                                                                                tADCPtr[0]->adcData.channelData[2], tADCPtr[0]->adcData.channelData[3],
                                                                                tADCPtr[0]->adcData.channelData[4], tADCPtr[0]->adcData.channelData[5],
                                                                                tADCPtr[0]->adcData.channelData[6], tADCPtr[0]->adcData.channelData[7]);
                tADCPtr[0]->adcStatus.isDataReady = FALSE;
            }
        }


        /*  If the ARM requires data, transmit. */
        if(tARMPtr->armStatus.isRequiringData && tMCUPtr->mcuStatus.isSPI0TxDMATransCompleted)
        {
            tARMPtr->armStatus.isRequiringData = FALSE;
            tMCUPtr->mcuStatus.isSPI0TxDMATransCompleted = FALSE;
            IOUploadReadyClrVal();
            if(flag1)
            {
//                SPI0ReceiveSendData((LDD_DMA_TAddress)msg, (LDD_DMA_TAddress)dummy,
//                                    (LDD_DMA_TByteCount)MSG_SIZE, (LDD_DMA_TByteCount)MSG_SIZE);
                flag1 = FALSE;
            }
            else
            {
//                SPI0ReceiveSendData((LDD_DMA_TAddress)msg2, (LDD_DMA_TAddress)dummy,
//                                    (LDD_DMA_TByteCount)MSG_SIZE, (LDD_DMA_TByteCount)MSG_SIZE);
                flag1 = TRUE;
            }
        }
    }

    /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END ProcessorExpert */
/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.2 [05.06]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
