#include <qextMvvmTagRow.h>

//! Constructs new tagrow representing next row in given tag.
//! No validity check.

QEXTMvvmTagRow QEXTMvvmTagRow::next() const
{
    return {tag, row + 1};
}

//! Constructs new tagrow representing previous row in given tag.
//! No validity check.

QEXTMvvmTagRow QEXTMvvmTagRow::prev() const
{
    return {tag, row - 1};
}

//! Returns QEXTMvvmTagRow corresponding to the append to tag_name.
//! If tag_name =="" the default name will be used in QEXTMvvmItemTags context.

QEXTMvvmTagRow QEXTMvvmTagRow::append(const QString &tag_name)
{
    return {tag_name, -1};
}

//! Returns QEXTMvvmTagRow corresponding to prepending to tag_name.
//! If tag_name =="" the default name will be used in QEXTMvvmItemTags context.

QEXTMvvmTagRow QEXTMvvmTagRow::prepend(const QString &tag_name)
{
    return {tag_name, 0};
}

bool QEXTMvvmTagRow::operator==(const QEXTMvvmTagRow& other) const
{
    return row == other.row && tag == other.tag;
}

bool QEXTMvvmTagRow::operator!=(const QEXTMvvmTagRow& other) const
{
    return !(*this == other);
}
