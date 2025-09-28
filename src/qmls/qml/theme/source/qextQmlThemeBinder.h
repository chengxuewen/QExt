/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2021 ChengXueWen.
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
** documentation files (the "Software"), to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions
** of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
** CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
** IN THE SOFTWARE.
**
***********************************************************************************************************************/

#ifndef _QEXTQMLTHEMEBINDER_H
#define _QEXTQMLTHEMEBINDER_H

#include <qextQmlThemeGlobal.h>
#include <qextQmlRegistration.h>

#include <QObject>
#include <QJsonObject>
#include <QScopedPointer>
#include <QQmlListProperty>

class QExtQmlThemeBinderPrivate;
class QEXT_QMLTHEME_API QExtQmlThemeBinder : public QObject
{
    Q_OBJECT
    QEXT_QML_ELEMENT()
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(QString groupName READ groupName WRITE setGroupName NOTIFY groupNameChanged)
    Q_PROPERTY(QString className READ className WRITE setClassName NOTIFY classNameChanged)
    Q_PROPERTY(QString childName READ childName WRITE setChildName NOTIFY childNameChanged)
    Q_PROPERTY(QString state READ stateName WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QObject* target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(QStringList filterPropertyName READ filterPropertyName WRITE setFilterPropertyName NOTIFY filterPropertyNameChanged)
    Q_PROPERTY(QStringList dynamicListener READ dynamicListener WRITE setDynamicListener NOTIFY dynamicListenerChanged)
    Q_PROPERTY(bool stateAsynchronous READ isStateAsynchronous WRITE setStateAsynchronous NOTIFY stateAsynchronousChanged)
    Q_PROPERTY(QExtQmlThemeBinder* parent READ themeBinderParent WRITE setThemeBinderParent NOTIFY parentChanged)
    Q_PROPERTY(QQmlListProperty<QExtQmlThemeBinder> childs READ childs NOTIFY childsChanged)
    Q_CLASSINFO("DefaultProperty", "childs")

public:
    explicit QExtQmlThemeBinder(QObject *parent = nullptr);
    ~QExtQmlThemeBinder() override;

    /**
     * \brief initialize
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
    bool isStateAsynchronous() const;
    QMap<QString, QVariant> themeBindingPropertyMap() const;

    QExtQmlThemeBinder *themeBinderParent() const;
    QExtQmlThemeBinder *childThemeBinder(const int &index) const;
    QQmlListProperty<QExtQmlThemeBinder> childs();
    QList<QExtQmlThemeBinder *> themeBinderChilds();
    void addChild(QExtQmlThemeBinder *childThemeBinder);
    int themeBinderChildsCount() const;

    static QList<QExtQmlThemeBinder *> allThemeBinders();
    static QString generateFieldKey(const QString &className, const QString &groupName, const QString &stateName);
    static QStringList generateFieldKeyList(const QString &className, const QString &groupName, const QString &stateName);

    QString binderFieldKey();
    QVariant propertyData(const QString &key);

Q_SIGNALS:
    void enabledChanged();
    void groupNameChanged();
    void classNameChanged();
    void childNameChanged();
    void stateChanged();
    void targetChanged();
    void filterPropertyNameChanged();
    void dynamicListenerChanged(const QStringList &listListener);
    void stateAsynchronousChanged();
    void parentChanged();
    void initialized();

    void childsChanged(const QList<QExtQmlThemeBinder *> &childs);

protected Q_SLOTS:
    void setEnabled(const bool &enabled);
    void setGroupName(const QString &name);
    void setClassName(const QString &name);
    void setChildName(const QString &name);
    void setState(const QString &state);
    void setTarget(QObject *target);
    void setFilterPropertyName(const QStringList &nameList);
    void setDynamicListener(const QStringList &listenerList);
    void setStateAsynchronous(const bool &asynchronous);
    void setThemeBinderParent(QExtQmlThemeBinder *parent);

    void onRefreshPropertys();
    void onPropertyChanged();

protected:
    QScopedPointer<QExtQmlThemeBinderPrivate> dd_ptr;

private:
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtQmlThemeBinder)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQmlThemeBinder)
};

#endif // _QEXTQMLTHEMEBINDER_H
