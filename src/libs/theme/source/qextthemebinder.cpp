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

#include <qextthemebinder.h>
#include <qextthemebinder_p.h>
#include <qextthememanager.h>
#include <qextthemeconstant.h>

#include <QMap>
#include <QDebug>
#include <QMapIterator>
#include <QMetaMethod>

#ifdef QEXT_BUILD_QJSON
#include <QJsonArray>
#endif


QList<QEXTThemeBinder *> QEXTThemeBinderPrivate::sm_allBindersList;
quint64 QEXTThemeBinderPrivate::sm_count = 0;

QEXTThemeBinderPrivate::QEXTThemeBinderPrivate(QEXTThemeBinder *qq)
    : QEXTObjectPrivate(qq),
      m_id(++sm_count)
{
    m_target = QEXT_NULLPTR;
    m_parent = QEXT_NULLPTR;
    m_isEnabled = false;
    m_isStateAsync = true;
}

QEXTThemeBinderPrivate::~QEXTThemeBinderPrivate()
{

}

QVariant QEXTThemeBinderPrivate::propertyData(const QString &key)
{
    QEXT_Q(QEXTThemeBinder);
    QString propertyFieldKey = q->binderFieldKey() + key;

    if(!m_isEnabled || m_filterPropertyNameList.contains(propertyFieldKey)) {
        qWarning() << "Warning: !m_isEnabled || m_filterPropertyNameList.contains(strPropertyFieldKey).";
        return QVariant();
    }

    if(m_className.isEmpty()){
        qWarning() << "Warning: Binder className cannot be empty." << key;
        return QVariant();
    }

    QStringList fieldKeyList = QEXTThemeBinder::generateFieldKeyList(m_className, m_groupName, m_stateName);
    foreach (QString fieldKey, fieldKeyList) {
        QVariant propertyData = QEXTThemeManager::instance()->propertyData(fieldKey, propertyFieldKey);
        if (propertyData.isValid()) {
            return propertyData;
        }
    }
    return QVariant();
}



QEXTThemeBinder::QEXTThemeBinder(QObject *parent)
    : QObject(parent), QEXTObject(*(new QEXTThemeBinderPrivate(this)))
{
    QEXT_D(QEXTThemeBinder);
    d->m_dynamicListenerList << "width" << "height" << "x" << "y";
    this->setEnabled(true);
    const QMetaObject *metaObj = this->metaObject();
    int propertyCount = metaObj->propertyCount();
    for (int i = 0; i < propertyCount; ++i) {
        QMetaProperty metaProperty = metaObj->property(i);
        d->m_filterPropertyNameList.append(metaProperty.name());
    }

    connect(this, SIGNAL(stateNameChanged()), this, SLOT(onStateChanged()), Qt::QueuedConnection);
    QEXTThemeBinderPrivate::sm_allBindersList.append(this);
    QEXTThemeManager::instance()->newThemeBinder(this);
}

QEXTThemeBinder::~QEXTThemeBinder()
{
    QEXTThemeBinderPrivate::sm_allBindersList.removeOne(this);
}

void QEXTThemeBinder::initialize()
{
    QEXT_D(QEXTThemeBinder);
    //    qDebug() << "QEXTThemeBinder::initialize()--------------------";
    //    qDebug() << "id = " << d->m_id;
    //    qDebug() << "m_className = " << d->m_className;
    //    qDebug() << "m_groupName = " << d->m_groupName;
    //    qDebug() << "m_childName = " << d->m_childName;
    //    qDebug() << "m_stateName = " << d->m_stateName;
    //    qDebug() << "m_parent = " << d->m_parent;
    //    qDebug() << "m_childNameList.size() = " << d->m_childNameList.size();
    if(!d->m_isEnabled) {
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
            d->m_bindingPropertyMap.insert(metaProperty.name(), property);
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
            if(d->m_bindingPropertyMap.contains(bindingName) && d->m_dynamicListenerList.contains(bindingName)) {
                bindingMethodIndexList.append(method.methodIndex());
            }
        } else if(method.methodType() == QMetaMethod::Slot && methodName == "onPropertyChanged") {
            binderSlotIndex = method.methodIndex();
        }
    }

    //[3 step]
    if(-1 != binderSlotIndex && bindingMethodIndexList.length() > 0) {
        foreach (int key, bindingMethodIndexList) {
            QMetaObject::connect(this, key, this, binderSlotIndex);
        }
    }

    //[4 step]
    foreach (QEXTThemeBinder *childBinder, d->m_childNameList) {
        childBinder->setStateAsync(d->m_isStateAsync);
        childBinder->setFilterPropertyName(d->m_filterPropertyNameList);
        childBinder->setClassName(d->m_className);
        childBinder->setGroupName(d->m_groupName);
        childBinder->setEnabled(d->m_isEnabled);
        childBinder->setStateName(d->m_stateName);
        childBinder->setParent(this);
        childBinder->initialize();
    }

    if(QEXTThemeManager::instance()->isCurrentThemeValid()){
        this->onRefreshPropertys();
    }

    emit this->initialized();
}

