/*****************************************************************************
** (C) Chris Wood 1995.
**
** APPWND.C - Application window.
**
******************************************************************************
*/

#include "af.h"
#include "winutils.h"
#include "menursc.h"
#include "strngrsc.h"

/**** Defs. *****************************************************************/
#define WM_ENDWATCH      WM_USER             /* Watch finished message. */
#define ENDED_ERROR      0                   /* Watch ended because of error. */
#define ENDED_OKAY       1                   /* Watch ended okay. */

/**** Global Vars. **********************************************************/
HWND		hAppWnd;						/* Application window. */
HMENU	hMenu;						/* Current menu. */
HMENU     hSysMenu;                          /* System menu. */

extern HINSTANCE hAppInst;              	/* Application instance. */
extern BYTE szTitle[];					/* Application title. */
extern HWND hDilWnd;					/* DIL window. */
extern HWND hCliWnd;					/* Client window. */
extern HWND hMsgWnd;                         /* Message window. */
extern HANDLE hDebugThread;                  /* The debugging thread handle. */

/**** Prototypes. ***********************************************************/
WINDOWPROC MainWindowProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

extern VOID FAR CreateDilWnd(VOID);
extern VOID FAR CreateClientWnd(VOID);
extern VOID FAR ResizeDil(int iNewWidth, int iNewHeight);
extern VOID FAR ResizeClient(int iNewWidth, int iNewHeight);
extern VOID FAR SetHint(LPSTR lpszHint);
extern VOID FAR ShowAboutBox(VOID);
extern BOOL FAR SetApplication(VOID);
extern VOID WaitForApp(BOOL bClear);
extern VOID WaitForDebugger(VOID);
extern VOID LaunchApp(VOID);
extern VOID IgnoreApp(VOID);

/*****************************************************************************
** Register the main window class.
*/
BOOL FAR RegisterAppWnd(VOID)
{    
	WNDCLASS	WndClass;
	
	/* Setup window class parameters. */
	WndClass.style         = CS_VREDRAW | CS_HREDRAW;
	WndClass.lpfnWndProc   = (WNDPROC) MainWindowProc;
	WndClass.cbClsExtra    = 0;
	WndClass.cbWndExtra    = 0;
	WndClass.hInstance     = hAppInst;
	WndClass.hIcon         = LoadRscIcon((LPSTR) "AppIcon");
	WndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName  = NULL;
	WndClass.lpszClassName = LoadTmpRscString(IDS_PRGWNDCLASS);

	return RegisterClass(&WndClass);
}

/*****************************************************************************
** Create the application window.
*/
VOID FAR CreateAppWnd(VOID)
{
	/* Get menu. */
	hMenu = LoadRscMenu("AppMenu");

	/* Create the window. */
	hAppWnd = CreateWindow(LoadTmpRscString(IDS_PRGWNDCLASS),
						(LPSTR) szTitle,
						WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
						CW_USEDEFAULT, CW_USEDEFAULT,
						CW_USEDEFAULT, CW_USEDEFAULT,
						NULL,
						hMenu,
						hAppInst,
						NULL);

	AssertEx(IsValidWnd(hAppWnd), "CreateWindow()");
     CentreWindow(hAppWnd);

	/* Create the DIL window and show. */
	CreateDilWnd();
	ShowWindow(hDilWnd, SW_SHOW);

	/* Create the client window and show. */
	CreateClientWnd();
	ShowWindow(hCliWnd, SW_SHOW);

     /* Get the system menu. */
     hSysMenu = GetSystemMenu(hAppWnd, FALSE);
     AppendMenu(hSysMenu, MF_SEPARATOR, 0, (LPSTR) NULL);
     AppendMenu(hSysMenu, MF_STRING, IDM_LAUNCH, (LPSTR) "Launch App");
     DrawMenuBar(hAppWnd);
}

/*****************************************************************************
** Clean up any application window leftovers. 
*/
VOID FAR CleanUpAppWnd(VOID)
{
	/* Destroy menus. */
	if (IsMenu(hMenu))
		DestroyMenu(hMenu);
}

