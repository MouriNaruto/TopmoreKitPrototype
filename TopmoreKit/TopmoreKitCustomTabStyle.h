#pragma once

#include <QtWidgets/QProxyStyle>

class TopmoreKitCustomTabStyle : public QProxyStyle
{
public:

    QSize sizeFromContents(
        ContentsType type,
        const QStyleOption* option,
        const QSize& size,
        const QWidget* widget) const;

    void drawControl(
        ControlElement element,
        const QStyleOption* option,
        QPainter* painter,
        const QWidget* widget) const;
};
