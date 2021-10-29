#ifndef QEXTGUIWINDOW_H
#define QEXTGUIWINDOW_H

#include <qextGuiGlobal.h>

#include <QObject>

class QEXTGuiWindow : public QObject
{
    Q_OBJECT
public:
    explicit QEXTGuiWindow(QObject * = QEXT_DECL_NULLPTR);

signals:

};

#endif // QEXTGUIWINDOW_H
