#ifndef _QEXTDOUBLELINEEDIT_H
#define _QEXTDOUBLELINEEDIT_H

#include <qextWidgetGlobal.h>

#include <QObject>
#include <QLineEdit>
#include <QScopedPointer>

class QExtDoubleLineEditPrivate;
class QEXT_WIDGETS_API QExtDoubleLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit QExtDoubleLineEdit(QWidget *parent = QEXT_NULLPTR);
    explicit QExtDoubleLineEdit(const QString &, QWidget *parent = QEXT_NULLPTR);
    ~QExtDoubleLineEdit() QEXT_OVERRIDE;

    double minimum() const;
    void setMinimum(double min);

    double maximum() const;
    void setMaximum(double max);

    void setRange(double min, double max);

    int decimals() const;
    void setDecimals(int prec);

    double doubleValue(bool *ok = QEXT_NULLPTR) const;
    void setDoubleValue(double value);

    double value(bool *ok = QEXT_NULLPTR) const { return this->doubleValue(ok); }
    void setValue(double value) { this->setDoubleValue(value); }

protected:
    QScopedPointer<QExtDoubleLineEditPrivate> dd_ptr;

private:
    Q_DECLARE_PRIVATE_D(dd_ptr, QExtDoubleLineEdit)
    Q_DISABLE_COPY_MOVE(QExtDoubleLineEdit)
};

#endif // _QEXTDOUBLELINEEDIT_H
