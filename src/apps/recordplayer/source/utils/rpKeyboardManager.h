#ifndef _RPKEYBOARDMANAGER_H
#define _RPKEYBOARDMANAGER_H

#include <QObject>
#include <QSettings>

#include <qextSingleton.h>

class RPKeyboardManagerPrivate;
class RPKeyboardManager : public QObject, public QExtSingleton<RPKeyboardManager>
{
    Q_OBJECT
    QEXT_DECLARE_SINGLETON(RPKeyboardManager)
public:
    bool isVirtualSoftKeyboardEnable() const;
    void setVirtualSoftKeyboardEnable(bool enable);

    void loadSettings(QSettings *settings);
    void saveSettings(QSettings *settings);

Q_SIGNALS:
    void virtualSoftKeyboardEnableChanged(bool enable);

protected:
    explicit RPKeyboardManager(QObject *parent = nullptr);
    ~RPKeyboardManager() override;

    QScopedPointer<RPKeyboardManagerPrivate> dd_ptr;

private:
    Q_DISABLE_COPY(RPKeyboardManager)
    Q_DECLARE_PRIVATE_D(dd_ptr, RPKeyboardManager)
};

#endif // _RPKEYBOARDMANAGER_H
