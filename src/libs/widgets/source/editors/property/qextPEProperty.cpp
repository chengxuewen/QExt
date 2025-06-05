#include <private/qextPEProperty_p.h>
#include <private/qextPEPropertyManager_p.h>


/***********************************************************************************************************************
 * QExtPEProperty
***********************************************************************************************************************/
QExtPEPropertyPrivate::QExtPEPropertyPrivate(QExtPEProperty *q, QExtPEAbstractPropertyManager *manager)
    : q_ptr(q)
    , mManager(manager)
    , mStyleChanged(false)
    , mModified(false)
    , mEnabled(true)
{
}

QExtPEProperty::QExtPEProperty(QExtPEAbstractPropertyManager *manager)
    : dd_ptr(new QExtPEPropertyPrivate(this, manager))
{
}

QExtPEProperty::~QExtPEProperty()
{
    Q_D(QExtPEProperty);
    QSetIterator<QExtPEProperty *> itParent(d->mParentItems);
    while (itParent.hasNext())
    {
        QExtPEProperty *property = itParent.next();
        property->d_func()->mManager->d_func()->propertyRemoved(this, property);
    }

    d->mManager->d_func()->propertyDestroyed(this);

    QListIterator<QExtPEProperty *> itChild(d->mSubItems);
    while (itChild.hasNext())
    {
        QExtPEProperty *property = itChild.next();
        property->dd_ptr->mParentItems.remove(this);
    }

    itParent.toFront();
    while (itParent.hasNext())
    {
        QExtPEProperty *property = itParent.next();
        property->dd_ptr->mSubItems.removeAll(this);
    }
}

QList<QExtPEProperty *> QExtPEProperty::subProperties() const
{
    Q_D(const QExtPEProperty);
    return d->mSubItems;
}

QExtPEAbstractPropertyManager *QExtPEProperty::propertyManager() const
{
    Q_D(const QExtPEProperty);
    return d->mManager;
}

QString QExtPEProperty::toolTip() const
{
    Q_D(const QExtPEProperty);
    return d->mToolTip;
}

QString QExtPEProperty::statusTip() const
{
    Q_D(const QExtPEProperty);
    return d->mStatusTip;
}

QString QExtPEProperty::whatsThis() const
{
    Q_D(const QExtPEProperty);
    return d->mWhatsThis;
}

QString QExtPEProperty::propertyName() const
{
    Q_D(const QExtPEProperty);
    return d->mName;
}

bool QExtPEProperty::isStyleChanged() const
{
    Q_D(const QExtPEProperty);
    return d->mStyleChanged;
}

bool QExtPEProperty::isEnabled() const
{
    Q_D(const QExtPEProperty);
    return d->mEnabled;
}

bool QExtPEProperty::isModified() const
{
    Q_D(const QExtPEProperty);
    return d->mModified;
}

bool QExtPEProperty::hasValue() const
{
    Q_D(const QExtPEProperty);
    return d->mManager->hasValue(this);
}

QIcon QExtPEProperty::valueIcon() const
{
    Q_D(const QExtPEProperty);
    return d->mManager->valueIcon(this);
}

QString QExtPEProperty::valueText() const
{
    Q_D(const QExtPEProperty);
    return d->mManager->valueText(this);
}

QString QExtPEProperty::displayText() const
{
    Q_D(const QExtPEProperty);
    return d->mManager->displayText(this);
}

void QExtPEProperty::setToolTip(const QString &text)
{
    Q_D(QExtPEProperty);
    if (d->mToolTip == text)
    {
        return;
    }

    d->mToolTip = text;
    this->onPropertyChanged();
}

void QExtPEProperty::setStatusTip(const QString &text)
{
    Q_D(QExtPEProperty);
    if (text != d->mStatusTip)
    {
        d->mStatusTip = text;
        this->onPropertyChanged();
    }
}

void QExtPEProperty::setWhatsThis(const QString &text)
{
    Q_D(QExtPEProperty);
    if (d->mWhatsThis == text)
    {
        return;
    }

    d->mWhatsThis = text;
    this->onPropertyChanged();
}

void QExtPEProperty::setPropertyName(const QString &text)
{
    Q_D(QExtPEProperty);
    if (text != d->mName)
    {
        d->mName = text;
        this->onPropertyChanged();
    }
}

void QExtPEProperty::setStyleChanged(bool changed)
{
    Q_D(QExtPEProperty);
    if (changed != d->mStyleChanged)
    {
        d->mStyleChanged = changed;
        this->onPropertyChanged();
    }
}

