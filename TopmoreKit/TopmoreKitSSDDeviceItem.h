#pragma once

#include <QWidget>
#include "ui_TopmoreKitSSDDeviceItem.h"

#include <AtaSmart.h>

class TopmoreKitSSDDeviceItem : public QWidget
{
	Q_OBJECT

public:
	TopmoreKitSSDDeviceItem(QWidget *parent = nullptr);
	~TopmoreKitSSDDeviceItem();

    void UpdateInformation(
        CAtaSmart::ATA_SMART_INFO const& DiskInfo);

private:
	Ui::TopmoreKitSSDDeviceItemClass ui;
};
