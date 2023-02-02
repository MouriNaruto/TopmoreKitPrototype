#pragma once

#include <QWidget>
#include "ui_TopmoreKitSSDManagerTab.h"

class TopmoreKitSSDManagerTab : public QWidget
{
	Q_OBJECT

public:
	TopmoreKitSSDManagerTab(QWidget *parent = nullptr);
	~TopmoreKitSSDManagerTab();

private:
	Ui::TopmoreKitSSDManagerTabClass ui;
};
