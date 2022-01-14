// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QDoubleValidator>
#include <QLineEdit>
#include <QVBoxLayout>
#include <qextMvvmScientificDoubleEditor.h>
#include <qextMvvmNumericUtils.h>
#include <stdexcept>

namespace
{
const int max_digits = 1000;
}

using namespace ModelView;

QEXTMvvmScientificDoubleEditor::QEXTMvvmScientificDoubleEditor(QWidget* parent)
    : QEXTMvvmCustomEditor(parent), m_lineEdit(new QLineEdit)

{
    setAutoFillBackground(true);

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(m_lineEdit);

    m_validator = new QDoubleValidator(0.0, std::numeric_limits<double>::max(), max_digits, this);
    m_validator->setNotation(QDoubleValidator::ScientificNotation);
    m_lineEdit->setValidator(m_validator);

    connect(m_lineEdit, &QLineEdit::editingFinished, this,
            &QEXTMvvmScientificDoubleEditor::onEditingFinished);

    setLayout(layout);
}

void QEXTMvvmScientificDoubleEditor::setRange(double minimum, double maximum)
{
    m_validator->setRange(minimum, maximum, max_digits);
}

void QEXTMvvmScientificDoubleEditor::onEditingFinished()
{
    double new_value = m_lineEdit->text().toDouble();

    if (!QEXTMvvmUtils::AreAlmostEqual(new_value, m_data.value<double>()))
        setDataIntern(QVariant::fromValue(new_value));
}

void QEXTMvvmScientificDoubleEditor::update_components()
{
    if (m_data.type() != QVariant::Double)
        throw std::runtime_error(
            "ScientificDoubleEditor::update_components() -> Error. Wrong variant type");

    m_lineEdit->setText(QString::number(m_data.value<double>(), 'g'));
}
