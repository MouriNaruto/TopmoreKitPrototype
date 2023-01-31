// stdafx.cpp : source file that includes just the standard includes
// DiskInfo.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

#include <assert.h>

int AfxMessageBox(LPCTSTR lpszText, UINT nType, UINT nIDHelp)
{
    UNREFERENCED_PARAMETER(nIDHelp);

    // determine icon based on type specified
    if ((nType & MB_ICONMASK) == 0)
    {
        switch (nType & MB_TYPEMASK)
        {
        case MB_OK:
        case MB_OKCANCEL:
            nType |= MB_ICONEXCLAMATION;
            break;

        case MB_YESNO:
        case MB_YESNOCANCEL:
            nType |= MB_ICONQUESTION;
            break;

        case MB_ABORTRETRYIGNORE:
        case MB_RETRYCANCEL:
            // No default icon for these types, since they are rarely used.
            // The caller should specify the icon.
            break;
        }
    }

    return ::MessageBoxW(
        nullptr,
        lpszText,
        L"TOPMORE Kit",
        nType);
}

int AfxMessageBox(UINT nIDPrompt, UINT nType, UINT nIDHelp)
{
    CString string;
    if (!string.LoadString(nIDPrompt))
    {
        assert(FALSE);
    }
    if (nIDHelp == (UINT)-1)
        nIDHelp = nIDPrompt;
    return AfxMessageBox(string, nType, nIDHelp);
}

BOOL AfxExtractSubString(
    CString& rString,
    LPCTSTR lpszFullString,
    int iSubString,
    TCHAR chSep)
{
    if (lpszFullString == NULL)
        return FALSE;

    while (iSubString--)
    {
        lpszFullString = _tcschr(lpszFullString, chSep);
        if (lpszFullString == NULL)
        {
            rString.Empty();        // return empty string as well
            return FALSE;
        }
        lpszFullString++;       // point past the separator
    }
    LPCTSTR lpchEnd = _tcschr(lpszFullString, chSep);
    int nLen = (lpchEnd == NULL) ?
        static_cast<int>(_tcslen(lpszFullString)) : (int)(lpchEnd - lpszFullString);
    assert(nLen >= 0);
    Checked::memcpy_s(rString.GetBufferSetLength(nLen), nLen * sizeof(TCHAR),
        lpszFullString, nLen * sizeof(TCHAR));
    rString.ReleaseBuffer();	// Need to call ReleaseBuffer 
    // after calling GetBufferSetLength
    return TRUE;
}
