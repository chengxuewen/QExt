/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2024~Present ChengXueWen. Contact: 1398831004@qq.com
** Copyright (C) 2023-2024 Stdware Collections
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
** documentation files (the "Software"), to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions
** of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
** CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
** IN THE SOFTWARE.
**
***********************************************************************************************************************/

#include <private/qextFramelessUtils_p.h>
#include <private/qextFramelessContext_p.h>

#include <QDebug>

static constexpr const quint8 kDefaultResizeBorderThickness = 8;

static Qt::CursorShape calculateCursorShape(const QWindow *window, const QPoint &pos)
{
#ifdef Q_OS_MACOS
    Q_UNUSED(window);
    Q_UNUSED(pos);
    return Qt::ArrowCursor;
#else
    Q_ASSERT(window);
    if (!window)
    {
        return Qt::ArrowCursor;
    }
    if (window->visibility() != QWindow::Windowed)
    {
        return Qt::ArrowCursor;
    }
    const int x = pos.x();
    const int y = pos.y();
    const int w = window->width();
    const int h = window->height();
    if (((x < kDefaultResizeBorderThickness) && (y < kDefaultResizeBorderThickness)) ||
        ((x >= (w - kDefaultResizeBorderThickness)) && (y >= (h - kDefaultResizeBorderThickness))))
    {
        return Qt::SizeFDiagCursor;
    }
    if (((x >= (w - kDefaultResizeBorderThickness)) && (y < kDefaultResizeBorderThickness)) ||
        ((x < kDefaultResizeBorderThickness) && (y >= (h - kDefaultResizeBorderThickness))))
    {
        return Qt::SizeBDiagCursor;
    }
    if ((x < kDefaultResizeBorderThickness) || (x >= (w - kDefaultResizeBorderThickness)))
    {
        return Qt::SizeHorCursor;
    }
    if ((y < kDefaultResizeBorderThickness) || (y >= (h - kDefaultResizeBorderThickness)))
    {
        return Qt::SizeVerCursor;
    }
    return Qt::ArrowCursor;
#endif
}

static inline Qt::Edges calculateWindowEdges(const QWindow *window, const QPoint &pos)
{
#ifdef Q_OS_MACOS
    Q_UNUSED(window);
    Q_UNUSED(pos);
    return { };
#else
    Q_ASSERT(window);
    if (!window)
    {
        return {};
    }
    if (window->visibility() != QWindow::Windowed)
    {
        return {};
    }
    Qt::Edges edges = {};
    const int x = pos.x();
    const int y = pos.y();
    if (x < kDefaultResizeBorderThickness)
    {
        edges |= Qt::LeftEdge;
    }
    if (x >= (window->width() - kDefaultResizeBorderThickness))
    {
        edges |= Qt::RightEdge;
    }
    if (y < kDefaultResizeBorderThickness)
    {
        edges |= Qt::TopEdge;
    }
    if (y >= (window->height() - kDefaultResizeBorderThickness))
    {
        edges |= Qt::BottomEdge;
    }
    return edges;
#endif
}

class QtWindowEventFilter : public QExtFramelessSharedEventFilter
{
public:
    explicit QtWindowEventFilter(QExtAbstractFramelessContext *context);
    ~QtWindowEventFilter() QEXT_OVERRIDE {}

    enum WindowStatus
    {
        Idle,
        WaitingRelease,
        PreparingMove,
        Moving,
        Resizing,
    };

protected:
    bool sharedEventFilter(QObject *object, QEvent *event) QEXT_OVERRIDE;

private:
    QEXT_DISABLE_COPY_MOVE(QtWindowEventFilter)
    QExtAbstractFramelessContext *m_context;
    bool m_cursorShapeChanged;
    WindowStatus m_windowStatus;
};

QtWindowEventFilter::QtWindowEventFilter(QExtAbstractFramelessContext *context)
    : m_context(context), m_cursorShapeChanged(false), m_windowStatus(Idle)
{
    m_context->installQExtFramelessSharedEventFilter(this);
}

