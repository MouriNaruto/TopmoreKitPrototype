#pragma once

#include <QMainWindow>
#include "ui_TopmoreKitMainWindow.h"

class TopmoreKitMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	TopmoreKitMainWindow(QWidget *parent = nullptr);
	~TopmoreKitMainWindow();

private:
	Ui::TopmoreKitMainWindowClass ui;
};
