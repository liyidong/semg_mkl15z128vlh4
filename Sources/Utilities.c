/* ###################################################################
 **     THIS COMPONENT MODULE IS GENERATED BY USER
 **     Filename    : Utilities.c
 **     Project     : semg_mkl15z128vlh4
 **     Processor   : MKL15Z128VLH4
 **     Component   : 
 **     Version     : 
 **     Datasheet   : 
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2013-Jul 25, 2013, 7:28:29 PM, # CodeGen: 0
 **     Author	    : Dong
 **     Abstract    :
 **			This file contains general functions used in this project.
 **     Settings    :
 **
 **     Contents    :
 **         Delay             - void Delay1Us();
 **                           - LDD_TError DelayUs(uint32 n);
 **                           - LDD_TError DelayMs(uint32 n);
 **                           - LDD_TError DelayS(uint32 n);
 **                           - LDD_TError DelaySomeUs(uint32 n);
 **                           - LDD_TError DelaySomeMs(uint32 n);
 **                           - LDD_TError DelaySomeS(uint32 n);
 **         GetCurrentTime    - uint32 GetCurrentUs(void);
 **                           - uint32 GetCurrentMs(void);
 **                           - uint32 GetCurrentS(void);
 **         PrintErrorMessage - void PrintErrorMessage(LDD_TError err);
 **                         
 **                         
 **     mail      	: pzdongdong@163.com
 **
 **     Revision    : No.  Name        Data/Time        Content
 ** ###################################################################*/
/*!
 * @file Utilities.c
 * @version 01.00
 * @brief	
 *      This file contains general functions used in this project.
 */
/*!
 *  @addtogroup Uti Utilities
 *      This module contains general functions used in this project.
 *  @{
 */

/* Module Utilities */

/* {Default RTOS Adapter} No RTOS includes */
#include "Utilities.h"
#include "SysTick.h"
#include "SysTick_PDD.h"
#include "Aliases.h"
#include "Globals.h"
#include "limits.h"
#include "SysTick.h"
#include "Macros.h"
#include "PE_Error.h"
#include "stdio.h"
#include "string.h"

/* 
 * ===================================================================
 * Global Variables
 * ===================================================================
 */
volatile bool flagDelayed = FALSE;   /*!< Flag of delay status. */
extern volatile bool flagUartReceived;
extern volatile bool flagUartSent;

/*
 * ===================================================================
 *     Method      : Delay1Us(Module Utilities)
 */
/*!
 *     @brief
 *          This method delays 1us most precisely with assembly code.
 *          Error limit: +/-1%.
 */
/* ===================================================================*/
void Delay1Us()
{
    PE_NOP();
    PE_NOP();
    PE_NOP();
    PE_NOP();
    PE_NOP();
}

/*
 * ===================================================================
 *     Method      : DelayUs(Component SysTick)
 */
/*!
 *     @brief
 *          This method delays n us precisely with SysTick being the calculating
 *          the beats.
 *          Error limit: +/-0.001%.
 *     @param[in]
 *          n       - How many microseconds to delay.
 *     @return
 *                  - Error code.
 *                    See PE_Error.h and Macros.h for more detailed information.
 */
/* ===================================================================*/
LDD_TError DelayUs(uint32 n)
{
    if(n < MIN_DELAY_US || n > MAX_DELAY_US_PROCESSOR_CLOCK)
    {
        return ERR_PARAM_VALUE;     /* If the value is invalid, return error. */
    }
    SysTickWriteReloadValueReg(TICK_TO_US_PROCESSOR_CLOCK * (n - 4) - 1);      /* ReloadValueReg = Ticks/us - 1. 4 is a correction. */
    
    flagDelayed = FALSE;
    SysTickEnable();        /* Enable SysTick, start countdown. */
    while(!flagDelayed);    /* Wait. */
    
    return ERR_OK;
}

/*
 * ===================================================================
 *     Method      : DelayMs(Component SysTick)
 */
/*!
 *     @brief
 *          This method delays n Ms precisely with SysTick being the calculating
 *          the beats.
 *          Error limit: +/-0.001%.
 *     @param[in]
 *          n       - How many milliseconds to delay.
 *     @return
 *                  - Error code.
 *                    See PE_Error.h and Macros.h for more detailed information.
 */
