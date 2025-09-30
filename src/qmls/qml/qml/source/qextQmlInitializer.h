#ifndef _QEXTQMLINITIALIZER_H
#define _QEXTQMLINITIALIZER_H

#include <qextQmlGlobal.h>
#include <qextQmlRegistration.h>

#include <QQuickItem>

class QExtQmlInitializerPrivate;
class QEXT_QML_API QExtQmlInitializer : public QQuickItem
{
    Q_OBJECT
    QEXT_QML_ELEMENT()
    // Q_PROPERTY(int mouseAreaCursorShape READ mouseAreaCursorShape WRITE setMouseAreaCursorShape NOTIFY mouseAreaCursorShapeChanged)

public:
    explicit QExtQmlInitializer(QQuickItem *parent = QEXT_NULLPTR);
    ~QExtQmlInitializer() override;

    // int mouseAreaCursorShape() const;
    // void setMouseAreaCursorShape(int shape);

Q_SIGNALS:
    // void mouseAreaCursorShapeChanged(int shape);

protected Q_SLOTS:
    void onParentChanged(QQuickItem *parent);

protected:
    QScopedPointer<QExtQmlInitializerPrivate> dd_ptr;

private:
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtQmlInitializer)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQmlInitializer)
};



#endif // _QEXTQMLINITIALIZER_H
