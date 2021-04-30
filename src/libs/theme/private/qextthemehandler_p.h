#ifndef QEXTTHEMEHANDLER_P_H
#define QEXTTHEMEHANDLER_P_H

#include <qextobject_p.h>

#include <qextthemeglobal.h>

#include <QVariantMap>

class QEXTThemeHandler;
class QEXT_THEME_API QEXTThemeHandlerPrivate: public QEXTObjectPrivate
{
public:
    explicit QEXTThemeHandlerPrivate(QEXTThemeHandler *qq);
    ~QEXTThemeHandlerPrivate();

    QString m_themeName;
    QString m_themePath;
    QString m_lastError;
    QVariantMap m_themeInfoInfo;
    QMap<QString, QVariantMap> m_themeDataMap;
    bool m_themeValid;

private:
    QEXT_DECLARE_PUBLIC(QEXTThemeHandler)
    QEXT_DISABLE_COPY_MOVE(QEXTThemeHandlerPrivate)
};

#endif // QEXTTHEMEHANDLER_P_H
