/*****************************************************************************
** (C) Chris Wood 1995.
**
** DLLENTRY.C - MDATHUNK.DLL entry and exit point.
**
******************************************************************************
*/

#include <windows.h>

// DLL Instance handle.
HINSTANCE hDLLInstance;

// Prototypes.
BOOL _stdcall thk_ThunkConnect32(LPSTR pszDll16, LPSTR pszDll32, HINSTANCE hInst,
                                 DWORD dwReason);

/*****************************************************************************
** Dll entry and exit point. This sets up the thunk into the 16-bit DLL.
** It returns TRUE if okay or FALSE if an error occurred.
*/
BOOL WINAPI DllEntryPoint(HINSTANCE hInstDLL, DWORD fdwReason, LPVOID lpReserved)
{
     // Save instance handle.
     hDLLInstance = hInstDLL;

     // Connect 16 and 32-bit DLLs.
     if (!(thk_ThunkConnect32("MDALIB16.DLL", "MDATHUNK.DLL", hInstDLL, fdwReason)))
     {
          MessageBox(NULL, "Thunk Connection failed", "DllEntryPoint32", MB_OK | MB_ICONASTERISK);
          return FALSE;
     }

     // Decode reason.
     switch (fdwReason)
     {
          /* Do nothing. */
          case DLL_PROCESS_ATTACH:
          case DLL_PROCESS_DETACH:
          case DLL_THREAD_ATTACH:
          case DLL_THREAD_DETACH:
          default:
               break;
     }

	return TRUE;
}
