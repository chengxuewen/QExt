#ifndef _QEXTTHEMEMANAGER_P_H
#define _QEXTTHEMEMANAGER_P_H

#include <qextQmlThemeGlobal.h>

class QFileSystemWatcher;

class QEXTQmlThemeHandler;
class QEXTQmlThemeFileParser;
class QEXTQmlThemeManager;
class QEXT_QMLTHEME_API QEXTQmlThemeManagerPrivate
{
    Q_DISABLE_COPY(QEXTQmlThemeManagerPrivate)
    Q_DECLARE_PUBLIC(QEXTQmlThemeManager)
public:
    explicit QEXTQmlThemeManagerPrivate(QEXTQmlThemeManager *q);
    virtual ~QEXTQmlThemeManagerPrivate();

    QEXTQmlThemeManager * const q_ptr;

    QScopedPointer<QFileSystemWatcher> m_fileSystemWatcher;
    QScopedPointer<QEXTQmlThemeFileParser> m_themeFileParser;
    QMap<QString, QEXTQmlThemeHandler *> m_themeNameToHandlerMap;
    QString m_startupThemeName;
    QString m_currentThemeName;
    QString m_lastErrorString;
    bool m_generateThemeTemplateEnable;
};



#endif // _QEXTTHEMEMANAGER_P_H
