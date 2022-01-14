// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QMetaType>
#include <qextMvvmComboProperty.h>
#include <qextMvvmComparators.h>
#include <qextMvvmCustomVariants.h>
#include <qextMvvmExternalProperty.h>
#include <qextMvvmRealLimits.h>

using namespace ModelView;

bool QEXTMvvmComparators::m_is_registered = false;

void QEXTMvvmComparators::registerComparators()
{
    if (!m_is_registered) {
        QMetaType::registerComparators<std::string>();
        QMetaType::registerComparators<std::vector<double>>();
        QMetaType::registerComparators<QEXTMvvmComboProperty>();
        QMetaType::registerComparators<QEXTMvvmExternalProperty>();
        QMetaType::registerComparators<QEXTMvvmRealLimits>();
        m_is_registered = true;
    }
}

bool QEXTMvvmComparators::registered()
{
    return m_is_registered;
}
