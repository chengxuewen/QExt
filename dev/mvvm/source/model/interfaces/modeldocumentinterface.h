// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_INTERFACES_MODELDOCUMENTINTERFACE_H
#define MVVM_INTERFACES_MODELDOCUMENTINTERFACE_H

#include <qextMvvmGlobal.h>
#include <string>

namespace ModelView {

//! Pure virtual interface to save and restore session models to/from disk.

class QEXT_MVVM_API QExtMvvmModelDocumentInterface {
public:
    virtual ~QExtMvvmModelDocumentInterface() = default;

    virtual void save(const std::string& file_name) const = 0;
    virtual void load(const std::string& file_name) = 0;
};

} // namespace ModelView

#endif // MVVM_INTERFACES_MODELDOCUMENTINTERFACE_H
