/*****************************************************************************
** (C) Chris Wood 1995.
**
** WINMAIN.C - Application entry point, and all processing!
**
******************************************************************************
*/

#include <windows.h>
#include <stdlib.h>

/**** Global variables ******************************************************/
char * lpszAppName = "MDADebug";             /* Application name. */

/**** External Prototypes ***************************************************/
void OutputMsg32(LPSTR lpszMsg);

/*****************************************************************************
** Application entry point.
*/
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, 
				int iCmdShow)
{
     DWORD dwProcessID;
     BOOL  bDone = FALSE;
     MSG   Msg;

     /* Get process ID from command line. */
     dwProcessID = atoi(lpszCmdLine);
     if (!dwProcessID)
     {
          /* Signal error. */
          MessageBox(NULL, "Invalid process ID!", lpszAppName, MB_OK | MB_ICONSTOP);
          return FALSE;
     }

     /* Show state. */
     OutputMsg32("Process ID okay...\n");
         
     /* Turn us into a debugger. */
     if (!DebugActiveProcess(dwProcessID))
     {
          /* Signal error. */
          MessageBox(NULL, "Cant debug process!", lpszAppName, MB_OK | MB_ICONSTOP);
          return FALSE;
     }

     /* Show state. */
     OutputMsg32("Waiting for messages...\n");

     /* Process debug events. */
     while (!bDone)
     {
          DEBUG_EVENT    Event;

	     while(PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
	     {
		     TranslateMessage(&Msg);
		     DispatchMessage(&Msg);
	     }

          /* Wait forever. */
          if (WaitForDebugEvent(&Event, 100))
          {
               /* What event occurred. */
               switch(Event.dwDebugEventCode)
               {
                    /* String output. */
                    case OUTPUT_DEBUG_STRING_EVENT:
                         /* Message in ASCII? */
                         if (!Event.u.DebugString.fUnicode)
                              OutputMsg32(Event.u.DebugString.lpDebugStringData);
                         break;

                    /* Process terminated. */
                    case EXIT_PROCESS_DEBUG_EVENT:
                         /* Show state. */
                         OutputMsg32("Application terminated...\n");
                         bDone = TRUE;
                         break;

                    /* Safe. */
                    default:
                         OutputMsg32("Unknown Event...\n");
                         break;
               }

               /* And again... */
               if (!ContinueDebugEvent(Event.dwProcessId, Event.dwThreadId, DBG_EXCEPTION_NOT_HANDLED))
               {
                    /* Signal error. */
                    MessageBox(NULL, "Cant continue monitoring!", lpszAppName, MB_OK | MB_ICONSTOP);
                    return FALSE;
               }
          }
     }

     /* Show state. */
     OutputMsg32("Finished monitoring...\n");

     return TRUE;
}