int QEXTThemeBinder::id() const
{
    QEXT_DC(QEXTThemeBinder);
    return d->m_id;
}

bool QEXTThemeBinder::isEnabled() const
{
    QEXT_DC(QEXTThemeBinder);
    return d->m_isEnabled;
}

const QString &QEXTThemeBinder::groupName() const
{
    QEXT_DC(QEXTThemeBinder);
    return d->m_groupName;
}

const QString &QEXTThemeBinder::className() const
{
    QEXT_DC(QEXTThemeBinder);
    return d->m_className;
}

const QString &QEXTThemeBinder::childName() const
{
    QEXT_DC(QEXTThemeBinder);
    return d->m_childName;
}

const QString &QEXTThemeBinder::stateName() const
{
    QEXT_DC(QEXTThemeBinder);
    return d->m_stateName;
}

QObject *QEXTThemeBinder::target() const
{
    QEXT_DC(QEXTThemeBinder);
    return d->m_target;
}

QStringList QEXTThemeBinder::filterPropertyName() const
{
    QEXT_DC(QEXTThemeBinder);
    return d->m_filterPropertyNameList;
}

QStringList QEXTThemeBinder::dynamicListener() const
{
    QEXT_DC(QEXTThemeBinder);
    return d->m_dynamicListenerList;
}

bool QEXTThemeBinder::isStateAsync() const
{
    QEXT_DC(QEXTThemeBinder);
    return d->m_isStateAsync;
}

QMap<QString, QVariant> QEXTThemeBinder::bindingPropertyMap() const
{
    QEXT_DC(QEXTThemeBinder);
    return d->m_bindingPropertyMap;
}

int QEXTThemeBinder::childsCount() const
{
    QEXT_DC(QEXTThemeBinder);
    return d->m_childNameList.count();
}

QString QEXTThemeBinder::binderFieldKey()
{
    QEXT_D(QEXTThemeBinder);
    QString fieldKey;
    if (QEXT_NULLPTR != d->m_parent) {
        fieldKey = d->m_parent->binderFieldKey();
    }
    if (!d->m_childName.isEmpty()) {
        fieldKey += d->m_childName + ".";
    }
    return fieldKey;
}

QList<QEXTThemeBinder *> QEXTThemeBinder::allBindersList()
{
    return QEXTThemeBinderPrivate::sm_allBindersList;
}

QString QEXTThemeBinder::generateFieldKey(const QString &className, const QString &groupName, const QString &stateName)
{
    QString key = className;
    if (!groupName.isEmpty()) {
        key += "#" + groupName;
    }
    if (!stateName.isEmpty()) {
        key += ":" + stateName;
    }
    return key;
}

QStringList QEXTThemeBinder::generateFieldKeyList(const QString &className, const QString &groupName, const QString &stateName)
{
    QStringList keyList;
    keyList.append(QEXTThemeBinder::generateFieldKey(className, groupName, stateName));
    keyList.append(QEXTThemeBinder::generateFieldKey(className, groupName, ""));
    keyList.append(QEXTThemeBinder::generateFieldKey(className, "", stateName));
    keyList.append(QEXTThemeBinder::generateFieldKey(className, "", ""));
    keyList.removeDuplicates();
    return keyList;
}

QEXTThemeBinder *QEXTThemeBinder::child(const int &index) const
{
    QEXT_DC(QEXTThemeBinder);
    if (d->m_childNameList.count() <= index) {
        qCritical() << "QTKStyleBinder::getChild():iIndex out of range!";
        return QEXT_NULLPTR;
    }
    return d->m_childNameList.at(index);
}

