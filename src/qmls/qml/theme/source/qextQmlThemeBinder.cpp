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

#include <qextQmlThemeBinder.h>
#include <qextQmlThemeBinder.h>
#include <qextQmlThemeManager.h>
#include <qextQmlThemeConstant.h>

#include <QMap>
#include <QDebug>
#include <QPointer>
#include <QJsonArray>
#include <QMapIterator>
#include <QMetaMethod>

namespace internal
{
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
QVariant::Type getType(const QVariant &variant) { return variant.type(); }
QVariant::Type getType(const QMetaProperty &property) { return property.type(); }
#else
QMetaType getType(const QVariant &variant) { return variant.metaType(); }
QMetaType getType(const QMetaProperty &property) { return property.metaType(); }
#endif

}

class QExtQmlThemeBinder;
class QExtQmlThemeBinderPrivate
{
    Q_DISABLE_COPY(QExtQmlThemeBinderPrivate)
    Q_DECLARE_PUBLIC(QExtQmlThemeBinder)
public:
    explicit QExtQmlThemeBinderPrivate(QExtQmlThemeBinder *q);
    virtual ~QExtQmlThemeBinderPrivate();

    QExtQmlThemeBinder * const q_ptr;

    static QList<QExtQmlThemeBinder *> smAllBindersList;
    static int smCount;
    const int mId;

    bool mEnabled;
    QString mGroupName;
    QString mClassName;
    QString mChildName;
    QString mStateName;
    QPointer<QObject> mTarget;

    QMap<QString, QVariant> mBindingNameToPropertyMap;
    QStringList mPropertyInitfilterList;
    QStringList mFilterPropertyNameList;
    QStringList mDynamicListenerList;
    bool mStateAsynchronous;

    QList<QExtQmlThemeBinder *> mThemeBinderChildsList;
    QPointer<QExtQmlThemeBinder> mThemeBinderParent;
};


QList<QExtQmlThemeBinder *> QExtQmlThemeBinderPrivate::smAllBindersList;
int QExtQmlThemeBinderPrivate::smCount = 0;

QExtQmlThemeBinderPrivate::QExtQmlThemeBinderPrivate(QExtQmlThemeBinder *q)
    : q_ptr(q)
    , mId(++smCount)
{
    mEnabled = false;
    mStateAsynchronous = true;
}

QExtQmlThemeBinderPrivate::~QExtQmlThemeBinderPrivate()
{
}


QExtQmlThemeBinder::QExtQmlThemeBinder(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtQmlThemeBinderPrivate(this))
{
    Q_D(QExtQmlThemeBinder);
    d->mDynamicListenerList << "width" << "height" << "x" << "y";
    this->setEnabled(true);
    const QMetaObject *metaObj = this->metaObject();
    int propertyCount = metaObj->propertyCount();
    for (int i = 0; i < propertyCount; ++i)
    {
        QMetaProperty metaProperty = metaObj->property(i);
        d->mFilterPropertyNameList.append(metaProperty.name());
    }

    connect(this, &QExtQmlThemeBinder::stateChanged, this, [=]()
            {
                if(d->mStateAsynchronous && QExtQmlThemeManager::instance()->isCurrentThemeValid())
                {
                    this->onRefreshPropertys();
                }
            }, Qt::QueuedConnection);
    QExtQmlThemeBinderPrivate::smAllBindersList.append(this);
    QExtQmlThemeManager::instance()->newThemeBinder(this);
}

QExtQmlThemeBinder::~QExtQmlThemeBinder()
{
    QExtQmlThemeBinderPrivate::smAllBindersList.removeOne(this);
}

