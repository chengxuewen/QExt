#ifndef DSTYLEFACTORY_H
#define DSTYLEFACTORY_H

#include "dtkstyle_global.h"
#include <QStyle>

class DTK_STYLE_EXPORT DStyleFactory
{
public:
    DStyleFactory();

    static QStyle *create(const QString &key);
};

#endif // DSTYLEFACTORY_H
