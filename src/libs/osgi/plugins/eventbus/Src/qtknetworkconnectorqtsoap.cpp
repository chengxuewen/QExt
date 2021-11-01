#include "qtknetworkconnectorqtsoap.h"
#include "qtkeventbusmanager.h"

#include <QTKPluginFramework/Service/Event/QTKEvent>
#include <QTKSOAP/QTKSoapName>
#include <QTKSOAP/QTKSoapArray>
#include <QTKSOAP/QTKSoapMessage>
#include <QTKSOAP/QTKSoapHttpTransport>
#include <QTKSOAP/QTKSoapSimpleType>

using namespace qtkeventbus;

QTKNetworkConnectorQtSoap::QTKNetworkConnectorQtSoap()
    : QTKNetworkConnector(),
      m_pHttp(nullptr),
      m_strWSDLUrl(""),
      m_pResponse(nullptr)
{
    m_strProtocol = "SOAP";
}

QTKNetworkConnectorQtSoap::~QTKNetworkConnectorQtSoap()
{
    if(m_pHttp) {
        delete m_pHttp;
    }
}

QTKNetworkConnector *QTKNetworkConnectorQtSoap::clone()
{
    QTKNetworkConnectorQtSoap *pCopy = new QTKNetworkConnectorQtSoap();
    return pCopy;
}

void QTKNetworkConnectorQtSoap::initializeForEventBus()
{
    qtkRegisterRemoteSignal("qtk/remote/eventBus/comunication/soap", this, "remoteCommunication(const QString, QTKEventArgumentsList *)");
    qtkRegisterRemoteCallback("qtk/remote/eventBus/comunication/soap", this, "send(const QString, QTKEventArgumentsList *)");
}


void QTKNetworkConnectorQtSoap::registerServerMethod(QString strMethodName, QList<QVariant::Type> types)
{
    m_mapRegisterMethods.insert(strMethodName, types);
}

void QTKNetworkConnectorQtSoap::createClient(const QString strHostName, const unsigned int uiPort)
{
    if(m_pHttp == nullptr) {
        m_pHttp = new QTKSoapHttpTransport();
        QObject::connect(m_pHttp, SIGNAL(responseReady()), this, SLOT(retrieveRemoteResponse()));
    }

    //maf3 service registration
    QList<QVariant::Type> listParametersForRegisterteredFunction;
    listParametersForRegisterteredFunction.append(QVariant::String); //return argument
    listParametersForRegisterteredFunction.append(QVariant::List); //parameters to send, event control parameters
    listParametersForRegisterteredFunction.append(QVariant::List); //parameters to send, data parameters

    //registration of the method REMOTE_COMMUNICATION_SOAP at Soap level
    // this method need to reflect the name of the action of the service while QVariant::List are list of
    // strings, in  which each string represent the correct name of the parameter in the sevice function.
    registerServerMethod("testArray", listParametersForRegisterteredFunction);

    //ARRAY TEST
    QTKSoapArray arr(QTKSoapName("arr", ""), QTKSoapType::String, 2);
    arr.insert(0, new QTKSoapSimpleType(QTKSoapName("name"), "First"));
    arr.insert(1, new QTKSoapSimpleType(QTKSoapName("surName"), "Second"));

    //exp
    /*QTKSoapArray arrEvent(QTKSoapName("arrEvent", ""), QTKSoapType::String, 2);
    arrEvent.insert(0, new QTKSoapSimpleType(QTKSoapName("n1"), "eventA1"));
    arrEvent.insert(1, new QTKSoapSimpleType(QTKSoapName("n2"), "eventA2"));

    QTKSoapArray arrData(QTKSoapName("arrData", ""), QTKSoapType::String, 2);
    arrData.insert(0, new QTKSoapSimpleType(QTKSoapName("d1"), "dataA1"));
    arrData.insert(1, new QTKSoapSimpleType(QTKSoapName("d2"), "dataA2"));*/
    //end exp

    m_pHttp->setHost(strHostName, false, uiPort);


    //ARRAY TEST
    // Set the method and add one argument.
    /*request.setMethod("algorithmSIBA");
    request.addMethodArgument("input", "", "input.aim");
    request.addMethodArgument("output", "", "output.aim");
    
    request.addMethodArgument("gaussian", "", "0.42");
    request.addMethodArgument("load", "", "8");
    request.addMethodArgument("iteration", "", "40");
    
    qDebug() << request.toXmlString();

    // Submit the request the the web service.
    m_Http->setHost("localhost", false, 7889);
    m_Http->setAction("algorithmSIBA");*/
    //m_Http->submitRequest(m_Request, "http://localhost:7889/HelloWordService?wsdl");

    // Set the method and add one argument.
    /*request.setMethod("getPopulation", "http://www.abundanttech.com/WebServices/Population");
    request.addMethodArgument("strCountry", "", "Italy");

    // Submit the request the the web service.
    m_Http->setHost("www.abundanttech.com");
    m_Http->setAction("http://www.abundanttech.com/WebServices/Population/getPopulation");
    m_Http->submitRequest(request, "/WebServices/Population/population.asmx");*/

    qDebug("retrieve value...");
}

void QTKNetworkConnectorQtSoap::createServer(const unsigned int uiPort)
{
    Q_UNUSED(uiPort);
    qDebug() << tr("QtSoap doesn't support server side implementation.").toLatin1();
}

void QTKNetworkConnectorQtSoap::stopServer()
{
    qDebug() << tr("QtSoap doesn't support server side implementation.").toLatin1();
}

