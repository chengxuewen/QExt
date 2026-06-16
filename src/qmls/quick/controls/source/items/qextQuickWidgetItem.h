#ifndef _QEXTQUICKWIDGETITEM_H
#define _QEXTQUICKWIDGETITEM_H

#include <qextQuickControlsGlobal.h>
#include <qextQmlRegistration.h>

#include <QQuickItem>

class QExtQuickWidgetItemPrivate;
class QEXT_QUICKCONTROLS_API QExtQuickWidgetItem : public QQuickItem
{
    Q_OBJECT
    QEXT_QML_ELEMENT()
    Q_PROPERTY(bool widgetHideEnable READ isWidgetHideEnabled WRITE setWidgetHideEnable NOTIFY widgetHideEnableChanged)
    Q_PROPERTY(QWindow *rootWindow READ rootWindow WRITE setRootWindow NOTIFY rootWindowChanged)
    Q_PROPERTY(bool widgetVisible READ isWidgetVisible NOTIFY widgetVisibleChanged)

public:
    explicit QExtQuickWidgetItem(QQuickItem *parent = nullptr);
    QExtQuickWidgetItem(QExtQuickWidgetItemPrivate *d, QQuickItem *parent = nullptr);
    ~QExtQuickWidgetItem() override;

    Q_INVOKABLE QWindow *rootWindow() const;
    Q_INVOKABLE void setRootWindow(QWindow *window);

    Q_INVOKABLE QWidget *widget() const;
    Q_INVOKABLE void setWidget(QWidget *widget);

    bool isWidgetHideEnabled() const;
    void setWidgetHideEnable(bool enable);

    bool isWidgetVisible() const;
    bool isItemCompleted() const;

    void updateWidgetGeometry();

Q_SIGNALS:
    void widgetHideEnableChanged(bool enabled);
    void widgetVisibleChanged(bool visible);
    void rootWindowChanged(QWindow *window);
    void itemCompleted();

protected:
    void updatePolish() override;
    void componentComplete() override;

protected:
    QScopedPointer<QExtQuickWidgetItemPrivate> dd_ptr;

private:
    Q_DECLARE_PRIVATE_D(dd_ptr, QExtQuickWidgetItem)
    Q_DISABLE_COPY(QExtQuickWidgetItem)
};

#endif // _QEXTQUICKWIDGETITEM_H
