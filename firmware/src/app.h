/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

#ifndef _APP_H
#define _APP_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "configuration.h"
#include "GUI.h"
// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

    typedef union{
    uint8_t CMD_Byte[2];
    struct {
        //CMD_0
        bool CMD_StartUART_Transfer:1;
        //CMD_1
        bool CMD_1:1;
        //CMD_2
        bool CMD_2:1;
        //CMD_3
        bool CMD_3:1;
        //CMD_4
        bool CMD_4:1;
        //CMD_5
        bool CMD_5:1;
        //CMD_6
        bool CMD_6:1;
        //CMD_7
        bool CMD_7:1;
        //CMD_8
        bool CMD_8:1;
        //CMD_9
        bool CMD_9:1;
        //CMD_10
        bool CMD_10:1;
        //CMD_11
        bool CMD_11:1;
        //CMD_12
        bool CMD_12:1;
        //CMD_13
        bool CMD_13:1;
        //CMD_14
        bool CMD_14:1;
        //CMD_15
        bool CMD_15:1;
    };
}UCommand;

typedef union{
    uint8_t STAT_Byte[2];
    struct {
        //STAT 0
        bool STAT_0:1;
        //STAT 1
        bool STAT_1:1;
        //STAT 2
        bool STAT_2:1;
        //STAT 3
        bool STAT_3:1;
        //STAT 4
        bool STAT_4:1;
        //STAT 5
        bool STAT_5:1;
        //STAT 6
        bool STAT_6:1;
        //STAT 7
        bool STAT_7:1;
        //STAT 8
        bool STAT_8:1;
        //STAT 9
        bool STAT_9:1;
        //STAT 10
        bool STAT_10:1;
        //STAT 11
        bool STAT_11:1;
        //STAT 13
        bool STAT_12:1;
        //STAT 13
        bool STAT_13:1;
        //STAT 14
        bool STAT_14:1;
        //STAT 15
        bool STAT_15:1;
    };
}UStatus;

// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behavior of the application at various times.
*/

typedef enum
{
    /* Application's state machine's initial state. */
    APP_STATE_INIT=0,
    APP_STATE_SERVICE_TASKS,
    /* TODO: Define states used by the application state machine. */

} APP_STATES;


// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */

typedef struct
{
    /* The application's current state */
    APP_STATES state;

    UStatus status;
    UCommand commands;
    
    uint16_t noOfBytes;
    uint16_t transferTimeout;
    uint16_t LED_R_Timeout;
    bool transferMode;
    bool transferTimeoutFlag;
} APP_DATA;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the
    application in its initial state and prepares it to run so that its
    APP_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void APP_Initialize ( void );


/*******************************************************************************
  Function:
    void APP_Tasks ( void )

  Summary:
    MPLAB Harmony Demo application tasks function

  Description:
    This routine is the Harmony Demo application's tasks function.  It
    defines the application's state machine and core logic.

  Precondition:
    The system and application initialization ("SYS_Initialize") should be
    called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void APP_Tasks( void );

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif /* _APP_H */

/*******************************************************************************
 End of File
 */

