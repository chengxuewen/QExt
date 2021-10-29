#ifndef _QEXTGUIGVRECTANGLE_H
#define _QEXTGUIGVRECTANGLE_H

#include <qextGuiGlobal.h>
#include <qextGuiGVItem.h>

class QEXTGuiPen;
class QEXTGuiGradient;
class QEXTGuiGVRectanglePrivate;
class QEXT_GUI_API QEXTGuiGVRectangle : public QEXTGuiGVItem
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QEXTGuiGradient *gradient READ gradient WRITE setGradient)
    Q_PROPERTY(QEXTGuiPen * border READ border CONSTANT)
    Q_PROPERTY(qreal radius READ radius WRITE setRadius NOTIFY radiusChanged)

public:
    QEXTGuiGVRectangle(QEXTGuiGVItem *parent = QEXT_DECL_NULLPTR);
    ~QEXTGuiGVRectangle();

    QColor color() const;
    void setColor(const QColor &color);

    QEXTGuiPen *border();

    QEXTGuiGradient *gradient() const;
    void setGradient(QEXTGuiGradient *gradient);

    qreal radius() const;
    void setRadius(qreal radius);

    QRectF boundingRect() const QEXT_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) QEXT_DECL_OVERRIDE;

Q_SIGNALS:
    void colorChanged();
    void radiusChanged();

private Q_SLOTS:
    void doUpdate();

private:
    void generateRoundedRect();
    void generateBorderedRect();
    void drawRect(QPainter &painter);

private:
    Q_DISABLE_COPY(QEXTGuiGVRectangle)
    Q_DECLARE_PRIVATE_D(QEXTGuiGVItem::d_ptr.data(), QEXTGuiGVRectangle)
};

#endif // _QEXTGUIGVRECTANGLE_H
