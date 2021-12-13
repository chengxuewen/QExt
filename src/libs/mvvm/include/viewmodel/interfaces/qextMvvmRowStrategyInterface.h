// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_INTERFACES_ROWSTRATEGYINTERFACE_H
#define MVVM_INTERFACES_ROWSTRATEGYINTERFACE_H

#include <QStringList>
#include <memory>
#include <qextMvvmGlobal.h>
#include <vector>

namespace ModelView
{

class QEXTMvvmSessionItem;
class ViewItem;

//! Base class to construct row of ViewItem's from given QEXTMvvmSessionItem.
//! Used in context of AbstractViewModel while exposing SessionModel to Qt.

class QEXT_MVVM_API RowStrategyInterface
{
public:
    virtual ~RowStrategyInterface() = default;

    virtual QStringList horizontalHeaderLabels() const = 0;

    virtual std::vector<std::unique_ptr<ViewItem>> constructRow(QEXTMvvmSessionItem*) = 0;
};

} // namespace ModelView

#endif // MVVM_INTERFACES_ROWSTRATEGYINTERFACE_H
