/*****************************************************************************
** (C) Chris Wood 1995.
**
** DEBUGOUT.C - MDATHUNK.DLL Thunking functions.
**
******************************************************************************
*/

#include <windows.h>

// DLL Instance handle.
extern HINSTANCE hDLLInstance;

// 16-bit call prototype
void PASCAL OutputMsg16(LPSTR lpszMsg);
void PASCAL ClearOutput16(void);
void PASCAL SetTitle16(LPSTR lpszTitle);

/*****************************************************************************
** This calls the 16-bit version of the message output function.
*/
void __declspec(dllexport) OutputMsg32(LPSTR lpszMsg)
{
     // Pass onto 16bit DLL.
     OutputMsg16(lpszMsg);
}

/*****************************************************************************
** This calls the 16-bit version of the clear output function.
*/
void __declspec(dllexport) ClearOutput32(void)
{
     // Pass onto 16bit DLL.
     ClearOutput16();
}

/*****************************************************************************
** This calls the 16-bit version of the set title function.
*/
void __declspec(dllexport) SetTitle32(LPSTR lpszTitle)
{
     // Pass onto 16bit DLL.
     SetTitle16(lpszTitle);
}