void QTKNetworkConnectorQtSoap::startListen()
{
    qDebug() << tr("QtSoap doesn't support server side implementation.").toLatin1();
}

QTKSoapType *QTKNetworkConnectorQtSoap::marshall(const QString strName, const QVariant &parameter)
{
    QTKSoapType *pReturnValue = nullptr;
    switch( parameter.type() ){
    case QVariant::Int:
    {
        pReturnValue = new QTKSoapSimpleType(QTKSoapName(strName), QString::number(parameter.toInt()));
        break;
    }
    case QVariant::UInt:
    {
        pReturnValue = new QTKSoapSimpleType(QTKSoapName(strName), QString::number(parameter.toUInt()));
        break;
    }
    case QVariant::LongLong:
    {
        pReturnValue = new QTKSoapSimpleType(QTKSoapName(strName), QString::number(parameter.toLongLong()));
        break;
    }
    case QVariant::ULongLong:
    {
        pReturnValue = new QTKSoapSimpleType(QTKSoapName(strName), QString::number(parameter.toULongLong()));
        break;
    }
    case QVariant::Double:
    {
        pReturnValue = new QTKSoapSimpleType(QTKSoapName(strName), QString::number(parameter.toDouble()));
        break;
    }
    case QVariant::Bool:
    {
        pReturnValue = new QTKSoapSimpleType(QTKSoapName(strName), parameter.toBool()?"True":"False");
        break;
    }
    case QVariant::Date:
    {
        pReturnValue = new QTKSoapSimpleType(QTKSoapName(strName), parameter.toDate().toString());
        break;
    }
    case QVariant::DateTime:
    {
        pReturnValue = new QTKSoapSimpleType(QTKSoapName(strName), parameter.toDateTime().toString());
        break;
    }
    case QVariant::Time:
    {
        pReturnValue = new QTKSoapSimpleType(QTKSoapName(strName), parameter.toTime().toString());
        break;
    }
    case QVariant::StringList:
    case QVariant::List:
    {
        QTKSoapArray *pArr = new QTKSoapArray(QTKSoapName(strName, ""), QTKSoapType::String, parameter.toList().size());
        int iIndex = 0;
        foreach (QVariant item, parameter.toList()) {
            pArr->insert(iIndex, marshall(QString("Elem_").append(QString::number(iIndex)), item ));
            iIndex++;
        }
        pReturnValue = pArr;
        break;
    }
    case QVariant::Map:
    {
        QMap<QString, QVariant> map = parameter.toMap();
        QMap<QString, QVariant>::ConstIterator iter = map.begin();
        QTKSoapArray *pArr = new QTKSoapArray(QTKSoapName(strName, ""), QTKSoapType::String, parameter.toMap().size());
        int iIndex = 0;
        while(iter != map.end()) {
            pArr->insert(iIndex, marshall(iter.key(), *iter));
            ++iter;
            iIndex++;
        }
        pReturnValue = pArr;
        break;
    }
    case QVariant::Hash:
    {
        QHash<QString, QVariant> hash = parameter.toHash();
        QHash<QString, QVariant>::ConstIterator iter = hash.begin();
        QTKSoapArray *pArr = new QTKSoapArray(QTKSoapName(strName, ""), QTKSoapType::String, parameter.toHash().size());
        int iIndex = 0;
        while(iter != hash.end()) {
            pArr->insert(iIndex, marshall(iter.key(), *iter));
            ++iter;
            iIndex++;
        }
        pReturnValue = pArr;
        break;
    }
    case QVariant::ByteArray:
    {
        pReturnValue = new QTKSoapSimpleType(QTKSoapName(strName), parameter.toByteArray().data());
        break;
    }
    default:
    {
        if(parameter.canConvert(QVariant::String)) {
            pReturnValue = new QTKSoapSimpleType(QTKSoapName(strName), parameter.toString());
        } else {
            //self representation?
        }
        break;
    }
    }
    //ENSURE(returnValue != nullptr);
    return pReturnValue;
}

void QTKNetworkConnectorQtSoap::send(const QString strMethodName, QTKEventArgumentsList *pArgList) {
    //REQUIRE(!params->at(0).isNull());
    //REQUIRE(params->at(0).canConvert(QVariant::Hash) == true);

    QString strType = pArgList->at(0).name();
    if(pArgList == nullptr || strType != "qtkEventHash") {
        qDebug() << "nullptr or invalid argument, nothing to send!";
        return;
    }
    m_Request.clear();
    m_Request.setMethod(strMethodName);
    QTKEventHash *values;
    values = reinterpret_cast<QTKEventHash *> (pArgList->at(0).data());
    int iSize = values->size();
    for(int i = 0 ;i < iSize; i++) {
        m_Request.addMethodArgument(marshall(values->keys().at(i), values->values().at(i)));
    }
    qDebug() << m_Request.toXmlString();

    // Submit the request the the web service.
    m_pHttp->setAction(m_strAction);
    m_pHttp->submitRequest(m_Request, m_strPath);
}

void QTKNetworkConnectorQtSoap::retrieveRemoteResponse()
{
    // Get a reference to the response message.
    const QTKSoapMessage &message = m_pHttp->getResponse();
    qDebug() << message.toXmlString();
    // Check if the response is a SOAP Fault message
    if (message.isFault()) {
        qDebug("Error: %s", message.faultString().value().toString().toLatin1().constData());
        m_pResponse = nullptr;
    } else {
        // Get the return value, and print the result.
        m_pResponse = const_cast<QTKSoapType *>( &(message.returnValue()));
    }
}