/* ===================================================================*/
LDD_TError DelayMs(uint32 n)
{
    if(n > 300)      
    {   
        /* 
         * If delay time is more than 300ms, select external clock to allow longer delay.           
         * Processor clock allow a maximum delay of 349.525ms,
         * while external clock allow a maximum delay of 5.592s.
         */
        SysTickSetClockSource(SYSTICK_USE_EXTERNAL_CLOCK);
    }
    else    /* If delay time is less than 300ms, select processor clock for more precise delay. */
    {
        SysTickSetClockSource(SYSTICK_USE_PROCESSOR_CLOCK);
    }
    
    if(SysTickGetClockSource())     /* 1 - Processor Clock. */
    {
        if(n < MIN_DELAY_TIME || n > MAX_DELAY_MS_PROCESSOR_CLOCK)
        {
            return ERR_PARAM_VALUE;      /* If the value is invalid, return error. */
        }
        
        SysTickWriteReloadValueReg(TICK_TO_MS_PROCESSOR_CLOCK * n - TICK_TO_US_PROCESSOR_CLOCK * 4 - 1);      /* ReloadValueReg = Ticks/ms * n - 1. TICK_TO_US_CLOCK * 4 is a correction. */
    }
    else                            /* 0 - External Clock. */
    {
        if(n < MIN_DELAY_TIME || n > MAX_DELAY_MS_EXTERNAL_CLOCK)
        {
            return ERR_PARAM_VALUE;      /* If the value is invalid, return error. */
        }
        
        SysTickWriteReloadValueReg(TICK_TO_MS_EXTERNAL_CLOCK * n - TICK_TO_US_EXTERNAL_CLOCK * 4 - 1);
    }
    
    flagDelayed = FALSE;
    SysTickEnable();        /* Enable SysTick, start countdown. */
    while(!flagDelayed);    /* Wait. */
    SysTickSetClockSource(SYSTICK_USE_PROCESSOR_CLOCK);     /* Make sure processor clock is available before return. */
    
    return ERR_OK;
}

/*
 * ===================================================================
 *     Method      : DelayS(Component SysTick)
 */
/*!
 *     @brief
 *          This method delays n s with repeat a 1000ms delay in a loop which may
 *          not be that precisely.
 *          Error limit: +/-0.001%.
 *     @param[in]
 *          n       - How many seconds to delay.
 *     @return
 *                  - Error code.
 *                    See PE_Error.h and Macros.h for more detailed information.
 */
/* ===================================================================*/
LDD_TError DelayS(uint32 n)
{
    if(n < MIN_DELAY_TIME || n > ULONG_MAX)
    {
        return ERR_PARAM_VALUE;         /* If the value is invalid, return error. */
    }
    
    while(n > 0)
    {
        DelayMs(1000);
        n--;
    }
    
    return ERR_OK;
}

/*
 * ===================================================================
 *     Method      : DelaySomeUs(Module Utilities)
 */
/*!
 *     @brief
 *          This method delays n us roughly with codes calculating
 *          the time.
 *          Error limit: +4%.
 *     @param[in]
 *          n       - How many microseconds to delay.
 *     @return
 *                  - Error code.
 *                    See PE_Error.h and Macros.h for more detailed information.
 */
/* ===================================================================*/
LDD_TError DelaySomeUs(uint32 n)
{
    uint32 counter;
    
    if(n < MIN_DELAY_TIME || n > ULONG_MAX)
    {
        return ERR_PARAM_VALUE;         /* If the value is invalid, return error. */
    }
    
    counter = (PROCESSOR_CLOCK * n - 38) / 10;       /* Counters equal to n us. */
    
    for(; counter > 0; counter--);      /* Waiting. */
    
    return ERR_OK;
}

/*
 * ===================================================================
 *     Method      : DelaySomeMs(Module Utilities)
 */
/*!
 *     @brief
 *          This method delays n Ms roughly with codes calculating
 *          the time.
 *          Error limit: +4%.
 *     @param[in]
 *          n       - How many milliseconds to delay.
 *     @return
 *                  - Error code.
 *                    See PE_Error.h and Macros.h for more detailed information.
 */
