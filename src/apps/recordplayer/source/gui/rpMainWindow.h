#ifndef _RPMAINWINDOW_H
#define _RPMAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

#include <qextSerializable.h>

namespace Ui {
class RPMainWindow;
}

class RPMainWindowPrivate;
class RPMainWindow : public QMainWindow, public QExtSerializable
{
    Q_OBJECT
public:
    explicit RPMainWindow(QWidget *parent = nullptr);
    ~RPMainWindow();

    SerializedItemsMap serializeSave() const override;
    void serializeLoad(const SerializedItemsMap &items) override;

protected:
    bool eventFilter(QObject *watched, QEvent *event) QEXT_OVERRIDE;
    void closeEvent(QCloseEvent * event) QEXT_OVERRIDE;
    void changeEvent(QEvent *event) QEXT_OVERRIDE;

    void initTitleBar();
    void initContent();
    void initStatusBar();

private:
    Ui::RPMainWindow *ui;
    QScopedPointer<RPMainWindowPrivate> dd_ptr;
    QEXT_DECLARE_PRIVATE_D(dd_ptr, RPMainWindow)
    QEXT_DECLARE_DISABLE_COPY_MOVE(RPMainWindow)
};

#endif // _RPMAINWINDOW_H
