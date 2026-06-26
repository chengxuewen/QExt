#ifndef _QEXTQUICKWIDGETITEM_P_H
#define _QEXTQUICKWIDGETITEM_P_H

#include <qextQuickWidgetItem.h>

#include <QDebug>
#include <QWindow>
#include <QWidget>
#include <QPointer>

class QEXT_QUICKCONTROLS_API QExtQuickWidgetItemPrivate
{
public:
    explicit QExtQuickWidgetItemPrivate(QExtQuickWidgetItem *q);
    virtual ~QExtQuickWidgetItemPrivate();

    void init();
    void initEmbeddedWidget();
    void resetEmbeddedWidget();

    QExtQuickWidgetItem * const q_ptr;

    bool mItemCompleted;
    bool mWidgetHideEnable;
    QPointer<QWidget> mWidget;
    QPointer<QWindow> mRootWindow;
    bool mAppAboutToQuit = false;


private:
    Q_DECLARE_PUBLIC(QExtQuickWidgetItem)
    Q_DISABLE_COPY(QExtQuickWidgetItemPrivate)
};

#endif // _QEXTQUICKWIDGETITEM_P_H
