#include "qextQuickWidgetItem_p.h"
#include "qextQuickIpcWidgetItem.h"

#include <QApplication>
#include <QQuickWindow> 


QExtQuickWidgetItemPrivate::QExtQuickWidgetItemPrivate(QExtQuickWidgetItem *q)
    : q_ptr(q)
    , mItemCompleted(false)
    , mWidgetHideEnable(false)
{
}

QExtQuickWidgetItemPrivate::~QExtQuickWidgetItemPrivate()
{
    this->resetEmbeddedWidget();
}

void QExtQuickWidgetItemPrivate::init()
{
    QObject::connect(q_ptr, &QExtQuickWidgetItem::xChanged, q_ptr, &QExtQuickWidgetItem::updateWidgetGeometry);
    QObject::connect(q_ptr, &QExtQuickWidgetItem::yChanged, q_ptr, &QExtQuickWidgetItem::updateWidgetGeometry);
    QObject::connect(q_ptr, &QExtQuickWidgetItem::widthChanged, q_ptr, &QExtQuickWidgetItem::updateWidgetGeometry);
    QObject::connect(q_ptr, &QExtQuickWidgetItem::heightChanged, q_ptr, &QExtQuickWidgetItem::updateWidgetGeometry);
    QObject::connect(qApp, &QApplication::aboutToQuit, q_ptr, [=]()
    {
        mAppAboutToQuit = true;
    });
}

void QExtQuickWidgetItemPrivate::initEmbeddedWidget()
{
    if (!mRootWindow.isNull() && !mWidget.isNull())
    {
        QObject::connect(q_ptr, &QExtQuickWidgetItem::visibleChanged, mWidget.data(), [=]()
        {
            if (mWidgetHideEnable && !mAppAboutToQuit)
            {
                mWidget->setVisible(q_ptr->isVisible());
                emit q_ptr->widgetVisibleChanged(mWidget->isVisible());
            }
        });
        WId pWId = mRootWindow->winId();
        mWidget->setProperty("_q_embedded_native_parent_handle", QVariant(pWId));
        mWidget->winId();
        if (auto *wh = mWidget->windowHandle()) { wh->setParent(mRootWindow.data()); }
        q_ptr->updateWidgetGeometry();
        mWidget->show();
        emit q_ptr->widgetVisibleChanged(true);
        qCDebug(lcQExtQuickIpc) << "[QExtWidgetItem] initEmbeddedWidget: parentWId =" << pWId
                 << "QQuickItem size:" << q_ptr->width() << "x" << q_ptr->height();
    }
}

void QExtQuickWidgetItemPrivate::resetEmbeddedWidget()
{
    if (!mWidget.isNull())
    {
        q_ptr->disconnect(mWidget);
        mWidget->hide();
        emit q_ptr->widgetVisibleChanged(false);
        if (auto *wh = mWidget->windowHandle()) { wh->setParent(nullptr); }
        mWidget->deleteLater();
        mWidget.clear();
    }
}

QExtQuickWidgetItem::QExtQuickWidgetItem(QQuickItem *parent)
    : QQuickItem(parent)
    , dd_ptr(new QExtQuickWidgetItemPrivate(this))
{
    dd_ptr->init();
}

QExtQuickWidgetItem::QExtQuickWidgetItem(QExtQuickWidgetItemPrivate *d, QQuickItem *parent)
    : QQuickItem(parent)
    , dd_ptr(d)
{
    dd_ptr->init();
}

QExtQuickWidgetItem::~QExtQuickWidgetItem()
{
}

bool QExtQuickWidgetItem::isWidgetHideEnabled() const
{
    Q_D(const QExtQuickWidgetItem);
    return d->mWidgetHideEnable;
}

void QExtQuickWidgetItem::setWidgetHideEnabled(bool enable)
{
    Q_D(QExtQuickWidgetItem);
    if (enable != d->mWidgetHideEnable)
    {
        d->mWidgetHideEnable = enable;
        emit this->widgetHideEnabledChanged(enable);
    }
}

bool QExtQuickWidgetItem::isWidgetVisible() const
{
    Q_D(const QExtQuickWidgetItem);
    return d->mWidget.isNull() ? false : d->mWidget->isVisible();
}