#ifdef QEXT_BUILD_QML
QQmlListProperty<QEXTThemeBinder> QEXTThemeBinder::qmlChildsList()
{
    QEXT_D(QEXTThemeBinder);
    return QQmlListProperty<QEXTThemeBinder>(this, d->m_childNameList);
}
#endif

QList<QEXTThemeBinder *> QEXTThemeBinder::childsList()
{
    QEXT_D(QEXTThemeBinder);
    return d->m_childNameList;
}

void QEXTThemeBinder::addChild(QEXTThemeBinder *child)
{
    QEXT_D(QEXTThemeBinder);
    if (!d->m_childNameList.contains(child)) {
        d->m_childNameList.append(child);
        connect(child, SIGNAL(destroyed(QObject*)), this, SLOT(onDestroyed()));
        child->setParent(this);
    }
}

QEXTThemeBinder *QEXTThemeBinder::parent() const
{
    QEXT_DC(QEXTThemeBinder);
    return d->m_parent.data();
}

void QEXTThemeBinder::setEnabled(const bool &enabled)
{
    QEXT_D(QEXTThemeBinder);
    static QMetaObject::Connection connection;
    if(enabled != d->m_isEnabled) {
        d->m_isEnabled = enabled;
        if (d->m_isEnabled) {
            connection = connect(QEXTThemeManager::instance(), &QEXTThemeManager::currentThemeChanged, this, &QEXTThemeBinder::onRefreshPropertys);
        } else {
            disconnect(connection);
        }
        emit this->enabledChanged();
    }
}

void QEXTThemeBinder::setGroupName(const QString &name)
{
    QEXT_D(QEXTThemeBinder);
    if (name != d->m_groupName) {
        d->m_groupName = name;
        emit this->groupNameChanged();
    }
}

void QEXTThemeBinder::setClassName(const QString &name)
{
    QEXT_D(QEXTThemeBinder);
    if (name != d->m_className) {
        d->m_className = name;
        emit this->classNameChanged();
    }
}

void QEXTThemeBinder::setChildName(const QString &name)
{
    QEXT_D(QEXTThemeBinder);
    if (name != d->m_childName) {
        d->m_childName = name;
        emit this->childNameChanged();
    }
}

void QEXTThemeBinder::setStateName(const QString &name)
{
    QEXT_D(QEXTThemeBinder);
    if (name != d->m_stateName) {
        d->m_stateName = name;
        QEXTThemeManager::instance()->generateThemeTemplateFile(this);
        if(!d->m_isStateAsync && QEXTThemeManager::instance()->isCurrentThemeValid()){
            this->onRefreshPropertys();
        }
        emit this->stateNameChanged();
    }
}

void QEXTThemeBinder::setTarget(QObject *target)
{
    QEXT_D(QEXTThemeBinder);
    if (target != d->m_target) {
        d->m_target = target;
        emit this->targetChanged();
    }
}

void QEXTThemeBinder::setFilterPropertyName(const QStringList &nameList)
{
    QEXT_D(QEXTThemeBinder);
    if (nameList != d->m_filterPropertyNameList) {
        d->m_filterPropertyNameList += nameList;
        emit this->filterPropertyNameChanged();
    }
}

void QEXTThemeBinder::setDynamicListener(const QStringList &listenerList)
{
    QEXT_D(QEXTThemeBinder);
    if (listenerList != d->m_dynamicListenerList) {
        d->m_dynamicListenerList = listenerList;
        emit this->dynamicListenerChanged(listenerList);
    }
}

void QEXTThemeBinder::setStateAsync(const bool &async)
{
    QEXT_D(QEXTThemeBinder);
    if (async != d->m_isStateAsync) {
        d->m_isStateAsync = async;
        emit this->stateAsyncChanged();
    }
}

