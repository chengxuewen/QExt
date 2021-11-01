#ifndef _QEXTMVVMTAGROW_H
#define _QEXTMVVMTAGROW_H

#include <qextMvvmGlobal.h>
#include <string>

namespace ModelView
{

//! Aggregate to hold (tag, row) information for QEXTMvvmSessionModel.

class QEXT_MVVM_API QEXTMvvmTagRow
{
public:
    std::string tag = {};
    int row = -1;

    QEXTMvvmTagRow() {}

    QEXTMvvmTagRow(const std::string& name, int row = -1) : tag(name), row(row) {}
    QEXTMvvmTagRow(const char* name, int row = -1) : tag(name), row(row) {}

    QEXTMvvmTagRow next() const;

    QEXTMvvmTagRow prev() const;

    static QEXTMvvmTagRow append(const std::string& tag_name = {});

    static QEXTMvvmTagRow prepend(const std::string& tag_name = {});

    bool operator==(const QEXTMvvmTagRow& other) const;
    bool operator!=(const QEXTMvvmTagRow& other) const;
};

} // namespace ModelView

#endif // _QEXTMVVMTAGROW_H
