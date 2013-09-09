/* ###################################################################
 **     THIS COMPONENT MODULE IS GENERATED BY USER
 **     Filename    : Test.c
 **     Project     : semg_mkl15z128vlh4
 **     Processor   : MKL15Z128VLH4
 **     Component   : 
 **     Version     : 
 **     Datasheet   : 
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2013-07-12, 23:38, # CodeGen: 0
 **     Author	    : Dong
 **     Abstract    :
 **			This file contains test functions.
 **     Settings    :
 **
 **     Contents    :
 **     			        
 **         
 **     mail      	: pzdongdong@163.com
 **     
 **     Revision    : No.  Name        Date/Time        Content
 ** ###################################################################*/
/*!
 * @file Test.c
 * @version 01.00
 * @brief	
 * 		This file contains test functions.
 */         
/*!
 *  @addtogroup Test_module	Test module documentation
 *      This module contains test functions.
 *  @{
 */         

/* MODULE Test. */

/* {Default RTOS Adapter} No RTOS includes */
#include "SM_SPI1.h"
#include "SS_SPI0.h"
#include "BitIO_NOT_PWDN.h"
#include "BitIO_NOT_RESET.h"
#include "BitIO_START.h"
#include "BitIO_DAISY_IN.h"
#include "BitIO_CLKSEL.h"
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Events.h"
#include "Cpu.h"

#include "Aliases.h"
#include "Globals.h"
#include "Init.h"
#include "Macros.h"
#include "Settings.h"

/* 
 * ===================================================================
 * Global Variables
 * ===================================================================
 */
extern volatile bool flagUartReceived;
extern volatile bool flagUartSent;

/*
 * ===================================================================
 *     Method      :  GPIOTest (Component GPIO)
 */
/*!
 *     @brief
 *          Test and output GPIO level via UART. 
 */
/* ===================================================================*/
void GPIOTest(void)
{
	if(IOStartGetVal())
	{
		printf("START: 1\n");
	}
	else
	{
		printf("START: 0\n");
	}
	
	if(IODaisyInGetVal())
	{
		printf("DAISY_IN: 1\n");
	}
	else
	{
		printf("DAISY_IN: 0\n");
	}
	
	if(IOClockSelectGetVal())
	{
		printf("CLKSEL: 1\n");
	}
	else
	{
		printf("CLKSEL: 0\n");
	}
	
	if(IONotPowerDownGetVal())
	{
		printf("~PWDN: 1\n");
	}
	else
	{
		printf("~PWDN: 0\n");
	}
	
	if(IONotResetGetVal())
	{
		printf("~RESET: 1\n");
	}
	else
	{
		printf("~RESET: 0\n");
	}
}


/* END Test. */

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
