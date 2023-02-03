#include "TopmoreKitSSDManagerTab.h"

#include "TopmoreKitSSDDeviceItem.h"

#pragma comment(lib, "comsupp.lib")

TopmoreKitSSDManagerTab::TopmoreKitSSDManagerTab(QWidget *parent)
	: QWidget(parent)
{
	this->ui.setupUi(this);

    CAtaSmart AtaSmart;

    AtaSmart.FlagUsbSat = TRUE;
    AtaSmart.FlagUsbIodata = TRUE;
    AtaSmart.FlagUsbSunplus = TRUE;
    AtaSmart.FlagUsbLogitec = TRUE;
    AtaSmart.FlagUsbProlific = TRUE;
    AtaSmart.FlagUsbJmicron = TRUE;
    AtaSmart.FlagUsbCypress = TRUE;
    AtaSmart.FlagUsbASM1352R = TRUE;
    AtaSmart.FlagUsbMemory = FALSE;
    AtaSmart.FlagUsbNVMeJMicron = TRUE;
    AtaSmart.FlagUsbNVMeASMedia = TRUE;
    AtaSmart.FlagUsbNVMeRealtek = TRUE;
    AtaSmart.FlagMegaRAID = TRUE;

    BOOL UseWmi = TRUE;
    BOOL AdvancedDiskSearch = FALSE;
    BOOL WorkaroundHD204UI = FALSE;
    BOOL WorkaroundAdataSsd = TRUE;
    BOOL HideNoSmartDisk = FALSE;

    AtaSmart.Init(
        UseWmi,
        AdvancedDiskSearch,
        nullptr,
        WorkaroundHD204UI,
        WorkaroundAdataSsd,
        HideNoSmartDisk);

    std::size_t DeviceCount = AtaSmart.vars.GetCount();
    for (size_t i = 0; i < DeviceCount; ++i)
    {
        CAtaSmart::ATA_SMART_INFO& Current = AtaSmart.vars[i];
        if (0 != Current.Model.Find(L"TOPMORE"))
        {
            continue;
        }
        
        TopmoreKitSSDDeviceItem* CurrentUI = new TopmoreKitSSDDeviceItem();

        CurrentUI->UpdateInformation(Current);

        this->ui.DrivesTabWidget->addTab(
            CurrentUI,
            QString::fromWCharArray(std::format(
                L"{} {} GB (Disk {})",
                Current.Model.GetBuffer(),
                Current.TotalDiskSize / 1024,
                i).c_str()));
    }
}

TopmoreKitSSDManagerTab::~TopmoreKitSSDManagerTab()
{
}
