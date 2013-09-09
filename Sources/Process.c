/* ###################################################################
 **     THIS COMPONENT MODULE IS GENERATED BY USER
 **     Filename    : Process.h
 **     Project     : semg_mkl15z128vlh4
 **     Processor   : MKL15Z128VLH4
 **     Component   : 
 **     Version     : 
 **     Datasheet   : 
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2013-Aug 5, 2013, 8:54:36 PM, # CodeGen: 1
 **     Author      : Dong
 **     Abstract    :
 **         This file contains functions for kinds of data processing.
 **     Settings    :
 **
 **     Contents    :
 **         Process         - void Process(void);
 **         SplitRawData    - LDD_TError SplitRawData(TADCDataPtr adcDataPtr);
 **     mail        : pzdongdong@163.com
 **
 **     Revision    : No.  Name        Data/Time        Content
 ** ###################################################################*/
/*!
 * @file Process.h
 * @version 01.00
 * @brief   
 *      This file contains functions for kinds of data processing.
 */
/*!
 *  @addtogroup Proc Process module documentation
 *      This module contains functions for kinds of data processing.
 *  @{
 */

/* Module Process */

/* {Default RTOS Adapter} No RTOS includes */
#include "PE_Error.h"
#include "PE_Types.h"
#include "Macros.h"
#include "Utilities.h"

/*
 * ===================================================================
 *     Method      : Process(Module Process)
 */
/*!
 *     @brief
 *         	The primary routine of processing the data.
 */
/* ===================================================================*/
void Process(void)
{
    
}

/*
 * ===================================================================
 *     Method      : SplitRawData(Module Process)
 */
/*!
 *     @brief
 *         	This method splits the ADC raw data to each part of the ADC data
 *         	structure.
 *     @param[in]
 *         	adcDataPtr      - Pointer to ADC data structure.
 *     @return
 *         	                - ERR_PARAM_DATA: The head byte of the raw is not valid,
 *         	                                  so the data is invalid.
 *         	                - ERR_OK: Succeeded to split.
 */
/* ===================================================================*/
LDD_TError SplitRawData(TADCDataPtr adcDataPtr)
{
    LDD_TError err;
    uint8 i;
    byte head;
    byte loffStatP;
    byte loffStatN;
    byte regGPIOData;
    int16 channelData;
    
    head = ((adcDataPtr->rawData[0] & 0xF0) >> 4) & 0x0F;       /* Split head byte from raw data. */
    if(head != RAW_DATA_HEAD)                                   /* If the head byte is not right(0x0C), return with error. */
    {
        err = ERR_PARAM_DATA;
        PrintErrorMessage(err);
        return err;
    }
    
    loffStatP  = ((byte)(adcDataPtr->rawData[0] & 0x0F) << 4) & 0xF0;
    loffStatP |= ((byte)(adcDataPtr->rawData[1] & 0xF0) >> 4) & 0x0F;
    
    loffStatN  = ((byte)(adcDataPtr->rawData[1] & 0x0F) << 4) & 0xF0;
    loffStatN |= ((byte)(adcDataPtr->rawData[2] & 0xF0) >> 4) & 0x0F;
    
    regGPIOData =  (byte)adcDataPtr->rawData[2] & 0x0F;
    
    for(i = 0; i < USING_CHANNEL_NUMBER * BYTE_NUMBER_PER_CHANNEL; i += 2)    /* Every channel's data is 2 Bytes. */
    {
        channelData = ((int16)adcDataPtr->rawData[RAW_DATA_HEAD_SIZE + i] << 8) & 0xFF00;
        channelData |= (int16)adcDataPtr->rawData[RAW_DATA_HEAD_SIZE + i + 1] & 0x00FF;
        adcDataPtr->channelData[i / 2] = (int16)channelData;
    }
    
    adcDataPtr->head = (byte)head;
    adcDataPtr->loffStatP = (byte)loffStatP;
    adcDataPtr->loffStatN = (byte)loffStatN;
    adcDataPtr->regGPIOData = (byte)regGPIOData;
    
    return ERR_OK;
}

/* End Process */

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

