// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/model/externalproperty.h"

using namespace ModelView;

QExtMvvmExternalProperty::QExtMvvmExternalProperty() = default;

QExtMvvmExternalProperty::QExtMvvmExternalProperty(std::string text, QColor color, std::string id)
    : m_text(std::move(text)), m_color(std::move(color)), m_identifier(std::move(id))
{
}

QExtMvvmExternalProperty QExtMvvmExternalProperty::undefined()
{
    return QExtMvvmExternalProperty("Undefined", QColor(Qt::red));
}

std::string QExtMvvmExternalProperty::text() const
{
    return m_text;
}

QColor QExtMvvmExternalProperty::color() const
{
    return m_color;
}

std::string QExtMvvmExternalProperty::identifier() const
{
    return m_identifier;
}

bool QExtMvvmExternalProperty::isValid() const
{
    return !(m_identifier.empty() && m_text.empty() && !m_color.isValid());
}

bool QExtMvvmExternalProperty::operator==(const QExtMvvmExternalProperty& other) const
{
    return m_identifier == other.m_identifier && m_text == other.m_text && m_color == other.m_color;
}

bool QExtMvvmExternalProperty::operator!=(const QExtMvvmExternalProperty& other) const
{
    return !(*this == other);
}

bool QExtMvvmExternalProperty::operator<(const QExtMvvmExternalProperty& other) const
{
    return m_identifier < other.m_identifier && m_text < other.m_text
           && m_color.name() < other.m_color.name();
}
