#ifndef _QEXTMVCCOMMAND_H
#define _QEXTMVCCOMMAND_H

#include <qextPatternsGlobal.h>
#include <qextMVCInterface.h>

class QEXT_PATTERNS_API QExtMVCCommand : public QExtMVCCommandInterface, public QExtMVCObserverInterface
{
public:
    virtual void excute(QExtMVCNotificationInterface *notification);

    void notifyObserver(QExtMVCNotificationInterface *notification);
};

#endif // _QEXTMVCCOMMAND_H
