/*****************************************************************************
** (C) Chris Wood 1995.
**
** DILWND.C - DIL window.
**
******************************************************************************
*/

#include "af.h"
#include "winutils.h"
#include "menursc.h"
#include "strngrsc.h"

/**** Defs. *****************************************************************/
#define DIL_WND_ID	21					/* This windows ID. */

#define DIL_HINT		0				/* DIL in hint mode. */
#define DIL_PROGRESS	1				/* DIL in progress mode. */

#define TOP_BORDER		5				/* Top border size. */
#define BOT_BORDER		3				/* Bottom border size. */
#define LFT_BORDER		3				/* Left border size. */
#define RGT_BORDER		3				/* Right border size.*/
#define FIELD_GAP		3				/* Field gap. */

#define FONT_HEIGHT		15				/* DIL font height. */
#define TEXT_OFFSET		3				/* Text offset into hint line. */

#define MAX_HINT_LEN	128				/* Maximum length of hint. */

/**** Global Vars. **********************************************************/
HWND		hDilWnd;						/* DIL window. */
HFONT	hDilFont;						/* Text font. */
int		iDilWidth, iDilHeight;			/* DIL window dimensions. */
int	 	iDilFontWt, iDilFontHt;			/* Font width & height. */
int	 	iDilMode;						/* Information mode. */
BYTE 	szDilHint[MAX_HINT_LEN];			/* DIL hint. */
int  	iDilMax;						/* Maximum progress. */
int	 	iDilLast;						/* Last progress value. */

extern HINSTANCE hAppInst;              	/* Application instance. */
extern HWND hAppWnd;					/* Application window. */

/**** Prototypes. ***********************************************************/
WINDOWPROC DilWindowProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
VOID NEAR PaintDil(HDC hDC);

/*****************************************************************************
** Register the DIL window class.
*/
BOOL FAR RegisterDilWnd(VOID)
{    
	WNDCLASS	WndClass;
	
	/* Setup window class parameters. */
	WndClass.style         = CS_VREDRAW | CS_HREDRAW;
	WndClass.lpfnWndProc   = (WNDPROC) DilWindowProc;
	WndClass.cbClsExtra    = 0;
	WndClass.cbWndExtra    = 0;
	WndClass.hInstance     = hAppInst;
	WndClass.hIcon         = NULL;
	WndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = GetStockObject(LTGRAY_BRUSH);
	WndClass.lpszMenuName  = NULL;
	WndClass.lpszClassName = LoadTmpRscString(IDS_DILWNDCLASS);

	return RegisterClass(&WndClass);
}

