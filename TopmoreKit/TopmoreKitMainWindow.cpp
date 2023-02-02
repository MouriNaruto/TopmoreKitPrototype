#include "TopmoreKitMainWindow.h"

#include "TopmoreKitCustomTabStyle.h"

#include "TopmoreKitSSDManagerTab.h"
#include "TopmoreKitSettingsTab.h"

TopmoreKitMainWindow::TopmoreKitMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

    this->ui.FeatureTabWidget->tabBar()->setStyle(
        new TopmoreKitCustomTabStyle());

    this->ui.FeatureTabWidget->addTab(
        new TopmoreKitSSDManagerTab(),
        u8"SSD");

    this->ui.FeatureTabWidget->addTab(
        new TopmoreKitSettingsTab(),
        u8"设置");
}

TopmoreKitMainWindow::~TopmoreKitMainWindow()
{
}
