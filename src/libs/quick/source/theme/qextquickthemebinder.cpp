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

#include <qextquickthemebinder.h>
#include <qextquickthemebinder_p.h>
#include <qextquickthemebinder.h>
#include <qextquickthememanager.h>
#include <qextquickthemeconstant.h>

#include <QMap>
#include <QDebug>
#include <QJsonArray>
#include <QMapIterator>
#include <QMetaMethod>


QList<QEXTQuickThemeBinder *> QEXTQuickThemeBinderPrivate::sm_allBindersList;
int QEXTQuickThemeBinderPrivate::sm_count = 0;

QEXTQuickThemeBinderPrivate::QEXTQuickThemeBinderPrivate(QEXTQuickThemeBinder *qq)
    : QEXTObjectPrivate(qq),
      m_id(++sm_count)
{
    m_enabled = false;
    m_stateAsynchronous = true;
}

QEXTQuickThemeBinderPrivate::~QEXTQuickThemeBinderPrivate()
{

}



QEXTQuickThemeBinder::QEXTQuickThemeBinder(QObject *parent)
    : QObject(parent), QEXTObject(*(new QEXTQuickThemeBinderPrivate(this)))
{
    QEXT_D(QEXTQuickThemeBinder);
    d->m_dynamicListenerList << "width" << "height" << "x" << "y";
    this->setEnabled(true);
    const QMetaObject *metaObj = this->metaObject();
    int iPropertyCount = metaObj->propertyCount();
    for (int i = 0; i < iPropertyCount; ++i) {
        QMetaProperty metaProperty = metaObj->property(i);
        d->m_filterPropertyNameList.append(metaProperty.name());
    }

    connect(this, &QEXTQuickThemeBinder::stateChanged, this, [=]() {
        if(d->m_stateAsynchronous && QEXTQuickThemeManager::instance()->isCurrentThemeValid()){
            this->onRefreshPropertys();
        }
    }, Qt::QueuedConnection);
    QEXTQuickThemeBinderPrivate::sm_allBindersList.append(this);
    QEXTQuickThemeManager::instance()->newThemeBinder(this);
}

QEXTQuickThemeBinder::~QEXTQuickThemeBinder()
{
    QEXTQuickThemeBinderPrivate::sm_allBindersList.removeOne(this);
}

void QEXTQuickThemeBinder::initialize()
{
    QEXT_D(QEXTQuickThemeBinder);
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
    foreach (QEXTQuickThemeBinder *childBinder, d->m_themeBinderChildsList) {
        childBinder->setStateAsynchronous(d->m_stateAsynchronous);
        childBinder->setFilterPropertyName(d->m_filterPropertyNameList);
        childBinder->setClassName(d->m_className);
        childBinder->setGroupName(d->m_groupName);
        childBinder->setEnabled(d->m_enabled);
        childBinder->setState(d->m_stateName);
        childBinder->setThemeBinderParent(this);
        childBinder->initialize();
    }

    if(QEXTQuickThemeManager::instance()->isCurrentThemeValid()){
        this->onRefreshPropertys();
    }

    emit this->initialized();
}

int QEXTQuickThemeBinder::id() const
{
    QEXT_DC(QEXTQuickThemeBinder);
    return d->m_id;
}

bool QEXTQuickThemeBinder::isEnabled() const
{
    QEXT_DC(QEXTQuickThemeBinder);
    return d->m_enabled;
}

const QString &QEXTQuickThemeBinder::groupName() const
{
    QEXT_DC(QEXTQuickThemeBinder);
    return d->m_groupName;
}

const QString &QEXTQuickThemeBinder::className() const
{
    QEXT_DC(QEXTQuickThemeBinder);
    return d->m_className;
}

const QString &QEXTQuickThemeBinder::childName() const
{
    QEXT_DC(QEXTQuickThemeBinder);
    return d->m_childName;
}

const QString &QEXTQuickThemeBinder::stateName() const
{
    QEXT_DC(QEXTQuickThemeBinder);
    return d->m_stateName;
}

QObject *QEXTQuickThemeBinder::target() const
{
    QEXT_DC(QEXTQuickThemeBinder);
    return d->m_target.data();
}

QStringList QEXTQuickThemeBinder::filterPropertyName() const
{
    QEXT_DC(QEXTQuickThemeBinder);
    return d->m_filterPropertyNameList;
}

QStringList QEXTQuickThemeBinder::dynamicListener() const
{
    QEXT_DC(QEXTQuickThemeBinder);
    return d->m_dynamicListenerList;
}

bool QEXTQuickThemeBinder::isStateAsynchronous() const
{
    QEXT_DC(QEXTQuickThemeBinder);
    return d->m_stateAsynchronous;
}

QMap<QString, QVariant> QEXTQuickThemeBinder::themeBindingPropertyMap() const
{
    QEXT_DC(QEXTQuickThemeBinder);
    return d->m_bindingNameToPropertyMap;
}

