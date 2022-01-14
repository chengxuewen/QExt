#ifndef _QEXTMVVMWIDGETSSCIENTIFICSPINBOX_H
#define _QEXTMVVMWIDGETSSCIENTIFICSPINBOX_H

#include <qextMvvmGlobal.h>

#include <QAbstractSpinBox>

namespace ModelView
{

class QEXT_MVVM_API QEXTMvvmScientificSpinBox : public QAbstractSpinBox
{
    Q_OBJECT
    Q_PROPERTY(double value MEMBER m_value READ value WRITE setValue NOTIFY valueChanged USER true)

public:
    QEXTMvvmScientificSpinBox(QWidget* parent = nullptr);
    ~QEXTMvvmScientificSpinBox() override;

    double value() const;
    void setValue(double val);

    double singleStep() const;
    void setSingleStep(double step);

    double minimum() const;
    void setMinimum(double min);

    double maximum() const;
    void setMaximum(double max);

    void setDecimals(int);
    int decimals() const;

    void stepBy(int steps) override;
    QValidator::State validate(QString&, int&) const override { return QValidator::Acceptable; }
    void fixup(QString&) const override {}

    static QString toString(double val, int decimal_points);
    static double toDouble(QString text, const QDoubleValidator& validator, double min, double max,
                           double default_value);
    static double round(double val, int decimals);

signals:
    void valueChanged(double value);

protected:
    QAbstractSpinBox::StepEnabled stepEnabled() const override;

private:
    void updateValue();
    void updateText();
    bool inRange(double val) const;

    double m_value, m_min, m_max;
    double m_step;
    int m_decimals;
    QDoubleValidator m_validator;
};

} // namespace ModelView

#endif // _QEXTMVVMWIDGETSSCIENTIFICSPINBOX_H
