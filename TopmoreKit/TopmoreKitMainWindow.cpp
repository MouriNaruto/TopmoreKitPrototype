#include "TopmoreKitMainWindow.h"

#include "TopmoreKitCustomTabStyle.h"

TopmoreKitMainWindow::TopmoreKitMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
    ui.FeatureTabWidget->tabBar()->setStyle(
        new TopmoreKitCustomTabStyle());
}

TopmoreKitMainWindow::~TopmoreKitMainWindow()
{
}