int QEXTQuickThemeBinder::themeBinderChildsCount() const
{
    QEXT_DC(QEXTQuickThemeBinder);
    return d->m_themeBinderChildsList.count();
}

QList<QEXTQuickThemeBinder *> QEXTQuickThemeBinder::allThemeBinders()
{
    return QEXTQuickThemeBinderPrivate::sm_allBindersList;
}

QString QEXTQuickThemeBinder::generateFieldKey(const QString &className, const QString &groupName, const QString &stateName)
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

QStringList QEXTQuickThemeBinder::generateFieldKeyList(const QString &className, const QString &groupName, const QString &stateName)
{
    QStringList listKey;
    listKey.append(QEXTQuickThemeBinder::generateFieldKey(className, groupName, stateName));
    listKey.append(QEXTQuickThemeBinder::generateFieldKey(className, groupName, ""));
    listKey.append(QEXTQuickThemeBinder::generateFieldKey(className, "", stateName));
    listKey.append(QEXTQuickThemeBinder::generateFieldKey(className, "", ""));
    listKey.removeDuplicates();
    return listKey;
}

QString QEXTQuickThemeBinder::binderFieldKey()
{
    QEXT_D(QEXTQuickThemeBinder);
    QString fieldKey;
    if (!d->m_themeBinderParent.isNull()) {
        fieldKey = d->m_themeBinderParent->binderFieldKey();
    }
    if (!d->m_childName.isEmpty()) {
        fieldKey += d->m_childName + ".";
    }
    return fieldKey;
}

QVariant QEXTQuickThemeBinder::propertyData(const QString &key)
{
    QEXT_D(QEXTQuickThemeBinder);
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

    QStringList fieldKeyList = QEXTQuickThemeBinder::generateFieldKeyList(d->m_className, d->m_groupName, d->m_stateName);
    foreach (QString fieldKey, fieldKeyList) {
        QVariant propertyData = QEXTQuickThemeManager::instance()->getPropertyData(fieldKey, propertyFieldKey);
        if (propertyData.isValid()) {
            return propertyData;
        }
    }
    return QVariant();
}

QEXTQuickThemeBinder *QEXTQuickThemeBinder::childThemeBinder(const int &index) const
{
    QEXT_D(const QEXTQuickThemeBinder);
    if (d->m_themeBinderChildsList.count() <= index) {
        qCritical() << "QTKStyleBinder::getChild():iIndex out of range!";
        return nullptr;
    }
    return d->m_themeBinderChildsList.at(index);
}

QQmlListProperty<QEXTQuickThemeBinder> QEXTQuickThemeBinder::qmlThemeBinderChilds()
{
    QEXT_D(QEXTQuickThemeBinder);
    return QQmlListProperty<QEXTQuickThemeBinder>(this, d->m_themeBinderChildsList);
}

QList<QEXTQuickThemeBinder *> QEXTQuickThemeBinder::themeBinderChilds()
{
    QEXT_D(QEXTQuickThemeBinder);
    return d->m_themeBinderChildsList;
}

void QEXTQuickThemeBinder::addChild(QEXTQuickThemeBinder *child)
{
    QEXT_D(QEXTQuickThemeBinder);
    if (!d->m_themeBinderChildsList.contains(child)) {
        d->m_themeBinderChildsList.append(child);
        connect(child, &QEXTQuickThemeBinder::destroyed, [=](){
            if (QEXTQuickThemeBinderPrivate::sm_allBindersList.contains(this)) {
                d->m_themeBinderChildsList.removeOne(child);
            }
        });
        child->setThemeBinderParent(this);
    }
}

QEXTQuickThemeBinder *QEXTQuickThemeBinder::themeBinderParent() const
{
    QEXT_D(const QEXTQuickThemeBinder);
    return d->m_themeBinderParent.data();
}

void QEXTQuickThemeBinder::setEnabled(const bool &enabled)
{
    QEXT_D(QEXTQuickThemeBinder);
    static QMetaObject::Connection connection;
    if(enabled != d->m_enabled) {
        d->m_enabled = enabled;
        if (d->m_enabled) {
            connection = connect(QEXTQuickThemeManager::instance(), &QEXTQuickThemeManager::currentThemeChanged, this, &QEXTQuickThemeBinder::onRefreshPropertys);
        } else {
            disconnect(connection);
        }
        emit this->enabledChanged();
    }
}

void QEXTQuickThemeBinder::setGroupName(const QString &name)
{
    QEXT_D(QEXTQuickThemeBinder);
    if (name != d->m_groupName) {
        d->m_groupName = name;
        emit this->groupNameChanged();
    }
}

void QEXTQuickThemeBinder::setClassName(const QString &name)
{
    QEXT_D(QEXTQuickThemeBinder);
    if (name != d->m_className) {
        d->m_className = name;
        emit this->classNameChanged();
    }
}

void QEXTQuickThemeBinder::setChildName(const QString &name)
{
    QEXT_D(QEXTQuickThemeBinder);
    if (name != d->m_childName) {
        d->m_childName = name;
        emit this->childNameChanged();
    }
}

