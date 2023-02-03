#include "TopmoreKitSSDDeviceItem.h"

#include <QtWidgets/QTabBar>

#include "TopmoreKitCustomTabStyle.h"

TopmoreKitSSDDeviceItem::TopmoreKitSSDDeviceItem(QWidget *parent)
	: QWidget(parent)
{
    this->ui.setupUi(this);

    this->ui.FeaturesTabWidget->tabBar()->setStyle(
        new TopmoreKitCustomTabStyle());

    this->UpdateInformation();
}

TopmoreKitSSDDeviceItem::~TopmoreKitSSDDeviceItem()
{
}

void TopmoreKitSSDDeviceItem::UpdateInformation()
{
    this->ui.FirmwarePlainTextEdit->setPlainText(u8"3.F.F.R2");
    this->ui.InterfacePlainTextEdit->setPlainText(u8"UASP (NVM Express)");
    this->ui.TransferModePlainTextEdit->setPlainText(u8"---- | ----");
    this->ui.SerialNumberPlainTextEdit->setPlainText(u8"DTMCSC11220052");
    this->ui.HostTotalReadsPlainTextEdit->setPlainText(u8"45 GB");
    this->ui.HostTotalWritesPlainTextEdit->setPlainText(u8"88 GB");
    this->ui.PowerOnHoursPlainTextEdit->setPlainText(u8"2 小时");
    this->ui.PowerOnCountPlainTextEdit->setPlainText(u8"14 次");

    this->ui.HealthStatusPushButton->setText(u8"健康度\n100 %");
    this->ui.TemperaturePushButton->setText(u8"温度\n42 ℃");

    this->ui.SmartInformationTreeWidget->clear();

    {
        QTreeWidgetItem* Item = new QTreeWidgetItem(
            this->ui.SmartInformationTreeWidget);
        Item->setText(0, u8"01");
        Item->setText(1, u8"严重警告标志");
        Item->setText(2, u8"0");
    }

    {
        QTreeWidgetItem* Item = new QTreeWidgetItem(
            this->ui.SmartInformationTreeWidget);
        Item->setText(0, u8"02");
        Item->setText(1, u8"综合温度");
        Item->setText(2, u8"315");
    }

    while (QLayoutItem* Item = this->ui.PartitionTableLayout->takeAt(0))
    {
        if (QWidget* Widget = Item->widget())
        {
            Widget->deleteLater();
        }
        delete Item;
    }

    {
        QPushButton* PartitionButton = new QPushButton();

        PartitionButton->setMinimumSize(QSize(0, 64));
        PartitionButton->setMaximumSize(QSize(16777215, 64));

        QSizePolicy SizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        SizePolicy.setHorizontalStretch(5);
        PartitionButton->setSizePolicy(SizePolicy);

        PartitionButton->setText(u8"Data (E:) 500 GB\nNTFS");

        this->ui.PartitionTableLayout->addWidget(PartitionButton);
    }

    {
        QPushButton* PartitionButton = new QPushButton();

        PartitionButton->setMinimumSize(QSize(0, 64));
        PartitionButton->setMaximumSize(QSize(16777215, 64));

        QSizePolicy SizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        SizePolicy.setHorizontalStretch(2);
        PartitionButton->setSizePolicy(SizePolicy);

        PartitionButton->setText(u8"Workspace (F:) 200 GB\nNTFS");

        this->ui.PartitionTableLayout->addWidget(PartitionButton);
    }

    {
        QPushButton* PartitionButton = new QPushButton();

        PartitionButton->setMinimumSize(QSize(0, 64));
        PartitionButton->setMaximumSize(QSize(16777215, 64));

        QSizePolicy SizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        SizePolicy.setHorizontalStretch(13);
        PartitionButton->setSizePolicy(SizePolicy);

        PartitionButton->setText(u8"Backup (G:) 1300 GB\nNTFS");

        this->ui.PartitionTableLayout->addWidget(PartitionButton);
    }

    //this->ui.SmartInformationTreeWidget->add
}
