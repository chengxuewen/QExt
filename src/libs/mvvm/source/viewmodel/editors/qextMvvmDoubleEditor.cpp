#include <QDoubleSpinBox>
#include <QVBoxLayout>
#include <qextMvvmDoubleEditor.h>
#include <qextMvvmUtils.h>
#include <stdexcept>



QEXTMvvmDoubleEditor::QEXTMvvmDoubleEditor(QWidget* parent)
    : QEXTMvvmCustomEditor(parent), m_doubleEditor(new QDoubleSpinBox)
{
    setFocusPolicy(Qt::StrongFocus);
    m_doubleEditor->setFocusPolicy(Qt::StrongFocus);
    m_doubleEditor->setKeyboardTracking(false);

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(m_doubleEditor);

    connect(m_doubleEditor,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            [=] { this->onEditingFinished(); });

    setLayout(layout);

    setFocusProxy(m_doubleEditor);
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
    double new_value = m_doubleEditor->value();

    if (!QEXTMvvmUtils::AreAlmostEqual(new_value, m_data.value<double>()))
        setDataIntern(QVariant::fromValue(new_value));
}

void QEXTMvvmDoubleEditor::updateComponents()
{
    if (m_data.type() != QVariant::Double)
        throw std::runtime_error("QEXTMvvmDoubleEditor::update_components() -> Error. Wrong variant type");

    m_doubleEditor->setValue(m_data.value<double>());
}
