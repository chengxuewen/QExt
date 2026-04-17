#ifndef _QEXTQMLPENINFO_H
#define _QEXTQMLPENINFO_H

#include <qextQmlGlobal.h>
#include <qextQmlRegistration.h>

#include <QPen>
#include <QColor>
#include <QObject>

class QExtQmlPenInfoPrivate;
class QEXT_QML_API QExtQmlPenInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(Qt::PenStyle style READ style WRITE setStyle NOTIFY styleChanged)
    Q_PROPERTY(Qt::PenCapStyle capStyle READ capStyle WRITE setCapStyle NOTIFY capStyleChanged)
    Q_PROPERTY(Qt::PenJoinStyle joinStyle READ joinStyle WRITE setJoinStyle NOTIFY joinStyleChanged)
public:
    explicit QExtQmlPenInfo(QObject *parent = QEXT_NULLPTR);
    QExtQmlPenInfo(Qt::PenStyle style, QObject *parent = QEXT_NULLPTR);
    QExtQmlPenInfo(const QColor &color, QObject *parent = QEXT_NULLPTR);
    ~QExtQmlPenInfo() override;

    const QPen &pen() const;
    void setPen(const QPen &pen);

    qreal width() const;
    void setWidth(qreal width);

    QColor color() const;
    void setColor(const QColor &color);

    Qt::PenStyle style() const;
    void setStyle(Qt::PenStyle style);

    Qt::PenCapStyle capStyle() const;
    void setCapStyle(Qt::PenCapStyle pcs);

    Qt::PenJoinStyle joinStyle() const;
    void setJoinStyle(Qt::PenJoinStyle pcs);

Q_SIGNALS:
    void widthChanged(qreal width);
    void penChanged(const QPen &pen);
    void colorChanged(const QColor &color);
    void styleChanged(Qt::PenStyle style);
    void capStyleChanged(Qt::PenCapStyle pcs);
    void joinStyleChanged(Qt::PenJoinStyle pcs);

protected:
    QScopedPointer<QExtQmlPenInfoPrivate> dd_ptr;

private:
    QEXT_QML_ELEMENT()
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtQmlPenInfo)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtQmlPenInfo)
};

#endif // _QEXTQMLPENINFO_H
