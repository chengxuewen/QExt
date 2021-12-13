#include <qextQmlFramelessHelper.h>
#include <qextQmlFramelessHelper_p.h>

#include <QQuickItem>

QEXTQmlFramelessHelperPrivate::QEXTQmlFramelessHelperPrivate(QEXTQmlFramelessHelper *q)
    : q_ptr(q)
    , m_helper(nullptr)
    , m_window(nullptr)
    , m_titleBarHeight(0)
{
}

QEXTQmlFramelessHelperPrivate::~QEXTQmlFramelessHelperPrivate()
{
}

QMargins QEXTQmlFramelessHelperPrivate::draggableMargins() const
{
    return m_priDraggableMargins;
}

QMargins QEXTQmlFramelessHelperPrivate::maximizedMargins() const
{
    return m_priMaximizedMargins;
}

bool QEXTQmlFramelessHelperPrivate::hitTest(const QPoint &pos) const
{
    int scaledTitleBarHeight = m_titleBarHeight * m_helper->scaleFactor();

    if (!m_window)
        return false;
    else if (scaledTitleBarHeight == 0)
        return false;
    else if ((scaledTitleBarHeight > 0)
             && (pos.y() >= scaledTitleBarHeight))
        return false;

    auto rootItem = m_window->contentItem();
    if (nullptr == rootItem) {
        return false;
    }

    int currentIndex = -1;
    QQuickItem *items[32] = {0};
    auto child = rootItem;
    QPointF p = pos;

    while (child && (currentIndex < 31)) {
        items[++currentIndex] = child;
        auto grandchild = child->childAt(p.x(), p.y());
        if (nullptr == grandchild) {
            break;
        }

        p = child->mapToItem(grandchild, p);
        child = grandchild;
    }

    while (currentIndex > 0) {
        child = items[currentIndex];
        --currentIndex;

        if (m_includeItems.contains(child)) {
            break;
        } else if (m_excludeItems.contains(child)) {
            return false;
        } else if (rootItem == child) {
            break;
        }
    }

    return true;
}




QEXTQmlFramelessHelper::QEXTQmlFramelessHelper(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QEXTQmlFramelessHelperPrivate(this))
{
}

QEXTQmlFramelessHelper::~QEXTQmlFramelessHelper()
{
}

void QEXTQmlFramelessHelper::classBegin()
{
}

void QEXTQmlFramelessHelper::componentComplete()
{
    Q_D(QEXTQmlFramelessHelper);

    auto obj = parent();
    while (nullptr != obj) {
        if (obj->inherits("QQuickRootItem")) {
            if (auto rootItem = qobject_cast<QQuickItem *>(obj)) {
                if (auto window = rootItem->window()) {
                    d->m_window = window;

                    d->m_helper = new QEXTNativeWindowHelper(window, d);
                    connect(d->m_helper, &QEXTNativeWindowHelper::scaleFactorChanged,
                            this, &QEXTQmlFramelessHelper::scaleFactorChanged);
                    if (!qFuzzyCompare(d->m_helper->scaleFactor(), 1.0)) {
                        emit scaleFactorChanged();
                    }
                }

                break;
            }
        }

        obj = obj->parent();
    }
}

void QEXTQmlFramelessHelper::setTopDraggableMargin(int dm)
{
    Q_D(QEXTQmlFramelessHelper);

    if (dm != d->m_priDraggableMargins.top()) {
        d->m_priDraggableMargins.setTop(dm);
        emit topDraggableMarginChanged();
    }
}

void QEXTQmlFramelessHelper::setLeftDraggableMargin(int dm)
{
    Q_D(QEXTQmlFramelessHelper);

    if (dm != d->m_priDraggableMargins.left()) {
        d->m_priDraggableMargins.setLeft(dm);
        emit leftDraggableMarginChanged();
    }
}

void QEXTQmlFramelessHelper::setRightDraggableMargin(int dm)
{
    Q_D(QEXTQmlFramelessHelper);

    if (dm != d->m_priDraggableMargins.right()) {
        d->m_priDraggableMargins.setRight(dm);
        emit rightDraggableMarginChanged();
    }
}

void QEXTQmlFramelessHelper::setBottomDraggableMargin(int dm)
{
    Q_D(QEXTQmlFramelessHelper);

    if (dm != d->m_priDraggableMargins.bottom()) {
        d->m_priDraggableMargins.setBottom(dm);
        emit bottomDraggableMarginChanged();
    }
}

int QEXTQmlFramelessHelper::topDraggableMargin() const
{
    Q_D(const QEXTQmlFramelessHelper);

    return d->m_priDraggableMargins.top();
}

int QEXTQmlFramelessHelper::leftDraggableMargin() const
{
    Q_D(const QEXTQmlFramelessHelper);

    return d->m_priDraggableMargins.left();
}

