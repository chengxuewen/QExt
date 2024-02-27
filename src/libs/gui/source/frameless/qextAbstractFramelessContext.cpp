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

#include <private/qextAbstractFramelessContext_p.h>
#include <qextFramelessUtils.h>

#include <QPen>
#include <QScreen>
#include <QPainter>

namespace
{

class WinIdChangeEventFilter : public QObject
{
public:
    explicit WinIdChangeEventFilter(QObject *widget, QExtAbstractFramelessContext *ctx,
                                    QObject *parent = QEXT_NULLPTR)
        : QObject(parent), ctx(ctx)
    {
        widget->installEventFilter(this);
    }

protected:
    bool eventFilter(QObject *obj, QEvent *event) QEXT_OVERRIDE
    {
        Q_UNUSED(obj)
        if (event->type() == QEvent::WinIdChange)
        {
            ctx->notifyWinIdChange();
        }
        return false;
    }

protected:
    QExtAbstractFramelessContext *ctx;
};

class WindowEventFilter : public QObject
{
public:
    explicit WindowEventFilter(QWindow *window, QExtAbstractFramelessContext *ctx,
                               QObject *parent = QEXT_NULLPTR)
        : QObject(parent), ctx(ctx), window(window)
    {
        window->installEventFilter(this);
    }

protected:
    bool eventFilter(QObject *obj, QEvent *event) QEXT_OVERRIDE
    {
        return ctx->sharedDispatch(obj, event);
    }

protected:
    QExtAbstractFramelessContext *ctx;
    QWindow *window;
};
}

QExtAbstractFramelessContext::QExtAbstractFramelessContext()
    : m_host(QEXT_NULLPTR)
    , m_windowHandle(QEXT_NULLPTR)
    , m_titleBar(QEXT_NULLPTR)
    , m_systemButtons(QExtFramelessAgent::Close + 1)
{
}

QExtAbstractFramelessContext::~QExtAbstractFramelessContext()
{

}

void QExtAbstractFramelessContext::setup(QObject *host, QExtFramelessItemDelegate *delegate)
{
    if (m_host || !host || !delegate)
    {
        return;
    }
    m_host = host;
    m_delegate.reset(delegate);
    m_winIdChangeEventFilter.reset(new WinIdChangeEventFilter(host, this));

    m_windowHandle = m_delegate->hostWindow(m_host);
    if (m_windowHandle)
    {
        winIdChanged();
        m_windowEventFilter.reset(new WindowEventFilter(m_windowHandle, this));
    }
}

bool QExtAbstractFramelessContext::setHitTestVisible(const QObject *obj, bool visible)
{
    Q_ASSERT(obj);
    if (!obj)
    {
        return false;
    }

    if (visible)
    {
        m_hitTestVisibleItems.insert(obj);
    }
    else
    {
        m_hitTestVisibleItems.remove(obj);
    }
    return true;
}

bool QExtAbstractFramelessContext::setSystemButton(QExtFramelessAgent::SystemButton button,
                                            QObject *obj)
{
    Q_ASSERT(button != QExtFramelessAgent::Unknown);
    if (button == QExtFramelessAgent::Unknown)
    {
        return false;
    }

    if (m_systemButtons[button] == obj)
    {
        return false;
    }
    m_systemButtons[button] = obj;
    return true;
}

bool QExtAbstractFramelessContext::setTitleBar(QObject *item)
{
    Q_ASSERT(item);
    if (m_titleBar == item)
    {
        return false;
    }

    if (m_titleBar)
    {
        // Since the title bar is changed, all items inside it should be dereferenced right away
        for (auto &button: m_systemButtons)
        {
            button = QEXT_NULLPTR;
        }
        m_hitTestVisibleItems.clear();
    }

    m_titleBar = item;
    return true;
}

#ifdef Q_OS_MAC
void QExtAbstractFramelessContext::setSystemButtonAreaCallback(QExtScreenRectCallbackInterface *callback)
{
    m_systemButtonAreaCallback.reset(callback);
    virtualHook(SystemButtonAreaChangedHook, QEXT_NULLPTR);
}
#endif

bool QExtAbstractFramelessContext::isInSystemButtons(const QPoint &pos, QExtFramelessAgent::SystemButton *button) const
{
    *button = QExtFramelessAgent::Unknown;
    for (int i = QExtFramelessAgent::WindowIcon; i <= QExtFramelessAgent::Close; ++i)
    {
        auto currentButton = m_systemButtons[i];
        if (!currentButton || !m_delegate->isVisible(currentButton) || !m_delegate->isEnabled(currentButton))
        {
            continue;
        }
        if (m_delegate->mapGeometryToScene(currentButton).contains(pos))
        {
            *button = static_cast<QExtFramelessAgent::SystemButton>(i);
            return true;
        }
    }
    return false;
}

