#include "TopmoreKitSSDDeviceItem.h"

#include <QtWidgets/QTabBar>

#include "TopmoreKitCustomTabStyle.h"

const std::map<std::wstring, std::map<std::uint8_t, std::wstring>> g_SmartRes =
{
    {
        L"SmartSsd",
        {
            { 0x01, L"读取错误率" },
            { 0x02, L"吞吐性能" },
            { 0x03, L"启动时间" },
            { 0x04, L"启动-停止次数" },
            { 0x05, L"重新分配扇区计数" },
            { 0x06, L"读取通道余量" },
            { 0x07, L"寻址错误率" },
            { 0x08, L"寻址时间性能" },
            { 0x09, L"通电时间(小时)" },
            { 0x0A, L"启动重试次数" },
            { 0x0B, L"重新校准重试次数" },
            { 0x0C, L"通电次数" },
            { 0x0D, L"软读取错误率探针" },
            { 0xC0, L"不安全关机计数" },
            { 0xC2, L"温度" },
            { 0xC4, L"扇区位置重分配事件计数" },
            { 0xC5, L"有待处置扇区数" },
            { 0xC6, L"不可校正的扇区数" },
            { 0xF1, L"主机总计写入" },
            { 0xF2, L"主机总计读取" },
            { 0xFF, L"剩余寿命" },
        }
    },
    {
        L"SmartNVMe",
        {
            { 0x01, L"严重警告标志" },
            { 0x02, L"综合温度" },
            { 0x03, L"可用备用空间" },
            { 0x04, L"可用备用空间阈值" },
            { 0x05, L"已用寿命百分比" },
            { 0x06, L"读取单位计数" },
            { 0x07, L"写入单位计数" },
            { 0x08, L"主机读命令计数" },
            { 0x09, L"主机写命令计数" },
            { 0x0A, L"控制器忙状态时间" },
            { 0x0B, L"启动-关闭循环次数" },
            { 0x0C, L"通电时间(小时)" },
            { 0x0D, L"不安全关机计数" },
            { 0x0E, L"介质与数据完整性错误计数" },
            { 0x0F, L"错误日志项数" }
        }
    }
};

TopmoreKitSSDDeviceItem::TopmoreKitSSDDeviceItem(QWidget *parent)
	: QWidget(parent)
{
    this->ui.setupUi(this);

    this->ui.FeaturesTabWidget->tabBar()->setStyle(
        new TopmoreKitCustomTabStyle());

    this->ui.FeaturesTabWidget->removeTab(3);
    this->ui.FeaturesTabWidget->removeTab(2);
    this->ui.FeaturesTabWidget->removeTab(1);
}

TopmoreKitSSDDeviceItem::~TopmoreKitSSDDeviceItem()
{
}

void TopmoreKitSSDDeviceItem::UpdateInformation(
    CAtaSmart::ATA_SMART_INFO const& DiskInfo)
{
    UNREFERENCED_PARAMETER(DiskInfo);

    this->ui.FirmwarePlainTextEdit->setPlainText(
        QString::fromWCharArray(DiskInfo.FirmwareRev.GetString()));
    this->ui.InterfacePlainTextEdit->setPlainText(
        QString::fromWCharArray(DiskInfo.Interface.GetString()));
    this->ui.TransferModePlainTextEdit->setPlainText(
        QString::fromWCharArray(std::format(
            L"{} | {}",
            DiskInfo.CurrentTransferMode.GetString(),
            DiskInfo.MaxTransferMode.GetString()).c_str()));
    this->ui.SerialNumberPlainTextEdit->setPlainText(
        QString::fromWCharArray(DiskInfo.SerialNumber.GetString()));
    this->ui.HostTotalReadsPlainTextEdit->setPlainText(
        QString::fromWCharArray(std::format(
            L"{} GB",
            DiskInfo.HostReads).c_str()));
    this->ui.HostTotalWritesPlainTextEdit->setPlainText(
        QString::fromWCharArray(std::format(
            L"{} GB",
            DiskInfo.HostWrites).c_str()));
    this->ui.PowerOnHoursPlainTextEdit->setPlainText(
        QString::fromWCharArray(std::format(
            L"{} 小时",
            DiskInfo.MeasuredPowerOnHours).c_str()));
    this->ui.PowerOnCountPlainTextEdit->setPlainText(
        QString::fromWCharArray(std::format(
            L"{} 次",
            DiskInfo.PowerOnCount).c_str()));

    this->ui.HealthStatusPushButton->setText(
        QString::fromWCharArray(std::format(
            L"健康度\n{} %",
            DiskInfo.Life).c_str()));
    this->ui.TemperaturePushButton->setText(
        QString::fromWCharArray(std::format(
            L"温度\n{} ℃",
            DiskInfo.Temperature).c_str()));

    this->ui.SmartInformationTreeWidget->clear();

    for (DWORD i = 0; i < DiskInfo.AttributeCount; ++i)
    {
        QTreeWidgetItem* Item = new QTreeWidgetItem(
            this->ui.SmartInformationTreeWidget);

        Item->setText(
            0,
            QString::fromWCharArray(std::format(
                L"{:02x}",
                DiskInfo.Attribute[i].Id).c_str()));

        Item->setText(
            1,
            QString::fromWCharArray(
                g_SmartRes.find(DiskInfo.SmartKeyName.GetString())->second.find(
                    DiskInfo.Attribute[i].Id)->second.c_str()));

        Item->setText(
            2,
            QString::fromWCharArray(std::to_wstring(
                static_cast<std::uint64_t>(
                    DiskInfo.Attribute[i].Reserved) << 48 |
                static_cast<std::uint64_t>(
                    DiskInfo.Attribute[i].RawValue[5]) << 40 |
                static_cast<std::uint64_t>(
                    DiskInfo.Attribute[i].RawValue[4]) << 32 |
                static_cast<std::uint64_t>(
                    DiskInfo.Attribute[i].RawValue[3]) << 24 |
                static_cast<std::uint64_t>(
                    DiskInfo.Attribute[i].RawValue[2]) << 16 |
                static_cast<std::uint64_t>(
                    DiskInfo.Attribute[i].RawValue[1]) << 8 |
                static_cast<std::uint64_t>(
                    DiskInfo.Attribute[i].RawValue[0])).c_str()));
    }

    while (QLayoutItem* Item = this->ui.PartitionTableLayout->takeAt(0))
    {
        if (QWidget* Widget = Item->widget())
        {
            Widget->deleteLater();
        }
        delete Item;
    }

    /*{
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
    }*/
}
