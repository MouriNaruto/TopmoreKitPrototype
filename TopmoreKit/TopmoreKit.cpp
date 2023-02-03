/*
 * PROJECT:   TOPMORE Kit
 * FILE:      TopmoreKit.cpp
 * PURPOSE:   Implementation for TOPMORE Kit
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

#include "TopmoreKitMainWindow.h"

#include <Windows.h>

int main(int argc, char* argv[])
{
    ::CoInitialize(nullptr);

    QApplication Application(argc, argv);

    TopmoreKitMainWindow MainWindow;
    MainWindow.show();

    return Application.exec();
}
