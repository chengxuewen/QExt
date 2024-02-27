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

#ifndef _QEXTABSTRACTFRAMELESSCONTEXT_P_H
#define _QEXTABSTRACTFRAMELESSCONTEXT_P_H

#include <QSet>
#include <QRegion>
#include <QVector>
#include <QWindow>
#include <QPointer>

#include <qextFramelessAgent.h>
#include <private/qextFramelessItemDelegate_p.h>
#include <private/qextFramelessNativeEvent_p.h>
#include <private/qextFramelessSharedEvent_p.h>

class QEXT_GUI_API QExtAbstractFramelessContext : public QObject, public QExtFramelessNativeEventDispatcher, public QExtFramelessSharedEventDispatcher
{
    Q_OBJECT
public:
    QExtAbstractFramelessContext();
    ~QExtAbstractFramelessContext() QEXT_OVERRIDE;

public:
    void setup(QObject *host, QExtFramelessItemDelegate *delegate);

    inline QObject *host() const;
    inline QWindow *window() const;
    inline QExtFramelessItemDelegate *delegate() const;

    inline bool isHitTestVisible(const QObject *obj) const;
    bool setHitTestVisible(const QObject *obj, bool visible);

    inline QObject *systemButton(QExtFramelessAgent::SystemButton button) const;
    bool setSystemButton(QExtFramelessAgent::SystemButton button, QObject *obj);

    inline QObject *titleBar() const;
    bool setTitleBar(QObject *obj);

#ifdef Q_OS_MAC
    inline QExtScreenRectCallbackInterface *systemButtonAreaCallback() const;
    void setSystemButtonAreaCallback(QExtScreenRectCallbackInterface *callback);
#endif

    bool isInSystemButtons(const QPoint &pos, QExtFramelessAgent::SystemButton *button) const;
    bool isInTitleBarDraggableArea(const QPoint &pos) const;

    virtual QString key() const;

    enum WindowContextHook
    {
        CentralizeHook = 1,
        RaiseWindowHook,
        ShowSystemMenuHook,
        DefaultColorsHook,
        DrawWindows10BorderHook,     // Only works on Windows 10, emulated workaround
        DrawWindows10BorderHook2,    // Only works on Windows 10, native workaround
        SystemButtonAreaChangedHook, // Only works on Mac
    };
    virtual void virtualHook(int id, void *data);

    void showSystemMenu(const QPoint &pos);
    void notifyWinIdChange();

    virtual QVariant windowAttribute(const QString &key) const;
    virtual bool setWindowAttribute(const QString &key, const QVariant &attribute);

protected:
    virtual void winIdChanged() = 0;
    virtual bool windowAttributeChanged(const QString &key, const QVariant &attribute,
                                        const QVariant &oldAttribute);

protected:
    QObject *m_host;
    QWindow *m_windowHandle;
    QScopedPointer<QExtFramelessItemDelegate> m_delegate;

    QSet<const QObject *> m_hitTestVisibleItems;
#ifdef Q_OS_MAC
    QScopedPointer<QExtScreenRectCallbackInterface> m_systemButtonAreaCallback;
#endif

    QObject *m_titleBar;
    QVector<QObject *> m_systemButtons;

    QVariantHash m_windowAttributes;

    QScopedPointer<QObject> m_windowEventFilter;
    QScopedPointer<QObject> m_winIdChangeEventFilter;
};

inline QObject *QExtAbstractFramelessContext::host() const
{
    return m_host;
}

inline QWindow *QExtAbstractFramelessContext::window() const
{
    return m_windowHandle;
}

inline QExtFramelessItemDelegate *QExtAbstractFramelessContext::delegate() const
{
    return m_delegate.get();
}

inline bool QExtAbstractFramelessContext::isHitTestVisible(const QObject *obj) const
{
    return m_hitTestVisibleItems.contains(obj);
}

inline QObject *QExtAbstractFramelessContext::systemButton(QExtFramelessAgent::SystemButton button) const
{
    return m_systemButtons[button];
}

inline QObject *QExtAbstractFramelessContext::titleBar() const
{
    return m_titleBar;
}

#ifdef Q_OS_MAC
inline QExtScreenRectCallbackInterface *QExtAbstractFramelessContext::systemButtonAreaCallback() const
{
    return m_systemButtonAreaCallback.data();
}
#endif

#endif // _QEXTABSTRACTFRAMELESSCONTEXT_P_H
