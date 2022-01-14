// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QCheckBox>
#include <QHBoxLayout>
#include <qextMvvmBoolEditor.h>
#include <stdexcept>

namespace
{
const QString true_text = "True";
const QString false_text = "False";
} // namespace

using namespace ModelView;

QEXTMvvmBoolEditor::QEXTMvvmBoolEditor(QWidget* parent) : QEXTMvvmCustomEditor(parent), m_checkBox(new QCheckBox)

{
    setAutoFillBackground(true);
    auto layout = new QHBoxLayout;
    layout->setContentsMargins(4, 0, 0, 0);
    layout->addWidget(m_checkBox);
    setLayout(layout);

    connect(m_checkBox, &QCheckBox::toggled, this, &QEXTMvvmBoolEditor::onCheckBoxChange);
    setFocusProxy(m_checkBox);
    m_checkBox->setText(true_text);
}

bool QEXTMvvmBoolEditor::is_persistent() const
{
    return true;
}

void QEXTMvvmBoolEditor::onCheckBoxChange(bool value)
{
    if (value != m_data.value<bool>())
        setDataIntern(QVariant(value));
}

void QEXTMvvmBoolEditor::update_components()
{
    if (m_data.type() != QVariant::Bool)
        throw std::runtime_error("BoolEditor::update_components() -> Error. Wrong variant type");

    bool value = m_data.value<bool>();
    m_checkBox->blockSignals(true);
    m_checkBox->setChecked(value);
    m_checkBox->setText(value ? true_text : false_text);
    m_checkBox->blockSignals(false);
}
