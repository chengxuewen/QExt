// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_INTERFACES_EDITORFACTORYINTERFACE_H
#define MVVM_INTERFACES_EDITORFACTORYINTERFACE_H

#include <qextMvvmGlobal.h>
#include <memory>
#include <string>

class QModelIndex;
class QWidget;

namespace ModelView {

class QExtMvvmCustomEditor;

//! Interface for custom editor factory.
//! Intended for editor construction in cells of tables and trees in the context of delegate.

class QEXT_MVVM_API QExtMvvmEditorFactoryInterface {
public:
    virtual ~QExtMvvmEditorFactoryInterface() = default;

    virtual QExtUniquePointer<QExtMvvmCustomEditor> createEditor(const QModelIndex& index) const = 0;
};

} // namespace ModelView

#endif // MVVM_INTERFACES_EDITORFACTORYINTERFACE_H