void QExtQmlThemeBinder::initialize()
{
    Q_D(QExtQmlThemeBinder);
    //    qDebug() << "TThemeBinder::initialize()--------------------";
    //    qDebug() << "id = " << d->m_iId;
    //    qDebug() << "m_className = " << d->m_className;
    //    qDebug() << "m_groupName = " << d->m_groupName;
    //    qDebug() << "m_childName = " << d->m_childName;
    //    qDebug() << "m_stateName = " << d->m_stateName;
    //    qDebug() << "m_pParent = " << d->m_pParent;
    //    qDebug() << "m_themeBinderChildsList.size() = " << d->m_themeBinderChildsList.size();
    if(!d->mEnabled)
    {
        return;
    }
    const QMetaObject *metaObj = this->metaObject();

    //[1 step]
    int propertyCount = metaObj->propertyCount();
    for (int i = 0; i < propertyCount; ++i)
    {
        QMetaProperty metaProperty = metaObj->property(i);
        if(!d->mPropertyInitfilterList.contains(metaProperty.name()) &&
            !d->mFilterPropertyNameList.contains(metaProperty.name()))
        {
            QVariant property(internal::getType(metaProperty));
            property.setValue(this->property(metaProperty.name()));
            d->mBindingNameToPropertyMap.insert(metaProperty.name(), property);
            //            qDebug() << "metaProperty=" << metaProperty.name() << " , property=" << property;
        }
    }

    //[2 step]
    QList<int> bindingMethodIndexList;
    int binderSlotIndex = -1;
    int methodCount = metaObj->methodCount();
    for (int i = 0; i < methodCount; ++i)
    {
        QMetaMethod method = metaObj->method(i);
        QString methodName = QString::fromUtf8(method.name());
        if (method.methodType() == QMetaMethod::Signal && methodName.contains("Changed"))
        {
            QString bindingName = QString(methodName.mid(0, methodName.indexOf("Changed")));
            if(d->mBindingNameToPropertyMap.contains(bindingName) && d->mDynamicListenerList.contains(bindingName))
            {
                bindingMethodIndexList.append(method.methodIndex());
            }
        }
        else if(method.methodType() == QMetaMethod::Slot && methodName == "onPropertyChanged")
        {
            binderSlotIndex = method.methodIndex();
        }
    }

    //[3 step]
    if(-1 != binderSlotIndex && bindingMethodIndexList.length() > 0)
    {
        foreach (int iKey, bindingMethodIndexList)
        {
            QMetaObject::connect(this, iKey, this, binderSlotIndex);
        }
    }

    //[4 step]
    foreach (QExtQmlThemeBinder *childBinder, d->mThemeBinderChildsList)
    {
        childBinder->setStateAsynchronous(d->mStateAsynchronous);
        childBinder->setFilterPropertyName(d->mFilterPropertyNameList);
        childBinder->setClassName(d->mClassName);
        childBinder->setGroupName(d->mGroupName);
        childBinder->setEnabled(d->mEnabled);
        childBinder->setState(d->mStateName);
        childBinder->setThemeBinderParent(this);
        childBinder->initialize();
    }

    if(QExtQmlThemeManager::instance()->isCurrentThemeValid())
    {
        this->onRefreshPropertys();
    }

    emit this->initialized();
}

int QExtQmlThemeBinder::id() const
{
    Q_D(const QExtQmlThemeBinder);
    return d->mId;
}

bool QExtQmlThemeBinder::isEnabled() const
{
    Q_D(const QExtQmlThemeBinder);
    return d->mEnabled;
}

const QString &QExtQmlThemeBinder::groupName() const
{
    Q_D(const QExtQmlThemeBinder);
    return d->mGroupName;
}

const QString &QExtQmlThemeBinder::className() const
{
    Q_D(const QExtQmlThemeBinder);
    return d->mClassName;
}

const QString &QExtQmlThemeBinder::childName() const
{
    Q_D(const QExtQmlThemeBinder);
    return d->mChildName;
}

const QString &QExtQmlThemeBinder::stateName() const
{
    Q_D(const QExtQmlThemeBinder);
    return d->mStateName;
}

QObject *QExtQmlThemeBinder::target() const
{
    Q_D(const QExtQmlThemeBinder);
    return d->mTarget.data();
}

QStringList QExtQmlThemeBinder::filterPropertyName() const
{
    Q_D(const QExtQmlThemeBinder);
    return d->mFilterPropertyNameList;
}