void QEXTThemeBinder::setParent(QEXTThemeBinder *parent)
{
    QEXT_D(QEXTThemeBinder);
    if (QEXT_NULLPTR != d->m_parent || parent == d->m_parent) {
        return;
    }
    if (!QEXTThemeBinderPrivate::sm_allBindersList.contains(parent)) {
        return;
    }

    d->m_parent = parent;
    parent->addChild(this);

    this->setFilterPropertyName(d->m_parent->filterPropertyName());
    this->setClassName(d->m_parent->className());
    this->setGroupName(d->m_parent->groupName());
    this->setEnabled(d->m_parent->isEnabled());
    this->setStateName(d->m_parent->stateName());
    this->setStateAsync(d->m_parent->isStateAsync());

    connect(d->m_parent, SIGNAL(classNameChanged()), this, SLOT(onParentClassNameChanged()));
    connect(d->m_parent, SIGNAL(groupNameChanged()), this, SLOT(onParentGroupNameChanged()));
    connect(d->m_parent, SIGNAL(stateNameChanged()), this, SLOT(onParentStateNameChanged()));
    connect(d->m_parent, SIGNAL(enabledChanged()), this, SLOT(onParentEnabledChanged()));
    connect(d->m_parent, SIGNAL(stateAsyncChanged()), this, SLOT(onParentStateAsyncChanged()));
    emit this->parentChanged();
}

void QEXTThemeBinder::onRefreshPropertys()
{
    //    qDebug() << "QEXTThemeBinder::onRefreshPropertys()-------------------";
    QEXT_D(QEXTThemeBinder);
    if(!d->m_isEnabled) {
        return;
    }

    QObject *target = (QEXT_NULLPTR == d->m_target) ? this : d->m_target;
    QMapIterator<QString, QVariant> iter(d->m_bindingPropertyMap);

    while (iter.hasNext()) {
        iter.next();
        if(!QEXTThemeManager::instance()->isCurrentThemeValid()){
            //send default to qml property
            QVariant result(iter.value());
            target->setProperty(iter.key().toStdString().c_str(), result);
        } else {
            QVariant result(iter.value().type());
            result.setValue(d->propertyData(iter.key()));
            if(result.isValid()){
                target->setProperty(iter.key().toStdString().c_str(), result);
            }
        }
    }
}

void QEXTThemeBinder::onPropertyChanged()
{
    //    qDebug() << "QEXTThemeBinder::onPropertyChanged()-----------------";
    QEXT_D(QEXTThemeBinder);
    // todo
    QString methodName = this->metaObject()->method(this->senderSignalIndex()).name();
    if(methodName.contains("Changed")) {
        QString bindingName = QString(methodName.mid(0, methodName.indexOf("Changed")));

        QVariant result(this->property(bindingName.toStdString().c_str()).type());
        QVariant change(this->property(bindingName.toStdString().c_str()));

        if(QEXTThemeManager::instance()->isCurrentThemeValid()){
            result.setValue(d->propertyData(bindingName));
            if(result.isValid() && result == change) {
                return; //don't need change
            }
        }
        d->m_bindingPropertyMap[bindingName] = this->property(bindingName.toStdString().c_str());
    }
}

void QEXTThemeBinder::onStateChanged()
{
    QEXT_D(QEXTThemeBinder);
    if(d->m_isStateAsync && QEXTThemeManager::instance()->isCurrentThemeValid()){
        this->onRefreshPropertys();
    }
}

void QEXTThemeBinder::onDestroyed()
{
    QEXT_D(QEXTThemeBinder);
    QEXTThemeBinder *binder = qobject_cast<QEXTThemeBinder *>(sender());
    if (binder) {
        d->m_childNameList.removeOne(binder);
    }
}

void QEXTThemeBinder::onParentClassNameChanged()
{
    QEXTThemeBinder *binder = qobject_cast<QEXTThemeBinder *>(sender());
    if (binder) {
        this->setClassName(binder->className());
    }
}

void QEXTThemeBinder::onParentGroupNameChanged()
{
    QEXTThemeBinder *binder = qobject_cast<QEXTThemeBinder *>(sender());
    if (binder) {
        this->setGroupName(binder->groupName());
    }
}

void QEXTThemeBinder::onParentStateNameChanged()
{
    QEXTThemeBinder *binder = qobject_cast<QEXTThemeBinder *>(sender());
    if (binder) {
        this->setStateName(binder->stateName());
    }
}

void QEXTThemeBinder::onParentEnabledChanged()
{
    QEXTThemeBinder *binder = qobject_cast<QEXTThemeBinder *>(sender());
    if (binder) {
        this->setEnabled(binder->isEnabled());
    }
}

void QEXTThemeBinder::onParentStateAsyncChanged()
{
    QEXTThemeBinder *binder = qobject_cast<QEXTThemeBinder *>(sender());
    if (binder) {
        this->setStateAsync(binder->isStateAsync());
    }
}
