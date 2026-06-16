#ifndef _QEXTQUICKTRIANGLEITEM_H
#define _QEXTQUICKTRIANGLEITEM_H

#include <qextQuickControlsGlobal.h>
#include <qextQmlRegistration.h>

#include <QQuickPaintedItem>

class QExtQuickTrianglePrivate;
class QEXT_QUICKCONTROLS_API QExtQuickTriangle : public QQuickPaintedItem
{
    Q_OBJECT
    QEXT_QML_ELEMENT()
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY borderColorChanged)
    Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderWidth NOTIFY borderWidthChanged)
public:
    QExtQuickTriangle(QQuickItem *parent = nullptr);
    ~QExtQuickTriangle() override;

    QColor color() const;
    void setColor(const QColor &color);

    QColor borderColor() const;
    void setBorderColor(const QColor &color);

    int borderWidth() const;
    void setBorderWidth(int width);

Q_SIGNALS:
    void borderWidthChanged(int width);
    void colorChanged(const QColor &color);
    void borderColorChanged(const QColor &color);

protected:
    void paint(QPainter *painter) override;

    QScopedPointer<QExtQuickTrianglePrivate> dd_ptr;

private:
    Q_DISABLE_COPY(QExtQuickTriangle)
    Q_DECLARE_PRIVATE_D(dd_ptr, QExtQuickTriangle)
};

#endif // _QEXTQUICKTRIANGLEITEM_H
