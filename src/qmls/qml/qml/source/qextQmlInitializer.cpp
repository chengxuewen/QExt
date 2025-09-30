#include <qextQmlInitializer.h>
#include <qextOnceFlag.h>
#include <qextQml.h>

class QExtQmlInitializerPrivate
{
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQmlInitializerPrivate)
    QEXT_DECLARE_PUBLIC(QExtQmlInitializer)
public:
    explicit QExtQmlInitializerPrivate(QExtQmlInitializer *q);
    virtual ~QExtQmlInitializerPrivate();

    QExtQmlInitializer * const q_ptr;
};

QExtQmlInitializerPrivate::QExtQmlInitializerPrivate(QExtQmlInitializer *q)
    : q_ptr(q)
{
}

QExtQmlInitializerPrivate::~QExtQmlInitializerPrivate()
{
}

QExtQmlInitializer::QExtQmlInitializer(QQuickItem *parent)
    : QQuickItem(parent)
    , dd_ptr(new QExtQmlInitializerPrivate(this))
{
    static QExtOnceFlag onceFlag;
    if(onceFlag.enter())
    {
        this->setVisible(false);
        this->setEnabled(false);
        connect(this, &QQuickItem::parentChanged, this, &QExtQmlInitializer::onParentChanged);
        onceFlag.leave();
    }
    else
    {
        qErrnoWarning("Error:There is only one instance :)");
    }
    this->onParentChanged(parent);
}

QExtQmlInitializer::~QExtQmlInitializer()
{
}

// int QExtQmlInitializer::mouseAreaCursorShape() const
// {
//     return QExtQml::instance()->mouseAreaCursorShape();
// }

// void QExtQmlInitializer::setMouseAreaCursorShape(int shape)
// {
//     if (QExtQuickControls::instance()->mouseAreaCursorShape() != shape)
//     {
//         QExtQuickControls::instance()->setMouseAreaCursorShape((Qt::CursorShape)shape);
//         emit this->mouseAreaCursorShapeChanged(shape);
//     }
// }

void QExtQmlInitializer::onParentChanged(QQuickItem *parent)
{
    Q_UNUSED(parent);
    // QExtQml::instance()->initWorld(this);
    QExtQml::instance()->setRootWindow(dynamic_cast<QQuickWindow *>(this->parent()));
    disconnect(this, &QQuickItem::parentChanged, this, &QExtQmlInitializer::onParentChanged);
}
