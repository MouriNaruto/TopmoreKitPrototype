#include "TopmoreKitSettingsTab.h"

TopmoreKitSettingsTab::TopmoreKitSettingsTab(QWidget *parent)
	: QWidget(parent)
{
    this->ui.setupUi(this);

    this->connect(
        this->ui.WebsitePushButton,
        &QPushButton::clicked,
        this,
        []
    {
        ::OpenUriWithDefaultWebBrowser(L"https://www.topmore.com.tw");
    });

    this->connect(
        this->ui.SupportPushButton,
        &QPushButton::clicked,
        this,
        []
    {
        ::OpenUriWithDefaultWebBrowser(L"https://www.topmore.com.tw/edcontent_d.php?tb=3");
    });
}

TopmoreKitSettingsTab::~TopmoreKitSettingsTab()
{
}
