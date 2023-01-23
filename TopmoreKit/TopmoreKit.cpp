/*
 * PROJECT:   TOPMORE Kit
 * FILE:      TopmoreKit.cpp
 * PURPOSE:   Implementation for TOPMORE Kit
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

//#include <Windows.h>

#include <stdafx.h>

//ole32.lib

#pragma comment(lib, "comsupp.lib")

#include <AtaSmart.h>

int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nShowCmd);

    /*::MessageBoxW(
        nullptr,
        L"Hello World!\n",
        L"TOPMORE Kit",
        0);*/

    ::CoInitialize(nullptr);

    CAtaSmart AtaSmart;

    BOOL UseWmi = TRUE;
    BOOL AdvancedDiskSearch = FALSE;
    BOOL WorkaroundHD204UI = FALSE;
    BOOL WorkaroundAdataSsd = TRUE;
    BOOL HideNoSmartDisk = FALSE;

    AtaSmart.Init(
        UseWmi,
        AdvancedDiskSearch,
        nullptr,
        WorkaroundHD204UI,
        WorkaroundAdataSsd,
        HideNoSmartDisk);

    auto x = AtaSmart.vars[0];

    return 0;
}
