#include <private/qextStyleSheetHooker_p.h>

#include <QDebug>
#include <QEvent>

QExtStyleSheetHookerPrivate::QExtStyleSheetHookerPrivate(QExtStyleSheetHooker *q)
    : q_ptr(q)
{

}

QExtStyleSheetHookerPrivate::~QExtStyleSheetHookerPrivate()
{

}

QExtStyleSheetHooker::QExtStyleSheetHooker(QObject *parent)
    : QObject(parent)
{

}

QExtStyleSheetHooker::~QExtStyleSheetHooker()
{

}

QWidget *QExtStyleSheetHooker::hookTarget() const
{
    Q_D(const QExtStyleSheetHooker);
    return d->m_target.data();
}

void QExtStyleSheetHooker::setHookTarget(QWidget *target)
{
    Q_D(QExtStyleSheetHooker);
    if (target != d->m_target)
    {
        if (!d->m_target.isNull())
        {
            d->m_target->removeEventFilter(this);
        }
        d->m_target = target;
        Q_EMIT this->hookTargetChanged(target);
        if (!d->m_target.isNull())
        {
            d->m_target->installEventFilter(this);
        }
    }
}

bool QExtStyleSheetHooker::eventFilter(QObject *watched, QEvent *event)
{
    Q_D(QExtStyleSheetHooker);
    if (event->type() == QEvent::MouseButtonPress)
    {
        if (d->m_target.data() == watched)
        {
            // label->setStyleSheet("background-color: lightblue; color: red; font-size: 16px;");
        }
    }
    return QObject::eventFilter(watched, event);
}
