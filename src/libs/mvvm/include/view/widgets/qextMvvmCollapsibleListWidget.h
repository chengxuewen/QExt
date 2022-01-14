#ifndef _QEXTMVVMWIDGETSCOLLAPSIBLELISTWIDGET_H
#define _QEXTMVVMWIDGETSCOLLAPSIBLELISTWIDGET_H

#include <qextMvvmGlobal.h>

#include <QWidget>

class QSplitter;
class QString;

namespace ModelView
{

//! Vertical widget with column of panels displayed one under another.
//! Each panel contains user widget and can be collapsed/expanded. When expanded,
//! the place occupied by the panel can be changed by draging a splitter.

class QEXT_MVVM_API QEXTMvvmCollapsibleListWidget : public QWidget
{
    Q_OBJECT

public:
    QEXTMvvmCollapsibleListWidget(QWidget* parent = nullptr);

    void addWidget(QWidget* widget, const QString& title, bool collapsed = false);

private:
    QSplitter* m_splitter{nullptr};
};

} // namespace ModelView

#endif // _QEXTMVVMWIDGETSCOLLAPSIBLELISTWIDGET_H