bool QtWindowEventFilter::sharedEventFilter(QObject *obj, QEvent *event)
{
    Q_UNUSED(obj)
    const QEvent::Type type = event->type();
    if (type < QEvent::MouseButtonPress || type > QEvent::MouseMove)
    {
        return false;
    }
    QObject *host = m_context->host();
    QWindow *window = m_context->window();
    QExtFramelessItemDelegate *delegate = m_context->delegate();
    const QMouseEvent *mouseEvent = static_cast<const QMouseEvent *>(event);
    bool fixedSize = delegate->isHostSizeFixed(host);

    QPoint scenePos = getMouseEventScenePos(mouseEvent);
    QPoint globalPos = getMouseEventGlobalPos(mouseEvent);

    bool inTitleBar = m_context->isInTitleBarDraggableArea(scenePos);
    switch (type)
    {
    case QEvent::MouseButtonPress:
    {
        switch (mouseEvent->button())
        {
        case Qt::LeftButton:
        {
            if (!fixedSize)
            {
                Qt::Edges edges = calculateWindowEdges(window, scenePos);
                if (edges != Qt::Edges())
                {
                    m_windowStatus = Resizing;
                    startSystemResize(window, edges);
                    event->accept();
                    return true;
                }
            }
            if (inTitleBar)
            {
                // If we call startSystemMove() now but release the mouse without actual
                // movement, there will be no MouseReleaseEvent, so we defer it when the
                // mouse is actually moving for the first time
                m_windowStatus = PreparingMove;
                event->accept();
                return true;
            }
            break;
        }
        case Qt::RightButton:
        {
            m_context->showSystemMenu(globalPos);
            break;
        }
        default:
            break;
        }
        m_windowStatus = WaitingRelease;
        break;
    }

    case QEvent::MouseButtonRelease:
    {
        switch (m_windowStatus)
        {
        case PreparingMove:
        case Moving:
        case Resizing:
        {
            m_windowStatus = Idle;
            event->accept();
            return true;
        }
        case WaitingRelease:
        {
            m_windowStatus = Idle;
            break;
        }
        default:
        {
            if (inTitleBar)
            {
                event->accept();
                return true;
            }
            break;
        }
        }
        break;
    }

    case QEvent::MouseMove:
    {
        switch (m_windowStatus)
        {
        case Moving:
        {
            return true;
        }
        case PreparingMove:
        {
            m_windowStatus = Moving;
            startSystemMove(window);
            event->accept();
            return true;
        }
        case Idle:
        {
            if (!fixedSize)
            {
                const Qt::CursorShape shape = calculateCursorShape(window, scenePos);
                if (shape == Qt::ArrowCursor)
                {
                    if (m_cursorShapeChanged)
                    {
                        delegate->restoreCursorShape(host);
                        m_cursorShapeChanged = false;
                    }
                }
                else
                {
                    delegate->setCursorShape(host, shape);
                    m_cursorShapeChanged = true;
                }
            }
            break;
        }
        default:
            break;
        }
        break;
    }

    case QEvent::MouseButtonDblClick:
    {
        if (mouseEvent->button() == Qt::LeftButton && inTitleBar && !fixedSize)
        {
            Qt::WindowStates windowState = delegate->getWindowState(host);
            if (!(windowState & Qt::WindowFullScreen))
            {
                if (windowState & Qt::WindowMaximized)
                {
                    delegate->setWindowState(host, windowState & ~Qt::WindowMaximized);
                }
                else
                {
                    delegate->setWindowState(host, windowState | Qt::WindowMaximized);
                }
                event->accept();
                return true;
            }
        }
        break;
    }

    default:
        break;
    }
    return false;
}

QExtFramelessWindowContext::QExtFramelessWindowContext() : QExtAbstractFramelessContext()
{
    qtWindowEventFilter.reset(new QtWindowEventFilter(this));
}

QExtFramelessWindowContext::~QExtFramelessWindowContext() = default;

QString QExtFramelessWindowContext::key() const
{
    return QStringLiteral("qt");
}

void QExtFramelessWindowContext::virtualHook(int id, void *data)
{
    QExtAbstractFramelessContext::virtualHook(id, data);
}

void QExtFramelessWindowContext::winIdChanged()
{
    if (!m_windowHandle)
    {
        m_delegate->setWindowFlags(m_host, m_delegate->getWindowFlags(m_host) & ~Qt::FramelessWindowHint);
        return;
    }

    // Allocate new resources
    m_delegate->setWindowFlags(m_host, m_delegate->getWindowFlags(m_host) | Qt::FramelessWindowHint);
}
