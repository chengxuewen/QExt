#include <qextMvvmScientificSpinBoxEditor.h>
#include <qextMvvmScientificSpinBox.h>

#include <QVBoxLayout>
#include <QDebug>

QEXTMvvmScientificSpinBoxEditor::QEXTMvvmScientificSpinBoxEditor(QWidget *parent)
    : QEXTMvvmCustomEditor(parent),
      m_doubleEditor(new QEXTMvvmScientificSpinBox)
{
    this->setAutoFillBackground(true);
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

QEXTMvvmScientificSpinBoxEditor::~QEXTMvvmScientificSpinBoxEditor()
{

}

void QEXTMvvmScientificSpinBoxEditor::setRange(double minimum, double maximum)
{
    m_doubleEditor->setMinimum(minimum);
    m_doubleEditor->setMaximum(maximum);
}

void QEXTMvvmScientificSpinBoxEditor::setDecimals(int decimals)
{
    m_doubleEditor->setDecimals(decimals);
}

void QEXTMvvmScientificSpinBoxEditor::setSingleStep(double step)
{
    m_doubleEditor->setSingleStep(step);
}

bool QEXTMvvmScientificSpinBoxEditor::isPersistent() const
{
    return true;
}

void QEXTMvvmScientificSpinBoxEditor::onEditingFinished()
{
    double newValue = m_doubleEditor->value();
    if (qAbs(newValue - m_data.value<double>()) <= 0.1)
    {
        this->setDataIntern(QVariant::fromValue(newValue));
    }
}

void QEXTMvvmScientificSpinBoxEditor::updateComponents()
{
    if (m_data.type() != QVariant::Double)
    {
        qCritical() << "QEXTMvvmScientificDoubleEditor::updateComponents(): Wrong variant type";
        return;
    }
    m_doubleEditor->setValue(m_data.value<double>());
}
