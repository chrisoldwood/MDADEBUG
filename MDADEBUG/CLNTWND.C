/*****************************************************************************
** (C) Chris Wood 1995.
**
** CLNTWND.C - Client window.
**
******************************************************************************
*/

#include "af.h"
#include "winutils.h"
#include "menursc.h"
#include "strngrsc.h"

/**** Defs. *****************************************************************/
#define CLIENT_WND_ID	20				/* This windows ID. */
#define MESSAGE_WND_ID   21                  /* The message box ID. */

/**** Global Vars. **********************************************************/
HWND		hCliWnd;						/* Client window. */
int		iCliWidth, iCliHeight;			/* Client window dimensions. */
HWND      hMsgWnd;                           /* Message window. */

extern HINSTANCE hAppInst;              	/* Application instance. */
extern HWND hAppWnd;					/* Application window. */
extern int iDilHeight;					/* Dil window height. */

/**** Prototypes. ***********************************************************/
WINDOWPROC ClientWindowProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
VOID NEAR PaintClient(HDC hDC);

/*****************************************************************************
** Register the client window class.
*/
BOOL FAR RegisterClientWnd(VOID)
{    
	WNDCLASS	WndClass;
	
	/* Setup window class parameters. */
	WndClass.style         = CS_VREDRAW | CS_HREDRAW;
	WndClass.lpfnWndProc   = (WNDPROC) ClientWindowProc;
	WndClass.cbClsExtra    = 0;
	WndClass.cbWndExtra    = 0;
	WndClass.hInstance     = hAppInst;
	WndClass.hIcon         = NULL;
	WndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName  = NULL;
	WndClass.lpszClassName = LoadTmpRscString(IDS_CLIWNDCLASS);

	return RegisterClass(&WndClass);
}

/*****************************************************************************
** Create the client window.
*/
VOID FAR CreateClientWnd(VOID)
{
	RECT		rcParent;		/* The parents client dimensions. */
	
	/* Get parent size. */
	GetClientRect(hAppWnd, (LPRECT) &rcParent);

	/* Save window width. */
	iCliWidth  = rcParent.right;
	iCliHeight = rcParent.bottom - iDilHeight;

	/* Create the window. */
	hCliWnd = CreateWindow(LoadTmpRscString(IDS_CLIWNDCLASS),
						(LPSTR) NULL,
						WS_CHILD | WS_CLIPSIBLINGS,
						0, 0,
						iCliWidth, iCliHeight,
						hAppWnd,
						(HMENU)CLIENT_WND_ID,
						hAppInst,
						NULL);

	AssertEx(IsValidWnd(hCliWnd), "CreateWindow()");

     /* Create the message window that goes over the client. */
     hMsgWnd = CreateWindow("EDIT",
						(LPSTR) NULL,
						WS_CHILD | WS_CLIPSIBLINGS |
						ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_LEFT | ES_WANTRETURN | ES_MULTILINE, 
						0, 2,
						iCliWidth, iCliHeight-2,
						hCliWnd,
						(HMENU)MESSAGE_WND_ID,
						hAppInst,
						NULL);

	AssertEx(IsValidWnd(hMsgWnd), "CreateWindow()");

     /* Make it visible. */
	ShowWindow(hMsgWnd, SW_SHOW);
}

/*******************************************************************************
** Client window message handler.
**/
WINDOWPROC ClientWindowProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
     /* Decode message. */
     switch (iMsg)
     {
          case WM_COMMAND:
               if ( (LOWORD(wParam) == MESSAGE_WND_ID) 
                 && (HIWORD(wParam) == EN_ERRSPACE) )
               {
                    int iPos;

                    /* Turn off redraws. */
                    SendMessage(hMsgWnd, WM_SETREDRAW, FALSE, 0);

                    /* Get position of first 50 lines. */
                    iPos = SendMessage(hMsgWnd, EM_LINEINDEX, 50, 0);

                    /* Delete start text. */
                    SendMessage(hMsgWnd, EM_SETSEL, 0, iPos);
                    SendMessage(hMsgWnd, EM_REPLACESEL, FALSE, (LPARAM)"");

                    /* Return cursor to end. */
                    SendMessage(hMsgWnd, EM_SETSEL, 65530, 65530);

                    /* Turn on redraws. */
                    SendMessage(hMsgWnd, WM_SETREDRAW, TRUE, 0);
               }
               break;

          /* Redraw a portion of the window. */
          case WM_PAINT:
          	{
			PAINTSTRUCT ps;
          	
			/* Draw DIL. */
			BeginPaint(hWnd, (LPPAINTSTRUCT) &ps);
			PaintClient(ps.hdc);
			EndPaint(hWnd, (LPPAINTSTRUCT) &ps);
			}
			return FALSE;

		/* Window being destroyed. */
		case WM_DESTROY:
               DestroyWindow(hMsgWnd);
			return FALSE;
			
          /* Safe. */
          default:
     		break;
     }

     return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

/*******************************************************************************
** Resize the client window.
** This window sits in between the toolbar and the dil.
**/
VOID FAR ResizeClient(int iNewWidth, int iNewHeight)
{
	/* Save new width. */
	iCliWidth  = iNewWidth;
	iCliHeight = iNewHeight - iDilHeight;
	
	/* Resize. */
	MoveWindow(hCliWnd, 0, 0, iCliWidth, iCliHeight, TRUE);
	MoveWindow(hMsgWnd, 0, 2, iCliWidth, iCliHeight-2, TRUE);
}

/*******************************************************************************
** Paint the client border.
**/
VOID NEAR PaintClient(HDC hDC)
{
	HPEN  hOldPen;		// Old device pen.
	
	/* Draw window top black line. */
	hOldPen = SelectObject(hDC, GetStockObject(BLACK_PEN));
	MoveToEx(hDC, 0, 0, NULL);
	LineTo(hDC, iCliWidth, 0);

	/* Draw window top white line. */
	SelectObject(hDC, GetStockObject(WHITE_PEN));
	MoveToEx(hDC, 0, 1, NULL);
	LineTo(hDC, iCliWidth, 1);

	/* Restore HDC. */
	SelectObject(hDC, hOldPen);
}
