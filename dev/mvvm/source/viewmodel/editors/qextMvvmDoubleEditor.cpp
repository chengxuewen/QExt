// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmDoubleEditor.h>
#include <qextMvvmNumericUtils.h>
#include <QDoubleSpinBox>
#include <QVBoxLayout>
#include <stdexcept>

using namespace ModelView;

QExtMvvmDoubleEditor::QExtMvvmDoubleEditor(QWidget* parent)
    : QExtMvvmCustomEditor(parent), m_doubleEditor(new QDoubleSpinBox)
{
    setFocusPolicy(Qt::StrongFocus);
    m_doubleEditor->setFocusPolicy(Qt::StrongFocus);
    m_doubleEditor->setKeyboardTracking(false);

    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    layout->addWidget(m_doubleEditor);

    connect(m_doubleEditor,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            [=] { this->onEditingFinished(); });

    setLayout(layout);

    setFocusProxy(m_doubleEditor);
}

void QExtMvvmDoubleEditor::setRange(double minimum, double maximum)
{
    m_doubleEditor->setRange(minimum, maximum);
}

void QExtMvvmDoubleEditor::setDecimals(int decimals)
{
    m_doubleEditor->setDecimals(decimals);
}

void QExtMvvmDoubleEditor::setSingleStep(double value)
{
    m_doubleEditor->setSingleStep(value);
}

void QExtMvvmDoubleEditor::onEditingFinished()
{
    double new_value = m_doubleEditor->value();

    if (!Utils::AreAlmostEqual(new_value, m_data.value<double>()))
        setDataIntern(QVariant::fromValue(new_value));
}

void QExtMvvmDoubleEditor::update_components()
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    if (m_data.type() != QVariant::Double)
#else
    if (m_data.typeId() != QMetaType::Double)
#endif
    {
        throw std::runtime_error("QExtMvvmDoubleEditor::update_components() -> Error. Wrong variant type");
    }

    m_doubleEditor->setValue(m_data.value<double>());
}
