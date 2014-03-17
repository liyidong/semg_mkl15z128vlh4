/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : SM_SPI1.c
**     Project     : ProcessorExpert
**     Processor   : MKL15Z128VLH4
**     Component   : SPIMaster_LDD
**     Version     : Component 01.091, Driver 01.02, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2013-09-20, 15:43, # CodeGen: 145
**     Abstract    :
**         This component "SPIMaster_LDD" implements MASTER part of synchronous
**         serial master-slave communication.
**     Settings    :
**          Component name                                 : SM_SPI1
**          Device                                         : SPI1
**          Interrupt service/event                        : Disabled
**          Settings                                       :
**            Input pin                                    : Enabled
**              Pin                                        : PTD7/SPI1_MISO/UART0_TX/SPI1_MOSI
**              Pin signal                                 : SPI1_IN
**            Output pin                                   : Enabled
**              Pin                                        : ADC0_SE7b/PTD6/LLWU_P15/SPI1_MOSI/UART0_RX/SPI1_MISO
**              Pin signal                                 : SPI1_OUT
**            Clock pin                                    :
**              Pin                                        : ADC0_SE6b/PTD5/SPI1_SCK/UART2_TX/TPM0_CH5
**              Pin signal                                 : SPI1_SCK
**            Chip select list                             : 0
**            Attribute set list                           : 1
**              Attribute set 0                            :
**                Width                                    : 8 bits
**                MSB first                                : yes
**                Clock polarity                           : Low
**                Clock phase                              : Change on leading edge
**                Parity                                   : None
**                Chip select toggling                     : no
**                Clock rate index                         : 0
**            Clock rate                                   : 4 MHz
**            HW input buffer size                         : Max buffer size
**            HW input watermark                           : 1
**            HW output buffer size                        : Max buffer size
**            HW output watermark                          : 1
**          Initialization                                 :
**            Initial chip select                          : 0
**            Initial attribute set                        : 0
**            Enabled in init. code                        : no
**            Auto initialization                          : no
**            Event mask                                   :
**              OnBlockSent                                : Enabled
**              OnBlockReceived                            : Enabled
**              OnError                                    : Disabled
**          CPU clock/configuration selection              :
**            Clock configuration 0                        : This component enabled
**            Clock configuration 1                        : This component disabled
**            Clock configuration 2                        : This component disabled
**            Clock configuration 3                        : This component disabled
**            Clock configuration 4                        : This component disabled
**            Clock configuration 5                        : This component disabled
**            Clock configuration 6                        : This component disabled
**            Clock configuration 7                        : This component disabled
**     Contents    :
**         Init         - LDD_TDeviceData* SM_SPI1_Init(LDD_TUserData *UserDataPtr);
**         Enable       - LDD_TError SM_SPI1_Enable(LDD_TDeviceData *DeviceDataPtr);
**         Disable      - LDD_TError SM_SPI1_Disable(LDD_TDeviceData *DeviceDataPtr);
**         SendBlock    - LDD_TError SM_SPI1_SendBlock(LDD_TDeviceData *DeviceDataPtr, LDD_TData...
**         ReceiveBlock - LDD_TError SM_SPI1_ReceiveBlock(LDD_TDeviceData *DeviceDataPtr, LDD_TData...
**         Main         - void SM_SPI1_Main(LDD_TDeviceData *DeviceDataPtr);
**
**     Copyright : 1997 - 2013 Freescale Semiconductor, Inc. All Rights Reserved.
**     SOURCE DISTRIBUTION PERMISSIBLE as directed in End User License Agreement.
**
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/
/*!
** @file SM_SPI1.c
** @version 01.02
** @brief
**         This component "SPIMaster_LDD" implements MASTER part of synchronous
**         serial master-slave communication.
*/
/*!
**  @addtogroup SM_SPI1_module SM_SPI1 module documentation
**  @{
*/

/* MODULE SM_SPI1. */
/*lint -save  -e926 -e927 -e928 -e929 Disable MISRA rule (11.4) checking. */

#include "Events.h"
#include "SM_SPI1.h"
/* {Default RTOS Adapter} No RTOS includes */

#ifdef __cplusplus
extern "C" {
#endif

/*
** ===================================================================
**     Method      :  SM_SPI1_Init (component SPIMaster_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc.
**         If the "Enable in init. code" is set to "yes" value then the
**         device is also enabled(see the description of the Enable()
**         method). In this case the Enable() method is not necessary
**         and needn't to be generated.
**         This method can be called only once. Before the second call
**         of Init() the Deinit() must be called first.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Device data structure pointer.
*/
/* ===================================================================*/
LDD_TDeviceData* SM_SPI1_Init(LDD_TUserData *UserDataPtr)
{
  /* SIM_SCGC4: SPI1=1 */
  SIM_SCGC4 |= SIM_SCGC4_SPI1_MASK;
  /* PORTD_PCR7: ISF=0,MUX=2 */
  PORTD_PCR7 = (uint32_t)((PORTD_PCR7 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x05)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x02)
               ));
  /* PORTD_PCR6: ISF=0,MUX=2 */
  PORTD_PCR6 = (uint32_t)((PORTD_PCR6 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x05)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x02)
               ));
  /* PORTD_PCR5: ISF=0,MUX=2 */
  PORTD_PCR5 = (uint32_t)((PORTD_PCR5 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x05)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x02)
               ));
  /* SPI1_C1: SPIE=0,SPE=0,SPTIE=0,MSTR=1,CPOL=0,CPHA=1,SSOE=1,LSBFE=0 */
  SPI1_C1 = (SPI_C1_MSTR_MASK | SPI_C1_CPHA_MASK | SPI_C1_SSOE_MASK); /* Set configuration register */
  /* SPI1_C2: SPMIE=0,??=0,TXDMAE=0,MODFEN=1,BIDIROE=0,RXDMAE=0,SPISWAI=0,SPC0=0 */
  SPI1_C2 = SPI_C2_MODFEN_MASK;        /* Set configuration register */
  /* SPI1_BR: ??=0,SPPR=2,SPR=1 */
  SPI1_BR = (SPI_BR_SPPR(0x02) | SPI_BR_SPR(0x01)); /* Set baud rate register */

  return;
}

