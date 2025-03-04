// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_PATH_H
#define MVVM_MODEL_PATH_H

#include <qextMvvmGlobal.h>
#include <string>
#include <vector>

namespace ModelView {

//! Supports navigation through QExtMvvmSessionModel. Contains a chain of indexes that have to
//! be used to reach the desired QExtMvvmSessionItem starting from the root item. QExtMvvmPath class plays
//! a role of simplified QModelIndex for QExtMvvmSessionModel. Used for undo/redo only.

//! Example of tree:
//! - root              path:""
//!   - child           path:"0"
//!     - grandchild    path:"0,0"
//!     - grandchild    path:"0,1"
//!   - child           path:"1"

class QEXT_MVVM_API QExtMvvmPath {
public:
    using PathElement = int;
    using container_t = std::vector<PathElement>;
    using iterator = container_t::iterator;
    using const_iterator = container_t::const_iterator;

    QExtMvvmPath() = default;

    static QExtMvvmPath fromString(const std::string& str);

    static QExtMvvmPath fromVector(const std::vector<int>& data);

    std::string str() const;

    void append(PathElement element);
    void prepend(PathElement element);

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

private:
    container_t m_data;
};

} // namespace ModelView

#endif // MVVM_MODEL_PATH_H
