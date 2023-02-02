#include "TopmoreKitMainWindow.h"

#include "TopmoreKitCustomTabStyle.h"

#include "TopmoreKitSettingsTab.h"

TopmoreKitMainWindow::TopmoreKitMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

    ui.FeatureTabWidget->tabBar()->setStyle(
        new TopmoreKitCustomTabStyle());

    ui.FeatureTabWidget->addTab(
        new TopmoreKitSettingsTab(),
        u8"设置");
}

TopmoreKitMainWindow::~TopmoreKitMainWindow()
{
}
