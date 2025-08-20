# MDA Debug

A debugging tool that dumps all the Trace output from the OS and from calls to
`OutputDebugString()` onto the secondary monochrome display. It was written
because there was no Win32 version of `DBWIN`*. It accesses the MDA through a
Win16 .DLL, which in turn is accessed by a Win32 thunking .DLL.

Note: This requires the Thunk compiler from the DDK.

`*` The Sysinternals tool `DbgView` didn't appear until two years later in 1998.

Chris Oldwood\
29th January 2004
