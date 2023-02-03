#pragma once

#include <QWidget>
#include "ui_TopmoreKitSSDDeviceItem.h"

class TopmoreKitSSDDeviceItem : public QWidget
{
	Q_OBJECT

public:
	TopmoreKitSSDDeviceItem(QWidget *parent = nullptr);
	~TopmoreKitSSDDeviceItem();

private:
	Ui::TopmoreKitSSDDeviceItemClass ui;
};
