#include <QVBoxLayout>
#include <qextMvvmScientificSpinbox.h>
#include <qextMvvmScientificSpinboxEditor.h>
#include <qextMvvmUtils.h>
#include <stdexcept>



QEXTMvvmScientificSpinBoxEditor::QEXTMvvmScientificSpinBoxEditor(QWidget *parent)
    : QEXTMvvmCustomEditor(parent), m_doubleEditor(new QEXTMvvmScientificSpinBox)
{
    setAutoFillBackground(true);
    setFocusPolicy(Qt::StrongFocus);
    m_doubleEditor->setFocusPolicy(Qt::StrongFocus);
    m_doubleEditor->setKeyboardTracking(false);

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(m_doubleEditor);

    connect(m_doubleEditor, &QEXTMvvmScientificSpinBox::valueChanged, [ = ] { this->onEditingFinished(); });

    setLayout(layout);

    setFocusProxy(m_doubleEditor);
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
    double new_value = m_doubleEditor->value();

    if (!QEXTMvvmUtils::AreAlmostEqual(new_value, m_data.value<double>()))
    {
        setDataIntern(QVariant::fromValue(new_value));
    }
}

void QEXTMvvmScientificSpinBoxEditor::updateComponents()
{
    if (m_data.type() != QVariant::Double)
        throw std::runtime_error(
            "QEXTMvvmScientificSpinBoxEditor::update_components() -> Error. Wrong variant type");

    m_doubleEditor->setValue(m_data.value<double>());
}
