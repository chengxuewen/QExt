#ifndef _QEXTFRAMELESSHELPER_P_H
#define _QEXTFRAMELESSHELPER_P_H

#include <qextFramelessHelperGlobal.h>
#include <qextFramelessHelper.h>
#include <qextNativeWindowTester.h>

#include <QSet>
#include <QPointer>

class QEXTNativeWindowHelper;
class QEXT_FRAMELESSHELPER_API QEXTFramelessHelperPrivate : public QEXTNativeWindowTester
{
public:
    QEXTFramelessHelperPrivate();
    virtual ~QEXTFramelessHelperPrivate();

    QMargins draggableMargins() const final;
    QMargins maximizedMargins() const final;

    bool hitTest(const QPoint &pos) const final;

    QPointer<QWidget> m_window;
    QEXTNativeWindowHelper *m_helper;
    QMargins m_priDraggableMargins;
    QMargins m_priMaximizedMargins;
    QSet<QWidget *> m_extraTitleBars;
    QSet<QWidget *> m_includeItems;
    QSet<QWidget *> m_excludeItems;
    bool m_maximized;
    int m_titleBarHeight;
};

#endif // _QEXTFRAMELESSHELPER_P_H
