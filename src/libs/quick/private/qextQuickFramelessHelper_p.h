#ifndef _QEXTQUICKFRAMELESSHELPER_P_H
#define _QEXTQUICKFRAMELESSHELPER_P_H

#include <qextQuickGlobal.h>
#include <qextQuickFramelessHelper.h>
#include <qextNativeWindowHelper.h>
#include <qextNativeWindowTester.h>

#include <QSet>
#include <QQuickWindow>

class QEXTQuickFramelessHelper;
class QEXT_QUICK_API QEXTQuickFramelessHelperPrivate : public QEXTNativeWindowTester
{
public:
    explicit QEXTQuickFramelessHelperPrivate(QEXTQuickFramelessHelper *q);
    virtual ~QEXTQuickFramelessHelperPrivate();

    QMargins draggableMargins() const final;
    QMargins maximizedMargins() const final;

    bool hitTest(const QPoint &pos) const final;

    QEXTQuickFramelessHelper const *q_ptr;

    QEXTNativeWindowHelper *m_helper;
    QQuickWindow *m_window;
    QMargins m_priDraggableMargins;
    QMargins m_priMaximizedMargins;
    QSet<QQuickItem *> m_extraTitleBars;
    QSet<QQuickItem *> m_includeItems;
    QSet<QQuickItem *> m_excludeItems;
    int m_titleBarHeight;
};

#endif // _QEXTQUICKFRAMELESSHELPER_P_H
