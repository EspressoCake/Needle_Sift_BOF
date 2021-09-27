#pragma once

#include <windows.h>
#include <stdio.h>

WINBASEAPI  int         WINAPI      KERNEL32$lstrlenW (LPCWSTR lpString);
WINBASEAPI  int         __cdecl     MSVCRT$fclose (FILE *fStream);
WINBASEAPI  errno_t     __cdecl     MSVCRT$fopen_s (FILE **fStream, const char* _fName, const char *_Mode);
WINBASEAPI  int         __cdecl     MSVCRT$fseek (FILE *fStream, long _Offset, int _Origin);
WINBASEAPI  long        __cdecl     MSVCRT$ftell (FILE *fStream);
WINBASEAPI  int         __cdecl     MSVCRT$getc (FILE *fStream);
WINBASEAPI  long        __cdecl     MSVCRT$rewind (FILE *fStream);
WINBASEAPI  char*       __cdecl     MSVCRT$strstr (char* _String, const char* _SubString);
WINBASEAPI  void*       __cdecl     MSVCRT$memset (void* _Dst, int _Val, size_t Size);