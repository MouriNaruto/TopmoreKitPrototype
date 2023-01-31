// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#include <Windows.h>

#include <atlcoll.h>
#include <atlstr.h>

int AfxMessageBox(
    LPCTSTR lpszText,
    UINT nType = MB_OK,
    UINT nIDHelp = 0);

int AfxMessageBox(
    UINT nIDPrompt,
    UINT nType = MB_OK,
    UINT nIDHelp = (UINT)-1);

BOOL AfxExtractSubString(
    CString& rString,
    LPCTSTR lpszFullString,
    int iSubString,
    TCHAR chSep);

#include <comutil.h>

#include "CommonFx.h"
#include "UtilityFx.h"
