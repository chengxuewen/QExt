#include <qextDoubleLineEdit.h>
#include <qextNumeric.h>

#include <QDoubleValidator>

class QExtDoubleLineEditPrivate
{
public:
    explicit QExtDoubleLineEditPrivate(QExtDoubleLineEdit *q);
    virtual ~QExtDoubleLineEditPrivate();

    QExtDoubleLineEdit * const q_ptr;

    QDoubleValidator *m_doubleValidator;

private:
    Q_DECLARE_PUBLIC(QExtDoubleLineEdit)
    Q_DISABLE_COPY_MOVE(QExtDoubleLineEditPrivate)
};

QExtDoubleLineEditPrivate::QExtDoubleLineEditPrivate(QExtDoubleLineEdit *q)
    : q_ptr(q)
    , m_doubleValidator(new QDoubleValidator(std::numeric_limits<double>::min(),
                                             std::numeric_limits<double>::max(),
                                             6, q))
{
}

QExtDoubleLineEditPrivate::~QExtDoubleLineEditPrivate()
{
}

QExtDoubleLineEdit::QExtDoubleLineEdit(QWidget *parent)
    : QLineEdit(parent)
    , dd_ptr(new QExtDoubleLineEditPrivate(this))
{
    this->setValidator(dd_ptr->m_doubleValidator);
}

QExtDoubleLineEdit::QExtDoubleLineEdit(const QString &, QWidget *parent)
    : QLineEdit(parent)
    , dd_ptr(new QExtDoubleLineEditPrivate(this))
{
    this->setValidator(dd_ptr->m_doubleValidator);
}

QExtDoubleLineEdit::~QExtDoubleLineEdit()
{

}

double QExtDoubleLineEdit::minimum() const
{
    Q_D(const QExtDoubleLineEdit);
    return d->m_doubleValidator->bottom();
}

void QExtDoubleLineEdit::setMinimum(double min)
{
    Q_D(QExtDoubleLineEdit);
    d->m_doubleValidator->setBottom(min);
}

double QExtDoubleLineEdit::maximum() const
{
    Q_D(const QExtDoubleLineEdit);
    return d->m_doubleValidator->top();
}

void QExtDoubleLineEdit::setMaximum(double max)
{
    Q_D(QExtDoubleLineEdit);
    d->m_doubleValidator->setTop(max);
}

void QExtDoubleLineEdit::setRange(double min, double max)
{
    Q_D(QExtDoubleLineEdit);
    d->m_doubleValidator->setRange(min, max, d->m_doubleValidator->decimals());
}

int QExtDoubleLineEdit::decimals() const
{
    Q_D(const QExtDoubleLineEdit);
    return d->m_doubleValidator->decimals();
}

void QExtDoubleLineEdit::setDecimals(int prec)
{
    Q_D(QExtDoubleLineEdit);
    d->m_doubleValidator->setDecimals(prec);
}

double QExtDoubleLineEdit::doubleValue(bool *ok) const
{
    return this->text().toDouble(ok);
}

void QExtDoubleLineEdit::setDoubleValue(double value)
{
    Q_D(QExtDoubleLineEdit);
    this->setText(QExtNumeric::doubleFixedString(value, d->m_doubleValidator->decimals()));
}