/* ===================================================================*/
LDD_TError DelaySomeMs(uint32 n)
{
    uint32 counter;
    
    if(n < MIN_DELAY_TIME || n > ULONG_MAX)
    {
        return ERR_PARAM_VALUE;         /* If the value is invalid, return error. */
    }
    
    counter = (PROCESSOR_CLOCK * n * 1000 - 38) / 10;            /* Counters equal to n ms. */
    
    for(; counter > 0; counter--);      /* Waiting. */
    
    return ERR_OK;
}

/*
 * ===================================================================
 *     Method      : DelaySomeS(Module Utilities)
 */
/*!
 *     @brief
 *          This method delays n s roughly with codes calculating
 *          the time.
 *          Error limit: +4%.
 *     @param[in]
 *          n       - How many seconds to delay.
 *     @return
 *                  - Error code.
 *                    See PE_Error.h and Macros.h for more detailed information.
 */
/* ===================================================================*/
LDD_TError DelaySomeS(uint32 n)
{
    uint32 counter;
    
    if(n < MIN_DELAY_TIME || n > ULONG_MAX)
    {
        return ERR_PARAM_VALUE;         /* If the value is invalid, return error. */
    }
    
    counter = (PROCESSOR_CLOCK * n * 1000 * 1000 - 38) / 10;         /* Counters equal to n s. */
    
    for(; counter > 0; counter--);      /* Waiting. */
    
    return ERR_OK;
}

/*
 * ===================================================================
 *     Method      : GetCurrentUs(Module Utilities)
 */
/*!
 *     @brief
 *          This method returns the current value of total microseconds 
 *          since power on.         
 *     @return
 *                          - Total microseconds since power on.
 */
/* ===================================================================*/
uint32 GetCurrentUs(void)
{
    return 0;
}

/*
 * ===================================================================
 *     Method      : GetCurrentMs(Module Utilities)
 */
/*!
 *     @brief
 *          This method returns the current value of total milliseconds 
 *          since power on.         
 *     @return
 *                          - Total milliseconds since power on.
 */
/* ===================================================================*/
uint32 GetCurrentMs(void)
{    
    return 0;
}

/*
 * ===================================================================
 *     Method      : GetCurrentS(Module Utilities)
 */
/*!
 *     @brief
 *          This method returns the current value of total seconds since 
 *          power on.         
 *     @return
 *                          - Total seconds since power on.
 */
/* ===================================================================*/
uint32 GetCurrentS(void)
{
    return 0;
}

/*
 * ===================================================================
 *     Method      : //printfErrorMessage(Module Utilities)
 */
/*!
 *     @brief
 *          this method catches the error and print the right error message.
 *     @param[in]
 *          err             - The error occurred.           
 */
