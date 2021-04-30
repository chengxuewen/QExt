#ifndef QEXTTHEMEMANAGER_P_H
#define QEXTTHEMEMANAGER_P_H

#include <qextobject_p.h>

#include <qextthemeglobal.h>

#include <QScopedPointer>
#include <QFileSystemWatcher>
#include <QScopedPointer>

class QEXTThemeHandler;
class QEXTThemeFileParserBase;
class QEXTThemeManager;
class QEXT_THEME_API QEXTThemeManagerPrivate: public QEXTObjectPrivate
{
public:
    explicit QEXTThemeManagerPrivate(QEXTThemeManager *qq);
    ~QEXTThemeManagerPrivate();

    QScopedPointer<QFileSystemWatcher> m_fileSystemWatcher;
    QScopedPointer<QEXTThemeFileParserBase> m_themeFileParser;
    QMap<QString, QEXTThemeHandler *> m_themeHandlerMap;
    QString m_startupThemeName;
    QString m_currentThemeName;
    QString m_lastError;
    bool m_generateThemeTemplateEnable;

private:
    QEXT_DECLARE_PUBLIC(QEXTThemeManager)
    QEXT_DISABLE_COPY_MOVE(QEXTThemeManagerPrivate)
};

#endif // QEXTTHEMEMANAGER_P_H
