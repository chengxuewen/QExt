/****************************************************************************
**
** Library: QEXTQuick
**
** MIT License
**
** Copyright (c) 2019 toou http://www.toou.net
** Copyright (c) 2021 chengxuewen <1398831004@qq.com>
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

#include <qextQmlThemeBinder.h>
#include <qextQmlThemeBinder_p.h>
#include <qextQmlThemeBinder.h>
#include <qextQmlThemeManager.h>
#include <qextQmlThemeConstant.h>

#include <QMap>
#include <QDebug>
#include <QJsonArray>
#include <QMapIterator>
#include <QMetaMethod>

QList<QEXTQmlThemeBinder *> QEXTQmlThemeBinderPrivate::sm_allBindersList;
int QEXTQmlThemeBinderPrivate::sm_count = 0;

QEXTQmlThemeBinderPrivate::QEXTQmlThemeBinderPrivate(QEXTQmlThemeBinder *q)
    : q_ptr(q)
    , m_id(++sm_count)
{
    m_enabled = false;
    m_stateAsynchronous = true;
}

QEXTQmlThemeBinderPrivate::~QEXTQmlThemeBinderPrivate()
{

}



QEXTQmlThemeBinder::QEXTQmlThemeBinder(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QEXTQmlThemeBinderPrivate(this))
{
    Q_D(QEXTQmlThemeBinder);
    d->m_dynamicListenerList << "width" << "height" << "x" << "y";
    this->setEnabled(true);
    const QMetaObject *metaObj = this->metaObject();
    int iPropertyCount = metaObj->propertyCount();
    for (int i = 0; i < iPropertyCount; ++i) {
        QMetaProperty metaProperty = metaObj->property(i);
        d->m_filterPropertyNameList.append(metaProperty.name());
    }

    connect(this, &QEXTQmlThemeBinder::stateChanged, this, [=]() {
        if(d->m_stateAsynchronous && QEXTQmlThemeManager::instance()->isCurrentThemeValid()){
            this->onRefreshPropertys();
        }
    }, Qt::QueuedConnection);
    QEXTQmlThemeBinderPrivate::sm_allBindersList.append(this);
    QEXTQmlThemeManager::instance()->newThemeBinder(this);
}

QEXTQmlThemeBinder::~QEXTQmlThemeBinder()
{
    QEXTQmlThemeBinderPrivate::sm_allBindersList.removeOne(this);
}

void QEXTQmlThemeBinder::initialize()
{
    Q_D(QEXTQmlThemeBinder);
    //    qDebug() << "TThemeBinder::initialize()--------------------";
    //    qDebug() << "id = " << d->m_iId;
    //    qDebug() << "m_className = " << d->m_className;
    //    qDebug() << "m_groupName = " << d->m_groupName;
    //    qDebug() << "m_childName = " << d->m_childName;
    //    qDebug() << "m_stateName = " << d->m_stateName;
    //    qDebug() << "m_pParent = " << d->m_pParent;
    //    qDebug() << "m_themeBinderChildsList.size() = " << d->m_themeBinderChildsList.size();
    if(!d->m_enabled) {
        return;
    }
    const QMetaObject *metaObj = this->metaObject();

    //[1 step]
    int propertyCount = metaObj->propertyCount();
    for (int i = 0; i < propertyCount; ++i) {
        QMetaProperty metaProperty = metaObj->property(i);
        if(!d->m_propertyInitfilterList.contains(metaProperty.name()) && !d->m_filterPropertyNameList.contains(metaProperty.name())) {
            QVariant property(metaProperty.type());
            property.setValue(this->property(metaProperty.name()));
            d->m_bindingNameToPropertyMap.insert(metaProperty.name(), property);
            //            qDebug() << "metaProperty=" << metaProperty.name() << " , property=" << property;
        }
    }

    //[2 step]
    QList<int> bindingMethodIndexList;
    int binderSlotIndex = -1;
    int methodCount = metaObj->methodCount();
    for (int i = 0; i < methodCount; ++i) {
        QMetaMethod method = metaObj->method(i);
        QString methodName = QString::fromUtf8(method.name());
        if (method.methodType() == QMetaMethod::Signal && methodName.contains("Changed")){
            QString bindingName = QString(methodName.mid(0, methodName.indexOf("Changed")));
            if(d->m_bindingNameToPropertyMap.contains(bindingName) && d->m_dynamicListenerList.contains(bindingName)) {
                bindingMethodIndexList.append(method.methodIndex());
            }
        } else if(method.methodType() == QMetaMethod::Slot && methodName == "onPropertyChanged") {
            binderSlotIndex = method.methodIndex();
        }
    }

    //[3 step]
    if(-1 != binderSlotIndex && bindingMethodIndexList.length() > 0) {
        foreach (int iKey, bindingMethodIndexList) {
            QMetaObject::connect(this, iKey, this, binderSlotIndex);
        }
    }

    //[4 step]
    foreach (QEXTQmlThemeBinder *childBinder, d->m_themeBinderChildsList) {
        childBinder->setStateAsynchronous(d->m_stateAsynchronous);
        childBinder->setFilterPropertyName(d->m_filterPropertyNameList);
        childBinder->setClassName(d->m_className);
        childBinder->setGroupName(d->m_groupName);
        childBinder->setEnabled(d->m_enabled);
        childBinder->setState(d->m_stateName);
        childBinder->setThemeBinderParent(this);
        childBinder->initialize();
    }

    if(QEXTQmlThemeManager::instance()->isCurrentThemeValid()){
        this->onRefreshPropertys();
    }

    emit this->initialized();
}

int QEXTQmlThemeBinder::id() const
{
    Q_D(const QEXTQmlThemeBinder);
    return d->m_id;
}

bool QEXTQmlThemeBinder::isEnabled() const
{
    Q_D(const QEXTQmlThemeBinder);
    return d->m_enabled;
}

const QString &QEXTQmlThemeBinder::groupName() const
{
    Q_D(const QEXTQmlThemeBinder);
    return d->m_groupName;
}

const QString &QEXTQmlThemeBinder::className() const
{
    Q_D(const QEXTQmlThemeBinder);
    return d->m_className;
}

const QString &QEXTQmlThemeBinder::childName() const
{
    Q_D(const QEXTQmlThemeBinder);
    return d->m_childName;
}

const QString &QEXTQmlThemeBinder::stateName() const
{
    Q_D(const QEXTQmlThemeBinder);
    return d->m_stateName;
}

QObject *QEXTQmlThemeBinder::target() const
{
    Q_D(const QEXTQmlThemeBinder);
    return d->m_target.data();
}

QStringList QEXTQmlThemeBinder::filterPropertyName() const
{
    Q_D(const QEXTQmlThemeBinder);
    return d->m_filterPropertyNameList;
}

QStringList QEXTQmlThemeBinder::dynamicListener() const
{
    Q_D(const QEXTQmlThemeBinder);
    return d->m_dynamicListenerList;
}

bool QEXTQmlThemeBinder::isStateAsynchronous() const
{
    Q_D(const QEXTQmlThemeBinder);
    return d->m_stateAsynchronous;
}

QMap<QString, QVariant> QEXTQmlThemeBinder::themeBindingPropertyMap() const
{
    Q_D(const QEXTQmlThemeBinder);
    return d->m_bindingNameToPropertyMap;
}

int QEXTQmlThemeBinder::themeBinderChildsCount() const
{
    Q_D(const QEXTQmlThemeBinder);
    return d->m_themeBinderChildsList.count();
}

QList<QEXTQmlThemeBinder *> QEXTQmlThemeBinder::allThemeBinders()
{
    return QEXTQmlThemeBinderPrivate::sm_allBindersList;
}

QString QEXTQmlThemeBinder::generateFieldKey(const QString &className, const QString &groupName, const QString &stateName)
{
    QString strKey = className;
    if (!groupName.isEmpty()) {
        strKey += "#" + groupName;
    }
    if (!stateName.isEmpty()) {
        strKey += ":" + stateName;
    }
    return strKey;
}

QStringList QEXTQmlThemeBinder::generateFieldKeyList(const QString &className, const QString &groupName, const QString &stateName)
{
    QStringList listKey;
    listKey.append(QEXTQmlThemeBinder::generateFieldKey(className, groupName, stateName));
    listKey.append(QEXTQmlThemeBinder::generateFieldKey(className, groupName, ""));
    listKey.append(QEXTQmlThemeBinder::generateFieldKey(className, "", stateName));
    listKey.append(QEXTQmlThemeBinder::generateFieldKey(className, "", ""));
    listKey.removeDuplicates();
    return listKey;
}

QString QEXTQmlThemeBinder::binderFieldKey()
{
    Q_D(QEXTQmlThemeBinder);
    QString fieldKey;
    if (!d->m_themeBinderParent.isNull()) {
        fieldKey = d->m_themeBinderParent->binderFieldKey();
    }
    if (!d->m_childName.isEmpty()) {
        fieldKey += d->m_childName + ".";
    }
    return fieldKey;
}

QVariant QEXTQmlThemeBinder::propertyData(const QString &key)
{
    Q_D(QEXTQmlThemeBinder);
    QString propertyFieldKey = this->binderFieldKey() + key;
    //    qDebug() << "strPropertyFieldKey=" << strPropertyFieldKey;

    if(!d->m_enabled || d->m_filterPropertyNameList.contains(propertyFieldKey)) {
        qWarning() << "Warning: !m_bEnabled || m_filterPropertyNameList.contains(strPropertyFieldKey).";
        return QVariant();
    }

    if(d->m_className.isEmpty()){
        qWarning() << "Warning: Binder className cannot be empty." << key;
        return QVariant();
    }

    QStringList fieldKeyList = QEXTQmlThemeBinder::generateFieldKeyList(d->m_className, d->m_groupName, d->m_stateName);
    foreach (QString fieldKey, fieldKeyList) {
        QVariant propertyData = QEXTQmlThemeManager::instance()->getPropertyData(fieldKey, propertyFieldKey);
        if (propertyData.isValid()) {
            return propertyData;
        }
    }
    return QVariant();
}

QEXTQmlThemeBinder *QEXTQmlThemeBinder::childThemeBinder(const int &index) const
{
    Q_D(const QEXTQmlThemeBinder);
    if (d->m_themeBinderChildsList.count() <= index) {
        qCritical() << "QEXTQmlThemeBinder::childThemeBinder():iIndex out of range!";
        return nullptr;
    }
    return d->m_themeBinderChildsList.at(index);
}

QQmlListProperty<QEXTQmlThemeBinder> QEXTQmlThemeBinder::qmlThemeBinderChilds()
{
    Q_D(QEXTQmlThemeBinder);
    return QQmlListProperty<QEXTQmlThemeBinder>(this, d->m_themeBinderChildsList);
}

QList<QEXTQmlThemeBinder *> QEXTQmlThemeBinder::themeBinderChilds()
{
    Q_D(QEXTQmlThemeBinder);
    return d->m_themeBinderChildsList;
}

void QEXTQmlThemeBinder::addChild(QEXTQmlThemeBinder *child)
{
    Q_D(QEXTQmlThemeBinder);
    if (!d->m_themeBinderChildsList.contains(child)) {
        d->m_themeBinderChildsList.append(child);
        connect(child, &QEXTQmlThemeBinder::destroyed, [=](){
            if (QEXTQmlThemeBinderPrivate::sm_allBindersList.contains(this)) {
                d->m_themeBinderChildsList.removeOne(child);
            }
        });
        child->setThemeBinderParent(this);
    }
}

QEXTQmlThemeBinder *QEXTQmlThemeBinder::themeBinderParent() const
{
    Q_D(const QEXTQmlThemeBinder);
    return d->m_themeBinderParent.data();
}

void QEXTQmlThemeBinder::setEnabled(const bool &enabled)
{
    Q_D(QEXTQmlThemeBinder);
    static QMetaObject::Connection connection;
    if(enabled != d->m_enabled) {
        d->m_enabled = enabled;
        if (d->m_enabled) {
            connection = connect(QEXTQmlThemeManager::instance(), &QEXTQmlThemeManager::currentThemeChanged, this, &QEXTQmlThemeBinder::onRefreshPropertys);
        } else {
            disconnect(connection);
        }
        emit this->enabledChanged();
    }
}

void QEXTQmlThemeBinder::setGroupName(const QString &name)
{
    Q_D(QEXTQmlThemeBinder);
    if (name != d->m_groupName) {
        d->m_groupName = name;
        emit this->groupNameChanged();
    }
}

void QEXTQmlThemeBinder::setClassName(const QString &name)
{
    Q_D(QEXTQmlThemeBinder);
    if (name != d->m_className) {
        d->m_className = name;
        emit this->classNameChanged();
    }
}

void QEXTQmlThemeBinder::setChildName(const QString &name)
{
    Q_D(QEXTQmlThemeBinder);
    if (name != d->m_childName) {
        d->m_childName = name;
        emit this->childNameChanged();
    }
}

void QEXTQmlThemeBinder::setState(const QString &state)
{
    Q_D(QEXTQmlThemeBinder);
    if (state != d->m_stateName) {
        d->m_stateName = state;
        QEXTQmlThemeManager::instance()->generateThemeTemplateFile(this);
        if(!d->m_stateAsynchronous && QEXTQmlThemeManager::instance()->isCurrentThemeValid()){
            this->onRefreshPropertys();
        }
        emit this->stateChanged();
    }
}

void QEXTQmlThemeBinder::setTarget(QObject *target)
{
    Q_D(QEXTQmlThemeBinder);
    if (target != d->m_target.data()) {
        d->m_target = target;
        emit this->targetChanged();
    }
}

void QEXTQmlThemeBinder::setFilterPropertyName(const QStringList &nameList)
{
    Q_D(QEXTQmlThemeBinder);
    if (nameList != d->m_filterPropertyNameList) {
        d->m_filterPropertyNameList += nameList;
        emit this->filterPropertyNameChanged();
    }
}

void QEXTQmlThemeBinder::setDynamicListener(const QStringList &listenerList)
{
    Q_D(QEXTQmlThemeBinder);
    if (listenerList != d->m_dynamicListenerList) {
        d->m_dynamicListenerList = listenerList;
        emit this->dynamicListenerChanged(listenerList);
    }
}

void QEXTQmlThemeBinder::setStateAsynchronous(const bool &asynchronous)
{
    Q_D(QEXTQmlThemeBinder);
    if (asynchronous != d->m_stateAsynchronous) {
        d->m_stateAsynchronous = asynchronous;
        emit this->stateAsynchronousChanged();
    }
}

void QEXTQmlThemeBinder::setThemeBinderParent(QEXTQmlThemeBinder *parent)
{
    Q_D(QEXTQmlThemeBinder);
    if (!d->m_themeBinderParent.isNull() || parent == d->m_themeBinderParent.data()) {
        return;
    }
    if (!QEXTQmlThemeBinderPrivate::sm_allBindersList.contains(parent)) {
        return;
    }

    d->m_themeBinderParent = parent;
    parent->addChild(this);

    this->setFilterPropertyName(d->m_themeBinderParent->filterPropertyName());
    this->setClassName(d->m_themeBinderParent->className());
    this->setGroupName(d->m_themeBinderParent->groupName());
    this->setEnabled(d->m_themeBinderParent->isEnabled());
    this->setState(d->m_themeBinderParent->stateName());
    this->setStateAsynchronous(d->m_themeBinderParent->isStateAsynchronous());

    connect(d->m_themeBinderParent.data(), &QEXTQmlThemeBinder::classNameChanged, this, [this]() {
        Q_D(QEXTQmlThemeBinder);
        this->setClassName(d->m_themeBinderParent->className());
    });
    connect(d->m_themeBinderParent.data(), &QEXTQmlThemeBinder::groupNameChanged, this, [this]() {
        Q_D(QEXTQmlThemeBinder);
        this->setGroupName(d->m_themeBinderParent->groupName());
    });
    connect(d->m_themeBinderParent.data(), &QEXTQmlThemeBinder::stateChanged, this, [this]() {
        Q_D(QEXTQmlThemeBinder);
        this->setState(d->m_themeBinderParent->stateName());
    });
    connect(d->m_themeBinderParent.data(), &QEXTQmlThemeBinder::enabledChanged, this, [this]() {
        Q_D(QEXTQmlThemeBinder);
        this->setEnabled(d->m_themeBinderParent->isEnabled());
    });
    connect(d->m_themeBinderParent.data(), &QEXTQmlThemeBinder::stateAsynchronousChanged, this, [this]() {
        Q_D(QEXTQmlThemeBinder);
        this->setStateAsynchronous(d->m_themeBinderParent->isStateAsynchronous());
    });

    emit this->parentChanged();
}

void QEXTQmlThemeBinder::onRefreshPropertys()
{
    //    qDebug() << "QEXTQmlThemeBinder::onRefreshPropertys()-------------------";
    Q_D(QEXTQmlThemeBinder);
    if(!d->m_enabled) {
        return;
    }

    QObject *target = d->m_target.isNull() ? this : d->m_target.data();
    QMapIterator<QString, QVariant> mapIter(d->m_bindingNameToPropertyMap);

    while (mapIter.hasNext()) {
        mapIter.next();
        if(!QEXTQmlThemeManager::instance()->isCurrentThemeValid()){
            //send default to qml property
            QVariant result(mapIter.value());
            target->setProperty(mapIter.key().toStdString().c_str(), result);
        } else {
            QVariant result(mapIter.value().type());
            result.setValue(this->propertyData(mapIter.key()));
            if(result.isValid()){
                target->setProperty(mapIter.key().toStdString().c_str(), result);
            }
        }
    }
}

void QEXTQmlThemeBinder::onPropertyChanged()
{
    //    qDebug() << "QEXTQmlThemeBinder::onPropertyChanged()-----------------";
    Q_D(QEXTQmlThemeBinder);
    QString methodName = this->metaObject()->method(this->senderSignalIndex()).name();
    if(methodName.contains("Changed")) {
        QString bindingName = QString(methodName.mid(0, methodName.indexOf("Changed")));

        QVariant result(this->property(bindingName.toStdString().c_str()).type());
        QVariant change(this->property(bindingName.toStdString().c_str()));

        if(QEXTQmlThemeManager::instance()->isCurrentThemeValid()){
            result.setValue(this->propertyData(bindingName));
            if(result.isValid() && result == change) {
                return; //don't need change
            }
        }
        d->m_bindingNameToPropertyMap[bindingName] = this->property(bindingName.toStdString().c_str());
    }
}
