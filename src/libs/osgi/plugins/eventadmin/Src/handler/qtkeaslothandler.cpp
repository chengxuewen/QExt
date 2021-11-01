#include "qtkeaslothandler_p.h"

void QTKEASlotHandler::updateProperties(const QTKDictionary &properties)
{
    if (m_serviceReg) {
        m_serviceReg.setProperties(properties);
    }
}

void QTKEASlotHandler::handleEvent(const QTKEvent &event)
{
    emit this->eventOccured(event);
}
