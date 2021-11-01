#include <qextMvvmTagRow.h>

//! Constructs new tagrow representing next row in given tag.
//! No validity check.

ModelView::QEXTMvvmTagRow ModelView::QEXTMvvmTagRow::next() const
{
    return {tag, row + 1};
}

//! Constructs new tagrow representing previous row in given tag.
//! No validity check.

ModelView::QEXTMvvmTagRow ModelView::QEXTMvvmTagRow::prev() const
{
    return {tag, row - 1};
}

//! Returns QEXTMvvmTagRow corresponding to the append to tag_name.
//! If tag_name =="" the default name will be used in QEXTMvvmSessionItemTags context.

ModelView::QEXTMvvmTagRow ModelView::QEXTMvvmTagRow::append(const std::string& tag_name)
{
    return {tag_name, -1};
}

//! Returns QEXTMvvmTagRow corresponding to prepending to tag_name.
//! If tag_name =="" the default name will be used in QEXTMvvmSessionItemTags context.

ModelView::QEXTMvvmTagRow ModelView::QEXTMvvmTagRow::prepend(const std::string& tag_name)
{
    return {tag_name, 0};
}

bool ModelView::QEXTMvvmTagRow::operator==(const ModelView::QEXTMvvmTagRow& other) const
{
    return row == other.row && tag == other.tag;
}

bool ModelView::QEXTMvvmTagRow::operator!=(const ModelView::QEXTMvvmTagRow& other) const
{
    return !(*this == other);
}
