// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmBoolEditor.h>
#include <QCheckBox>
#include <QHBoxLayout>
#include <stdexcept>

namespace {
const QString true_text = "True";
const QString false_text = "False";
} // namespace

using namespace ModelView;

QExtMvvmBoolEditor::QExtMvvmBoolEditor(QWidget* parent) : QExtMvvmCustomEditor(parent), m_checkBox(new QCheckBox)

{
    setAutoFillBackground(true);
    auto layout = new QHBoxLayout;
    layout->setContentsMargins(4, 0, 0, 0);
    layout->addWidget(m_checkBox);
    setLayout(layout);

    connect(m_checkBox, &QCheckBox::toggled, this, &QExtMvvmBoolEditor::onCheckBoxChange);
    setFocusProxy(m_checkBox);
    m_checkBox->setText(true_text);
}

bool QExtMvvmBoolEditor::is_persistent() const
{
    return true;
}

void QExtMvvmBoolEditor::onCheckBoxChange(bool value)
{
    if (value != m_data.value<bool>())
        setDataIntern(QVariant(value));
}

void QExtMvvmBoolEditor::update_components()
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    if (m_data.type() != QVariant::Bool)
#else
    if (m_data.typeId() != QMetaType::Bool)
#endif
    {
        throw std::runtime_error("QExtMvvmBoolEditor::update_components() -> Error. Wrong variant type");
    }

    bool value = m_data.value<bool>();
    m_checkBox->blockSignals(true);
    m_checkBox->setChecked(value);
    m_checkBox->setText(value ? true_text : false_text);
    m_checkBox->blockSignals(false);
}
