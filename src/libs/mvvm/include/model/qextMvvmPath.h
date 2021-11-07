#ifndef _QEXTMVVMPATH_H
#define _QEXTMVVMPATH_H

#include <qextMvvmGlobal.h>

#include <QString>
#include <QVector>

//! Supports navigation through QEXTMvvmModel. It contains a chain of row indexes that have to
//! be used to reach the desired QEXTMvvmItem starting from the root item.

class QEXT_MVVM_API QEXTMvvmPath
{
public:
    typedef int                         PathElement;
    typedef QVector<PathElement>        Container;
    typedef Container::ConstIterator    ConstIterator;
    typedef Container::Iterator         Iterator;

    QEXTMvvmPath() { }

    QString string() const;

    void append(PathElement element);
    void prepend(PathElement element);

    Iterator begin();
    ConstIterator begin() const;

    Iterator end();
    ConstIterator end() const;

    static QEXTMvvmPath fromString(const QString &str);
    static QEXTMvvmPath fromVector(const QVector<int> &data);

private:
    Container m_data;
};


#endif // _QEXTMVVMPATH_H
