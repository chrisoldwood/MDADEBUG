/*****************************************************************************
** (C) Chris Wood 1995.
**
** DBGOUT.C - Debugger code and output.
**
******************************************************************************
*/

#include "af.h"
#include "menursc.h"
#include <string.h>
#include <memory.h>

/**** Defs. *****************************************************************/
#define TIMEOUT          250                 /* Timer interval - 1/4 sec. */
#define DEBUG_BUF_LEN    2048                /* Debug message buffer length. */
#define DLL_NAME_LEN     256                 /* Max DLL filename length. */
#define WM_ENDWATCH      WM_USER             /* Watch finished message. */
#define ENDED_ERROR      0                   /* Watch ended because of error. */
#define ENDED_OKAY       1                   /* Watch ended okay. */

typedef struct tagDebugParams
{
     BOOL      bActive;                      /* Process already active. */
     DWORD     dwProcessID;                  /* Active Process ID. */
} DEBUGPARAMS, * PDEBUGPARAMS;

/**** Global Vars. **********************************************************/
UINT      iTimerID;                          /* Application timer. */
HANDLE    hDebugThread;                      /* The debugging thread handle. */
INT       iDebugThreadID;                    /* The debugging thread ID. */
CHAR      szDebugMsg[DEBUG_BUF_LEN];         /* Temporary debug string buffer. */
CHAR      szDllName[DLL_NAME_LEN];           /* DLL filename. */
DEBUGPARAMS dbParams;                        /* Debugging parameters. */

extern HWND	  hAppWnd;			     /* Application window. */
extern HMENU	  hMenu;					/* Current menu. */
extern HMENU     hSysMenu;                   /* System menu. */
extern HWND      hMsgWnd;                    /* Message window. */
extern HINSTANCE hAppInst;              	/* Application instance. */
extern char      szAppClassName[];           /* Target main window classname. */
extern char      szAppPathName[];            /* Target path. */
extern BOOL      bNotifyProcesses;           /* Notify thread messages. */
extern BOOL      bNotifyThreads;             /* Notify thread messages. */
extern BOOL      bNotifyDlls;                /* Notify dll messages. */

/**** Prototypes. ***********************************************************/
VOID CALLBACK WaitForAppTimerProc(HWND hWnd, UINT uMsg, UINT iID, DWORD dwSysTime);
VOID CALLBACK WaitForDebuggerTimerProc(HWND hWnd, UINT uMsg, UINT iID, DWORD dwSysTime);
DWORD WINAPI DebugThread(DWORD dwIgnore);

/*****************************************************************************
** Output a message to the MDA and the window.
*/
VOID OutputMessage(LPSTR lpszOrigMsg)
{
static CHAR szMsg[DEBUG_BUF_LEN];
     LPSTR lpszText, lpszMsg;

     /* First copy the message. */
     lstrcpy(szMsg, lpszOrigMsg);

     /* Remove any unprintable chars. */
     lpszText = szMsg;
     while(*lpszText)
     {    
          /* Change to a space if not CR or LF. */
          if ( (*lpszText < ' ') && (*lpszText != '\n') && (*lpszText != '\r'))
               *lpszText = ' ';

          /* Next char. */
          lpszText++;
     }

     /* Now display the strings to the Window. */
     lpszMsg = szMsg;
     while (*lpszMsg)
     {
          BOOL bCRLF = FALSE;

          /* Get tmp pointer. */
          lpszText = lpszMsg;

          /* Find CR/LF. */
          while ( (*lpszText) && (*lpszText != '\r') && (*lpszText != '\n') )
               lpszText++;

          /* Found CR? */
          if (*lpszText == '\r')
          {
               bCRLF = TRUE;
               *lpszText++ = '\0';
          }

          /* Found LF? */
          if (*lpszText == '\n')
          {
               bCRLF = TRUE;
               *lpszText++ = '\0';
          }

          /* Add text. */
          SendMessage(hMsgWnd, EM_SETSEL, 65530, 65530);
          SendMessage(hMsgWnd, EM_REPLACESEL, FALSE, (LPARAM)lpszMsg);

          /* Append a CR/LF. */
          if (bCRLF)
          {
               SendMessage(hMsgWnd, EM_SETSEL, 65530, 65530);
               SendMessage(hMsgWnd, EM_REPLACESEL, FALSE, (LPARAM)"\r\n");
          }

          /* Move on a line. */
          lpszMsg = lpszText;
     }
}

