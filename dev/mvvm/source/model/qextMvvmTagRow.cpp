// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <qextMvvmTagRow.h>

//! Constructs new tagrow representing next row in given tag.
//! No validity check.

ModelView::QExtMvvmTagRow ModelView::QExtMvvmTagRow::next() const
{
    return {tag, row + 1};
}

//! Constructs new tagrow representing previous row in given tag.
//! No validity check.

ModelView::QExtMvvmTagRow ModelView::QExtMvvmTagRow::prev() const
{
    return {tag, row - 1};
}

//! Returns QExtMvvmTagRow corresponding to the append to tag_name.
//! If tag_name =="" the default name will be used in QExtMvvmSessionItemTags context.

ModelView::QExtMvvmTagRow ModelView::QExtMvvmTagRow::append(const std::string& tag_name)
{
    return {tag_name, -1};
}

//! Returns QExtMvvmTagRow corresponding to prepending to tag_name.
//! If tag_name =="" the default name will be used in QExtMvvmSessionItemTags context.

ModelView::QExtMvvmTagRow ModelView::QExtMvvmTagRow::prepend(const std::string& tag_name)
{
    return {tag_name, 0};
}

bool ModelView::QExtMvvmTagRow::operator==(const ModelView::QExtMvvmTagRow& other) const
{
    return row == other.row && tag == other.tag;
}

bool ModelView::QExtMvvmTagRow::operator!=(const ModelView::QExtMvvmTagRow& other) const
{
    return !(*this == other);
}