void QEXTQuickThemeBinder::setState(const QString &state)
{
    Q_D(QEXTQuickThemeBinder);
    if (state != d->m_stateName) {
        d->m_stateName = state;
        QEXTQuickThemeManager::instance()->generateThemeTemplateFile(this);
        if(!d->m_stateAsynchronous && QEXTQuickThemeManager::instance()->isCurrentThemeValid()){
            this->onRefreshPropertys();
        }
        emit this->stateChanged();
    }
}

void QEXTQuickThemeBinder::setTarget(QObject *target)
{
    QEXT_D(QEXTQuickThemeBinder);
    if (target != d->m_target.data()) {
        d->m_target = target;
        emit this->targetChanged();
    }
}

void QEXTQuickThemeBinder::setFilterPropertyName(const QStringList &nameList)
{
    QEXT_D(QEXTQuickThemeBinder);
    if (nameList != d->m_filterPropertyNameList) {
        d->m_filterPropertyNameList += nameList;
        emit this->filterPropertyNameChanged();
    }
}

void QEXTQuickThemeBinder::setDynamicListener(const QStringList &listenerList)
{
    QEXT_D(QEXTQuickThemeBinder);
    if (listenerList != d->m_dynamicListenerList) {
        d->m_dynamicListenerList = listenerList;
        emit this->dynamicListenerChanged(listenerList);
    }
}

void QEXTQuickThemeBinder::setStateAsynchronous(const bool &asynchronous)
{
    QEXT_D(QEXTQuickThemeBinder);
    if (asynchronous != d->m_stateAsynchronous) {
        d->m_stateAsynchronous = asynchronous;
        emit this->stateAsynchronousChanged();
    }
}

void QEXTQuickThemeBinder::setThemeBinderParent(QEXTQuickThemeBinder *parent)
{
    QEXT_D(QEXTQuickThemeBinder);
    if (!d->m_themeBinderParent.isNull() || parent == d->m_themeBinderParent.data()) {
        return;
    }
    if (!QEXTQuickThemeBinderPrivate::sm_allBindersList.contains(parent)) {
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

    connect(d->m_themeBinderParent.data(), &QEXTQuickThemeBinder::classNameChanged, this, [this]() {
        QEXT_D(QEXTQuickThemeBinder);
        this->setClassName(d->m_themeBinderParent->className());
    });
    connect(d->m_themeBinderParent.data(), &QEXTQuickThemeBinder::groupNameChanged, this, [this]() {
        QEXT_D(QEXTQuickThemeBinder);
        this->setGroupName(d->m_themeBinderParent->groupName());
    });
    connect(d->m_themeBinderParent.data(), &QEXTQuickThemeBinder::stateChanged, this, [this]() {
        QEXT_D(QEXTQuickThemeBinder);
        this->setState(d->m_themeBinderParent->stateName());
    });
    connect(d->m_themeBinderParent.data(), &QEXTQuickThemeBinder::enabledChanged, this, [this]() {
        QEXT_D(QEXTQuickThemeBinder);
        this->setEnabled(d->m_themeBinderParent->isEnabled());
    });
    connect(d->m_themeBinderParent.data(), &QEXTQuickThemeBinder::stateAsynchronousChanged, this, [this]() {
        QEXT_D(QEXTQuickThemeBinder);
        this->setStateAsynchronous(d->m_themeBinderParent->isStateAsynchronous());
    });

    emit this->parentChanged();
}

void QEXTQuickThemeBinder::onRefreshPropertys()
{
    //    qDebug() << "QEXTQuickThemeBinder::onRefreshPropertys()-------------------";
    QEXT_D(QEXTQuickThemeBinder);
    if(!d->m_enabled) {
        return;
    }

    QObject *target = d->m_target.isNull() ? this : d->m_target.data();
    QMapIterator<QString, QVariant> mapIter(d->m_bindingNameToPropertyMap);

    while (mapIter.hasNext()) {
        mapIter.next();
        if(!QEXTQuickThemeManager::instance()->isCurrentThemeValid()){
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

void QEXTQuickThemeBinder::onPropertyChanged()
{
    //    qDebug() << "QEXTQuickThemeBinder::onPropertyChanged()-----------------";
    QEXT_D(QEXTQuickThemeBinder);
    QString methodName = this->metaObject()->method(this->senderSignalIndex()).name();
    if(methodName.contains("Changed")) {
        QString bindingName = QString(methodName.mid(0, methodName.indexOf("Changed")));

        QVariant result(this->property(bindingName.toStdString().c_str()).type());
        QVariant change(this->property(bindingName.toStdString().c_str()));

        if(QEXTQuickThemeManager::instance()->isCurrentThemeValid()){
            result.setValue(this->propertyData(bindingName));
            if(result.isValid() && result == change) {
                return; //don't need change
            }
        }
        d->m_bindingNameToPropertyMap[bindingName] = this->property(bindingName.toStdString().c_str());
    }
}