/*
** ===================================================================
**     Method      :  SM_SPI1_Enable (component SPIMaster_LDD)
*/
/*!
**     @brief
**         This method enables SPI device. This method is intended to
**         be used together with <Disable()> method to temporary switch
**         On/Off the device after the device is initialized. This
**         method is required if the <Enabled in init. code> property
**         is set to "no" value.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The device doesn't work in the
**                           active clock configuration
*/
/* ===================================================================*/
LDD_TError SM_SPI1_Enable(LDD_TDeviceData *DeviceDataPtr)
{
  SPI_PDD_EnableDevice(SPI1_BASE_PTR,PDD_ENABLE); /* Enable device */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  SM_SPI1_Disable (component SPIMaster_LDD)
*/
/*!
**     @brief
**         Disables the SPI device. When the device is disabled, some
**         component methods should not be called. If so, error
**         ERR_DISABLED may be reported. This method is intended to be
**         used together with <Enable()> method to temporary switch
**         on/off the device after the device is initialized. This
**         method is not required. The <Deinit()> method can be used to
**         switch off and uninstall the device.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by <Init> method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The device doesn't work in the
**                           active clock configuration
*/
/* ===================================================================*/
LDD_TError SM_SPI1_Disable(LDD_TDeviceData *DeviceDataPtr)
{
  SPI_PDD_EnableDevice(SPI1_BASE_PTR,PDD_DISABLE); /* Disable device */
  return ERR_OK;                       /* OK */
}

/*lint -restore Enable MISRA rule (11.4) checking. */
/* END SM_SPI1. */

#ifdef __cplusplus
}  /* extern "C" */
#endif

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.2 [05.07]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
