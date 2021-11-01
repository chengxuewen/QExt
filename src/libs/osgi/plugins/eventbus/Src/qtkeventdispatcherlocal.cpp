#include "qtkeventdispatcherlocal.h"
#include "qtkbusevent.h"

using namespace qtkeventbus;

QTKEventDispatcherLocal::QTKEventDispatcherLocal()
    : QTKEventDispatcher()
{
    this->initializeGlobalEvents();
}

void QTKEventDispatcherLocal::initializeGlobalEvents()
{
    QTKBusEvent *pProperties = new QTKBusEvent("QTK/local/eventBus/globalUpdate", QTKEventTypeLocal,QTKSignatureTypeSignal,
                                               this, "notifyDefaultEvent()");
    this->registerSignal(*pProperties);
    QTKEventDispatcher::initializeGlobalEvents();
}

void QTKEventDispatcherLocal::notifyEvent(QTKBusEvent &eventDictionary, QTKEventArgumentsList *pArgList,
                                          QTKGenericReturnArgument *pReturnArg) const
{
    QString strTopic = eventDictionary[TOPIC].toString();
    QTKEventItemListType items = signalItemProperty(strTopic);
    foreach(QTKBusEvent *pItemEventProp, items) {
        if((*pItemEventProp)[SIGNATURE].toString().length() != 0) {
            QString strSignalToEmit = (*pItemEventProp)[SIGNATURE].toString().split("(")[0];
            QObject *pObj = (*pItemEventProp)[OBJECT].value<QObject *>();
            if(pArgList != nullptr) {
                if (pReturnArg == nullptr || pReturnArg->data() == nullptr) { //don't use return value
                    switch (pArgList->count()) {
                    case 0:
                    {
                        this->metaObject()->invokeMethod(pObj, strSignalToEmit.toLatin1());
                        break;
                    }
                    case 1:
                    {
                        this->metaObject()->invokeMethod(pObj, strSignalToEmit.toLatin1(), pArgList->at(0));
                        break;
                    }
                    case 2:
                    {
                        this->metaObject()->invokeMethod(pObj, strSignalToEmit.toLatin1(), pArgList->at(0),
                                                         pArgList->at(1));
                        break;
                    }
                    case 3:
                    {
                        this->metaObject()->invokeMethod(pObj, strSignalToEmit.toLatin1(), pArgList->at(0),
                                                         pArgList->at(1), pArgList->at(2));
                        break;
                    }
                    case 4:
                    {
                        this->metaObject()->invokeMethod(pObj, strSignalToEmit.toLatin1(), pArgList->at(0),
                                                         pArgList->at(1), pArgList->at(2), pArgList->at(3));
                        break;
                    }
                    case 5:
                    {
                        this->metaObject()->invokeMethod(pObj, strSignalToEmit.toLatin1(), pArgList->at(0),
                                                         pArgList->at(1), pArgList->at(2), pArgList->at(3),
                                                         pArgList->at(4));
                        break;
                    }
                    case 6:
                    {
                        this->metaObject()->invokeMethod(pObj, strSignalToEmit.toLatin1(), pArgList->at(0),
                                                         pArgList->at(1), pArgList->at(2), pArgList->at(3),
                                                         pArgList->at(4), pArgList->at(5));
                        break;
                    }
                    case 7:
                    {
                        this->metaObject()->invokeMethod(pObj, strSignalToEmit.toLatin1(), pArgList->at(0),
                                                         pArgList->at(1), pArgList->at(2), pArgList->at(3),
                                                         pArgList->at(4), pArgList->at(5), pArgList->at(6));
                        break;
                    }
                    case 8:
                    {
                        this->metaObject()->invokeMethod(pObj, strSignalToEmit.toLatin1(), pArgList->at(0),
                                                         pArgList->at(1), pArgList->at(2), pArgList->at(3),
                                                         pArgList->at(4), pArgList->at(5), pArgList->at(6),
                                                         pArgList->at(7));
                        break;
                    }
                    case 9:
                    {
                        this->metaObject()->invokeMethod(pObj, strSignalToEmit.toLatin1(), pArgList->at(0),
                                                         pArgList->at(1), pArgList->at(2), pArgList->at(3),
                                                         pArgList->at(4), pArgList->at(5), pArgList->at(6),
                                                         pArgList->at(7), pArgList->at(8));
                        break;
                    }
                    case 10:
                    {
                        this->metaObject()->invokeMethod(pObj, strSignalToEmit.toLatin1(), pArgList->at(0),
                                                         pArgList->at(1), pArgList->at(2), pArgList->at(3),
                                                         pArgList->at(4), pArgList->at(5), pArgList->at(6),
                                                         pArgList->at(7), pArgList->at(8), pArgList->at(9));
                        break;
                    }
                    default:
                        qWarning("%s", tr("Number of arguments not supported. Max 10 arguments").toLatin1().data());
                    } //switch
                } else { //use return value
                    switch (pArgList->count()) {
                    case 0:
                    {
                        this->metaObject()->invokeMethod(pObj, strSignalToEmit.toLatin1(), *pReturnArg);
                        break;
                    }
                    case 1:
                    {
                        this->metaObject()->invokeMethod(pObj, strSignalToEmit.toLatin1(), *pReturnArg,
                                                         pArgList->at(0));
                        break;
                    }
                    case 2:
                    {
                        this->metaObject()->invokeMethod(pObj, strSignalToEmit.toLatin1(), *pReturnArg,
                                                         pArgList->at(0), pArgList->at(1));
                        break;
                    }
                    case 3:
                    {
                        this->metaObject()->invokeMethod(pObj, strSignalToEmit.toLatin1(), *pReturnArg,
                                                         pArgList->at(0), pArgList->at(1), pArgList->at(2));
                        break;
                    }
                    case 4:
                    {
                        this->metaObject()->invokeMethod(pObj, strSignalToEmit.toLatin1(), *pReturnArg,
                                                         pArgList->at(0), pArgList->at(1), pArgList->at(2),
                                                         pArgList->at(3));
                        break;
                    }
                    case 5:
                    {
                        this->metaObject()->invokeMethod(pObj, strSignalToEmit.toLatin1(), *pReturnArg,
                                                         pArgList->at(0), pArgList->at(1), pArgList->at(2),
                                                         pArgList->at(3), pArgList->at(4));
                        break;
                    }
                    case 6:
                    {
                        this->metaObject()->invokeMethod(pObj, strSignalToEmit.toLatin1(), *pReturnArg,
                                                         pArgList->at(0), pArgList->at(1), pArgList->at(2),
                                                         pArgList->at(3), pArgList->at(4), pArgList->at(5));
                        break;
                    }
                    case 7:
                    {
                        this->metaObject()->invokeMethod(pObj, strSignalToEmit.toLatin1(), *pReturnArg,
                                                         pArgList->at(0), pArgList->at(1), pArgList->at(2),
                                                         pArgList->at(3), pArgList->at(4), pArgList->at(5),
                                                         pArgList->at(6));
                        break;
                    }
                    case 8:
                    {
                        this->metaObject()->invokeMethod(pObj, strSignalToEmit.toLatin1(), *pReturnArg,
                                                         pArgList->at(0), pArgList->at(1), pArgList->at(2),
                                                         pArgList->at(3), pArgList->at(4), pArgList->at(5),
                                                         pArgList->at(6), pArgList->at(7));
                        break;
                    }
                    case 9:
                    {
                        this->metaObject()->invokeMethod(pObj, strSignalToEmit.toLatin1(), *pReturnArg,
                                                         pArgList->at(0), pArgList->at(1), pArgList->at(2),
                                                         pArgList->at(3), pArgList->at(4), pArgList->at(5),
                                                         pArgList->at(6), pArgList->at(7), pArgList->at(8));
                        break;
                    }
                    case 10:
                    {
                        this->metaObject()->invokeMethod(pObj, strSignalToEmit.toLatin1(), *pReturnArg,
                                                         pArgList->at(0), pArgList->at(1), pArgList->at(2),
                                                         pArgList->at(3), pArgList->at(4), pArgList->at(5),
                                                         pArgList->at(6), pArgList->at(7), pArgList->at(8),
                                                         pArgList->at(9));
                        break;
                    }
                    default:
                        qWarning("%s", tr("Number of arguments not supported. Max 10 arguments").toLatin1().data());
                    } //switch
                }
            } else {
                if (pReturnArg == nullptr || pReturnArg->data() == nullptr) { //don't use return value
                    this->metaObject()->invokeMethod(pObj, strSignalToEmit.toLatin1());
                } else {
                    this->metaObject()->invokeMethod(pObj, strSignalToEmit.toLatin1(), *pReturnArg);
                }
            }
        }
    }
}

