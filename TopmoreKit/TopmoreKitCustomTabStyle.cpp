#include "TopmoreKitCustomTabStyle.h"

#include <QtWidgets/QStyleOption>
#include <QtWidgets/QTabBar>

QSize TopmoreKitCustomTabStyle::sizeFromContents(
    ContentsType type,
    const QStyleOption* option,
    const QSize& size,
    const QWidget* widget) const
{
    QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
    if (QStyle::CT_TabBarTab == type)
    {
        s.transpose();
    }
    return s;
}

void TopmoreKitCustomTabStyle::drawControl(
    ControlElement element,
    const QStyleOption* option,
    QPainter* painter,
    const QWidget* widget) const
{
    if (CE_TabBarTabLabel == element)
    {
        const QStyleOptionTab* tab =
            qstyleoption_cast<const QStyleOptionTab*>(option);
        if (tab)
        {
            QStyleOptionTab opt(*tab);
            opt.shape = QTabBar::RoundedNorth;
            QProxyStyle::drawControl(element, &opt, painter, widget);
            return;
        }
    }
    QProxyStyle::drawControl(element, option, painter, widget);
}