bool QExtAbstractFramelessContext::isInTitleBarDraggableArea(const QPoint &pos) const
{
    if (!m_titleBar)
    {
        // There's no title bar at all, the mouse will always be in the client area.
        return false;
    }
    if (!m_delegate->isVisible(m_titleBar) || !m_delegate->isEnabled(m_titleBar))
    {
        // The title bar is hidden or disabled for some reason, treat it as there's
        // no title bar.
        return false;
    }
    QRect windowRect = {QPoint(0, 0), m_windowHandle->size()};
    QRect titleBarRect = m_delegate->mapGeometryToScene(m_titleBar);
    if (!titleBarRect.intersects(windowRect))
    {
        // The title bar is totally outside the window for some reason,
        // also treat it as there's no title bar.
        return false;
    }

    if (!titleBarRect.contains(pos))
    {
        return false;
    }

    for (int i = QExtFramelessAgent::WindowIcon; i <= QExtFramelessAgent::Close; ++i)
    {
        auto currentButton = m_systemButtons[i];
        if (currentButton && m_delegate->isVisible(currentButton) &&
            m_delegate->isEnabled(currentButton) &&
            m_delegate->mapGeometryToScene(currentButton).contains(pos))
        {
            return false;
        }
    }

    for (auto widget: m_hitTestVisibleItems)
    {
        if (widget && m_delegate->isVisible(widget) && m_delegate->isEnabled(widget) &&
            m_delegate->mapGeometryToScene(widget).contains(pos))
        {
            return false;
        }
    }

    return true;
}

QString QExtAbstractFramelessContext::key() const
{
    return { };
}

#define MAKE_RGB_COLOR(r, g, b) \
    ((quint32) (((r) &0xFF) << 16) | (((g) &0xFF) << 8) | ((b) &0xFF))

#define MAKE_RGBA_COLOR(r, g, b, a) \
    ((quint32) (((a) &0xFF) << 24) | (((r) &0xFF) << 16) | (((g) &0xFF) << 8) | ((b) &0xFF))

QEXT_ATTR_USED static constexpr const struct
{
    const quint32 activeLight = MAKE_RGBA_COLOR(210, 233, 189, 226);
    const quint32 activeDark = MAKE_RGBA_COLOR(177, 205, 190, 240);
    const quint32 inactiveLight = MAKE_RGBA_COLOR(193, 195, 211, 203);
    const quint32 inactiveDark = MAKE_RGBA_COLOR(240, 240, 250, 255);
} kSampleColorSet;

void QExtAbstractFramelessContext::virtualHook(int id, void *data)
{
    switch (id)
    {
        case CentralizeHook:
        {
            if (!m_windowHandle)
            {
                return;
            }

            QRect screenGeometry = m_windowHandle->screen()->geometry();
            int x = (screenGeometry.width() - m_windowHandle->width()) / 2;
            int y = (screenGeometry.height() - m_windowHandle->height()) / 2;
            QPoint pos(x, y);
            pos += screenGeometry.topLeft();
            m_windowHandle->setPosition(pos);
            return;
        }

        case RaiseWindowHook:
        {
            if (!m_windowHandle)
            {
                return;
            }

            m_delegate->setWindowVisible(m_host, true);
            Qt::WindowStates state = m_delegate->getWindowState(m_host);
            if (state & Qt::WindowMinimized)
            {
                m_delegate->setWindowState(m_host, state & ~Qt::WindowMinimized);
            }
            m_delegate->bringWindowToTop(m_host);
            return;
        }

        case DefaultColorsHook:
        {
            auto &map = *static_cast<QMap<QString, QColor> *>(data);
            map.clear();
            map.insert(QStringLiteral("activeLight"), kSampleColorSet.activeLight);
            map.insert(QStringLiteral("activeDark"), kSampleColorSet.activeDark);
            map.insert(QStringLiteral("inactiveLight"), kSampleColorSet.inactiveLight);
            map.insert(QStringLiteral("inactiveDark"), kSampleColorSet.inactiveDark);
            return;
        }

        default:
            break;
    }
}

void QExtAbstractFramelessContext::showSystemMenu(const QPoint &pos)
{
    virtualHook(ShowSystemMenuHook, &const_cast<QPoint &>(pos));
}

void QExtAbstractFramelessContext::notifyWinIdChange()
{
    auto oldWindow = m_windowHandle;
    m_windowHandle = m_delegate->hostWindow(m_host);
    if (oldWindow == m_windowHandle)
    {
        return;
    }
    m_windowEventFilter.reset();
    winIdChanged();
    if (m_windowHandle)
    {
        m_windowEventFilter.reset(new WindowEventFilter(m_windowHandle, this));

        // Refresh window attributes
        auto attributes = m_windowAttributes;
        m_windowAttributes.clear();
        for (auto it = attributes.begin(); it != attributes.end(); ++it)
        {
            if (!windowAttributeChanged(it.key(), it.value(), { }))
            {
                continue;
            }
            m_windowAttributes.insert(it.key(), it.value());
        }
    }
}

QVariant QExtAbstractFramelessContext::windowAttribute(const QString &key) const
{
    return m_windowAttributes.value(key);
}

bool QExtAbstractFramelessContext::setWindowAttribute(const QString &key, const QVariant &attribute)
{
    auto it = m_windowAttributes.find(key);
    if (it == m_windowAttributes.end())
    {
        if (!attribute.isValid())
        {
            return true;
        }
        if (!m_windowHandle || !windowAttributeChanged(key, attribute, { }))
        {
            return false;
        }
        m_windowAttributes.insert(key, attribute);
        return true;
    }

    if (it.value() == attribute)
    {
        return true;
    }
    if (!m_windowHandle || !windowAttributeChanged(key, attribute, it.value()))
    {
        return false;
    }

    if (attribute.isValid())
    {
        it.value() = attribute;
    }
    else
    {
        m_windowAttributes.erase(it);
    }
    return true;
}

bool QExtAbstractFramelessContext::windowAttributeChanged(const QString &key,
                                                   const QVariant &attribute,
                                                   const QVariant &oldAttribute)
{
    return false;
}
