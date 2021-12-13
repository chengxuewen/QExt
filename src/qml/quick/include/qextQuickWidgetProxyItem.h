#ifndef _QEXTQUICKWIDGETPROXYITEM_H
#define _QEXTQUICKWIDGETPROXYITEM_H

#include <qextQuickGlobal.h>

#include <QPointer>
#include <QWidget>
#include <QQuickItem>
#include <QQuickPaintedItem>

class QEXT_QUICK_API QEXTQuickWidgetProxyItem : public QQuickPaintedItem
{
    Q_OBJECT
public:
    QEXTQuickWidgetProxyItem(QQuickItem *parent = QEXT_DECL_NULLPTR);
    QEXTQuickWidgetProxyItem(QWidget *widget, QQuickItem *parent = QEXT_DECL_NULLPTR);
    ~QEXTQuickWidgetProxyItem();

    Q_INVOKABLE virtual void initWidget();

    QWidget *widget() const;
    void setWidget(QWidget *widget);

protected Q_SLOTS:
    virtual void updateWidgetSize();

protected:
    virtual void routeHoverEnterEvents(QHoverEvent *event);
    virtual void routeHoverLeaveEvents(QHoverEvent *event);
    virtual void routeHoverMoveEvents(QHoverEvent *event);
    virtual void routeMouseEvents(QMouseEvent *event);
    virtual void routeWheelEvents(QWheelEvent *event);
    virtual void routeTimerEvents(QTimerEvent *event);

    bool eventFilter(QObject *watched, QEvent *event) QEXT_DECL_OVERRIDE;
    void hoverEnterEvent(QHoverEvent *event) QEXT_DECL_OVERRIDE;
    void hoverLeaveEvent(QHoverEvent *event) QEXT_DECL_OVERRIDE;
    void hoverMoveEvent(QHoverEvent *event) QEXT_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) QEXT_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) QEXT_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) QEXT_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QMouseEvent *event) QEXT_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *event) QEXT_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *event) QEXT_DECL_OVERRIDE;

    void paint(QPainter *painter) QEXT_DECL_OVERRIDE;

private:
    QScopedPointer<QWidget> m_widget;
};

#endif // _QEXTQUICKWIDGETPROXYITEM_H
