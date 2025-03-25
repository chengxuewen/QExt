// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_TAGROW_H
#define MVVM_MODEL_TAGROW_H

#include <qextMvvmGlobal.h>
#include <string>

namespace ModelView {

//! Aggregate to hold (tag, row) information for QExtMvvmSessionModel.
//! row=-1 is a special value for appending to the end of the in the SessionIteTags context.

class QEXT_MVVM_API QExtMvvmTagRow {
public:
    std::string tag = {};
    int row = -1;

    QExtMvvmTagRow() {}

    QExtMvvmTagRow(const std::string& name, int row = -1) : tag(name), row(row) {}
    QExtMvvmTagRow(const char* name, int row = -1) : tag(name), row(row) {}

    QExtMvvmTagRow next() const;

    QExtMvvmTagRow prev() const;

    static QExtMvvmTagRow append(const std::string& tag_name = {});

    static QExtMvvmTagRow prepend(const std::string& tag_name = {});

    bool operator==(const QExtMvvmTagRow& other) const;
    bool operator!=(const QExtMvvmTagRow& other) const;
};

} // namespace ModelView

#endif // MVVM_MODEL_TAGROW_H
