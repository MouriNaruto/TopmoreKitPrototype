/*
 * PROJECT:   TOPMORE Kit
 * FILE:      TopmoreKit.cpp
 * PURPOSE:   Implementation for TOPMORE Kit
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include <Windows.h>

#pragma comment(lib, "comsupp.lib")

#include <AtaSmart.h>

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

#include "TopmoreKitMainWindow.h"

int main(int argc, char* argv[])
{
    ::CoInitialize(nullptr);

    QApplication Application(argc, argv);

    /*CAtaSmart AtaSmart;

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

    auto x = AtaSmart.vars[0];*/

    TopmoreKitMainWindow MainWindow;
    MainWindow.show();

    return Application.exec();
}
