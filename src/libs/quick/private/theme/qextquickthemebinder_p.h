#ifndef QEXTTHEMEBINDER_P_H
#define QEXTTHEMEBINDER_P_H

#include <qextquickglobal.h>

#include <qextobject_p.h>

#include <QPointer>

class QEXTQuickThemeBinder;
class QEXT_QUICK_API QEXTQuickThemeBinderPrivate : public QEXTObjectPrivate
{
public:
    explicit QEXTQuickThemeBinderPrivate(QEXTQuickThemeBinder *qq);
    ~QEXTQuickThemeBinderPrivate();

    static QList<QEXTQuickThemeBinder *> sm_allBindersList;
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

    QList<QEXTQuickThemeBinder *> m_themeBinderChildsList;
    QPointer<QEXTQuickThemeBinder> m_themeBinderParent;

private:
    QEXT_DECLARE_PUBLIC(QEXTQuickThemeBinder)
    QEXT_DISABLE_COPY_MOVE(QEXTQuickThemeBinderPrivate)
};

#endif // QEXTTHEMEBINDER_P_H
