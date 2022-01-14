#ifndef _QEXTMVVMWIDGETSADJUSTINGSCROLLAREA_H
#define _QEXTMVVMWIDGETSADJUSTINGSCROLLAREA_H

#include <qextMvvmGlobal.h>

#include <QScrollArea>

namespace ModelView
{

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

} // namespace ModelView

#endif // _QEXTMVVMWIDGETSADJUSTINGSCROLLAREA_H
