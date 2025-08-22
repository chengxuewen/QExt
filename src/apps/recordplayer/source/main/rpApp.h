#ifndef _RPAPP_H
#define _RPAPP_H

#include <QObject>
#include <QScopedPointer>
#include <QMainWindow>

class RPAppPrivate;
class RPApp : public QObject
{
    Q_OBJECT
public:
    ~RPApp() override;
    static RPApp *instance();

    QMainWindow *mainwindow() const;

    bool startApp();
    bool quit();

    void setImportProfileFlag();
    void saveSettings();

public slots:
    void raiseMainWindow();

protected:
    explicit RPApp(QObject *parent = nullptr);

    QScopedPointer<RPAppPrivate> dd_ptr;

private:
    Q_DISABLE_COPY(RPApp)
    Q_DECLARE_PRIVATE_D(dd_ptr, RPApp)
};

#endif // _RPAPP_H
