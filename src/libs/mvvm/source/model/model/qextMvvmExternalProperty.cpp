// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmExternalProperty.h>

using namespace ModelView;

QEXTMvvmExternalProperty::QEXTMvvmExternalProperty() = default;

QEXTMvvmExternalProperty::QEXTMvvmExternalProperty(std::string text, QColor color, std::string id)
    : m_text(std::move(text)), m_color(std::move(color)), m_identifier(std::move(id))
{
}

QEXTMvvmExternalProperty QEXTMvvmExternalProperty::undefined()
{
    return QEXTMvvmExternalProperty("Undefined", QColor(Qt::red));
}

std::string QEXTMvvmExternalProperty::text() const
{
    return m_text;
}

QColor QEXTMvvmExternalProperty::color() const
{
    return m_color;
}

std::string QEXTMvvmExternalProperty::identifier() const
{
    return m_identifier;
}

bool QEXTMvvmExternalProperty::isValid() const
{
    return !(m_identifier.empty() && m_text.empty() && !m_color.isValid());
}

bool QEXTMvvmExternalProperty::operator==(const QEXTMvvmExternalProperty& other) const
{
    return m_identifier == other.m_identifier && m_text == other.m_text && m_color == other.m_color;
}

bool QEXTMvvmExternalProperty::operator!=(const QEXTMvvmExternalProperty& other) const
{
    return !(*this == other);
}

bool QEXTMvvmExternalProperty::operator<(const QEXTMvvmExternalProperty& other) const
{
    return m_identifier < other.m_identifier && m_text < other.m_text
           && m_color.name() < other.m_color.name();
}
