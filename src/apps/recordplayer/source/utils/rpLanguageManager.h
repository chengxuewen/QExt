#ifndef _RPLANGUAGEMANAGER_H
#define _RPLANGUAGEMANAGER_H

#include <QObject>
#include <QSettings>

#include <qextSingleton.h>

class RPLanguageManagerPrivate;
class RPLanguageManager : public QObject, public QExtSingleton<RPLanguageManager>
{
    Q_OBJECT
    QEXT_DECLARE_SINGLETON(RPLanguageManager)
public:
    void refreshLanguages();
    QStringList languageList() const;

    QString currentLanguage() const;
    bool setCurrentLanguage(const QString &language);

    QString translationsPath() const;

    void loadSettings(QSettings *settings);
    void saveSettings(QSettings *settings);

Q_SIGNALS:
    void languageChanged();

protected:
    explicit RPLanguageManager(QObject *parent = nullptr);
    ~RPLanguageManager() override;

    QScopedPointer<RPLanguageManagerPrivate> dd_ptr;

private:
    Q_DISABLE_COPY(RPLanguageManager)
    Q_DECLARE_PRIVATE_D(dd_ptr, RPLanguageManager)
};

#endif // _RPLANGUAGEMANAGER_H
