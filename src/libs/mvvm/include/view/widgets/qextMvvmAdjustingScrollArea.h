#ifndef _QEXTMVVMADJUSTINGSCROLLAREA_H
#define _QEXTMVVMADJUSTINGSCROLLAREA_H

#include <QScrollArea>
#include <qextMvvmGlobal.h>


//! Modification of standard scroll area, which makes widget with dynamic layout occupy the whole
//! available space.

class QEXT_MVVM_API QEXTMvvmAdjustingScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    QEXTMvvmAdjustingScrollArea(QWidget* parent = 0);
    void setWidget(QWidget* w);

    QSize sizeHint() const;

private:
    bool eventFilter(QObject* obj, QEvent* ev);
};

#endif // _QEXTMVVMADJUSTINGSCROLLAREA_H
