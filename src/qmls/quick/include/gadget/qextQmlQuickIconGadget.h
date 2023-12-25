#ifndef _QEXTQMLQUICKICONGADGET_H
#define _QEXTQMLQUICKICONGADGET_H

#include <qextQmlQuickGlobal.h>

#include <QColor>
#include <QObject>

class QEXTQmlQuickIconGadgetPrivate;
class QEXT_QUICK_API QEXTQmlQuickIconGadget : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QEXTQmlQuickIconGadget)
    Q_DECLARE_PRIVATE_D(dd_ptr, QEXTQmlQuickIconGadget)

    Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(qreal height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(qreal scale READ scale WRITE setScale NOTIFY scaleChanged)
    Q_PROPERTY(int position READ position WRITE setPosition NOTIFY positionChanged)

public:
    explicit QEXTQmlQuickIconGadget(QObject *parent = QEXT_NULLPTR);
    ~QEXTQmlQuickIconGadget();

    qreal width() const;
    qreal height() const;
    QColor color() const;
    qreal scale() const;
    QString source() const;
    int type() const;
    int position() const;

Q_SIGNALS:
    void widthChanged();
    void heightChanged();
    void colorChanged();
    void scaleChanged();
    void sourceChanged();
    void typeChanged(const int &type);
    void positionChanged(const int &position);

protected Q_SLOTS:
    void setWidth(const qreal &width);
    void setHeight(const qreal &height);
    void setColor(const QColor &color);
    void setScale(const qreal &scale);
    void setSource(const QString &source);
    void setType(const int &type);
    void setPosition(const int &position);

protected:
    QScopedPointer<QEXTQmlQuickIconGadgetPrivate> dd_ptr;
};

#endif // _QEXTQMLQUICKICONGADGET_H
