// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "model/model/comparators.h"
#include "model/model/comboproperty.h"
#include "model/model/customvariants.h"
#include "model/model/externalproperty.h"
#include "model/utils/reallimits.h"
#include <QMetaType>

using namespace ModelView;

bool Comparators::m_is_registered = false;

void Comparators::registerComparators()
{
    if (!m_is_registered) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        QMetaType::registerComparators<std::string>();
        QMetaType::registerComparators<std::vector<double>>();
        QMetaType::registerComparators<ComboProperty>();
        QMetaType::registerComparators<ExternalProperty>();
        QMetaType::registerComparators<RealLimits>();
        m_is_registered = true;
#endif

    }
}

bool Comparators::registered()
{
    return m_is_registered;
}
