// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QUuid>
#include <qextMvvmUniqueIdGenerator.h>

using namespace ModelView;

identifier_type QEXTMvvmUniqueIdGenerator::generate()
{
    return QUuid::createUuid().toString().toStdString();
}
