/*****************************************************************************
** (C) Chris Wood 1995.
**
** WINMAIN.C - Application entry point.
**
******************************************************************************
*/

#include "af.h"
#include <direct.h>
#include "winutils.h"
#include "strngrsc.h"

/**** Defs. *****************************************************************/
#define TITLE_LEN		40				/* Length of application name. */

/**** Global Vars. **********************************************************/
HINSTANCE hAppInst;              			/* Application instance. */
HINSTANCE	hPrevInst;					/* Previous instance. */
LPSTR	lpszArgs;						/* Command line. */
HACCEL	hAccel;						/* Keyboard accelerator table. */
BYTE		szTitle[TITLE_LEN];				/* Application title. */

extern HWND	hAppWnd;					/* Application window. */

/**** Prototypes. ***********************************************************/
extern BOOL FAR RegisterAppWnd(VOID);
extern BOOL FAR RegisterDilWnd(VOID);
extern BOOL FAR RegisterClientWnd(VOID);
extern VOID FAR CreateAppWnd(VOID);
extern VOID FAR CleanUpAppWnd(VOID);
extern BOOL FAR SetApplication(VOID);
extern VOID OutputMsg32(LPSTR lpszMsg);
extern VOID WaitForApp(BOOL bClear);
extern VOID IgnoreApp(VOID);
extern VOID LoadPrefs(VOID);
extern VOID SavePrefs(VOID);

/*****************************************************************************
** Application entry point.
*/
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, 
				int iCmdShow)
{
     MSG	msg;                	/* Windows message. */

	/* Setup this instance. */
	hAppInst  = hInstance;
	hPrevInst = hPrevInstance;
	lpszArgs  = lpszCmdLine;

     /* Check for previous instance. */
     if (!hPrevInst)
     {                            
          /* Register window classes. */
		if (!RegisterAppWnd())
			return ERROR;
		if (!RegisterDilWnd())
			return ERROR;
		if (!RegisterClientWnd())
			return ERROR;
     }

     /* Load the users' preferences. */
     LoadPrefs();
     	
	/* Get the application title. */
	LoadRscString(IDS_APPNAME, (LPSTR) szTitle, TITLE_LEN);

	/* Get the keyboard accelerator table. */
	hAccel = LoadRscAccelerators("AppKeys");	

	/* Create the main window. */
	CreateAppWnd();

	/* Show the window and update toolbar. */
	ShowWindow(hAppWnd, iCmdShow);

     /* Get the target class name. */
     if (SetApplication())
          WaitForApp(TRUE);
     else
          IgnoreApp();

     /* Process the windows messages. */
     while(GetMessage(&msg, NULL, 0, 0))
     {    
     	if (!TranslateAccelerator(hAppWnd, hAccel, &msg))
     	{
	     	TranslateMessage(&msg);
          	DispatchMessage(&msg);
          }
     }

     /* Save the users' preferences. */
     SavePrefs();

	/* Cleanup. */
     CleanUpAppWnd();
     
     /* Exit. */
     return msg.wParam;
}
