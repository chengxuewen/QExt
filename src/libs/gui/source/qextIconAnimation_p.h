#ifndef _QEXTICONANIMATION_P_H
#define _QEXTICONANIMATION_P_H

#include <qextIconAnimation.h>

#include <QVariantAnimation>

class QEXT_GUI_API QExtAnimationIconEngine : public QObject, public QIconEngine
{
    Q_OBJECT
public:
    QExtAnimationIconEngine(QExtIconAnimation *animation);
    ~QExtAnimationIconEngine() QEXT_OVERRIDE;

    QIconEngine *clone() const QEXT_OVERRIDE;
    QPixmap pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state) QEXT_OVERRIDE;
    void paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state) QEXT_OVERRIDE;

protected Q_SLOTS:
    void onAnimationAboutToBeDestroyed();

private:
    QIcon m_rawIcon;
    QExtIconAnimation *m_animation;
};

class QExtIconAnimationPrivate
{
public:
    explicit QExtIconAnimationPrivate(QExtIconAnimation *q);
    virtual ~QExtIconAnimationPrivate();

    QExtIconAnimation * const q_ptr;

    QIcon m_rawIcon;
    QIcon m_animationIcon;
    QScopedPointer<QPropertyAnimation> m_rotationAnimation;

private:
    QEXT_DECL_PUBLIC(QExtIconAnimation)
    QEXT_DISABLE_COPY_MOVE(QExtIconAnimationPrivate)
};

#endif // _QEXTICONANIMATION_P_H
