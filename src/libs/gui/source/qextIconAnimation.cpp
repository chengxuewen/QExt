#include <private/qextIconAnimation_p.h>

#include <QDebug>
#include <QPainter>
#include <QVariantAnimation>

QExtAnimationIconEngine::QExtAnimationIconEngine(QExtIconAnimation *animation)
    : m_animation(animation)
{
    connect(animation, SIGNAL(aboutToBeDestroyed()), this, SLOT(onAnimationAboutToBeDestroyed()));
}

QExtAnimationIconEngine::~QExtAnimationIconEngine()
{

}

QIconEngine *QExtAnimationIconEngine::clone() const
{
    return new QExtAnimationIconEngine(m_animation);
}

QPixmap QExtAnimationIconEngine::pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state)
{
    QImage image(size, QImage::Format_ARGB32);
    image.fill(qRgba(0, 0, 0, 0));
    QPixmap pixmap = QPixmap::fromImage(image, Qt::NoFormatConversion);
    {
        QPainter painter(&pixmap);
        QRect rect(QPoint(0.0, 0.0), size);
        this->paint(&painter, rect, mode, state);
    }
    return pixmap;
}

void QExtAnimationIconEngine::paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state)
{
    const QIcon &rawIcon = m_animation ? m_animation->rawIcon() : m_rawIcon;
    const int rotationAngle = m_animation ? m_animation->rotationAngle() : 0;
    const QSize actualSize = rawIcon.actualSize(rect.size(), mode, state);
    QPixmap pixmap = rawIcon.pixmap(actualSize, mode, state);
    // const qreal width = pixmap.width();
    // const qreal height = pixmap.height();

    painter->save();
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter->translate(actualSize.width() / 2, actualSize.height() / 2);
    QRect translateRect(-rect.width() / 2, -rect.height() / 2, rect.width(), rect.height());
    painter->rotate(rotationAngle);
    painter->drawPixmap(translateRect, pixmap);
    painter->restore();
}

void QExtAnimationIconEngine::onAnimationAboutToBeDestroyed()
{
    m_rawIcon = m_animation->rawIcon();
    m_animation = QEXT_NULLPTR;
}



QExtIconAnimationPrivate::QExtIconAnimationPrivate(QExtIconAnimation *q)
    : q_ptr(q)
{
    m_animationIcon = QIcon(new QExtAnimationIconEngine(q));
    m_rotationAnimation.reset(new QVariantAnimation(q));
    QObject::connect(m_rotationAnimation.data(), SIGNAL(valueChanged(QVariant)), q, SLOT(onRotationAnimationValueChanged(QVariant)));
    q->addAnimation(m_rotationAnimation.data());
}

QExtIconAnimationPrivate::~QExtIconAnimationPrivate()
{

}



QExtIconAnimation::QExtIconAnimation(QObject *parent)
    : QParallelAnimationGroup(parent)
    , dd_ptr(new QExtIconAnimationPrivate(this))
{

}

QExtIconAnimation::QExtIconAnimation(const QIcon &icon, QObject *parent)
    : QParallelAnimationGroup(parent)
    , dd_ptr(new QExtIconAnimationPrivate(this))
{
    Q_D(QExtIconAnimation);
    d->m_rawIcon = icon;
}

QExtIconAnimation::~QExtIconAnimation()
{
    emit this->aboutToBeDestroyed();
}

const QIcon &QExtIconAnimation::rawIcon() const
{
    Q_D(const QExtIconAnimation);
    return d->m_rawIcon;
}

void QExtIconAnimation::setRawIcon(const QIcon &icon)
{
    Q_D(QExtIconAnimation);
    d->m_rawIcon = icon;
}

const QIcon &QExtIconAnimation::animationIcon() const
{
    Q_D(const QExtIconAnimation);
    return d->m_animationIcon;
}

int QExtIconAnimation::rotationAngle() const
{
    Q_D(const QExtIconAnimation);
    return d->m_rotationAnimation.isNull() ? 0 : d->m_rotationAnimation->currentValue().toInt();
}

QVariantAnimation *QExtIconAnimation::rotationAnimation() const
{
    Q_D(const QExtIconAnimation);
    return d->m_rotationAnimation.data();
}

void QExtIconAnimation::removeAnimation(QAbstractAnimation *animation)
{
    Q_D(QExtIconAnimation);
    QAnimationGroup::removeAnimation(animation);
    if (d->m_rotationAnimation.data() == animation)
    {
        d->m_rotationAnimation->disconnect(this);
        d->m_rotationAnimation.take();
    }
}

QAbstractAnimation *QExtIconAnimation::takeAnimation(int index)
{
    Q_D(QExtIconAnimation);
    QAbstractAnimation *animation = QAnimationGroup::takeAnimation(index);
    if (d->m_rotationAnimation.data() == animation)
    {
        d->m_rotationAnimation->disconnect(this);
        d->m_rotationAnimation.take();
    }
    return animation;
}

void QExtIconAnimation::onRotationAnimationValueChanged(const QVariant &value)
{
    emit this->rotationAngleChanged(value.toInt());
}
