#include <qextModelTagRow.h>

QExtModelTagRow::~QExtModelTagRow()
{

}

QExtModelTagRow &QExtModelTagRow::operator=(const QExtModelTagRow &other)
{
    if (this != &other)
    {
        tag = other.tag;
        row = other.row;
    }
    return *this;
}

bool QExtModelTagRow::operator==(const QExtModelTagRow &other) const
{
    if (this != &other)
    {
        return row == other.row && tag == other.tag;
    }
    return true;
}
