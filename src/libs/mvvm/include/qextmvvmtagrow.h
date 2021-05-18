#ifndef QEXTMVVMTAGROW_H
#define QEXTMVVMTAGROW_H

#include <qextmvvmglobal.h>

#include <QString>



class QEXT_MVVM_API QEXTMvvmTagRow
{
public:
    QEXTMvvmTagRow() : tag(), row(-1) {}

    QEXTMvvmTagRow(const QString &name, int row = -1) : tag(name), row(row) {}
    QEXTMvvmTagRow(const char* name, int row = -1) : tag(name), row(row) {}

    QEXTMvvmTagRow next() const;
    QEXTMvvmTagRow prev() const;
    static QEXTMvvmTagRow append(const QString &tag_name = "");
    static QEXTMvvmTagRow prepend(const QString &tag_name = "");

    bool operator==(const QEXTMvvmTagRow &other) const;
    bool operator!=(const QEXTMvvmTagRow &other) const;

    QString tag;
    int row;
};



#endif // QEXTMVVMTAGROW_H
