#include <qextDoubleSpinBox.h>
#include <qextNumeric.h>

#include <QDebug>

class QExtDoubleSpinBoxPrivate
{
public:
    explicit QExtDoubleSpinBoxPrivate(QExtDoubleSpinBox *q);
    virtual ~QExtDoubleSpinBoxPrivate();

    QExtDoubleSpinBox * const q_ptr;

    bool m_valueTextTrimedEnable;

private:
    Q_DECLARE_PUBLIC(QExtDoubleSpinBox)
    QEXT_DISABLE_COPY_MOVE(QExtDoubleSpinBoxPrivate)
};

QExtDoubleSpinBoxPrivate::QExtDoubleSpinBoxPrivate(QExtDoubleSpinBox *q)
    : q_ptr(q)
    , m_valueTextTrimedEnable(false)
{
}

QExtDoubleSpinBoxPrivate::~QExtDoubleSpinBoxPrivate()
{
}

QExtDoubleSpinBox::QExtDoubleSpinBox(QWidget *parent)
    : QDoubleSpinBox(parent)
    , dd_ptr(new QExtDoubleSpinBoxPrivate(this))
{
}

QExtDoubleSpinBox::QExtDoubleSpinBox(bool valueTextTrimed, QWidget *parent)
    : QDoubleSpinBox(parent)
    , dd_ptr(new QExtDoubleSpinBoxPrivate(this))
{
    this->setValueTextTrimedEnable(valueTextTrimed);
}

QExtDoubleSpinBox::~QExtDoubleSpinBox()
{
}

bool QExtDoubleSpinBox::isValueTextTrimedEnabled() const
{
    Q_D(const QExtDoubleSpinBox);
    return d->m_valueTextTrimedEnable;
}

void QExtDoubleSpinBox::setValueTextTrimedEnable(bool enable)
{
    Q_D(QExtDoubleSpinBox);
    if (enable != d->m_valueTextTrimedEnable)
    {
        d->m_valueTextTrimedEnable = enable;
        Q_EMIT this->valueTextTrimedEnableChanged(enable);
    }
}

double QExtDoubleSpinBox::valueFromText(const QString &text) const
{
    return QDoubleSpinBox::valueFromText(text);
}

QString QExtDoubleSpinBox::textFromValue(double val) const
{
    Q_D(const QExtDoubleSpinBox);
    QString text = QDoubleSpinBox::textFromValue(val);
    // qDebug() << "textFromValue():text=" << text;
    return d->m_valueTextTrimedEnable ? QExtNumeric::doubleTrimmedText(text) : text;
}
