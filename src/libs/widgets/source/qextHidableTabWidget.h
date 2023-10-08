#ifndef _QEXTHIDABLETABWIDGET_H
#define _QEXTHIDABLETABWIDGET_H

#include <qextWidgetGlobal.h>

#include <QTabWidget>
#include <QAction>

class QEXTHidableTabWidgetPrivate;
class QEXT_WIDGETS_API QEXTHidableTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit QEXTHidableTabWidget(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTHidableTabWidget();

public slots:
    void showTabs();

private slots:
    void onHideAction(bool checked);
    void onTabBarClicked();
    void onTabBarDoubleClicked();

    void connectSignals();

protected:
    QScopedPointer<QEXTHidableTabWidgetPrivate> dd_ptr;

private:
    Q_DISABLE_COPY(QEXTHidableTabWidget)
    Q_DECLARE_PRIVATE_D(dd_ptr, QEXTHidableTabWidget)
};

#endif // _QEXTHIDABLETABWIDGET_H
