#ifndef _QEXTPATTERNCOMMAND_H
#define _QEXTPATTERNCOMMAND_H

#include <qextPatternGlobal.h>
#include <qextPatternInterface.h>

class QEXT_PATTERN_API QExtPatternCommand : public QExtPatternCommandInterface, public QExtPatternObserverInterface
{
public:
    virtual void excute(QExtPatternNotificationInterface *notification);

    void notifyObserver(QExtPatternNotificationInterface *notification);
};

#endif // _QEXTPATTERNCOMMAND_H