/* ===================================================================*/
void PrintErrorMessage(LDD_TError err)
{
#if DEBUG
    switch(err)
    {
    case ERR_OK:
        printf(ERR_MSG_OK);
        break;
    case ERR_SPEED:
        printf(ERR_MSG_SPEED);
        break;
    case ERR_RANGE:
        printf(ERR_MSG_RANGE);
        break;
    case ERR_VALUE:
        printf(ERR_MSG_VALUE);
        break;
    case ERR_OVERFLOW:
        printf(ERR_MSG_OVERFLOW);
        break;
    case ERR_MATH:
        printf(ERR_MSG_MATH);
        break;
    case ERR_ENABLED:
        printf(ERR_MSG_ENABLED);
        break;
    case ERR_DISABLED:
        printf(ERR_MSG_DISABLED);
        break;
    case ERR_BUSY:
        printf(ERR_MSG_BUSY);
        break;
    case ERR_NOTAVAIL:
        printf(ERR_MSG_NOTAVAIL);
        break;
    case ERR_RXEMPTY:
        printf(ERR_MSG_RXEMPTY);
        break;
    case ERR_TXFULL:
        printf(ERR_MSG_TXFULL);
        break;
    case ERR_BUSOFF:
        printf(ERR_MSG_BUSOFF);
        break;
    case ERR_OVERRUN:
        printf(ERR_MSG_OVERRUN);
        break;
    case ERR_FRAMING:
        printf(ERR_MSG_FRAMING);
        break;
    case ERR_PARITY:
        printf(ERR_MSG_PARITY);
        break;
    case ERR_NOISE:
        printf(ERR_MSG_NOISE);
        break;
    case ERR_IDLE:
        printf(ERR_MSG_IDLE);
        break;
    case ERR_FAULT:
        printf(ERR_MSG_FAULT);
        break;
    case ERR_BREAK:
        printf(ERR_MSG_BREAK);
        break;
    case ERR_CRC:
        printf(ERR_MSG_CRC);
        break;
    case ERR_ARBITR:
        printf(ERR_MSG_ARBITR);
        break;
    case ERR_PROTECT:
        printf(ERR_MSG_PROTECT);
        break;
    case ERR_UNDERFLOW:
        printf(ERR_MSG_UNDERFLOW);
        break;
    case ERR_UNDERRUN:
        printf(ERR_MSG_UNDERRUN);
        break;
    case ERR_COMMON:
        printf(ERR_MSG_COMMON);
        break;
    case ERR_LINSYNC:
        printf(ERR_MSG_LINSYNC);
        break;
    case ERR_FAILED:
        printf(ERR_MSG_FAILED);
        break;
    case ERR_QFULL:
        printf(ERR_MSG_QFULL);
        break;
//    case ERR_WRITE_FAILED:
//        printf(ERR_MSG_WRITE_FAILED);
        break;
    case ERR_PARAM_MASK:
        printf(ERR_MSG_PARAM_MASK);
        break;
    case ERR_PARAM_MODE:
        printf(ERR_MSG_PARAM_MODE);
        break;
    case ERR_PARAM_INDEX:
        printf(ERR_MSG_PARAM_INDEX);
        break;
    case ERR_PARAM_DATA:
        printf(ERR_MSG_PARAM_DATA);
        break;
    case ERR_PARAM_SIZE:
        printf(ERR_MSG_PARAM_SIZE);
        break;
    case ERR_PARAM_VALUE:
        printf(ERR_MSG_PARAM_VALUE);
        break;
    case ERR_PARAM_RANGE:
        printf(ERR_MSG_PARAM_RANGE);
        break;
    case ERR_PARAM_LOW_VALUE:
        printf(ERR_MSG_PARAM_LOW_VALUE);
        break;
    case ERR_PARAM_HIGH_VALUE:
        printf(ERR_MSG_PARAM_HIGH_VALUE);
        break;
    case ERR_PARAM_ADDRESS:
        printf(ERR_MSG_PARAM_ADDRESS);
        break;
    case ERR_PARAM_PARITY:
        printf(ERR_MSG_PARAM_PARITY);
        break;
    case ERR_PARAM_WIDTH:
        printf(ERR_MSG_PARAM_WIDTH);
        break;
    case ERR_PARAM_LENGTH:       
        printf(ERR_MSG_PARAM_LENGTH);
        break;
    case ERR_PARAM_ADDRESS_TYPE:
        printf(ERR_MSG_PARAM_ADDRESS_TYPE);
        break;
    case ERR_PARAM_COMMAND_TYPE:
        printf(ERR_MSG_PARAM_COMMAND_TYPE);
        break;
    case ERR_PARAM_COMMAND:
        printf(ERR_MSG_PARAM_COMMAND);
        break;
    case ERR_PARAM_RECIPIENT:
        printf(ERR_MSG_PARAM_RECIPIENT);
        break;
    case ERR_PARAM_BUFFER_COUNT:
        printf(ERR_MSG_PARAM_BUFFER_COUNT);
        break;
    case ERR_PARAM_ID:
        printf(ERR_MSG_PARAM_ID);
        break;
    case ERR_PARAM_GROUP:
        printf(ERR_MSG_PARAM_GROUP);
        break;
    case ERR_PARAM_CHIP_SELECT:
        printf(ERR_MSG_PARAM_CHIP_SELECT);
        break;
    case ERR_PARAM_ATTRIBUTE_SET:
        printf(ERR_MSG_PARAM_ATTRIBUTE_SET);
        break;
    case ERR_PARAM_SAMPLE_COUNT:
        printf(ERR_MSG_PARAM_SAMPLE_COUNT);
        break;
    case ERR_PARAM_CONDITION:
        printf(ERR_MSG_PARAM_CONDITION);
        break;
    case ERR_PARAM_TICKS:
        printf(ERR_MSG_PARAM_TICKS);
        break;
    default:
        printf(ERR_MSG_UNKNOWN);
        break;
    }
#endif  /* #if DEBUG */
}

/* End Utilities */

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


