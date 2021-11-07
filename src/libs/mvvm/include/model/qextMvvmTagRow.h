#ifndef _QEXTMVVMTAGROW_H
#define _QEXTMVVMTAGROW_H

#include <qextMvvmGlobal.h>

#include <QString>

//! Aggregate to hold (tag, row) information for QEXTMvvmModel.

class QEXT_MVVM_API QEXTMvvmTagRow
{
public:
    QString tag = {};
    int row = -1;

    QEXTMvvmTagRow() {}

    QEXTMvvmTagRow(const QString &name, int row = -1) : tag(name), row(row) {}
    QEXTMvvmTagRow(const char* name, int row = -1) : tag(name), row(row) {}

    QEXTMvvmTagRow next() const;

    QEXTMvvmTagRow prev() const;

    static QEXTMvvmTagRow append(const QString& tag_name = QString());

    static QEXTMvvmTagRow prepend(const QString& tag_name = QString());

    bool operator==(const QEXTMvvmTagRow& other) const;
    bool operator!=(const QEXTMvvmTagRow& other) const;
};


#endif // _QEXTMVVMTAGROW_H