QStringList QExtQmlThemeBinder::dynamicListener() const
{
    Q_D(const QExtQmlThemeBinder);
    return d->mDynamicListenerList;
}

bool QExtQmlThemeBinder::isStateAsynchronous() const
{
    Q_D(const QExtQmlThemeBinder);
    return d->mStateAsynchronous;
}

QMap<QString, QVariant> QExtQmlThemeBinder::themeBindingPropertyMap() const
{
    Q_D(const QExtQmlThemeBinder);
    return d->mBindingNameToPropertyMap;
}

int QExtQmlThemeBinder::themeBinderChildsCount() const
{
    Q_D(const QExtQmlThemeBinder);
    return d->mThemeBinderChildsList.count();
}

QList<QExtQmlThemeBinder *> QExtQmlThemeBinder::allThemeBinders()
{
    return QExtQmlThemeBinderPrivate::smAllBindersList;
}

QString QExtQmlThemeBinder::generateFieldKey(const QString &className, const QString &groupName,
                                             const QString &stateName)
{
    QString strKey = className;
    if (!groupName.isEmpty())
    {
        strKey += "#" + groupName;
    }
    if (!stateName.isEmpty())
    {
        strKey += ":" + stateName;
    }
    return strKey;
}

QStringList QExtQmlThemeBinder::generateFieldKeyList(const QString &className, const QString &groupName,
                                                     const QString &stateName)
{
    QStringList listKey;
    listKey.append(QExtQmlThemeBinder::generateFieldKey(className, groupName, stateName));
    listKey.append(QExtQmlThemeBinder::generateFieldKey(className, groupName, ""));
    listKey.append(QExtQmlThemeBinder::generateFieldKey(className, "", stateName));
    listKey.append(QExtQmlThemeBinder::generateFieldKey(className, "", ""));
    listKey.removeDuplicates();
    return listKey;
}

QString QExtQmlThemeBinder::binderFieldKey()
{
    Q_D(QExtQmlThemeBinder);
    QString fieldKey;
    if (!d->mThemeBinderParent.isNull())
    {
        fieldKey = d->mThemeBinderParent->binderFieldKey();
    }
    if (!d->mChildName.isEmpty())
    {
        fieldKey += d->mChildName + ".";
    }
    return fieldKey;
}

QVariant QExtQmlThemeBinder::propertyData(const QString &key)
{
    Q_D(QExtQmlThemeBinder);
    QString propertyFieldKey = this->binderFieldKey() + key;
    //    qDebug() << "strPropertyFieldKey=" << strPropertyFieldKey;

    if(!d->mEnabled || d->mFilterPropertyNameList.contains(propertyFieldKey))
    {
        qWarning() << "Warning: !m_bEnabled || m_filterPropertyNameList.contains(strPropertyFieldKey).";
        return QVariant();
    }

    if(d->mClassName.isEmpty())
    {
        qWarning() << "Warning: Binder className cannot be empty." << key;
        return QVariant();
    }

    QStringList fieldKeyList = QExtQmlThemeBinder::generateFieldKeyList(d->mClassName, d->mGroupName, d->mStateName);
    foreach (QString fieldKey, fieldKeyList)
    {
        QVariant propertyData = QExtQmlThemeManager::instance()->getPropertyData(fieldKey, propertyFieldKey);
        if (propertyData.isValid())
        {
            return propertyData;
        }
    }
    return QVariant();
}

QExtQmlThemeBinder *QExtQmlThemeBinder::childThemeBinder(const int &index) const
{
    Q_D(const QExtQmlThemeBinder);
    if (d->mThemeBinderChildsList.count() <= index)
    {
        qCritical() << "QExtQmlThemeBinder::childThemeBinder():iIndex out of range!";
        return nullptr;
    }
    return d->mThemeBinderChildsList.at(index);
}

QQmlListProperty<QExtQmlThemeBinder> QExtQmlThemeBinder::childs()
{
    Q_D(QExtQmlThemeBinder);
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    return QQmlListProperty<QExtQmlThemeBinder>(this, d->mThemeBinderChildsList);
#else
    return QQmlListProperty<QExtQmlThemeBinder>(this, &d->mThemeBinderChildsList);
#endif
}

