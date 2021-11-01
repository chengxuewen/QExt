#ifndef QTKEVENTDISPATCHERLOCAL_H
#define QTKEVENTDISPATCHERLOCAL_H

#include "qtkeventdefinitions.h"
#include "qtkeventdispatcher.h"

namespace qtkeventbus {

class QTK_EVENTBUS_EXPORT QTKEventDispatcherLocal : public QTKEventDispatcher
{
    Q_OBJECT

public:
    QTKEventDispatcherLocal();

    virtual void notifyEvent(QTKBusEvent &eventDictionary, QTKEventArgumentsList *pArgList = nullptr,
                             QTKGenericReturnArgument *pReturnArg = nullptr) const;

protected:
    void initializeGlobalEvents();
};

} // namespace qtkeventbus

#endif // QTKEVENTDISPATCHERLOCAL_H
