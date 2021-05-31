#include <qextmvvmitem.h>
#include <qextmvvmitem_p.h>

QEXT_USE_NAMESPACE

QEXTMvvmItemPrivate::QEXTMvvmItemPrivate(QEXTMvvmItem *qq)
    : QEXTObjectPrivate(qq)
{

}

QEXTMvvmItemPrivate::~QEXTMvvmItemPrivate()
{

}

bool QEXTMvvmItemPrivate::setData(const QVariant &variant, int role)
{

}



QEXTMvvmItem::QEXTMvvmItem(const QString &modelType)
    : QEXTObject(*(new QEXTMvvmItemPrivate(this)))
{

}

QEXTMvvmItem::~QEXTMvvmItem()
{

}

QString QEXTMvvmItem::modelType() const
{

}

QString QEXTMvvmItem::identifier() const
{

}

QString QEXTMvvmItem::displayName() const
{

}

QEXTMvvmItem *QEXTMvvmItem::setDisplayName(const QString &name)
{

}

QEXTMvvmModel *QEXTMvvmItem::model() const
{

}

QEXTMvvmItem *QEXTMvvmItem::parent() const
{

}

QEXTMvvmItemMapper *QEXTMvvmItem::mapper() const
{

}

int QEXTMvvmItem::childrenCount() const
{

}

QList<QEXTMvvmItem *> QEXTMvvmItem::children() const
{

}

QString QEXTMvvmItem::defaultTag() const
{

}

void QEXTMvvmItem::setDefaultTag(const QString &tag)
{

}

void QEXTMvvmItem::registerTag(const QEXTMvvmTagInfo &tagInfo, bool set_as_default)
{

}

bool QEXTMvvmItem::isTag(const QString &name) const
{

}

QString QEXTMvvmItem::tag() const
{

}

QEXTMvvmTagRow QEXTMvvmItem::tagRow() const
{

}

int QEXTMvvmItem::itemCount(const QString &tag) const
{

}

QEXTMvvmItem *QEXTMvvmItem::getItem(const QString &tag, int row) const
{

}

QList<QEXTMvvmItem *> QEXTMvvmItem::getItems(const QString &tag) const
{

}

QString QEXTMvvmItem::tagOfItem(const QEXTMvvmItem *item) const
{

}

QEXTMvvmTagRow QEXTMvvmItem::tagRowOfItem(const QEXTMvvmItem *item) const
{

}

bool QEXTMvvmItem::insertItem(QEXTMvvmItem *item, const QEXTMvvmTagRow &tagrow)
{

}

QEXTMvvmItem *QEXTMvvmItem::takeItem(const QEXTMvvmTagRow &tagrow)
{

}

QVector<int> QEXTMvvmItem::roles() const
{

}

bool QEXTMvvmItem::hasData(int role) const
{

}

QEXTMvvmItemData *QEXTMvvmItem::itemData() const
{

}

bool QEXTMvvmItem::isEditable() const
{

}

QEXTMvvmItem *QEXTMvvmItem::setEditable(bool value)
{

}

bool QEXTMvvmItem::isEnabled() const
{

}

QEXTMvvmItem *QEXTMvvmItem::setEnabled(bool value)
{

}

QString QEXTMvvmItem::toolTip() const
{

}

QEXTMvvmItem *QEXTMvvmItem::setToolTip(const QString &tooltip)
{

}

QString QEXTMvvmItem::editorType() const
{

}

QEXTMvvmItem *QEXTMvvmItem::setEditorType(const QString &editor_type)
{

}

bool QEXTMvvmItem::isSinglePropertyTag(const QString &tag) const
{

}

void QEXTMvvmItem::setProperty(const QString &tag, const char *value)
{

}

bool QEXTMvvmItem::set_data_internal(QVariant value, int role)
{

}

QVariant QEXTMvvmItem::data_internal(int role) const
{

}

void QEXTMvvmItem::setParent(QEXTMvvmItem *parent)
{

}

void QEXTMvvmItem::setModel(QEXTMvvmModel *model)
{

}

void QEXTMvvmItem::setAppearanceFlag(int flag, bool value)
{

}

QEXTMvvmItemTags *QEXTMvvmItem::itemTags() const
{

}

void QEXTMvvmItem::setDataAndTags(QEXTMvvmItemData *data, QEXTMvvmItemTags *tags)
{

}