QList<QExtQmlThemeBinder *> QExtQmlThemeBinder::themeBinderChilds()
{
    Q_D(QExtQmlThemeBinder);
    return d->mThemeBinderChildsList;
}

void QExtQmlThemeBinder::addChild(QExtQmlThemeBinder *child)
{
    Q_D(QExtQmlThemeBinder);
    if (!d->mThemeBinderChildsList.contains(child))
    {
        d->mThemeBinderChildsList.append(child);
        connect(child, &QExtQmlThemeBinder::destroyed, this, [=]()
                {
                    if (QExtQmlThemeBinderPrivate::smAllBindersList.contains(this))
                    {
                        d->mThemeBinderChildsList.removeOne(child);
                    }
                });
        child->setThemeBinderParent(this);
    }
}

QExtQmlThemeBinder *QExtQmlThemeBinder::themeBinderParent() const
{
    Q_D(const QExtQmlThemeBinder);
    return d->mThemeBinderParent.data();
}

void QExtQmlThemeBinder::setEnabled(const bool &enabled)
{
    Q_D(QExtQmlThemeBinder);
    static QMetaObject::Connection connection;
    if(enabled != d->mEnabled)
    {
        d->mEnabled = enabled;
        if (d->mEnabled)
        {
            connection = connect(QExtQmlThemeManager::instance(), &QExtQmlThemeManager::currentThemeChanged,
                                 this, &QExtQmlThemeBinder::onRefreshPropertys);
        }
        else
        {
            disconnect(connection);
        }
        emit this->enabledChanged();
    }
}

void QExtQmlThemeBinder::setGroupName(const QString &name)
{
    Q_D(QExtQmlThemeBinder);
    if (name != d->mGroupName)
    {
        d->mGroupName = name;
        emit this->groupNameChanged();
    }
}

void QExtQmlThemeBinder::setClassName(const QString &name)
{
    Q_D(QExtQmlThemeBinder);
    if (name != d->mClassName)
    {
        d->mClassName = name;
        emit this->classNameChanged();
    }
}

void QExtQmlThemeBinder::setChildName(const QString &name)
{
    Q_D(QExtQmlThemeBinder);
    if (name != d->mChildName)
    {
        d->mChildName = name;
        emit this->childNameChanged();
    }
}

void QExtQmlThemeBinder::setState(const QString &state)
{
    Q_D(QExtQmlThemeBinder);
    if (state != d->mStateName)
    {
        d->mStateName = state;
        QExtQmlThemeManager::instance()->generateThemeTemplateFile(this);
        if(!d->mStateAsynchronous && QExtQmlThemeManager::instance()->isCurrentThemeValid())
        {
            this->onRefreshPropertys();
        }
        emit this->stateChanged();
    }
}

void QExtQmlThemeBinder::setTarget(QObject *target)
{
    Q_D(QExtQmlThemeBinder);
    if (target != d->mTarget.data())
    {
        d->mTarget = target;
        emit this->targetChanged();
    }
}

void QExtQmlThemeBinder::setFilterPropertyName(const QStringList &nameList)
{
    Q_D(QExtQmlThemeBinder);
    if (nameList != d->mFilterPropertyNameList)
    {
        d->mFilterPropertyNameList += nameList;
        emit this->filterPropertyNameChanged();
    }
}

void QExtQmlThemeBinder::setDynamicListener(const QStringList &listenerList)
{
    Q_D(QExtQmlThemeBinder);
    if (listenerList != d->mDynamicListenerList)
    {
        d->mDynamicListenerList = listenerList;
        emit this->dynamicListenerChanged(listenerList);
    }
}

void QExtQmlThemeBinder::setStateAsynchronous(const bool &asynchronous)
{
    Q_D(QExtQmlThemeBinder);
    if (asynchronous != d->mStateAsynchronous)
    {
        d->mStateAsynchronous = asynchronous;
        emit this->stateAsynchronousChanged();
    }
}

