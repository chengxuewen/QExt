#ifndef _QEXTQUICKTRIANGLEITEM_H
#define _QEXTQUICKTRIANGLEITEM_H

#include <qextQuickControlsGlobal.h>

#include <QQuickPaintedItem>

class QExtQuickTriangleItemPrivate;
class QExtQuickTriangleItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY borderColorChanged)
    Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderWidth NOTIFY borderWidthChanged)
public:
    QExtQuickTriangleItem(QQuickItem *parent = nullptr);
    ~QExtQuickTriangleItem() override;

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

    QScopedPointer<QExtQuickTriangleItemPrivate> dd_ptr;

private:
    Q_DISABLE_COPY(QExtQuickTriangleItem)
    Q_DECLARE_PRIVATE_D(dd_ptr, QExtQuickTriangleItem)
};

#endif // _QEXTQUICKTRIANGLEITEM_H
