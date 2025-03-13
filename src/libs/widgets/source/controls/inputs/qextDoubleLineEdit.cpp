#include <qextDoubleLineEdit.h>
#include <qextNumeric.h>

#include <QDebug>
#include <QEvent>
#include <QTimer>
#include <QKeyEvent>
#include <QApplication>
#include <QDoubleValidator>

class QExtDoubleLineEditPrivate
{
public:
    explicit QExtDoubleLineEditPrivate(QExtDoubleLineEdit *q);
    virtual ~QExtDoubleLineEditPrivate();

    void updateEnglishLatinUnitedStatesLocale(const QValidator *validator);

    QExtDoubleLineEdit * const q_ptr;

    QDoubleValidator *m_doubleValidator;
    bool m_englishLatinUnitedStatesLocale;

private:
    Q_DECLARE_PUBLIC(QExtDoubleLineEdit)
    Q_DISABLE_COPY_MOVE(QExtDoubleLineEditPrivate)
};

QExtDoubleLineEditPrivate::QExtDoubleLineEditPrivate(QExtDoubleLineEdit *q)
    : q_ptr(q)
    , m_doubleValidator(new QDoubleValidator(std::numeric_limits<double>::min(),
                                             std::numeric_limits<double>::max(),
                                             6, q))
    , m_englishLatinUnitedStatesLocale(false)
{
}

QExtDoubleLineEditPrivate::~QExtDoubleLineEditPrivate()
{
}

void QExtDoubleLineEditPrivate::updateEnglishLatinUnitedStatesLocale(const QValidator *validator)
{
    QLocale locale = validator ? validator->locale() : q_ptr->locale();
    m_englishLatinUnitedStatesLocale = locale.language() == QLocale::English &&
                                       locale.script() == QLocale::LatinScript &&
                                       locale.country() == QLocale::UnitedStates;
}

QExtDoubleLineEdit::QExtDoubleLineEdit(QWidget *parent)
    : QLineEdit(parent)
    , dd_ptr(new QExtDoubleLineEditPrivate(this))
{
    qApp->installEventFilter(this);
    this->setValidator(dd_ptr->m_doubleValidator);
    this->setEnglishLatinUnitedStatesLocale(true);
}

QExtDoubleLineEdit::QExtDoubleLineEdit(const QString &text, QWidget *parent)
    : QLineEdit(parent)
    , dd_ptr(new QExtDoubleLineEditPrivate(this))
{
    qApp->installEventFilter(this);
    this->setValidator(dd_ptr->m_doubleValidator);
    this->setEnglishLatinUnitedStatesLocale(true);
    this->setText(text);
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

bool QExtDoubleLineEdit::isEnglishLatinUnitedStatesLocale() const
{
    Q_D(const QExtDoubleLineEdit);
    return d->m_englishLatinUnitedStatesLocale;
}

void QExtDoubleLineEdit::setEnglishLatinUnitedStatesLocale(bool enable)
{
    Q_D(QExtDoubleLineEdit);
    if (enable != d->m_englishLatinUnitedStatesLocale)
    {
        d->m_doubleValidator->setLocale(QLocale(QLocale::English,
                                                QLocale::LatinScript,
                                                QLocale::UnitedStates));
    }
    d->updateEnglishLatinUnitedStatesLocale(this->validator());
}

void QExtDoubleLineEdit::onValidatorChanged()
{
    Q_D(QExtDoubleLineEdit);
    d->updateEnglishLatinUnitedStatesLocale(this->validator());
}

void QExtDoubleLineEdit::setValidator(const QValidator *validator)
{
    Q_D(QExtDoubleLineEdit);
    const QValidator *oldValidator = this->validator();
    if (oldValidator != validator)
    {
        if (oldValidator)
        {
            oldValidator->disconnect(this);
        }
        if (validator)
        {
            connect(validator, SIGNAL(changed()), this, SLOT(onValidatorChanged()));
        }
    }
    QLineEdit::setValidator(validator);
    d->updateEnglishLatinUnitedStatesLocale(validator);
}

bool QExtDoubleLineEdit::eventFilter(QObject *obj, QEvent *event)
{
    return QLineEdit::eventFilter(obj, event);
}

void QExtDoubleLineEdit::keyPressEvent(QKeyEvent *event)
{
    QLineEdit::keyPressEvent(event);
}