void QExtQmlThemeBinder::setThemeBinderParent(QExtQmlThemeBinder *parent)
{
    Q_D(QExtQmlThemeBinder);
    if (!d->mThemeBinderParent.isNull() || parent == d->mThemeBinderParent.data())
    {
        return;
    }
    if (!QExtQmlThemeBinderPrivate::smAllBindersList.contains(parent))
    {
        return;
    }

    d->mThemeBinderParent = parent;
    parent->addChild(this);

    this->setFilterPropertyName(d->mThemeBinderParent->filterPropertyName());
    this->setClassName(d->mThemeBinderParent->className());
    this->setGroupName(d->mThemeBinderParent->groupName());
    this->setEnabled(d->mThemeBinderParent->isEnabled());
    this->setState(d->mThemeBinderParent->stateName());
    this->setStateAsynchronous(d->mThemeBinderParent->isStateAsynchronous());

    connect(d->mThemeBinderParent.data(), &QExtQmlThemeBinder::classNameChanged, this, [this]()
            {
                Q_D(QExtQmlThemeBinder);
                this->setClassName(d->mThemeBinderParent->className());
            });
    connect(d->mThemeBinderParent.data(), &QExtQmlThemeBinder::groupNameChanged, this, [this]()
            {
                Q_D(QExtQmlThemeBinder);
                this->setGroupName(d->mThemeBinderParent->groupName());
            });
    connect(d->mThemeBinderParent.data(), &QExtQmlThemeBinder::stateChanged, this, [this]()
            {
                Q_D(QExtQmlThemeBinder);
                this->setState(d->mThemeBinderParent->stateName());
            });
    connect(d->mThemeBinderParent.data(), &QExtQmlThemeBinder::enabledChanged, this, [this]()
            {
                Q_D(QExtQmlThemeBinder);
                this->setEnabled(d->mThemeBinderParent->isEnabled());
            });
    connect(d->mThemeBinderParent.data(), &QExtQmlThemeBinder::stateAsynchronousChanged, this, [this]()
            {
                Q_D(QExtQmlThemeBinder);
                this->setStateAsynchronous(d->mThemeBinderParent->isStateAsynchronous());
            });

    emit this->parentChanged();
}

void QExtQmlThemeBinder::onRefreshPropertys()
{
    //    qDebug() << "QExtQmlThemeBinder::onRefreshPropertys()-------------------";
    Q_D(QExtQmlThemeBinder);
    if(!d->mEnabled)
    {
        return;
    }

    QObject *target = d->mTarget.isNull() ? this : d->mTarget.data();
    QMapIterator<QString, QVariant> mapIter(d->mBindingNameToPropertyMap);

    while (mapIter.hasNext())
    {
        mapIter.next();
        if(!QExtQmlThemeManager::instance()->isCurrentThemeValid())
        {
            //send default to qml property
            QVariant result(mapIter.value());
            target->setProperty(mapIter.key().toStdString().c_str(), result);
        }
        else
        {
            QVariant result(internal::getType(mapIter.value()));
            result.setValue(this->propertyData(mapIter.key()));
            if(result.isValid())
            {
                target->setProperty(mapIter.key().toStdString().c_str(), result);
            }
        }
    }
}

void QExtQmlThemeBinder::onPropertyChanged()
{
    //    qDebug() << "QExtQmlThemeBinder::onPropertyChanged()-----------------";
    Q_D(QExtQmlThemeBinder);
    QString methodName = this->metaObject()->method(this->senderSignalIndex()).name();
    if(methodName.contains("Changed"))
    {
        QString bindingName = QString(methodName.mid(0, methodName.indexOf("Changed")));

        QVariant result(internal::getType(this->property(bindingName.toStdString().c_str())));
        QVariant change(this->property(bindingName.toStdString().c_str()));

        if(QExtQmlThemeManager::instance()->isCurrentThemeValid())
        {
            result.setValue(this->propertyData(bindingName));
            if(result.isValid() && result == change)
            {
                return; //don't need change
            }
        }
        d->mBindingNameToPropertyMap[bindingName] = this->property(bindingName.toStdString().c_str());
    }
}
