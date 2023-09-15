/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "peripheral/tmr/plib_tmr6.h"
#include "peripheral/gpio/plib_gpio.h"
#include "peripheral/dmac/plib_dmac.h"
// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;
uint8_t __attribute__((coherent)) arrLedBuffer[4000];
// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


void TMR6_CB (uint32_t status, uintptr_t context);
void DMAC_0_CB (DMAC_TRANSFER_EVENT status, uintptr_t contextHandle);
void DMAC_1_CB (DMAC_TRANSFER_EVENT status, uintptr_t contextHandle);

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;
    

    TMR6_CallbackRegister(&TMR6_CB,0);
    TMR6_Start();
    
    //Register DMAC Callback functions
    DMAC_ChannelCallbackRegister(DMAC_CHANNEL_0, &DMAC_0_CB, 0 );
    DMAC_ChannelCallbackRegister(DMAC_CHANNEL_1, &DMAC_1_CB, 0 );
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            bool appInitialized = true;


            if (appInitialized)
            {

                appData.state = APP_STATE_SERVICE_TASKS;
            }
            break;
        }

        case APP_STATE_SERVICE_TASKS:
        {

            break;
        }

        /* TODO: implement your application state machine.*/


        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
    GUI_FSM();
    
    if (appData.commands.CMD_StartUART_Transfer){
        appData.commands.CMD_StartUART_Transfer=false;
        //enter UART data transfer mode
        appData.transferMode=true;
        appData.transferTimeoutFlag=false;
        //Configure DMA Transfer
        DMAC_ChannelTransfer(DMAC_CHANNEL_0, (void*)(&U6RXREG), 1, arrLedBuffer, appData.noOfBytes, 1);
        LED_2_Set();
        LED_3_Set();
        LED_1_Clear();
        //Signal the PC
        
        //Set timeout interval
        appData.transferTimeout=5000; //5sec
    }
    
    //analyze timeout condition
    if (appData.transferMode && (appData.transferTimeout==0)){
        appData.transferMode=false;
        appData.transferTimeoutFlag=true;
        DMAC_ChannelDisable(DMAC_CHANNEL_0);
        DMAC_ChannelDisable(DMAC_CHANNEL_1);
        LED_2_Set();
        LED_3_Set();
        LED_1_Set();
    }
}

/*******************************************************************************
 Local Functions implementation
 */

void TMR6_CB (uint32_t status, uintptr_t context){
    if(appData.transferTimeout>0) appData.transferTimeout--;
    if(appData.LED_R_Timeout>0){
        appData.LED_R_Timeout--;
    }else{
        appData.LED_R_Timeout=1000;
        LED_R_Toggle();
    }
}

void DMAC_0_CB (DMAC_TRANSFER_EVENT status, uintptr_t contextHandle){
    if(status==DMAC_TRANSFER_EVENT_COMPLETE){
        //disable DMA channel
        DMAC_ChannelDisable(DMAC_CHANNEL_0);
        //Configure next transfer
        SPI1BUF=0; //trigger first byte transfer
        DMAC_ChannelTransfer(DMAC_CHANNEL_1, &arrLedBuffer[0], appData.noOfBytes, (void*)(&SPI1BUF), 1, 1);
        LED_2_Clear();
        //TO DO - delete the following lines after tests
        //appData.transferMode=false;
    }
}

void DMAC_1_CB (DMAC_TRANSFER_EVENT status, uintptr_t contextHandle){
    //disable DMA channel
    if(status==DMAC_TRANSFER_EVENT_COMPLETE){
    DMAC_ChannelDisable(DMAC_CHANNEL_1);
        appData.transferMode=false;
        LED_1_Set();
        LED_3_Clear();
    }
}
/*******************************************************************************
 End of File
 */
