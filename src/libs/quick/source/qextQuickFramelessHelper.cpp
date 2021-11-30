#include <qextQuickFramelessHelper.h>
#include <qextQuickFramelessHelper_p.h>

#include <QQuickItem>

QEXTQuickFramelessHelperPrivate::QEXTQuickFramelessHelperPrivate(QEXTQuickFramelessHelper *q)
    : q_ptr(q)
    , m_helper(nullptr)
    , m_window(nullptr)
    , m_titleBarHeight(0)
{
}

QEXTQuickFramelessHelperPrivate::~QEXTQuickFramelessHelperPrivate()
{
}

QMargins QEXTQuickFramelessHelperPrivate::draggableMargins() const
{
    return m_priDraggableMargins;
}

QMargins QEXTQuickFramelessHelperPrivate::maximizedMargins() const
{
    return m_priMaximizedMargins;
}

bool QEXTQuickFramelessHelperPrivate::hitTest(const QPoint &pos) const
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




QEXTQuickFramelessHelper::QEXTQuickFramelessHelper(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QEXTQuickFramelessHelperPrivate(this))
{
}

QEXTQuickFramelessHelper::~QEXTQuickFramelessHelper()
{
}

void QEXTQuickFramelessHelper::classBegin()
{
}

void QEXTQuickFramelessHelper::componentComplete()
{
    Q_D(QEXTQuickFramelessHelper);

    auto obj = parent();
    while (nullptr != obj) {
        if (obj->inherits("QQuickRootItem")) {
            if (auto rootItem = qobject_cast<QQuickItem *>(obj)) {
                if (auto window = rootItem->window()) {
                    d->m_window = window;

                    d->m_helper = new QEXTNativeWindowHelper(window, d);
                    connect(d->m_helper, &QEXTNativeWindowHelper::scaleFactorChanged,
                            this, &QEXTQuickFramelessHelper::scaleFactorChanged);
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

void QEXTQuickFramelessHelper::setTopDraggableMargin(int dm)
{
    Q_D(QEXTQuickFramelessHelper);

    if (dm != d->m_priDraggableMargins.top()) {
        d->m_priDraggableMargins.setTop(dm);
        emit topDraggableMarginChanged();
    }
}

void QEXTQuickFramelessHelper::setLeftDraggableMargin(int dm)
{
    Q_D(QEXTQuickFramelessHelper);

    if (dm != d->m_priDraggableMargins.left()) {
        d->m_priDraggableMargins.setLeft(dm);
        emit leftDraggableMarginChanged();
    }
}

void QEXTQuickFramelessHelper::setRightDraggableMargin(int dm)
{
    Q_D(QEXTQuickFramelessHelper);

    if (dm != d->m_priDraggableMargins.right()) {
        d->m_priDraggableMargins.setRight(dm);
        emit rightDraggableMarginChanged();
    }
}

void QEXTQuickFramelessHelper::setBottomDraggableMargin(int dm)
{
    Q_D(QEXTQuickFramelessHelper);

    if (dm != d->m_priDraggableMargins.bottom()) {
        d->m_priDraggableMargins.setBottom(dm);
        emit bottomDraggableMarginChanged();
    }
}

int QEXTQuickFramelessHelper::topDraggableMargin() const
{
    Q_D(const QEXTQuickFramelessHelper);

    return d->m_priDraggableMargins.top();
}

int QEXTQuickFramelessHelper::leftDraggableMargin() const
{
    Q_D(const QEXTQuickFramelessHelper);

    return d->m_priDraggableMargins.left();
}

int QEXTQuickFramelessHelper::rightDraggableMargin() const
{
    Q_D(const QEXTQuickFramelessHelper);

    return d->m_priDraggableMargins.right();
}

int QEXTQuickFramelessHelper::bottomDraggableMargin() const
{
    Q_D(const QEXTQuickFramelessHelper);

    return d->m_priDraggableMargins.bottom();
}

void QEXTQuickFramelessHelper::setTopMaximizedMargin(int dm)
{
    Q_D(QEXTQuickFramelessHelper);

    if (dm != d->m_priMaximizedMargins.top()) {
        d->m_priMaximizedMargins.setTop(dm);
        emit topMaximizedMarginChanged();
    }
}

void QEXTQuickFramelessHelper::setLeftMaximizedMargin(int dm)
{
    Q_D(QEXTQuickFramelessHelper);

    if (dm != d->m_priMaximizedMargins.left()) {
        d->m_priMaximizedMargins.setLeft(dm);
        emit leftMaximizedMarginChanged();
    }
}

void QEXTQuickFramelessHelper::setRightMaximizedMargin(int dm)
{
    Q_D(QEXTQuickFramelessHelper);

    if (dm != d->m_priMaximizedMargins.right()) {
        d->m_priMaximizedMargins.setRight(dm);
        emit rightMaximizedMarginChanged();
    }
}

void QEXTQuickFramelessHelper::setBottomMaximizedMargin(int dm)
{
    Q_D(QEXTQuickFramelessHelper);

    if (dm != d->m_priMaximizedMargins.bottom()) {
        d->m_priMaximizedMargins.setBottom(dm);
        emit bottomMaximizedMarginChanged();
    }
}

int QEXTQuickFramelessHelper::topMaximizedMargin() const
{
    Q_D(const QEXTQuickFramelessHelper);

    return d->m_priMaximizedMargins.top();
}

int QEXTQuickFramelessHelper::leftMaximizedMargin() const
{
    Q_D(const QEXTQuickFramelessHelper);

    return d->m_priMaximizedMargins.left();
}

int QEXTQuickFramelessHelper::rightMaximizedMargin() const
{
    Q_D(const QEXTQuickFramelessHelper);

    return d->m_priMaximizedMargins.right();
}

int QEXTQuickFramelessHelper::bottomMaximizedMargin() const
{
    Q_D(const QEXTQuickFramelessHelper);

    return d->m_priMaximizedMargins.bottom();
}

void QEXTQuickFramelessHelper::addIncludeItem(QQuickItem *item)
{
    Q_D(QEXTQuickFramelessHelper);

    d->m_includeItems.insert(item);
}

void QEXTQuickFramelessHelper::removeIncludeItem(QQuickItem *item)
{
    Q_D(QEXTQuickFramelessHelper);

    d->m_includeItems.remove(item);
}

void QEXTQuickFramelessHelper::addExcludeItem(QQuickItem *item)
{
    Q_D(QEXTQuickFramelessHelper);

    d->m_excludeItems.insert(item);
}

void QEXTQuickFramelessHelper::removeExcludeItem(QQuickItem *item)
{
    Q_D(QEXTQuickFramelessHelper);

    d->m_excludeItems.remove(item);
}

void QEXTQuickFramelessHelper::setTitleBarHeight(int value)
{
    Q_D(QEXTQuickFramelessHelper);

    if (value != d->m_titleBarHeight) {
        d->m_titleBarHeight = value;
        emit titleBarHeightChanged();
    }
}

int QEXTQuickFramelessHelper::titleBarHeight() const
{
    Q_D(const QEXTQuickFramelessHelper);

    return d->m_titleBarHeight;
}

qreal QEXTQuickFramelessHelper::scaleFactor() const
{
    Q_D(const QEXTQuickFramelessHelper);

    return d->m_helper ? d->m_helper->scaleFactor() : 1.0;
}

void QEXTQuickFramelessHelper::triggerMinimizeButtonAction()
{
    Q_D(QEXTQuickFramelessHelper);

    if (d->m_window) {
        auto oldStates = d->m_window->windowStates();
        d->m_window->setWindowStates((oldStates & ~Qt::WindowActive) | Qt::WindowMinimized);
    }
}

void QEXTQuickFramelessHelper::triggerMaximizeButtonAction()
{
    Q_D(QEXTQuickFramelessHelper);

    if (d->m_window) {
        if (QWindow::Maximized == d->m_window->visibility()) {
            d->m_window->showNormal();
        } else {
            d->m_window->showMaximized();
        }
    }
}

void QEXTQuickFramelessHelper::triggerCloseButtonAction()
{
    Q_D(QEXTQuickFramelessHelper);

    if (d->m_window) {
        d->m_window->close();
    }
}
