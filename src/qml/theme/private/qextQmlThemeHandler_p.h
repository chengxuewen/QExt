#ifndef _QEXTTHEMEHANDLER_P_H
#define _QEXTTHEMEHANDLER_P_H

#include <qextQmlThemeGlobal.h>

#include <QVariantMap>
#include <QPointer>

class QEXTQmlThemeHandler;
class QEXT_QMLTHEME_API QEXTQmlThemeHandlerPrivate
{
    Q_DISABLE_COPY(QEXTQmlThemeHandlerPrivate)
    Q_DECLARE_PUBLIC(QEXTQmlThemeHandler)
public:
    explicit QEXTQmlThemeHandlerPrivate(QEXTQmlThemeHandler *q);
    virtual ~QEXTQmlThemeHandlerPrivate();

    QEXTQmlThemeHandler * const q_ptr;

    QString m_name;
    QString m_path;
    QString m_lastErrorString;
    QVariantMap m_themeInfoMap;
    QMap<QString, QVariantMap> m_themeDataMap;
    bool m_valid;
};



#endif // _QEXTTHEMEHANDLER_P_H
