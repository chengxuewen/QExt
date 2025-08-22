#include <qextDoubleSpinBox.h>
#include <qextNumeric.h>

#include <QDebug>
#include <QLineEdit>
#include <QKeyEvent>

class QExtDoubleSpinBoxPrivate
{
public:
    typedef QExtDoubleSpinBox::CursorMoveTriggerFlags CursorMoveTriggerFlags;

    explicit QExtDoubleSpinBoxPrivate(QExtDoubleSpinBox *q);
    virtual ~QExtDoubleSpinBoxPrivate();

    QExtDoubleSpinBox * const q_ptr;

    bool mValueTextTrimedEnable;
    CursorMoveTriggerFlags mCursorMoveTriggerFlags;

private:
    Q_DECLARE_PUBLIC(QExtDoubleSpinBox)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtDoubleSpinBoxPrivate)
};

QExtDoubleSpinBoxPrivate::QExtDoubleSpinBoxPrivate(QExtDoubleSpinBox *q)
    : q_ptr(q)
    , mValueTextTrimedEnable(false)
    , mCursorMoveTriggerFlags(0)
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

QExtDoubleSpinBox::QExtDoubleSpinBox(bool valueTextTrimed, CursorMoveTriggerFlags flags, QWidget *parent)
    : QDoubleSpinBox(parent)
    , dd_ptr(new QExtDoubleSpinBoxPrivate(this))
{
    this->setValueTextTrimedEnable(valueTextTrimed);
    this->setCursorMoveTriggerFlags(flags);
}

QExtDoubleSpinBox::~QExtDoubleSpinBox()
{
}

bool QExtDoubleSpinBox::isValueTextTrimedEnabled() const
{
    Q_D(const QExtDoubleSpinBox);
    return d->mValueTextTrimedEnable;
}

void QExtDoubleSpinBox::setValueTextTrimedEnable(bool enable)
{
    Q_D(QExtDoubleSpinBox);
    if (enable != d->mValueTextTrimedEnable)
    {
        d->mValueTextTrimedEnable = enable;
        Q_EMIT this->valueTextTrimedEnableChanged(enable);
    }
}

QExtDoubleSpinBox::CursorMoveTriggerFlags QExtDoubleSpinBox::cursorMoveTriggerFlags() const
{
    Q_D(const QExtDoubleSpinBox);
    return d->mCursorMoveTriggerFlags;
}

void QExtDoubleSpinBox::setCursorMoveTriggerFlags(QExtDoubleSpinBox::CursorMoveTriggerFlags flags)
{
    Q_D(QExtDoubleSpinBox);
    if (flags != d->mCursorMoveTriggerFlags)
    {
        d->mCursorMoveTriggerFlags = flags;
        Q_EMIT this->cursorMoveTriggerFlagsChanged(flags);
    }
}

double QExtDoubleSpinBox::valueFromText(const QString &text) const
{
    return QDoubleSpinBox::valueFromText(text);
}

QString QExtDoubleSpinBox::textFromValue(double val) const
{
    Q_D(const QExtDoubleSpinBox);
    const QString text = QDoubleSpinBox::textFromValue(val);
    // qDebug() << "textFromValue():text=" << text;
    return d->mValueTextTrimedEnable ? QExtNumeric::doubleTrimmedText(text) : text;
}

void QExtDoubleSpinBox::keyPressEvent(QKeyEvent *event)
{
    Q_D(QExtDoubleSpinBox);
    if (Qt::Key_Right == event->key() && d->mCursorMoveTriggerFlags.testFlag(CursorMoveTrigger_RightKey))
    {
        QLineEdit *lineEdit = this->lineEdit();
        const QString text = lineEdit->text();
        if (lineEdit->selectedText() == text)
        {
            lineEdit->setCursorPosition(text.length());
            return;
        }
    }
    QDoubleSpinBox::keyPressEvent(event);
}