/*****************************************************************************
** Create the DIL window.
*/
VOID FAR CreateDilWnd(VOID)
{
	RECT		rcParent;		/* The parents client dimensions. */
	HDC 		hScnDC;		/* Screen device. */
	HFONT	hOldFont;		/* Old device font. */
     SIZE      Extents;       /* Text extents. */
	
	/* Get parent size. */
	GetClientRect(hAppWnd, (LPRECT) &rcParent);

	/* Get DIL font. */
	hDilFont = CreateFont(FONT_HEIGHT, 0, 0, 0, FW_NORMAL, 0, 0, 0, 
     					ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
     					DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial" );
     
	/* Create screen HDC. */
	hScnDC = GetDC(NULL);

	/* Set font and get extents. */
	hOldFont = SelectObject(hScnDC, hDilFont);
	GetTextExtentPoint32(hScnDC, (LPSTR) "ABCDEFGH", 8, &Extents);
	SelectObject(hScnDC, hOldFont);
	
	// Extract extents and save.
	iDilFontHt = Extents.cy;
	iDilFontWt = Extents.cx / 8;
     
	/* Free HDC. */
	ReleaseDC(NULL, hScnDC);

	/* Save window width. */
	iDilWidth  = rcParent.right;
	iDilHeight = iDilFontHt + TOP_BORDER + BOT_BORDER;

	/* Create the window. */
	hDilWnd = CreateWindow(LoadTmpRscString(IDS_DILWNDCLASS),
						(LPSTR) NULL,
						WS_CHILD | WS_CLIPSIBLINGS,
						0, rcParent.bottom - iDilHeight,
						iDilWidth, iDilHeight,
						hAppWnd,
						(HMENU)DIL_WND_ID,
						hAppInst,
						NULL);

	AssertEx(IsValidWnd(hDilWnd), "CreateWindow()");

	/* Set hint mode. */
	iDilMode = DIL_HINT;
     
	/* Set the hint to "". */
	szDilHint[0] = '\0';
	
	/* Reset progress counters. */
	iDilMax  = 0;
	iDilLast = 0;
}

/*******************************************************************************
** DIL window message handler.
**/
WINDOWPROC DilWindowProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
     /* Decode message. */
     switch (iMsg)
     {
          /* Redraw a portion of the window. */
          case WM_PAINT:
          	{
			PAINTSTRUCT ps;
          	
			/* Draw DIL. */
			BeginPaint(hWnd, (LPPAINTSTRUCT) &ps);
			PaintDil(ps.hdc);
			EndPaint(hWnd, (LPPAINTSTRUCT) &ps);
			}
			return FALSE;

		/* Window being destroyed. */
		case WM_DESTROY:
			DeleteObject(hDilFont);
			return FALSE;
			
          /* Safe. */
          default:
     		break;
     }

     return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

/*******************************************************************************
** Resize the DIL window.
** This window sits at the bottom of the main window.
**/
VOID FAR ResizeDil(int iNewWidth, int iNewHeight)
{
	/* Save new width. */
	iDilWidth = iNewWidth;
	
	/* Resize. */
	MoveWindow(hDilWnd, 0, iNewHeight-iDilHeight, iDilWidth, iDilHeight, TRUE);
}

/*******************************************************************************
** Paint the DIL.
** The DIL consists of a recessed border with a hint. It may also be displaying
** a progress meter, if in progress mode.
**/
VOID NEAR PaintDil(HDC hDC)
{
	HPEN  hOldPen;		// Old device pen.
	HFONT hOldFont;	// Old device font.
	RECT  rcClip;		// Text clipping rectangle.
	
	/*
	** Draw border.
	*/
	  
	/* Draw window top black line. */
	hOldPen = SelectObject(hDC, GetStockObject(BLACK_PEN));
	MoveToEx(hDC, 0, 0, NULL);
	LineTo(hDC, iDilWidth, 0);
	
     /* Draw hint border top-left portion. */
	MoveToEx(hDC, LFT_BORDER, iDilHeight-BOT_BORDER, NULL);
	LineTo(hDC, LFT_BORDER, TOP_BORDER);
	LineTo(hDC, iDilWidth-RGT_BORDER, TOP_BORDER);

	/* Draw window top white line. */
	SelectObject(hDC, GetStockObject(WHITE_PEN));
	MoveToEx(hDC, 0, 1, NULL);
	LineTo(hDC, iDilWidth, 1);

     /* Draw hint border bottom-right portion. */
	MoveToEx(hDC, LFT_BORDER, iDilHeight-BOT_BORDER, NULL);
	LineTo(hDC, iDilWidth-RGT_BORDER, iDilHeight-BOT_BORDER);
	LineTo(hDC, iDilWidth-RGT_BORDER, TOP_BORDER);
     
	/* Restore HDC. */
	SelectObject(hDC, hOldPen);

	/*
	** Draw hint.
	*/                 
	
	/* Setup text. */
	hOldFont = SelectObject(hDC, hDilFont);
	SetTextAlign(hDC, TA_TOP | TA_LEFT);
	SetBkMode(hDC, TRANSPARENT);
	
	/* Setup clipping rectangle. */
	rcClip.left   = LFT_BORDER;
	rcClip.top    = TOP_BORDER;
	rcClip.right  = iDilWidth-RGT_BORDER;
	rcClip.bottom = iDilHeight-BOT_BORDER;
	
	/* Output text. */
	ExtTextOut(hDC, LFT_BORDER + TEXT_OFFSET, TOP_BORDER, ETO_CLIPPED, 
				(LPRECT) &rcClip, (LPSTR) szDilHint, lstrlen((LPSTR) szDilHint), NULL);
	     
	/* Restore HDC. */
	SelectObject(hDC, hOldFont);
	
	/* 
	** Draw mode information.
	*/
	if (iDilMode == DIL_PROGRESS)
	{
		RECT	  rcArea;			/* Area to fill. */
		int	  iMeterWidth;		/* Meter width. */

	     /* Calculate meter width. */
     	iMeterWidth = iDilWidth - LFT_BORDER - RGT_BORDER;
     
		/* Calculate the new area. */
		rcArea.left   = LFT_BORDER;
		rcArea.top    = TOP_BORDER;
		rcArea.right  = (int) (((long) iDilLast * (long) iMeterWidth) / (long) iDilMax);
		rcArea.bottom = iDilHeight - BOT_BORDER + 1;

		/* Adjust for border. */
		rcArea.right += LFT_BORDER;
		
		/* Perform the update. */
		InvertRect(hDC, (LPRECT) &rcArea);
	}
}

/*******************************************************************************
** Set the hint.
** If the hint is the same as before it will ignore it.
**/
VOID FAR SetHint(LPSTR lpszHint)
{                
	AssertEx(IsValidPtr(lpszHint), "SetHint(lpszHint)");

	/* Check for change. */
	if (lstrcmp(lpszHint, (LPSTR) szDilHint) == 0)
		return;

	/* Copy in new string and re-draw. */
	lstrcpy((LPSTR) szDilHint, lpszHint);

	/* Redraw. */
	InvalidateRect(hDilWnd, NULL, TRUE);
	UpdateWindow(hDilWnd);
}

/*******************************************************************************
** Initialise the progress meter.
**/
VOID FAR InitProgress(LPSTR lpszProcess, int iMax)
{    
	AssertEx(IsValidPtr(lpszProcess), "InitProgress(lpszProcess)");
	AssertEx(iMax, "InitProgress(iMax)");

	/* Set DIL mode. */
	iDilMode = DIL_PROGRESS;
	
	/* Setup values. */
	iDilMax  = iMax;
	iDilLast = 0;
	
	/* Copy in process string. */
	lstrcpy((LPSTR) szDilHint, lpszProcess);
	
	/* Redraw. */
	InvalidateRect(hDilWnd, NULL, TRUE);
	UpdateWindow(hDilWnd);
}

/*******************************************************************************
** Set the current progress.
**/
VOID FAR SetProgress(int iVal)
{    
	RECT	rcArea;			/* Area to fill. */
	int	iMeterWidth;		/* Meter width. */
	HDC	hDC;				/* Window HDC. */
	
	AssertEx((iVal <= iDilMax), "SetProgress(iVal)");

	/* Check value for change. */
	if (iVal <= iDilLast)
		return;
     
	/* Calculate meter width. */
	iMeterWidth = iDilWidth - LFT_BORDER - RGT_BORDER;
     
	/* Calculate the new area. */
	rcArea.left   = (int) (((long) iDilLast * (long) iMeterWidth) / (long) iDilMax);
	rcArea.top    = TOP_BORDER;
	rcArea.right  = (int) (((long) iVal * (long) iMeterWidth) / (long) iDilMax);
	rcArea.bottom = iDilHeight - BOT_BORDER + 1;

	/* Adjust for border. */
	rcArea.left  += LFT_BORDER;
	rcArea.right += LFT_BORDER;
		
	/* Get an HDC for the window. */
	hDC = GetDC(hDilWnd);

	/* Perform the update. */
	InvertRect(hDC, (LPRECT) &rcArea);

	/* Free HDC. */
	ReleaseDC(hDilWnd, hDC);
     
	/* Update current & last value. */
	iDilLast  = iVal;
}

/*******************************************************************************
** Terminate the progress meter.
**/
VOID FAR TermProgress(VOID)
{
	/* Reset values. */
	iDilMax = iDilLast = 0;
	
	/* Reset DIL mode. */
	iDilMode = DIL_HINT;
	
	/* Create empty string. */
	szDilHint[0] = '\0';
	
	/* Redraw. */
	InvalidateRect(hDilWnd, NULL, TRUE);
	UpdateWindow(hDilWnd);
}
