#include <qextmvvmtagrow.h>

#include <QDebug>

QEXT_USE_NAMESPACE

QEXTMvvmTagRow QEXTMvvmTagRow::next() const
{
    return QEXTMvvmTagRow(tag, row + 1);
}

QEXTMvvmTagRow QEXTMvvmTagRow::prev() const
{
    return QEXTMvvmTagRow(tag, row - 1);
}

QEXTMvvmTagRow QEXTMvvmTagRow::append(const QString &tag_name)
{
    return QEXTMvvmTagRow(tag_name, -1);
}

QEXTMvvmTagRow QEXTMvvmTagRow::prepend(const QString &tag_name)
{
    return QEXTMvvmTagRow(tag_name, 0);
}

bool QEXTMvvmTagRow::operator==(const QEXTMvvmTagRow &other) const
{
    return row == other.row && tag == other.tag;
}

bool QEXTMvvmTagRow::operator!=(const QEXTMvvmTagRow &other) const
{
    return !(*this == other);
}
