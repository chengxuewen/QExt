#ifndef _QEXTLED_H
#define _QEXTLED_H

#include <qextWidgetGlobal.h>

#include <QWidget>
#include <QSize>
#include <QColor>

class QEXTLedPrivate;
class QEXT_WIDGETS_API QEXTLed : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(QEXTLed)
    Q_DECLARE_PRIVATE_D(dd_ptr, QEXTLed)

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(bool state READ isOn WRITE setOn NOTIFY stateChanged)

public:
    explicit QEXTLed(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTLed();

    QColor color() const;
    bool isOn() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

Q_SIGNALS:
    void colorChanged(QColor ledColor);
    void stateChanged(bool on);

public Q_SLOTS:
    void setColor(const QColor &color);
    void setOn(bool on);
    void turnOn();
    void turnOff();
    void toggle();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    QScopedPointer<QEXTLedPrivate> dd_ptr;
};

#endif // _QEXTLED_H
