#ifndef _QEXTICONANIMATION_H
#define _QEXTICONANIMATION_H

#include <qextGuiGlobal.h>

#include <QObject>
#include <QIconEngine>
#include <QVariantAnimation>
#include <QParallelAnimationGroup>

class QExtIconAnimationPrivate;
class QEXT_GUI_API QExtIconAnimation : public QParallelAnimationGroup
{
    Q_OBJECT
public:
    explicit QExtIconAnimation(QObject *parent = QEXT_NULLPTR);
    QExtIconAnimation(const QIcon &icon, QObject *parent = QEXT_NULLPTR);
    ~QExtIconAnimation() QEXT_OVERRIDE;

    const QIcon &rawIcon() const;
    void setRawIcon(const QIcon &icon);

    const QIcon &animationIcon() const;

    int rotationAngle() const;
    QVariantAnimation *rotationAnimation() const;

    void removeAnimation(QAbstractAnimation *animation); // cover base class
    QAbstractAnimation *takeAnimation(int index); // cover base class

Q_SIGNALS:
    void aboutToBeDestroyed();
    void rotationAngleChanged(int angle);

protected Q_SLOTS:
    void onRotationAnimationValueChanged(const QVariant &value);

protected:
    QScopedPointer<QExtIconAnimationPrivate> dd_ptr;

private:
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtIconAnimation)
    QEXT_DISABLE_COPY_MOVE(QExtIconAnimation)
};

#endif // _QEXTICONANIMATION_H
