#ifndef QEXTTHEMEMANAGER_P_H
#define QEXTTHEMEMANAGER_P_H

#include <qextquickglobal.h>

#include <qextobject_p.h>

class QFileSystemWatcher;
class QEXTQuickThemeHandler;
class QEXTQuickThemeFileParser;
class QEXTQuickThemeManager;
class QEXT_QUICK_API QEXTQuickThemeManagerPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTQuickThemeManagerPrivate(QEXTQuickThemeManager *qq);
    ~QEXTQuickThemeManagerPrivate();

    QScopedPointer<QFileSystemWatcher> m_fileSystemWatcher;
    QScopedPointer<QEXTQuickThemeFileParser> m_themeFileParser;
    QMap<QString, QEXTQuickThemeHandler *> m_themeNameToHandlerMap;
    QString m_startupThemeName;
    QString m_currentThemeName;
    QString m_lastErrorString;
    bool m_generateThemeTemplateEnable;

private:
    QEXT_DECLARE_PUBLIC(QEXTQuickThemeManager)
    QEXT_DISABLE_COPY_MOVE(QEXTQuickThemeManagerPrivate)
};

#endif // QEXTTHEMEMANAGER_P_H
