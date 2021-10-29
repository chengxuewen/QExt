#ifndef QEXTGUIWINDOW_H
#define QEXTGUIWINDOW_H

#include <QObject>

class QEXTGuiWindow : public QObject
{
    Q_OBJECT
public:
    explicit QEXTGuiWindow(QObject *parent = nullptr);

signals:

};

#endif // QEXTGUIWINDOW_H