int QEXTQmlFramelessHelper::rightDraggableMargin() const
{
    Q_D(const QEXTQmlFramelessHelper);

    return d->m_priDraggableMargins.right();
}

int QEXTQmlFramelessHelper::bottomDraggableMargin() const
{
    Q_D(const QEXTQmlFramelessHelper);

    return d->m_priDraggableMargins.bottom();
}

void QEXTQmlFramelessHelper::setTopMaximizedMargin(int dm)
{
    Q_D(QEXTQmlFramelessHelper);

    if (dm != d->m_priMaximizedMargins.top()) {
        d->m_priMaximizedMargins.setTop(dm);
        emit topMaximizedMarginChanged();
    }
}

void QEXTQmlFramelessHelper::setLeftMaximizedMargin(int dm)
{
    Q_D(QEXTQmlFramelessHelper);

    if (dm != d->m_priMaximizedMargins.left()) {
        d->m_priMaximizedMargins.setLeft(dm);
        emit leftMaximizedMarginChanged();
    }
}

void QEXTQmlFramelessHelper::setRightMaximizedMargin(int dm)
{
    Q_D(QEXTQmlFramelessHelper);

    if (dm != d->m_priMaximizedMargins.right()) {
        d->m_priMaximizedMargins.setRight(dm);
        emit rightMaximizedMarginChanged();
    }
}

void QEXTQmlFramelessHelper::setBottomMaximizedMargin(int dm)
{
    Q_D(QEXTQmlFramelessHelper);

    if (dm != d->m_priMaximizedMargins.bottom()) {
        d->m_priMaximizedMargins.setBottom(dm);
        emit bottomMaximizedMarginChanged();
    }
}

int QEXTQmlFramelessHelper::topMaximizedMargin() const
{
    Q_D(const QEXTQmlFramelessHelper);

    return d->m_priMaximizedMargins.top();
}

int QEXTQmlFramelessHelper::leftMaximizedMargin() const
{
    Q_D(const QEXTQmlFramelessHelper);

    return d->m_priMaximizedMargins.left();
}

int QEXTQmlFramelessHelper::rightMaximizedMargin() const
{
    Q_D(const QEXTQmlFramelessHelper);

    return d->m_priMaximizedMargins.right();
}

int QEXTQmlFramelessHelper::bottomMaximizedMargin() const
{
    Q_D(const QEXTQmlFramelessHelper);

    return d->m_priMaximizedMargins.bottom();
}

void QEXTQmlFramelessHelper::addIncludeItem(QQuickItem *item)
{
    Q_D(QEXTQmlFramelessHelper);

    d->m_includeItems.insert(item);
}

void QEXTQmlFramelessHelper::removeIncludeItem(QQuickItem *item)
{
    Q_D(QEXTQmlFramelessHelper);

    d->m_includeItems.remove(item);
}

void QEXTQmlFramelessHelper::addExcludeItem(QQuickItem *item)
{
    Q_D(QEXTQmlFramelessHelper);

    d->m_excludeItems.insert(item);
}

void QEXTQmlFramelessHelper::removeExcludeItem(QQuickItem *item)
{
    Q_D(QEXTQmlFramelessHelper);

    d->m_excludeItems.remove(item);
}

void QEXTQmlFramelessHelper::setTitleBarHeight(int value)
{
    Q_D(QEXTQmlFramelessHelper);

    if (value != d->m_titleBarHeight) {
        d->m_titleBarHeight = value;
        emit titleBarHeightChanged();
    }
}

int QEXTQmlFramelessHelper::titleBarHeight() const
{
    Q_D(const QEXTQmlFramelessHelper);

    return d->m_titleBarHeight;
}

qreal QEXTQmlFramelessHelper::scaleFactor() const
{
    Q_D(const QEXTQmlFramelessHelper);

    return d->m_helper ? d->m_helper->scaleFactor() : 1.0;
}

void QEXTQmlFramelessHelper::triggerMinimizeButtonAction()
{
    Q_D(QEXTQmlFramelessHelper);

    if (d->m_window) {
        auto oldStates = d->m_window->windowStates();
        d->m_window->setWindowStates((oldStates & ~Qt::WindowActive) | Qt::WindowMinimized);
    }
}

void QEXTQmlFramelessHelper::triggerMaximizeButtonAction()
{
    Q_D(QEXTQmlFramelessHelper);

    if (d->m_window) {
        if (QWindow::Maximized == d->m_window->visibility()) {
            d->m_window->showNormal();
        } else {
            d->m_window->showMaximized();
        }
    }
}

void QEXTQmlFramelessHelper::triggerCloseButtonAction()
{
    Q_D(QEXTQmlFramelessHelper);

    if (d->m_window) {
        d->m_window->close();
    }
}