/*****************************************************************************
** Start the waiting process. This clears the output and kicks off a timer.
*/
VOID WaitForApp(BOOL bClear)
{
     /* Clear the display? */
     if (bClear)
     {
          SendMessage(hMsgWnd, EM_SETSEL, 0, (LPARAM)-1);
          SendMessage(hMsgWnd, EM_REPLACESEL, FALSE, (LPARAM)"");
     }

     /* Kick off timer. */
     if (!iTimerID)
          iTimerID = SetTimer(NULL, 0, TIMEOUT, (TIMERPROC) WaitForAppTimerProc);

     /* Show status. */
     OutputMessage("Waiting for application...\n");

     /* Hide main window. */
     ShowWindow(hAppWnd, SW_MINIMIZE);
}

/*****************************************************************************
** Stop waiting for the application.
*/
VOID IgnoreApp(VOID)
{
     /* Kill timer. */
     if (iTimerID)
     {
          KillTimer(NULL, iTimerID);
          iTimerID = 0;
     }

     /* Show status. */
     OutputMessage("\nIgnoring application...\n");
}

/*****************************************************************************
** Timer callback procedure to wait for application start.
*/
VOID CALLBACK WaitForAppTimerProc(HWND hWnd, UINT uMsg, UINT iID, DWORD dwSysTime)
{
     HWND      hFindWnd;
     DWORD     dwProcessID;
     char      szProcID[80];

     /* Look for window. */
     hFindWnd = FindWindow(szAppClassName, NULL);
     if (!hFindWnd)
          return;

     /* Kill off timer. */
     KillTimer(NULL, iTimerID);
     iTimerID = 0;

     /* Clear the MDA and window. */
     SendMessage(hMsgWnd, EM_SETSEL, 0, (LPARAM)-1);
     SendMessage(hMsgWnd, EM_REPLACESEL, FALSE, (LPARAM)"");

     /* Get Process ID. */
     GetWindowThreadProcessId(hFindWnd, &dwProcessID);

     /* Show Process ID. */
     wsprintf(szProcID, "Process ID: %x\n", dwProcessID);
     OutputMessage(szProcID);

     /* Start debugging thread. */
     dbParams.dwProcessID = dwProcessID;
     dbParams.bActive     = TRUE;
     hDebugThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) DebugThread, 
                                   (LPVOID) 0, 0, &iDebugThreadID);
     CloseHandle(hDebugThread);
}

/*****************************************************************************
** Wait for the debugger to finish debugging.
*/
VOID WaitForDebugger(VOID)
{
     /* Kick off timer. */
     if (!iTimerID)
          iTimerID = SetTimer(NULL, 0, TIMEOUT, (TIMERPROC) WaitForDebuggerTimerProc);

     /* Show status. */
     OutputMessage("Waiting for application to terminate...\n");

     /* Hide main window. */
     ShowWindow(hAppWnd, SW_MINIMIZE);
}

/*****************************************************************************
** Timer callback procedure to wait for the debugger to finish.
*/
VOID CALLBACK WaitForDebuggerTimerProc(HWND hWnd, UINT uMsg, UINT iID, DWORD dwSysTime)
{
     HWND      hFindWnd;

     /* Look for window. */
     hFindWnd = FindWindow(szAppClassName, NULL);
     if (hFindWnd)
          return;

     /* Kill off timer. */
     KillTimer(NULL, iTimerID);
     iTimerID = 0;

     /* Notify main window of completion. */
     OutputMessage("Application terminated.\n\n");
     PostMessage(hAppWnd, WM_ENDWATCH, ENDED_OKAY, 0);
}

/*****************************************************************************
** Launch application.
*/
VOID LaunchApp(VOID)
{
     /* Kill off timer. */
     KillTimer(NULL, iTimerID);
     iTimerID = 0;

     /* Clear the MDA and window. */
     SendMessage(hMsgWnd, EM_SETSEL, 0, (LPARAM)-1);
     SendMessage(hMsgWnd, EM_REPLACESEL, FALSE, (LPARAM)"");

     /* Show status. */
     OutputMessage("Launching application:\n");
     OutputMessage(szAppPathName);
     OutputMessage("\n\n");

     /* Hide main window. */
     ShowWindow(hAppWnd, SW_MINIMIZE);

     /* Start debugging thread. */
     dbParams.dwProcessID = 0;
     dbParams.bActive     = FALSE;
     hDebugThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) DebugThread, 
                                   (LPVOID) 0, 0, &iDebugThreadID);
     CloseHandle(hDebugThread);
}

