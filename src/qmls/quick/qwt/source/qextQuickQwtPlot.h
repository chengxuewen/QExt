#ifndef _QEXTQUICKQWTPLOT_H
#define _QEXTQUICKQWTPLOT_H

#include <qextQuickQwtGlobal.h>
#include <qextQmlRegistration.h>

#include <QQuickPaintedItem>
#include <QScopedPointer>

class QExtQuickQwtPlotPrivate;
class QEXT_QUICKQWT_API QExtQuickQwtPlot : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(bool autoReplot READ autoReplot WRITE setAutoReplot NOTIFY autoReplotChanged)
    Q_PROPERTY(QString styleSheet READ styleSheet WRITE setStyleSheet NOTIFY styleSheetChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(QColor canvasBackgroundColor READ canvasBackgroundColor WRITE setCanvasBackgroundColor NOTIFY canvasBackgroundColorChanged)
public:
    enum AxisEnum
    {
        AxisLeft = 0,
        AxisRight,
        AxisBottom,
        AxisTop
    };
    Q_ENUM(AxisEnum)

    QExtQuickQwtPlot(QQuickItem* parent = nullptr);
    QExtQuickQwtPlot(QExtQuickQwtPlotPrivate *d, QQuickItem* parent = nullptr);
    ~QExtQuickQwtPlot() override;

    void paint(QPainter* painter) override;

    bool autoReplot() const;
    void setAutoReplot(bool value = true);

    QString styleSheet() const;
    void setStyleSheet(const QString& styleSheet);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);

    QColor canvasBackgroundColor() const;
    void setCanvasBackgroundColor(const QColor &color);

    Q_INVOKABLE double axisMin(AxisEnum axis) const;
    Q_INVOKABLE void setAxisMin(AxisEnum axis, double value);

    Q_INVOKABLE double axisMax(AxisEnum axis) const;
    Q_INVOKABLE void setAxisMax(AxisEnum axis, double value);

    Q_INVOKABLE void setAxisRange(AxisEnum axis, double min, double max);

    Q_INVOKABLE bool isAxisValid(AxisEnum axis) const;
    Q_INVOKABLE bool isAxisVisible(AxisEnum axis) const;
    Q_INVOKABLE void setAxisVisible(AxisEnum axis, bool on = true);

    Q_INVOKABLE bool axisAutoScale(AxisEnum axis) const;
    Q_INVOKABLE void setAxisAutoScale(AxisEnum axis, bool on = true);

Q_SIGNALS:
    void autoReplotChanged(bool value);
    void axisMinChanged(AxisEnum axis, double value);
    void axisMaxChanged(AxisEnum axis, double value);
    void styleSheetChanged(const QString& styleSheet);
    void axisVisibleChanged(AxisEnum axis, bool visible);
    void axisAutoScaleChanged(AxisEnum axis, bool on = true);
    void backgroundColorChanged(const QColor &color);
    void canvasBackgroundColorChanged(const QColor &color);

public Q_SLOTS:
    Q_INVOKABLE void updatePlotSize();
    Q_INVOKABLE void replotAndUpdate();

protected:
    virtual void routeMouseEvents(QMouseEvent* event);
    virtual void routeWheelEvents(QWheelEvent* event);

    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent *event) override;

protected:
    QScopedPointer<QExtQuickQwtPlotPrivate> dd_ptr;

private:
    QEXT_QML_ELEMENT()
    friend class QExtQuickQwtPlotCurve;
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtQuickQwtPlot)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQuickQwtPlot)
};

#endif // _QEXTQUICKQWTPLOT_H
