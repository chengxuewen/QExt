#ifndef _QEXTMVVMITEMCOPYSTRATEGY_H
#define _QEXTMVVMITEMCOPYSTRATEGY_H

#include <qextMvvmGlobal.h>

#include <QSharedPointer>

class QEXTMvvmItem;
class QEXT_MVVM_API QEXTMvvmItemCopyStrategy
{
public:
    virtual ~QEXTMvvmItemCopyStrategy() { }

    //! Creates item copy by deep copying all children. QEXTMvvmItem identifiers will be regenerated.
    virtual QEXTMvvmItem *createCopy(const QEXTMvvmItem *item) const = 0;
};


#endif // _QEXTMVVMITEMCOPYSTRATEGY_H