/*****************************************************************************
** Check if we can exit. 
*/
BOOL FAR QueryExit(VOID)
{
     /* Debug thread running? */
     if (!hDebugThread)
          return TRUE;

     /* Continue with exit? */
     if (MessageBox(hAppWnd, "Exiting MDADebug will cause the debugee to terminate.\nContinue with exit?",
                         szTitle, MB_YESNO | MB_ICONSTOP) == IDYES)
          return TRUE;

     return FALSE;
}

/*******************************************************************************
** Application window message handler.
**/
WINDOWPROC MainWindowProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
     /* Decode message. */
     switch (iMsg)
     {
     	/* A menu command. */
     	case WM_COMMAND:
     		{     
     			/* Decode command. */
     			switch(LOWORD(wParam))
     			{
     				/* 
     				** Debug menu. 
     				*/
					
					/* Set new application. */
					case IDM_APP:
						if (SetApplication())
                                   WaitForApp(TRUE);
                              else
                                   IgnoreApp();
						return FALSE;
						
					/* Close the application. */
     				case IDM_EXIT:
     					PostMessage(hWnd, WM_CLOSE, 0, 0L);
     					return FALSE;
     					
					/* 
					** Edit menu. 
					*/

					/* Copy to the clipboard. */
     				case IDM_COPY:
     					return FALSE;
                         
					/* Clear the window. */
     				case IDM_CLEAR:
                              SendMessage(hMsgWnd, EM_SETSEL, 0, (LPARAM)-1);
                              SendMessage(hMsgWnd, EM_REPLACESEL, FALSE, (LPARAM)"");
     					return FALSE;
                         
					/* 
					** Help menu. 
					*/
                         
                         /* Show the about box. */
					case IDM_ABOUT:
						ShowAboutBox();
						return FALSE;

     				default:
						break;
     			}
     		}
     		break;

          /* System menu. */
          case WM_SYSCOMMAND:
               if (wParam == IDM_LAUNCH)
               {
                    /* Launch application. */
                    LaunchApp();
                    return FALSE;
               }
               break;

          /* Watch finished. */
          case WM_ENDWATCH:
               /* Re-enable preferences menu item. */
               EnableMenuItem(hMenu, IDM_APP, MF_BYCOMMAND | MF_ENABLED);
               EnableMenuItem(hSysMenu, IDM_LAUNCH, MF_BYCOMMAND | MF_ENABLED);

               /* Restart watch if okay. */
               if (wParam == ENDED_OKAY)
                    WaitForApp(FALSE);
               else /* wait till finished. */
                    WaitForDebugger();
               return FALSE;

		/* Window resized. */
		case WM_SIZE:
			/* Ignore iconification or other window changes. */
			if ( (wParam != SIZE_MAXIMIZED) && (wParam != SIZE_RESTORED) )
				return FALSE;

			/* Resize our children. */
			ResizeDil(LOWORD(lParam), HIWORD(lParam));
			ResizeClient(LOWORD(lParam), HIWORD(lParam));
			return FALSE;
     		
		/* A menu item selected. */
		case WM_MENUSELECT:
			if ( (HIWORD(wParam) & MF_POPUP) || (HIWORD(wParam) & MF_SEPARATOR) )
				SetHint((LPSTR) "");
			else
				SetHint(LoadTmpRscString(IDS_MENUHINTS+LOWORD(wParam)));
			return FALSE;
		
     	/* Exit. */
     	case WM_CLOSE:
               if (QueryExit())
               {
                    /* Kill timer and window. */
                    IgnoreApp();
     		     DestroyWindow(hWnd);
     		}
     		return FALSE;

          /* Exit procedure. */
          case WM_DESTROY:  
			/* Send WM_QUIT. */
               PostQuitMessage(0);
               return FALSE;
                              
          /* Safe. */
          default:
     		break;
     }

     return DefWindowProc(hWnd, iMsg, wParam, lParam);
}
