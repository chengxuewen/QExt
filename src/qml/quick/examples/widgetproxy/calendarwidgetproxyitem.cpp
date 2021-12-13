#include "calendarwidgetproxyitem.h"

#include <QTimer>
#include <QDial>
#include <QPushButton>

CalendarWidgetProxyItem::CalendarWidgetProxyItem(QQuickItem *parent)
    : QEXTQuickWidgetProxyItem(new QDial, parent)
{
}
