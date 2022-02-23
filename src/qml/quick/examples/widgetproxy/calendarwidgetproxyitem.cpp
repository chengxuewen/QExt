#include "calendarwidgetproxyitem.h"

#include <QTimer>
#include <QDial>
#include <QPushButton>

CalendarWidgetProxyItem::CalendarWidgetProxyItem(QQuickItem *parent)
    : QEXTQmlQuickWidgetProxyItem(new QDial, parent)
{
}
