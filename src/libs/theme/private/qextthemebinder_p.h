#ifndef QEXTTHEMEBINDER_P_H
#define QEXTTHEMEBINDER_P_H

#include <qextobject_p.h>

#include <qextthemeglobal.h>

#include <QStringList>
#include <QVariant>
#include <QPointer>

class QEXTThemeBinder;
class QEXT_THEME_API QEXTThemeBinderPrivate: public QEXTObjectPrivate
{
public:
    explicit QEXTThemeBinderPrivate(QEXTThemeBinder *qq);
    ~QEXTThemeBinderPrivate();

    QVariant propertyData(const QString &key);

    static QList<QEXTThemeBinder *> sm_allBindersList;
    static quint64 sm_count;
    const quint64 m_id;
    bool m_isEnabled;
    QString m_groupName;
    QString m_className;
    QString m_childName;
    QString m_stateName;
    QPointer<QObject> m_target;

    QMap<QString, QVariant> m_bindingPropertyMap;
    QStringList m_propertyInitfilterList;
    QStringList m_filterPropertyNameList;
    QStringList m_dynamicListenerList;
    bool m_isStateAsync;

    QList<QEXTThemeBinder *> m_childNameList;
    QPointer<QEXTThemeBinder> m_themeBinderParent;

private:
    QEXT_DECLARE_PUBLIC(QEXTThemeBinder)
    QEXT_DISABLE_COPY_MOVE(QEXTThemeBinderPrivate)
};

#endif // QEXTTHEMEBINDER_P_H