bool QExtQuickWidgetItem::isItemCompleted() const
{
    Q_D(const QExtQuickWidgetItem);
    return d->mItemCompleted;
}

QWidget *QExtQuickWidgetItem::widget() const
{
    Q_D(const QExtQuickWidgetItem);
    return d->mWidget.data();
}

void QExtQuickWidgetItem::setWidget(QWidget *widget)
{
    Q_D(QExtQuickWidgetItem);
    if (d->mWidget.data() != widget)
    {
        qCDebug(lcQExtQuickIpc) << "QExtQuickWidgetItem::setWidget: " << widget;
        d->resetEmbeddedWidget();
        d->mWidget = widget;
        d->initEmbeddedWidget();
        this->updateWidgetGeometry();
    }
}

QWindow *QExtQuickWidgetItem::rootWindow() const
{
    Q_D(const QExtQuickWidgetItem);
    return d->mRootWindow.data();
}

void QExtQuickWidgetItem::setRootWindow(QWindow *window)
{
    Q_D(QExtQuickWidgetItem);
    if (d->mRootWindow.data() != window)
    {
        qCDebug(lcQExtQuickIpc) << "QExtQuickWidgetItem::setRootWindow: " << window;
        if (!d->mRootWindow.isNull())
        {
            d->mRootWindow->disconnect(this);
        }
        d->mRootWindow = window;
        if (window)
        {
            connect(window, &QWindow::xChanged, this, &QExtQuickWidgetItem::updateWidgetGeometry);
            connect(window, &QWindow::yChanged, this, &QExtQuickWidgetItem::updateWidgetGeometry);
            connect(window, &QWindow::widthChanged, this, &QExtQuickWidgetItem::updateWidgetGeometry);
            connect(window, &QWindow::heightChanged, this, &QExtQuickWidgetItem::updateWidgetGeometry);
        }
        qCDebug(lcQExtQuickIpc) << "[QExtWidgetItem] setRootWindow: widget.isNull =" << d->mWidget.isNull()
                 << "QQuickItem geometry:" << this->x() << this->y() << this->width() << this->height();
        d->initEmbeddedWidget();
        emit this->rootWindowChanged(window);
    }
}

void QExtQuickWidgetItem::updatePolish()
{
    qCDebug(lcQExtQuickIpc) << "[QExtQuickWidgetItem] updatePolish";
    this->updateWidgetGeometry();
}

void QExtQuickWidgetItem::componentComplete()
{
    Q_D(QExtQuickWidgetItem);
    QQuickItem::componentComplete();
    d->mItemCompleted = true;
    qCDebug(lcQExtQuickIpc) << "[QExtWidgetItem] componentComplete: QQuickItem geometry ="
             << "x" << this->x() << "y" << this->y()
             << "w" << this->width() << "h" << this->height()
             << "implicitW" << this->implicitWidth() << "implicitH" << this->implicitHeight();
    emit this->itemCompleted();
    auto *win = this->window();
    qCDebug(lcQExtQuickIpc) << "[QExtWidgetItem] componentComplete: auto-discover rootWindow =" << win;
    if (win) 
    {
        this->setRootWindow(win);
    }
}

void QExtQuickWidgetItem::updateWidgetGeometry()
{
    Q_D(QExtQuickWidgetItem);
    qCDebug(lcQExtQuickIpc) << "[QExtQuickWidgetItem] updateWidgetGeometry";
    if (!d->mWidget.isNull() && !d->mRootWindow.isNull())
    {
        qCDebug(lcQExtQuickIpc) << "QExtQuickWidgetItem::updateWidgetGeometry: " << this->x() << this->y() << this->width() << this->height();
        qCDebug(lcQExtQuickIpc) << "[QExtQuickWidgetItem] updateWidgetGeometry globalPos";
        auto globalPos = this->mapToGlobal(QPointF(0, 0));
        auto localPos = d->mRootWindow->mapFromGlobal(globalPos.toPoint());
        d->mWidget->setGeometry(localPos.x(), localPos.y(), this->width(), this->height());
        qCDebug(lcQExtQuickIpc) << "[QExtWidgetItem] updateWidgetGeometry: widget.actualSize =" << d->mWidget->size()
                 << "childGeometry:" << d->mWidget->geometry();
    }
}