void QExtPEProperty::setEnabled(bool enable)
{
    Q_D(QExtPEProperty);
    if (enable != d->mEnabled)
    {
        d->mEnabled = enable;
        this->onPropertyChanged();
    }
}

void QExtPEProperty::setModified(bool modified)
{
    Q_D(QExtPEProperty);
    if (modified != d->mModified)
    {
        d->mModified = modified;
        this->onPropertyChanged();
    }
}

void QExtPEProperty::addSubProperty(QExtPEProperty *property)
{
    Q_D(QExtPEProperty);
    QExtPEProperty *after = QEXT_NULLPTR;
    if (d->mSubItems.count() > 0)
    {
        after = d->mSubItems.last();
    }
    this->insertSubProperty(property, after);
}

void QExtPEProperty::insertSubProperty(QExtPEProperty *property, QExtPEProperty *afterProperty)
{
    Q_D(QExtPEProperty);
    if (!property)
    {
        return;
    }

    if (property == this)
    {
        return;
    }

    // traverse all children of item. if this item is a child of item then cannot add.
    QList<QExtPEProperty *> pendingList = property->subProperties();
    QHash<QExtPEProperty *, bool> visited;
    while (!pendingList.isEmpty())
    {
        QExtPEProperty *i = pendingList.first();
        if (i == this)
        {
            return;
        }
        pendingList.removeFirst();
        if (visited.contains(i))
        {
            continue;
        }
        visited[i] = true;
        pendingList += i->subProperties();
    }

    pendingList = this->subProperties();
    int pos = 0;
    int newPos = 0;
    QExtPEProperty *properAfterProperty = QEXT_NULLPTR;
    while (pos < pendingList.count())
    {
        QExtPEProperty *i = pendingList.at(pos);
        if (i == property)
        {
            return; // if item is already inserted in this item then cannot add.
        }
        if (i == afterProperty)
        {
            newPos = pos + 1;
            properAfterProperty = afterProperty;
        }
        pos++;
    }

    d->mSubItems.insert(newPos, property);
    property->dd_ptr->mParentItems.insert(this);

    d->mManager->d_func()->propertyInserted(property, this, properAfterProperty);
}

void QExtPEProperty::removeSubProperty(QExtPEProperty *property)
{
    Q_D(QExtPEProperty);
    if (!property)
    {
        return;
    }

    d->mManager->d_func()->propertyRemoved(property, this);

    QList<QExtPEProperty *> pendingList = this->subProperties();
    int pos = 0;
    while (pos < pendingList.count())
    {
        if (pendingList.at(pos) == property)
        {
            d->mSubItems.removeAt(pos);
            property->dd_ptr->mParentItems.remove(this);

            return;
        }
        pos++;
    }
}

void QExtPEProperty::onPropertyChanged()
{
    Q_D(QExtPEProperty);
    d->mManager->d_func()->propertyChanged(this);
}


/***********************************************************************************************************************
 * QExtPEPropertyItem
***********************************************************************************************************************/
void QExtPEPropertyItemPrivate::addChild(QExtPEPropertyItem *index, QExtPEPropertyItem *after)
{
    if (mChildren.contains(index))
    {
        return;
    }
    int idx = mChildren.indexOf(after) + 1; // we insert after returned idx, if it was -1 then we set idx to 0;
    mChildren.insert(idx, index);
}

void QExtPEPropertyItemPrivate::removeChild(QExtPEPropertyItem *index)
{
    mChildren.removeAll(index);
}


QExtPEProperty *QExtPEPropertyItem::property() const
{
    Q_D(const QExtPEPropertyItem);
    return d->mProperty;
}

QExtPEPropertyItem *QExtPEPropertyItem::parent() const
{
    Q_D(const QExtPEPropertyItem);
    return d->mParent;
}

QList<QExtPEPropertyItem *> QExtPEPropertyItem::children() const
{
    Q_D(const QExtPEPropertyItem);
    return d->mChildren;
}

QExtPEAbstractPropertyEditor *QExtPEPropertyItem::browser() const
{
    Q_D(const QExtPEPropertyItem);
    return d->mBrowser;
}

QExtPEPropertyItem::QExtPEPropertyItem(QExtPEAbstractPropertyEditor *browser,
                                       QExtPEProperty *property,
                                       QExtPEPropertyItem *parent)
    : dd_ptr(new QExtPEPropertyItemPrivate(this, browser, parent, property))
{
}

QExtPEPropertyItem::~QExtPEPropertyItem()
{
}

