/****************************************************************************
**
** Library: QEXTQuick
**
** MIT License
**
** Copyright (c) 2019 toou http://www.toou.net
** Copyright (c) 2020 chengxuewen <1398831004@qq.com>
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all
** copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
****************************************************************************/

#ifndef QEXTTHEMEBINDER_H
#define QEXTTHEMEBINDER_H

#include <qextobject.h>

#include <qextthemeglobal.h>

#include <QObject>
#include <QMap>
#include <QStringList>
#include <QScopedPointer>

#ifdef QEXT_BUILD_QML
#include <QJsonObject>
#include <QQmlListProperty>
#endif

class QEXTThemeBinderPrivate;
class QEXT_THEME_API QEXTThemeBinder : public QObject, public QEXTObject
{
    Q_OBJECT

    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(QString groupName READ groupName WRITE setGroupName NOTIFY groupNameChanged)
    Q_PROPERTY(QString className READ className WRITE setClassName NOTIFY classNameChanged)
    Q_PROPERTY(QString childName READ childName WRITE setChildName NOTIFY childNameChanged)
    Q_PROPERTY(QString state READ stateName WRITE setStateName NOTIFY stateNameChanged)
    Q_PROPERTY(QObject* target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(QStringList filterPropertyName READ filterPropertyName WRITE setFilterPropertyName NOTIFY filterPropertyNameChanged)
    Q_PROPERTY(QStringList dynamicListener READ dynamicListener WRITE setDynamicListener NOTIFY dynamicListenerChanged)
    Q_PROPERTY(bool stateAsynchronous READ isStateAsync WRITE setStateAsync NOTIFY stateAsyncChanged)
    Q_PROPERTY(QEXTThemeBinder* parent READ parent WRITE setParent NOTIFY parentChanged)

#ifdef QEXT_BUILD_QML
    Q_PROPERTY(QQmlListProperty<QEXTThemeBinder> childs READ qmlChildsList)
    Q_CLASSINFO("DefaultProperty", "childs")
#endif

public:
    explicit QEXTThemeBinder(QObject *parent = QEXT_NULLPTR);
    virtual ~QEXTThemeBinder();

    /**
     * @brief initialize
     * binding trigger styledata
     * must init in Component.onCompleted: {}
     * such as Component.onCompleted: initialize()
     */
    Q_INVOKABLE void initialize();

    int id() const;
    bool isEnabled() const;

    const QString &groupName() const;
    const QString &className() const;
    const QString &childName() const;
    const QString &stateName() const;

    QObject *target() const;
    QStringList filterPropertyName() const;
    QStringList dynamicListener() const;
    bool isStateAsync() const;
    QMap<QString, QVariant> bindingPropertyMap() const;

#ifdef QEXT_BUILD_QML
    QQmlListProperty<QEXTThemeBinder> qmlChildsList();
#endif

    QEXTThemeBinder *parent() const;
    QEXTThemeBinder *child(const int &index) const;
    QList<QEXTThemeBinder *> childsList();
    void addChild(QEXTThemeBinder *child);
    int childsCount() const;

    QString binderFieldKey();
    static QList<QEXTThemeBinder *> allBindersList();
    static QString generateFieldKey(const QString &className,
                                    const QString &groupName,
                                    const QString &stateName);
    static QStringList generateFieldKeyList(const QString &className,
                                            const QString &groupName,
                                            const QString &stateName);

Q_SIGNALS:
    void enabledChanged();
    void groupNameChanged();
    void classNameChanged();
    void childNameChanged();
    void stateNameChanged();
    void targetChanged();
    void filterPropertyNameChanged();
    void dynamicListenerChanged(const QStringList &listListener);
    void stateAsyncChanged();
    void parentChanged();
    void initialized();

protected Q_SLOTS:
    void setEnabled(const bool &enabled);
    void setGroupName(const QString &name);
    void setClassName(const QString &name);
    void setChildName(const QString &name);
    void setStateName(const QString &name);
    void setTarget(QObject *target);
    void setFilterPropertyName(const QStringList &nameList);
    void setDynamicListener(const QStringList &listenerList);
    void setStateAsync(const bool &async);
    void setParent(QEXTThemeBinder *parent);

    void onRefreshPropertys();
    void onPropertyChanged();
    void onStateChanged();
    void onDestroyed();

    void onParentClassNameChanged();
    void onParentGroupNameChanged();
    void onParentStateNameChanged();
    void onParentEnabledChanged();
    void onParentStateAsyncChanged();

private:
    QEXT_DECLARE_PRIVATE(QEXTThemeBinder)
    QEXT_DISABLE_COPY_MOVE(QEXTThemeBinder)
};

#endif // QEXTTHEMEBINDER_H
