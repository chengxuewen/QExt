#ifndef _QEXTQUICK_H
#define _QEXTQUICK_H

#include <qextQuickGlobal.h>

#include <QObject>

class QEXT_QUICK_API QEXTQuick : public QObject
{
    Q_OBJECT
public:
    explicit QEXTQuick(QObject *parent = QEXT_DECL_NULLPTR);
    ~QEXTQuick();
};

#endif // _QEXTQUICK_H
