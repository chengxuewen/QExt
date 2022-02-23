#ifndef _QEXTQMLFRAMELESSHELPER_P_H
#define _QEXTQMLFRAMELESSHELPER_P_H

#include <qextQmlFramelessHelperGlobal.h>
#include <qextQmlFramelessHelper.h>
#include <qextNativeWindowHelper.h>
#include <qextNativeWindowTester.h>

#include <QSet>
#include <QQuickWindow>

class QEXTQmlFramelessHelper;
class QEXT_QMLFRAMELESSHELPER_API QEXTQmlFramelessHelperPrivate : public QEXTNativeWindowTester
{
public:
    explicit QEXTQmlFramelessHelperPrivate(QEXTQmlFramelessHelper *q);
    virtual ~QEXTQmlFramelessHelperPrivate();

    QMargins draggableMargins() const final;
    QMargins maximizedMargins() const final;

    bool hitTest(const QPoint &pos) const final;

    QEXTQmlFramelessHelper const *q_ptr;

    QEXTNativeWindowHelper *m_helper;
    QQuickWindow *m_window;
    QMargins m_priDraggableMargins;
    QMargins m_priMaximizedMargins;
    QSet<QQuickItem *> m_extraTitleBars;
    QSet<QQuickItem *> m_includeItems;
    QSet<QQuickItem *> m_excludeItems;
    int m_titleBarHeight;
};

#endif // _QEXTQMLFRAMELESSHELPER_P_H
