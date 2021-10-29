#ifndef _QEXTGUIPEN_H
#define _QEXTGUIPEN_H

#include <qextGuiGlobal.h>

#include <QObject>

class QEXTGuiPenPrivate;
class QEXT_GUI_API QEXTGuiPen : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY penChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY penChanged)

public:
    QEXTGuiPen(QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTGuiPen();

    int width() const;
    void setWidth(int width);

    QColor color() const;
    void setColor(const QColor &color);

    bool isValid() const;

Q_SIGNALS:
    void penChanged();

protected:
    QScopedPointer<QEXTGuiPenPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QEXTGuiPen)
    Q_DECLARE_PRIVATE(QEXTGuiPen)
};

#endif // _QEXTGUIPEN_H
