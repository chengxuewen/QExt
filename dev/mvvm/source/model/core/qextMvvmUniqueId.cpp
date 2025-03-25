// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmUniqueId.h>
#include <QUuid>

using namespace ModelView;

QExtMvvmIdentifierType QExtMvvmUniqueIdGenerator::generate()
{
    return QUuid::createUuid().toString().toStdString();
}
