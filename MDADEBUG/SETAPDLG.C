/*****************************************************************************
** (C) Chris Wood 1995.
**
** SETAPP.C - Show and handle the set application dialog.
**
******************************************************************************
*/

#include "af.h"
#include "winutils.h"
#include "resource.h"

/**** Global Vars. **********************************************************/
#define MAX_CLASSNAME_LEN     256            /* Max length of classname. */
#define MAX_PATHNAME_LEN      260            /* Max length of pathname. */

char szAppClassName[MAX_CLASSNAME_LEN];      /* Target main window classname. */
char szAppPathName[MAX_PATHNAME_LEN];        /* Target application. */
BOOL bNotifyProcesses;                       /* Notify process message. */
BOOL bNotifyThreads;                         /* Notify thread messages. */
BOOL bNotifyDlls;                            /* Notify dll messages. */

extern HINSTANCE hAppInst;				/* Application instance. */
extern HWND hAppWnd;					/* Application window. */

/**** Prototypes. ***********************************************************/
DIALOGPROC SetAppDialogProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

/*****************************************************************************
** Show the set application dialog and return whether a name was entered.
*/
BOOL FAR SetApplication(VOID)
{
     BOOL bOkay;

     /* Show the dislog. */
     bOkay = DialogBox(hAppInst, "SETAPP_DIALOG", hAppWnd, (DLGPROC) SetAppDialogProc);

     /* Cancel pressed? */
     if (bOkay != TRUE)
          return FALSE;

     /* Check for an entry. */
     if (szAppClassName[0] == '\0')
          return FALSE;

     return TRUE;
}

/*******************************************************************************
** Set Application dialog message handler.
**/
DIALOGPROC SetAppDialogProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
     /* Decode message. */
     switch (iMsg)
     {
		/* Initialisation. */
		case WM_INITDIALOG:
			CentreWindow(hDlg);
               SetDlgItemText(hDlg, IDC_CLASSNAME, szAppClassName);
               SetDlgItemText(hDlg, IDC_PATHNAME, szAppPathName);
               CheckDlgButton(hDlg, IDC_NOTIFYPROCESSES, bNotifyProcesses);
               CheckDlgButton(hDlg, IDC_NOTIFYTHREADS, bNotifyThreads);
               CheckDlgButton(hDlg, IDC_NOTIFYDLLS, bNotifyDlls);
			return TRUE;
			
		/* Command. */
		case WM_COMMAND:
			/* Decode command. */
			switch(wParam)
			{
				/* OK button pressed. */
				case IDOK:
                         GetDlgItemText(hDlg, IDC_CLASSNAME, szAppClassName, MAX_CLASSNAME_LEN);
                         GetDlgItemText(hDlg, IDC_PATHNAME, szAppPathName, MAX_PATHNAME_LEN);
                         bNotifyProcesses = IsDlgButtonChecked(hDlg, IDC_NOTIFYPROCESSES);
                         bNotifyThreads   = IsDlgButtonChecked(hDlg, IDC_NOTIFYTHREADS);
                         bNotifyDlls      = IsDlgButtonChecked(hDlg, IDC_NOTIFYDLLS);
					EndDialog(hDlg, TRUE);
					return TRUE;

                    /* Cancel button pressed. */
				case IDCANCEL:
					EndDialog(hDlg, FALSE);
					return TRUE;
					
				/* Safe. */
				default:
					break;
			}
			return TRUE;
			
          /* Safe. */
          default:
     		break;
     }

	/* All others. */
     return FALSE;
}

/*****************************************************************************
** Load preferences.
*/
void LoadPrefs(void)
{
     ReadIniString("Preferences", "ClassName", "", szAppClassName, MAX_CLASSNAME_LEN);
     ReadIniString("Preferences", "PathName", "", szAppPathName, MAX_PATHNAME_LEN);
     bNotifyProcesses = ReadIniInt("Preferences", "Processes", FALSE);
     bNotifyThreads   = ReadIniInt("Preferences", "Threads", FALSE);
     bNotifyDlls      = ReadIniInt("Preferences", "Dlls", FALSE);
}

/*****************************************************************************
** Save preferences.
*/
void SavePrefs(void)
{
     WriteIniString("Preferences", "ClassName", szAppClassName);
     WriteIniString("Preferences", "PathName", szAppPathName);
     WriteIniInt("Preferences", "Processes", bNotifyProcesses);
     WriteIniInt("Preferences", "Threads", bNotifyThreads);
     WriteIniInt("Preferences", "Dlls", bNotifyDlls);
}
