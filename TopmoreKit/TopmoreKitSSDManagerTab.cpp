#include "TopmoreKitSSDManagerTab.h"

#include "TopmoreKitSSDDeviceItem.h"

TopmoreKitSSDManagerTab::TopmoreKitSSDManagerTab(QWidget *parent)
	: QWidget(parent)
{
	this->ui.setupUi(this);

    this->ui.DrivesTabWidget->addTab(
        new TopmoreKitSSDDeviceItem(),
        u8"TOPMORE Pesudo SSD (Disk 3)");

    this->ui.DrivesTabWidget->addTab(
        new TopmoreKitSSDDeviceItem(),
        u8"TOPMORE Pesudo SSD (Disk 4)");
}

TopmoreKitSSDManagerTab::~TopmoreKitSSDManagerTab()
{
}
