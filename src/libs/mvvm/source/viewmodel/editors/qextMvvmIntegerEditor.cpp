#include <QSpinBox>
#include <QVBoxLayout>
#include <cmath>
#include <qextMvvmIntegerEditor.h>
#include <stdexcept>

namespace
{
const int max_val = 65536;
const int min_val = -max_val;
} // namespace



QEXTMvvmIntegerEditor::QEXTMvvmIntegerEditor(QWidget* parent) : QEXTMvvmCustomEditor(parent), m_intEditor(new QSpinBox)
{
    setAutoFillBackground(true);
    m_intEditor->setFocusPolicy(Qt::StrongFocus);
    m_intEditor->setKeyboardTracking(false);
    m_intEditor->setRange(min_val, max_val);

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(m_intEditor);

    connect(m_intEditor, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            [=] { this->onEditingFinished(); });

    setLayout(layout);

    setFocusProxy(m_intEditor);
}

void QEXTMvvmIntegerEditor::setRange(int minimum, int maximum)
{
    m_intEditor->setRange(minimum, maximum);
}

void QEXTMvvmIntegerEditor::onEditingFinished()
{
    int new_value = m_intEditor->value();
    if (new_value != m_data.value<int>())
        setDataIntern(QVariant::fromValue(new_value));
}

void QEXTMvvmIntegerEditor::updateComponents()
{
    if (m_data.type() != QVariant::Int)
        throw std::runtime_error("QEXTMvvmIntegerEditor::update_components() -> Error. Wrong variant type");

    m_intEditor->setValue(m_data.value<int>());
}
