#include <qextFramelessHelper.h>
#include <qextFramelessHelper_p.h>
#include <qextNativeWindowHelper.h>

#include <QApplication>

#if defined(QEXT_OS_WIN32)

#include <windows.h>
#pragma comment (lib,"user32.lib")

QEXTFramelessHelper::QEXTFramelessHelper(QWidget *parent)
    : QObject(parent)
    , dd_ptr(new QEXTFramelessHelperPrivate())
{
    Q_D(QEXTFramelessHelper);
    d->m_window = parent;
    Q_CHECK_PTR(parent);

    if (!d->m_window.isNull())
    {
        d->m_window->installEventFilter(this);
    }
}

QEXTFramelessHelper::~QEXTFramelessHelper()
{
}

void QEXTFramelessHelper::setDraggableMargins(int left, int top, int right, int bottom)
{
    Q_D(QEXTFramelessHelper);

    d->m_priDraggableMargins = QMargins(left, top, right, bottom);
}

void QEXTFramelessHelper::setMaximizedMargins(int left, int top, int right, int bottom)
{
    Q_D(QEXTFramelessHelper);

    d->m_priMaximizedMargins = QMargins(left, top, right, bottom);
}

void QEXTFramelessHelper::setDraggableMargins(const QMargins &margins)
{
    Q_D(QEXTFramelessHelper);

    d->m_priDraggableMargins = margins;
}

void QEXTFramelessHelper::setMaximizedMargins(const QMargins &margins)
{
    Q_D(QEXTFramelessHelper);

    d->m_priMaximizedMargins = margins;
}

QMargins QEXTFramelessHelper::draggableMargins() const
{
    Q_D(const QEXTFramelessHelper);

    return d->m_priDraggableMargins;
}

QMargins QEXTFramelessHelper::maximizedMargins() const
{
    Q_D(const QEXTFramelessHelper);

    return d->m_priMaximizedMargins;
}

void QEXTFramelessHelper::addIncludeItem(QWidget *item)
{
    Q_D(QEXTFramelessHelper);

    d->m_includeItems.insert(item);
}

void QEXTFramelessHelper::removeIncludeItem(QWidget *item)
{
    Q_D(QEXTFramelessHelper);

    d->m_includeItems.remove(item);
}

void QEXTFramelessHelper::addExcludeItem(QWidget *item)
{
    Q_D(QEXTFramelessHelper);

    d->m_excludeItems.insert(item);
}

void QEXTFramelessHelper::removeExcludeItem(QWidget *item)
{
    Q_D(QEXTFramelessHelper);

    d->m_excludeItems.remove(item);
}

void QEXTFramelessHelper::setTitleBarHeight(int value)
{
    Q_D(QEXTFramelessHelper);

    if (value != d->m_titleBarHeight) {
        d->m_titleBarHeight = value;
        emit titleBarHeightChanged(value);
    }
}

int QEXTFramelessHelper::titleBarHeight() const
{
    Q_D(const QEXTFramelessHelper);

    return d->m_titleBarHeight;
}

qreal QEXTFramelessHelper::scaleFactor() const
{
    Q_D(const QEXTFramelessHelper);

    return d->m_helper ? d->m_helper->scaleFactor() : 1.0;
}

bool QEXTFramelessHelper::isMaximized() const
{
    Q_D(const QEXTFramelessHelper);

    return d->m_maximized;
}

void QEXTFramelessHelper::triggerMinimizeButtonAction()
{
    Q_D(QEXTFramelessHelper);

    if (!d->m_window.isNull()) {
        d->m_window->showMinimized();
    }
}

void QEXTFramelessHelper::triggerMaximizeButtonAction()
{
    Q_D(QEXTFramelessHelper);

    if (!d->m_window.isNull()) {
        if (d->m_window->windowState() & Qt::WindowMaximized) {
            d->m_window->showNormal();
        } else {
            d->m_window->showMaximized();
        }
    }
}

void QEXTFramelessHelper::triggerCloseButtonAction()
{
    Q_D(QEXTFramelessHelper);

    if (!d->m_window.isNull()) {
        d->m_window->close();
    }
}

bool QEXTFramelessHelper::eventFilter(QObject *obj, QEvent *ev)
{
    Q_D(QEXTFramelessHelper);
    if (ev->type() == QEvent::WindowStateChange) {
        bool maximized = d->m_window->windowState() & Qt::WindowMaximized;
        if (maximized != d->m_maximized) {
            d->m_maximized = maximized;
            emit maximizedChanged(maximized);
        }
    } else if (ev->type() == QEvent::WinIdChange) {
        if (nullptr == d->m_helper) {
            auto w = d->m_window->windowHandle();

            d->m_helper = new QEXTNativeWindowHelper(w, d);
            connect(d->m_helper, &QEXTNativeWindowHelper::scaleFactorChanged,
                    this, &QEXTFramelessHelper::scaleFactorChanged);
            if (!qFuzzyCompare(d->m_helper->scaleFactor(), 1.0)) {
                emit scaleFactorChanged(d->m_helper->scaleFactor());
            }
        }
    }

#if QT_VERSION < QT_VERSION_CHECK(5, 9, 0)
    if ((ev->type() == QEvent::Resize) || (ev->type() == QEvent::WindowStateChange)) {
        if (d->window->windowState() & Qt::WindowMaximized) {
            const QMargins &m = d->priMaximizedMargins;
            int r = GetSystemMetrics(SM_CXFRAME) * 2 - m.left() - m.right();
            int b = GetSystemMetrics(SM_CYFRAME) * 2 - m.top() - m.bottom();

            d->window->setContentsMargins(0, 0, r, b);
        } else {
            d->window->setContentsMargins(0 ,0, 0, 0);
        }
    }
#endif

    return QObject::eventFilter(obj, ev);
}

// class QEXTFramelessHelperPrivate

QEXTFramelessHelperPrivate::QEXTFramelessHelperPrivate()
    : m_window(nullptr)
    , m_helper(nullptr)
    , m_maximized(false)
    , m_titleBarHeight(0)
{
}

QEXTFramelessHelperPrivate::~QEXTFramelessHelperPrivate()
{
}

QMargins QEXTFramelessHelperPrivate::draggableMargins() const
{
    return m_priDraggableMargins;
}

QMargins QEXTFramelessHelperPrivate::maximizedMargins() const
{
    return m_priMaximizedMargins;
}

bool QEXTFramelessHelperPrivate::hitTest(const QPoint &pos) const
{
    int scaledTitleBarHeight = m_titleBarHeight * m_helper->scaleFactor();

    if (m_window.isNull())
        return false;
    else if (scaledTitleBarHeight == 0)
        return false;
    else if ((scaledTitleBarHeight > 0)
             && (pos.y() >= scaledTitleBarHeight))
        return false;

    int currentIndex = -1;
    QWidget *items[32] = {0};
    auto child = m_window.data();
    QPoint p = pos;

    while (child && (currentIndex < 31)) {
        items[++currentIndex] = child;
        auto grandchild = child->childAt(p);
        if (nullptr == grandchild) {
            break;
        }

        p = grandchild->mapFrom(child, p);
        child = grandchild;
    }

    while (currentIndex > 0) {
        child = items[currentIndex];
        --currentIndex;

        if (m_includeItems.contains(child)) {
            break;
        } else if (m_excludeItems.contains(child)) {
            return false;
        } else if (m_window.data() == child) {
            break;
        }
    }

    return true;
}

#endif // defined(QEXT_OS_WIN32)
