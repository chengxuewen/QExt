#include <qextObject.h>

#include <QEvent>

QExtObject::QExtObject(QObject *parent)
    : QObject(parent)
{
}

QExtObject::~QExtObject()
{
}

void QExtObject::setParent(QObject *parent)
{
    QObject *oldParent = this->parent();
    QObject::setParent(parent);
    if (parent != oldParent)
    {
        emit this->parentChanged(parent);
    }
}

bool QExtObject::eventFilter(QObject *obj, QEvent *event)
{
    if (this == obj && event->type() == QEvent::ParentChange)
    {
        emit this->parentChanged(this->parent());
    }
    return QObject::eventFilter(obj, event);
}
