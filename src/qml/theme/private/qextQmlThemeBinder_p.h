#ifndef _QEXTTHEMEBINDER_P_H
#define _QEXTTHEMEBINDER_P_H

#include <qextQmlThemeGlobal.h>

#include <QPointer>

class QEXTQmlThemeBinder;
class QEXT_QMLTHEME_API QEXTQmlThemeBinderPrivate
{
    Q_DISABLE_COPY(QEXTQmlThemeBinderPrivate)
    Q_DECLARE_PUBLIC(QEXTQmlThemeBinder)
public:
    explicit QEXTQmlThemeBinderPrivate(QEXTQmlThemeBinder *q);
    virtual ~QEXTQmlThemeBinderPrivate();

    QEXTQmlThemeBinder * const q_ptr;

    static QList<QEXTQmlThemeBinder *> sm_allBindersList;
    static int sm_count;
    const int m_id;

    bool m_enabled;
    QString m_groupName;
    QString m_className;
    QString m_childName;
    QString m_stateName;
    QPointer<QObject> m_target;

    QMap<QString, QVariant> m_bindingNameToPropertyMap;
    QStringList m_propertyInitfilterList;
    QStringList m_filterPropertyNameList;
    QStringList m_dynamicListenerList;
    bool m_stateAsynchronous;

    QList<QEXTQmlThemeBinder *> m_themeBinderChildsList;
    QPointer<QEXTQmlThemeBinder> m_themeBinderParent;
};



#endif // _QEXTTHEMEBINDER_P_H
