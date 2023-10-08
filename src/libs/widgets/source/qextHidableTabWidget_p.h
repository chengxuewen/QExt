#ifndef _QEXTHIDABLETABWIDGET_P_H
#define _QEXTHIDABLETABWIDGET_P_H

#include <qextWidgetGlobal.h>
#include <qextHidableTabWidget.h>

#include <QToolButton>

class QEXTHidableTabWidgetPrivate
{
public:
    explicit QEXTHidableTabWidgetPrivate(QEXTHidableTabWidget *q);
    virtual ~QEXTHidableTabWidgetPrivate();

    QEXTHidableTabWidget * const q_ptr;

    QScopedPointer<QAction> m_hideAction;
    QScopedPointer<QToolButton> m_hideButton;
    int m_maxHeight;

private:
    Q_DISABLE_COPY(QEXTHidableTabWidgetPrivate)
    Q_DECLARE_PUBLIC(QEXTHidableTabWidget)
};

#endif // _QEXTHIDABLETABWIDGET_P_H
