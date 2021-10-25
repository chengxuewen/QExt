#include <qextMvvmDoubleEditor.h>

#include <QVBoxLayout>
#include <QDebug>

QEXTMvvmDoubleEditor::QEXTMvvmDoubleEditor(QWidget *parent)
    : QEXTMvvmCustomEditor(parent),
      m_doubleEditor(new QDoubleSpinBox)
{
    this->setFocusPolicy(Qt::StrongFocus);
    m_doubleEditor->setFocusPolicy(Qt::StrongFocus);
    m_doubleEditor->setKeyboardTracking(false);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_doubleEditor);

    connect(m_doubleEditor, SIGNAL(valueChanged(double)), this, SLOT(onEditingFinished()));

    this->setLayout(layout);
    this->setFocusProxy(m_doubleEditor);
}

QEXTMvvmDoubleEditor::~QEXTMvvmDoubleEditor()
{

}

void QEXTMvvmDoubleEditor::setRange(double minimum, double maximum)
{
    m_doubleEditor->setRange(minimum, maximum);
}

void QEXTMvvmDoubleEditor::setDecimals(int decimals)
{
    m_doubleEditor->setDecimals(decimals);
}

void QEXTMvvmDoubleEditor::setSingleStep(double value)
{
    m_doubleEditor->setSingleStep(value);
}

void QEXTMvvmDoubleEditor::onEditingFinished()
{
    double newValue = m_doubleEditor->value();
    if (qAbs(newValue - m_data.value<double>()) <= 0.1)
    {
        this->setDataIntern(QVariant::fromValue(newValue));
    }
}

void QEXTMvvmDoubleEditor::updateComponents()
{
    if (m_data.type() != QVariant::Double)
    {
        qCritical() << "QEXTMvvmDoubleEditor::updateComponents(): Wrong variant type";
        return;
    }

    m_doubleEditor->setValue(m_data.value<double>());
}
