/*****************************************************************************
** (C) Chris Wood 1995.
**
** MDATHUNK.C - DLL thunking entry point.
**
******************************************************************************
*/

#include <windows.h>
#include "mdalib.h"
                 
/**** Defines & Global variables. *******************************************/
int iCursorX, iCursorY;			/* Cursor position. */
                 
/**** Prototypes. ***********************************************************/
BOOL FAR PASCAL __export DllEntryPoint (DWORD dwReason, WORD hInst, WORD wDS,
                               		WORD wHeapSize, DWORD dwReserved1,
                               		WORD wReserved2);

BOOL FAR PASCAL thk_ThunkConnect16(LPSTR pszDll16, LPSTR pszDll32, WORD hInst,
                                   DWORD dwReason);

/******************************************************************************
** This is the 16-bit call that draws the program title on the MDA.
*/
void FAR PASCAL __export SetTitle16(LPSTR lpszTitle)
{
	MDADrawLftString(2, 0, lpszTitle, BRIGHT);
}			

/******************************************************************************
** This is the 16-bit call that outputs the actual debug message.
*/
void FAR PASCAL __export ClearOutput16(void)
{
	/* Call inside window. */
	MDAClearRect(1, 1, 78, 23);
	
	/* Reset cursor. */
	iCursorX = 1;
	iCursorY = 1;
}

/******************************************************************************
** This is the 16-bit call that outputs the actual debug message.
*/
void FAR PASCAL __export OutputMsg16(LPSTR lpszMsg)
{    
	/* Loop through string a character at a time. */
	while (*lpszMsg)
	{
		/* Check for EOL. */
		if (*lpszMsg == '\n')
		{               
			/* Move down a line. */
			iCursorX = 1;
			iCursorY++;
			
			/* Check for bottom of display. */
			if (iCursorY >= 24)
			{
				/* Scroll messages up. */
				MDAScrollUp(1, 1, 78, 23);
				iCursorY--;
			}

			/* Skip it. */
			lpszMsg++;
			continue;
		}
	
		/* Check for unprintable chars. */
		if (*lpszMsg < ' ')
		{
			/* Skip it. */
			lpszMsg++;
			continue;
		}
		
		/* Write out a character. */
		MDADrawChar(iCursorX, iCursorY, *lpszMsg, NORMAL);
		
		/* Move along one character. */
		lpszMsg++;
		iCursorX++;
		
		/* Check for EOL. */
		if (iCursorX >= 79)
		{
			/* Reset to start of line. */
			iCursorX = 3;
			
			/* Move down a line. */
			iCursorY++;
			
			/* Check for bottom of display. */
			if (iCursorY >= 24)
			{
				/* Scroll messages up. */
				MDAScrollUp(1, 1, 78, 23);
				iCursorY--;
			}
		}
	}
}

/******************************************************************************
** This is the 16-bit call that outputs the actual debug message.
*/
BOOL FAR PASCAL __export DllEntryPoint (DWORD dwReason, WORD hInst, WORD wDS,
                               		WORD wHeapSize, DWORD dwReserved1, 
                               		WORD wReserved2)
{
    	if (!thk_ThunkConnect16("MDALIB16.DLL", "MDATHUNK.DLL", hInst, dwReason))
    	{	
    		MessageBox(NULL, "Thunk connection failed" , "DllEntryPoint16", MB_OK | MB_ICONASTERISK);
     	return FALSE;
	}
     
    	return TRUE;
}
