#include <qextMvvmScientificSpinBox.h>
#include <qextMvvmConstants.h>

#include <cfloat>

#include <QLineEdit>

const double g_upperSwitch = 1000;
const double g_lowerSwitch = 0.1;
const double g_minVal = DBL_MIN;
const double g_maxVal = DBL_MAX;

bool qextMvvmUseExponentialNotation(double val)
{
    const double absVal = std::abs(val);
    if (absVal <= g_minVal)
    {
        return false;
    }
    return absVal >= g_upperSwitch || absVal < g_lowerSwitch;
}

QEXTMvvmScientificSpinBox::QEXTMvvmScientificSpinBox(QWidget *parent)
    : QAbstractSpinBox(parent),
      m_value(0.0),
      m_min(-g_maxVal),
      m_max(g_maxVal),
      m_step(1.0),
      m_decimals(QEXTMvvmConstants::default_double_decimals)
{
    QLocale locale;
    locale.setNumberOptions(QLocale::RejectGroupSeparator);
    m_validator.setLocale(locale);
    m_validator.setNotation(QDoubleValidator::ScientificNotation);

    connect(this, SIGNAL(editingFinished()), this, SLOT(updateValue()));
}

QEXTMvvmScientificSpinBox::~QEXTMvvmScientificSpinBox()
{

}

double QEXTMvvmScientificSpinBox::value() const
{
    // return last acceptable input (required for the proper focus-out behaviour)
    double val = this->toDouble(this->text(), m_validator, m_min, m_max, m_value);
    return this->round(val, m_decimals);
}

void QEXTMvvmScientificSpinBox::setValue(double val)
{
    double oldVal = m_value;
    m_value = this->round(val, m_decimals);
    this->updateText();
    if (std::abs(oldVal - m_value) > g_minVal)
    {
        emit this->valueChanged(m_value);
    }
}

double QEXTMvvmScientificSpinBox::singleStep() const
{
    return m_step;
}

void QEXTMvvmScientificSpinBox::setSingleStep(double step)
{
    m_step = step;
}

double QEXTMvvmScientificSpinBox::minimum() const
{
    return m_min;
}

void QEXTMvvmScientificSpinBox::setMinimum(double min)
{
    m_min = min;
    if (m_value < m_min)
    {
        this->setValue(m_min);
    }
}

double QEXTMvvmScientificSpinBox::maximum() const
{
    return m_max;
}

void QEXTMvvmScientificSpinBox::setMaximum(double max)
{
    m_max = max;
    if (m_value > m_max)
    {
        setValue(m_max);
    }
}

void QEXTMvvmScientificSpinBox::setDecimals(int val)
{
    if (val <= 0)
    {
        return;
    }
    m_decimals = val;
    this->setValue(m_value);
}

int QEXTMvvmScientificSpinBox::decimals() const
{
    return m_decimals;
}

void QEXTMvvmScientificSpinBox::stepBy(int steps)
{
    double newVal = round(m_value + m_step * steps, m_decimals);
    if (this->inRange(newVal))
    {
        this->setValue(newVal);
    }
}

QValidator::State QEXTMvvmScientificSpinBox::validate(QString &, int &) const
{
    return QValidator::Acceptable;
}

void QEXTMvvmScientificSpinBox::fixup(QString &) const
{

}

QString QEXTMvvmScientificSpinBox::toString(double val, int decimalPoints)
{
    QString result = qextMvvmUseExponentialNotation(val) ? QString::number(val, 'e', decimalPoints)
                     : QString::number(val, 'f', decimalPoints);

    return result.replace(QRegExp("(\\.?0+)?((e{1}[\\+|-]{1})(0+)?([1-9]{1}.*))?$"), "\\3\\5");
}

double QEXTMvvmScientificSpinBox::toDouble(QString text, const QDoubleValidator &validator, double min, double max, double defaultValue)
{
    int pos = 0;
    if (validator.validate(text, pos) == QValidator::Acceptable)
    {
        double newVal = validator.locale().toDouble(text);
        if (std::abs(newVal) < g_minVal)
        {
            newVal = 0.0;
        }
        return newVal >= min && newVal <= max ? newVal : defaultValue;
    }
    return defaultValue;
}

double QEXTMvvmScientificSpinBox::round(double val, int decimals)
{
    char notation = qextMvvmUseExponentialNotation(val) ? 'e' : 'f';
    return QString::number(val, notation, decimals).toDouble();
}

QAbstractSpinBox::StepEnabled QEXTMvvmScientificSpinBox::stepEnabled() const
{
    return this->isReadOnly() ? StepNone : StepUpEnabled | StepDownEnabled;
}

void QEXTMvvmScientificSpinBox::updateValue()
{
    double newVal = this->toDouble(this->text(), m_validator, m_min, m_max, m_value);
    this->setValue(newVal);
}

void QEXTMvvmScientificSpinBox::updateText()
{
    QString newText = this->toString(m_value, m_decimals);
    if (newText != this->text())
    {
        this->lineEdit()->setText(newText);
    }
}

bool QEXTMvvmScientificSpinBox::inRange(double val) const
{
    return val >= m_min && val <= m_max;
}
