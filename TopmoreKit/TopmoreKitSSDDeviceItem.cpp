#include "TopmoreKitSSDDeviceItem.h"

#include <QtWidgets/QTabBar>

#include "TopmoreKitCustomTabStyle.h"

TopmoreKitSSDDeviceItem::TopmoreKitSSDDeviceItem(QWidget *parent)
	: QWidget(parent)
{
    this->ui.setupUi(this);

    this->ui.FeaturesTabWidget->tabBar()->setStyle(
        new TopmoreKitCustomTabStyle());
}

TopmoreKitSSDDeviceItem::~TopmoreKitSSDDeviceItem()
{
}
