#ifndef QTKEVENTDEFINITIONS_H
#define QTKEVENTDEFINITIONS_H

// Qt includes
#include <QByteArray>
#include <QList>
#include <QMap>
#include <QVariant>
#include <QString>
#include <QStringList>
#include <QHash>
#include <QThread>
#include <QThreadPool>
#include <QObject>
#include <QDebug>

#include "qtkeventbus_global.h"

//defines
#define TOPIC "event.topics"
#define TYPE "EventType"
#define SIGTYPE "SignatureType"
#define OBJECT "ObjectPointer"
#define SIGNATURE "Signature"

class QTKBusEvent;

#define qtkRegisterLocalSignal(topic, sender, signature) \
{\
    QTKBusEvent *properties = new QTKBusEvent(topic, qtkeventbus::QTKEventTypeLocal, qtkeventbus::QTKSignatureTypeSignal, static_cast<QObject*>(sender), signature); \
    bool ok = qtkeventbus::QTKEventBusManager::instance()->addEventProperty(*properties);\
    if(!ok) {\
    qWarning("%s", tr("Some problem occourred during the signal registration with ID '%1'.").arg(topic).toLatin1().data());\
    if(properties) {delete properties; properties = nullptr;} \
    }\
    }

#define qtkRegisterRemoteSignal(topic, sender, signature) \
{\
    QTKBusEvent *properties = new QTKBusEvent(topic, qtkeventbus::QTKEventTypeRemote, qtkeventbus::QTKSignatureTypeSignal, static_cast<QObject*>(sender), signature); \
    bool ok =  qtkeventbus::QTKEventBusManager::instance()->addEventProperty(*properties);\
    if(!ok) {\
    qWarning("%s", tr("Some problem occourred during the signal registration with ID '%1'.").arg(topic).toLatin1().data());\
    if(properties) {delete properties; properties = nullptr;} \
    }\
    }

#define qtkRegisterLocalCallback(topic, observer, signature) \
{\
    QTKBusEvent *properties = new QTKBusEvent(topic, qtkeventbus::QTKEventTypeLocal, qtkeventbus::QTKSignatureTypeCallback, static_cast<QObject*>(observer), signature); \
    bool ok =  qtkeventbus::QTKEventBusManager::instance()->addEventProperty(*properties);\
    if(!ok) {\
    qWarning("%s", tr("Some problem occourred during the callback registration with ID '%1'.").arg(topic).toLatin1().data());\
    if(properties) {delete properties; properties = nullptr;} \
    }\
    }

#define qtkRegisterRemoteCallback(topic, sender, signature) \
{\
    QTKBusEvent *properties = new QTKBusEvent(topic, qtkeventbus::QTKEventTypeRemote, qtkeventbus::QTKSignatureTypeCallback, static_cast<QObject*>(sender), signature); \
    bool ok =  qtkeventbus::QTKEventBusManager::instance()->addEventProperty(*properties);\
    if(!ok) {\
    qWarning("%s", tr("Some problem occourred during the callback registration with ID '%1'.").arg(topic).toLatin1().data());\
    if(properties) {delete properties; properties = nullptr;} \
    }\
    }


namespace qtkeventbus {
//forward classes
class QTKNetworkConnector;

/// Hash table that associate the communication protocol with the corresponding network connector class (Eg. XMLRPC, QTKEventBus::QTKNetworkConnectorQXMLRPC)
typedef QHash<QString, QTKNetworkConnector *> QTKNetworkConnectorHash;

/// typedef that represents dictionary entries ( key  , value )
typedef QHash<QString, QVariant> QTKEventHash;

///< Enum that identify the QTKEventType's type: Local or Remote.
typedef enum {
    QTKEventTypeLocal,
    QTKEventTypeRemote
} QTKEventType;

///< Enum that identify the mafSignatureType's type: Signal or Callback.
typedef enum {
    QTKSignatureTypeSignal = 0,
    QTKSignatureTypeCallback = 1
} QTKSignatureType;

/// List of the arguments to be sent through the event bus.
typedef QList<QGenericArgument> QTKEventArgumentsList;
typedef QTKEventArgumentsList * QTKEventArgumentsListPointer;
#define QTKEventArgument(type, data) QArgument<type >(#type, data)
#define QTKGenericReturnArgument QGenericReturnArgument
#define QTKEventReturnArgument(type, data) QReturnArgument<type >(#type, data)


/// Types definitions for events' hash (to be more readable).
typedef QHash<QString, QTKBusEvent *> QTKEventsHashType;

/// type definition for observers' properties list to be stored into the event's hash.
typedef QList<QTKBusEvent *> QTKEventItemListType;

/// map which represent list of function to be registered in the server, with parameters
typedef QMap<QString, QList<QVariant::Type> >  mafRegisterMethodsMap;

} // namespace QTKEventBus


Q_DECLARE_METATYPE(qtkeventbus::QTKEventArgumentsListPointer)
Q_DECLARE_METATYPE(qtkeventbus::mafRegisterMethodsMap)

#endif // QTKEVENTDEFINITIONS_H
