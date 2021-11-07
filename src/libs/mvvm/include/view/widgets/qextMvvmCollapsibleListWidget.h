#ifndef _QEXTMVVMCOLLAPSIBLELISTWIDGET_H
#define _QEXTMVVMCOLLAPSIBLELISTWIDGET_H

#include <QWidget>
#include <qextMvvmGlobal.h>

class QSplitter;
class QString;

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


#endif // _QEXTMVVMCOLLAPSIBLELISTWIDGET_H
