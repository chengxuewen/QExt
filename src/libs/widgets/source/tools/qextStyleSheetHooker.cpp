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
    return d->mTarget.data();
}

void QExtStyleSheetHooker::setHookTarget(QWidget *target)
{
    Q_D(QExtStyleSheetHooker);
    if (target != d->mTarget)
    {
        if (!d->mTarget.isNull())
        {
            d->mTarget->removeEventFilter(this);
        }
        d->mTarget = target;
        Q_EMIT this->hookTargetChanged(target);
        if (!d->mTarget.isNull())
        {
            d->mTarget->installEventFilter(this);
        }
    }
}

bool QExtStyleSheetHooker::eventFilter(QObject *watched, QEvent *event)
{
    Q_D(QExtStyleSheetHooker);
    if (event->type() == QEvent::MouseButtonPress)
    {
        if (d->mTarget.data() == watched)
        {
            // label->setStyleSheet("background-color: lightblue; color: red; font-size: 16px;");
        }
    }
    return QObject::eventFilter(watched, event);
}
