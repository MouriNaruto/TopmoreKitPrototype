#pragma once

#include <QWidget>
#include "ui_TopmoreKitSettingsTab.h"

class TopmoreKitSettingsTab : public QWidget
{
	Q_OBJECT

public:
	TopmoreKitSettingsTab(QWidget *parent = nullptr);
	~TopmoreKitSettingsTab();

private:
	Ui::TopmoreKitSettingsTabClass ui;
};