// Stop "no return value" compiler warning.
#pragma warning ( disable : 4035)

/*****************************************************************************
** Debugging thread.
*/
DWORD WINAPI DebugThread(DWORD dwIgnore)
{
     DEBUG_EVENT    dbEvent;
     BOOL           bOkay = FALSE;
     BOOL           bDone = FALSE;
     LPSTR          lpszMsg;
     HANDLE         hProcess;
     INT            iResult = ENDED_OKAY;
     DWORD          dwProcessID;
     STARTUPINFO    StartInfo;
     PROCESS_INFORMATION   ProcInfo;

     /* Disable preferences/launch menu item. */
     EnableMenuItem(hMenu, IDM_APP, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
     EnableMenuItem(hSysMenu, IDM_LAUNCH, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

     /* Set the amount of error reporting. */
     SetDebugErrorLevel(SLE_WARNING);

     if (dbParams.bActive)
     {
          /* Get processID. */
          dwProcessID = dbParams.dwProcessID;
     
          /* Attempt to become a debugger. */
          if (!DebugActiveProcess(dwProcessID))
          {
               OutputMessage("Cannot Watch - Debugger Running?\n");
               bDone = TRUE;
               iResult = ENDED_ERROR;
          }

          /* Get a handle to the process. */
          hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessID);
          if (!hProcess)
          {
               OutputMessage("Cannot Get Process Handle.\n");
               bDone = TRUE;
               iResult = ENDED_ERROR;
          }
     }
     else /* launching ourseleves. */
     {
          /* Set startup info.*/
          memset(&StartInfo, 0, sizeof(STARTUPINFO));
          StartInfo.cb = sizeof(STARTUPINFO);

          /* Launch it. */
          bOkay = CreateProcess(szAppPathName, NULL, NULL, NULL, FALSE, DEBUG_PROCESS, 
                                   NULL, NULL, &StartInfo, &ProcInfo);
          if (!bOkay)
          {
               DWORD dwError = GetLastError();

               OutputMessage("Cannot launch application!\n");

               switch(dwError) 
               {
                    case ERROR_FILE_NOT_FOUND:
                         OutputMessage("File not file.\n");
                         break;

                    case ERROR_ACCESS_DENIED:
                         OutputMessage("Access Denied.\n");
                         break;

                    case ERROR_FILE_INVALID:
                         OutputMessage("Invalid file.\n");
                         break;

                    default:
                         wsprintf(szDebugMsg, "Error code: %d (0x%08X)\n", dwError, dwError);
                         OutputMessage(szDebugMsg);
                         break;
               }

               bDone = TRUE;
               iResult = ENDED_ERROR;
          }

          hProcess = ProcInfo.hProcess;

          // Close thread handle as we dont need it.
          CloseHandle(ProcInfo.hThread);
     }

     /* Loop until error or termination. */
     while(!bDone)
     {
          /* Wait... */
          if(!WaitForDebugEvent(&dbEvent, INFINITE))
          {
               /* Bail out. */
               bDone = TRUE;
               continue;
          }

          /* Reset message string. */
          lpszMsg = NULL;

          /* Wait was the event. */
          switch(dbEvent.dwDebugEventCode) 
          {
               case EXCEPTION_DEBUG_EVENT:
                    /* What type of exception. */
                    switch(dbEvent.u.Exception.ExceptionRecord.ExceptionCode) 
                    {
                         //
                         // Exceptions.
                         //

                         case EXCEPTION_ACCESS_VIOLATION:
                              lpszMsg = "EXCEPTION: Access Violation.\n";
                              break;

                         case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
                              lpszMsg = "EXCEPTION: Array Bounds Exceeded.\n";
                              break;

                         case EXCEPTION_BREAKPOINT:
                              lpszMsg = "EXCEPTION: Breakpoint.\n";
                              break;

                         case EXCEPTION_DATATYPE_MISALIGNMENT:
                              lpszMsg = "EXCEPTION: Datatype Misaligment.\n";
                              break;

                         case EXCEPTION_FLT_DENORMAL_OPERAND:
                              lpszMsg = "EXCEPTION: Floating Point Error (Denormal Operand).\n";
                              break;

                         case EXCEPTION_FLT_DIVIDE_BY_ZERO:
                              lpszMsg = "EXCEPTION: Floating Point Error (Divide by Zero).\n";
                              break;

                         case EXCEPTION_FLT_INEXACT_RESULT:
                              lpszMsg = "EXCEPTION: Floating Point Error (Inexact Result).\n";
                              break;

                         case EXCEPTION_FLT_INVALID_OPERATION:
                              lpszMsg = "EXCEPTION: Floating Point Error (Invalid Operation).\n";
                              break;

                         case EXCEPTION_FLT_OVERFLOW:
                              lpszMsg = "EXCEPTION: Floating Point Error (Overflow).\n";
                              break;

                         case EXCEPTION_FLT_STACK_CHECK:
                              lpszMsg = "EXCEPTION: Floating Point Error (Stack Check).\n";
                              break;

                         case EXCEPTION_FLT_UNDERFLOW:
                              lpszMsg = "EXCEPTION: Floating Point Error (Underflow).\n";
                              break;

                         case EXCEPTION_ILLEGAL_INSTRUCTION:
                              lpszMsg = "EXCEPTION: Illegal Instruction.\n";
                              break;

                         case EXCEPTION_IN_PAGE_ERROR:
                              lpszMsg = "EXCEPTION: In Page Error.\n";
                              break;

                         case EXCEPTION_INT_DIVIDE_BY_ZERO:
                              lpszMsg = "EXCEPTION: Integer Error (Divide by Zero).\n";
                              break;

                         case EXCEPTION_INT_OVERFLOW:
                              lpszMsg = "EXCEPTION: Integer Error (Overflow).\n";
                              break;

                         case EXCEPTION_INVALID_DISPOSITION:
                              lpszMsg = "EXCEPTION: Invalid Disposition.\n";
                              break;

                         case EXCEPTION_NONCONTINUABLE_EXCEPTION:
                              lpszMsg = "EXCEPTION: NonContinuable Exception.\n";
                              break;

                         case EXCEPTION_PRIV_INSTRUCTION:
                              lpszMsg = "EXCEPTION: Privileged Instruction!\n";
                              break;

                         case EXCEPTION_SINGLE_STEP:
                              lpszMsg = "EXCEPTION: Single Step.\n";
                              break;

                         case EXCEPTION_STACK_OVERFLOW:
                              lpszMsg = "EXCEPTION: Stack Overflow.\n";
                              break;

                         default:
                              lpszMsg = "EXCEPTION: Unknown Exception...\n";
                              break;
                    }

                    // Show exception message.
                    if (lpszMsg)
                         OutputMessage(lpszMsg);

                    // Set exception count message.
                    if(dbEvent.u.Exception.dwFirstChance)
                         lpszMsg = "->First Chance...\n";
                    else
                         lpszMsg = "->Second Chance...\n";

                    // Call application/system exception handlers.
                    if (dbEvent.u.Exception.ExceptionRecord.ExceptionCode != EXCEPTION_BREAKPOINT) 
                         ContinueDebugEvent(dbEvent.dwProcessId, dbEvent.dwThreadId,
                                             DBG_EXCEPTION_NOT_HANDLED );
                    break;

               //
               // Process activity.
               //

               case CREATE_PROCESS_DEBUG_EVENT:
                    if (bNotifyProcesses)
                         lpszMsg = "PROCESS: Created.\n";
                    break;

               case EXIT_PROCESS_DEBUG_EVENT:
                    if (bNotifyProcesses)
                         lpszMsg = "PROCESS: Exited.\n";
                    bDone = TRUE;
                    break;

               //
               // Thread activity.
               //

               case CREATE_THREAD_DEBUG_EVENT:
                    if (bNotifyThreads)
                         lpszMsg = "THREAD: Created.\n";
                    break;

               case EXIT_THREAD_DEBUG_EVENT:
                    if (bNotifyThreads)
                         lpszMsg = "THREAD: Exited.\n";
                    break;

               //
               // DLL activity.
               //

               case LOAD_DLL_DEBUG_EVENT:
                    if (bNotifyDlls)
                    { 
                         /* Reset message. */
                         lpszMsg = NULL;

                         /* Filename available? */
                         if (dbEvent.u.LoadDll.lpImageName)
                         {
                              DWORD dwRead;
                              LPSTR lpszFileName = NULL;
                              DWORD iLoop;

                              /* Attempt to read file name. */
                              memset(szDllName, '\0', DLL_NAME_LEN);
                              ReadProcessMemory(hProcess, dbEvent.u.LoadDll.lpImageName,
                                   szDllName, DLL_NAME_LEN, &dwRead);

                              /* Find pathname. */
                              for (iLoop=0; iLoop < dwRead; iLoop++)
                              {
                                   /* Look for : in pathname. */
                                   if (szDllName[iLoop] == ':')
                                   {
                                        /* Check for \ following. */
                                        if (szDllName[iLoop+1] == '\\')
                                        {
                                             /* Found. */
                                             lpszFileName = &szDllName[iLoop-1];
                                             break;
                                        }
                                   }
                              }

                              /* Valid? */
                              if (lpszFileName)
                              {
                                   wsprintf(szDebugMsg, "DLL: Loaded @ 0x%08X (%s).\n", 
                                             (int) dbEvent.u.LoadDll.lpBaseOfDll, lpszFileName);
                                   lpszMsg = szDebugMsg;
                              }
                         }
                         
                         /* Try and get it from the base address. */
                         if ( (!lpszMsg)
                           && (dbEvent.u.LoadDll.lpBaseOfDll)
                           && (GetModuleFileName(dbEvent.u.LoadDll.lpBaseOfDll, szDllName, DLL_NAME_LEN)) )
                         {
                              wsprintf(szDebugMsg, "DLL: Loaded @ 0x%08X (%s).\n", 
                                        (int) dbEvent.u.LoadDll.lpBaseOfDll, szDllName);
                         }
                         else if (!lpszMsg)
                         {
                              wsprintf(szDebugMsg, "DLL: Loaded @ 0x%08X (File unknown).\n", 
                                        (int) dbEvent.u.LoadDll.lpBaseOfDll);
                         }

                         lpszMsg = szDebugMsg;
                    }
                    break;

               case UNLOAD_DLL_DEBUG_EVENT:
                    if (bNotifyDlls)
                    {
                         /* Valid base address?*/
                         if ( (dbEvent.u.UnloadDll.lpBaseOfDll)
                           && (GetModuleFileName(dbEvent.u.UnloadDll.lpBaseOfDll, szDllName, DLL_NAME_LEN)) )
                         {
                              wsprintf(szDebugMsg, "DLL: Unloaded @ 0x%08X (%s).\n", 
                                        (int) dbEvent.u.UnloadDll.lpBaseOfDll, szDllName);
                         }
                         else /* Can't get filename. */
                         {
                              wsprintf(szDebugMsg, "DLL: Unloaded @ 0x%08X (File unknown).\n", 
                                        (int) dbEvent.u.UnloadDll.lpBaseOfDll);
                         }

                         lpszMsg = szDebugMsg;
                    }
                    break;

               //
               // Application messages.
               //

               case OUTPUT_DEBUG_STRING_EVENT:
                    // Copy string + null terminator to our buffer.
                    if (ReadProcessMemory(hProcess, dbEvent.u.DebugString.lpDebugStringData,
                         szDebugMsg, dbEvent.u.DebugString.nDebugStringLength+1, NULL))
                    {
                         lpszMsg = szDebugMsg;
                    }
                    break;

               //
               // System debugging error.
               //

               case RIP_EVENT:
                    lpszMsg = "RIP: System error.\n";
                    break;

               default:
                    lpszMsg = "ERROR: Unknown...\n";
                    break;
          }

          /* Display the message, if one */
          if (lpszMsg)
               OutputMessage(lpszMsg);

          /* And on we go... */
          ContinueDebugEvent(dbEvent.dwProcessId, dbEvent.dwThreadId, DBG_CONTINUE);
     }

     /* Notify main window of completion. */
     OutputMessage("\n\n");
     PostMessage(hAppWnd, WM_ENDWATCH, iResult, 0);

     /* Close handles. */
     CloseHandle(hProcess);

     /* Reset thread handle. */
     hDebugThread = NULL;

     /* All done. */
     ExitThread(TRUE);
}
