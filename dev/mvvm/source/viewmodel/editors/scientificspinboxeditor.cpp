// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "viewmodel/editors/scientificspinboxeditor.h"
#include "viewmodel/editors/scientificspinbox.h"
#include "model/utils/numericutils.h"
#include <QVBoxLayout>
#include <stdexcept>

using namespace ModelView;

QExtMvvmScientificSpinBoxEditor::QExtMvvmScientificSpinBoxEditor(QWidget* parent)
    : QExtMvvmCustomEditor(parent), m_doubleEditor(new QExtMvvmScientificSpinBox)
{
    setAutoFillBackground(true);
    setFocusPolicy(Qt::StrongFocus);
    m_doubleEditor->setFocusPolicy(Qt::StrongFocus);
    m_doubleEditor->setKeyboardTracking(false);

    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    layout->addWidget(m_doubleEditor);

    connect(m_doubleEditor, &QExtMvvmScientificSpinBox::valueChanged, [=] { this->onEditingFinished(); });

    setLayout(layout);

    setFocusProxy(m_doubleEditor);
}

void QExtMvvmScientificSpinBoxEditor::setRange(double minimum, double maximum)
{
    m_doubleEditor->setMinimum(minimum);
    m_doubleEditor->setMaximum(maximum);
}

void QExtMvvmScientificSpinBoxEditor::setDecimals(int decimals)
{
    m_doubleEditor->setDecimals(decimals);
}

void QExtMvvmScientificSpinBoxEditor::setSingleStep(double step)
{
    m_doubleEditor->setSingleStep(step);
}

bool QExtMvvmScientificSpinBoxEditor::is_persistent() const
{
    return true;
}

void QExtMvvmScientificSpinBoxEditor::onEditingFinished()
{
    double new_value = m_doubleEditor->value();

    if (!Utils::AreAlmostEqual(new_value, m_data.value<double>()))
        setDataIntern(QVariant::fromValue(new_value));
}

void QExtMvvmScientificSpinBoxEditor::update_components()
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    if (m_data.type() != QVariant::Double)
#else
    if (m_data.typeId() != QMetaType::Double)
#endif
    {
        throw std::runtime_error(
            "QExtMvvmScientificSpinBoxEditor::UpdateComponents() -> Error. Wrong variant type");
    }
}
