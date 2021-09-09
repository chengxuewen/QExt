#ifndef QEXTTHEMEHANDLER_P_H
#define QEXTTHEMEHANDLER_P_H

#include <qextquickglobal.h>

#include <qextObject_p.h>

#include <QVariantMap>
#include <QPointer>



class QEXTQuickThemeHandler;
class QEXT_QUICK_API QEXTQuickThemeHandlerPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTQuickThemeHandlerPrivate(QEXTQuickThemeHandler *qq);
    ~QEXTQuickThemeHandlerPrivate();

    QString m_name;
    QString m_path;
    QString m_lastErrorString;
    QVariantMap m_themeInfoMap;
    QMap<QString, QVariantMap> m_themeDataMap;
    bool m_valid;

private:
    QEXT_DECL_PUBLIC(QEXTQuickThemeHandler)
    QEXT_DISABLE_COPY_MOVE(QEXTQuickThemeHandlerPrivate)
};



#endif // QEXTTHEMEHANDLER_P_H
