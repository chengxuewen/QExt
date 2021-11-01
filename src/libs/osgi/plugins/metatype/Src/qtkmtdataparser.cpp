#include "qtkmtdataparser_p.h"
#include "qtkattributedefinitionimpl_p.h"
#include "qtkmtmsg_p.h"

#include <QTKPluginFramework/Service/Log/QTKLogService>

#include <QCoreApplication>
#include <QDebug>

const QString QTKMTDataParser::METADATA = "MetaData";
const QString QTKMTDataParser::LOCALIZATION = "localization";
const QString QTKMTDataParser::CONTEXT = "context";
const QString QTKMTDataParser::OCD = "OCD";
const QString QTKMTDataParser::ICON = "Icon";
const QString QTKMTDataParser::AD = "AD";
const QString QTKMTDataParser::CARDINALITY = "cardinality";
const QString QTKMTDataParser::OPTION = "Option";
const QString QTKMTDataParser::LABEL = "label";
const QString QTKMTDataParser::VALUE = "value";
const QString QTKMTDataParser::MIN = "min";
const QString QTKMTDataParser::MAX = "max";
const QString QTKMTDataParser::TYPE = "type";
const QString QTKMTDataParser::SIZE = "size";
const QString QTKMTDataParser::ID = "id";
const QString QTKMTDataParser::NAME = "name";
const QString QTKMTDataParser::DESCRIPTION = "description";
const QString QTKMTDataParser::RESOURCE = "resource";
const QString QTKMTDataParser::PID = "pid";
const QString QTKMTDataParser::DEFAULT = "default";
const QString QTKMTDataParser::ADREF = "adref";
const QString QTKMTDataParser::CONTENT = "content";
const QString QTKMTDataParser::FACTORY = "factoryPid";
const QString QTKMTDataParser::PLUGIN = "plugin";
const QString QTKMTDataParser::OPTIONAL = "optional";
const QString QTKMTDataParser::OBJECT = "Object";
const QString QTKMTDataParser::OCDREF = "ocdref";
const QString QTKMTDataParser::ATTRIBUTE = "Attribute";
const QString QTKMTDataParser::DESIGNATE = "Designate";
const QString QTKMTDataParser::MERGE = "merge";
const QString QTKMTDataParser::REQUIRED = "required";

const QString QTKMTDataParser::INTEGER = "Integer";
const QString QTKMTDataParser::STRING = "String";
const QString QTKMTDataParser::DOUBLE = "Double";
const QString QTKMTDataParser::LONG = "Long";
const QString QTKMTDataParser::CHAR = "Char";
const QString QTKMTDataParser::BOOLEAN = "Boolean";
const QString QTKMTDataParser::PASSWORD = "Password";


QTKMTDataParser::QTKMTDataParser(const QSharedPointer<QTKPlugin>& plugin, QIODevice* device, QTKLogService* logger)
    : _dp_plugin(plugin), _dp_xmlReader(device), logger(logger)
{

}

QHash<QString, QTKObjectClassDefinitionImplPtr> QTKMTDataParser::doParse()
{
    QTK_DEBUG(logger) << "Starting to parse metadata";
    while (_dp_xmlReader.readNextStartElement())
    {
        QStringRef name = _dp_xmlReader.name();
        if (name.compare(METADATA, Qt::CaseInsensitive) == 0)
        {
            metaDataHandler();
        }
        else
        {
            QTK_WARN(logger) << QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::UNEXPECTED_ELEMENT).arg(name.toString());
            _dp_xmlReader.skipCurrentElement();
        }
    }

    if (_dp_xmlReader.hasError() &&
            !(_dp_xmlReader.atEnd() && _dp_xmlReader.error() == QXmlStreamReader::PrematureEndOfDocumentError))
    {
        errorHandler();
        return QHash<QString, QTKObjectClassDefinitionImplPtr>();
    }

    return _dp_pid_to_OCDs;
}

void QTKMTDataParser::metaDataHandler()
{
    Q_ASSERT(_dp_xmlReader.isStartElement() && _dp_xmlReader.name().compare(METADATA, Qt::CaseInsensitive) == 0);

    QXmlStreamAttributes attributes = _dp_xmlReader.attributes();
    _dp_localization = attributes.value(LOCALIZATION).toString();
    _dp_context = attributes.value(CONTEXT).toString();
    // The variables "_dp_localization" and "_dp_context" will be used within
    // ocdHandler() and attributeDefinitionHandler() later.

    _dp_xmlReader.readNext();
    while(!_dp_xmlReader.hasError() && _dp_xmlReader.readNextStartElement())
    {
        QStringRef name = _dp_xmlReader.name();
        if (name.compare(DESIGNATE, Qt::CaseInsensitive) == 0)
        {
            designateHandler();
        }
        else if (name.compare(OCD, Qt::CaseInsensitive) == 0)
        {
            ocdHandler();
        }
        else
        {
            QTK_WARN(logger) << QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::UNEXPECTED_ELEMENT).arg(name.toString());
            _dp_xmlReader.skipCurrentElement();
        }
    }

    if (_dp_xmlReader.hasError()) return;

    if (_dp_designateInfos.isEmpty())
    {
        // Schema defines at least one DESIGNATE is required.
        QString msg = QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::MISSING_ELEMENT).arg(DESIGNATE);
        _dp_xmlReader.raiseError(msg);
        return;
    }

    for (int i = 0; i < _dp_designateInfos.size(); ++i)
    {
        const DesignateInfo& designateInfo = _dp_designateInfos[i];
        QTKObjectClassDefinitionImplPtr ocd = _dp_OCDs.value(designateInfo._ocdref);
        if (ocd)
        {
            if (designateInfo._factory_val.isEmpty())
            {
                ocd->setType(QTKObjectClassDefinitionImpl::PID);
                _dp_pid_to_OCDs.insert(designateInfo._pid_val, ocd);
            }
            else
            {
                ocd->setType(QTKObjectClassDefinitionImpl::FPID);
                _dp_pid_to_OCDs.insert(designateInfo._factory_val, ocd);
            }
        }
        else
        {
            QString msg = QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::OCD_ID_NOT_FOUND).arg(designateInfo._ocdref);
            _dp_xmlReader.raiseError(msg);
            return;
        }
    }
}

void QTKMTDataParser::designateHandler()
{
    Q_ASSERT(_dp_xmlReader.isStartElement() && _dp_xmlReader.name().compare(DESIGNATE, Qt::CaseInsensitive) == 0);

    DesignateInfo info;
    QXmlStreamAttributes atts = _dp_xmlReader.attributes();

    info._pid_val = atts.value(PID).toString();
    if (info._pid_val.isNull())
    {
        QString msg = QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::MISSING_ATTRIBUTE).arg(PID).arg(_dp_xmlReader.name().toString());
        _dp_xmlReader.raiseError(msg);
        return;
    }
    info._factory_val = atts.value(FACTORY).toString();

    info._plugin_val = atts.value(PLUGIN).toString();
    if (info._plugin_val.isNull())
    {
        // Not a problem because PLUGIN is an optional attribute.
    }

    QString optional_str = atts.value(OPTIONAL).toString();
    if (optional_str.isNull())
    {
        // Not a problem, because OPTIONAL is an optional attribute.
        // The default value is "false".
        info._optional_val = false;
    }
    else
    {
        info._optional_val = toBool(optional_str);
    }

    QString merge_str = atts.value(MERGE).toString();
    if (merge_str.isNull())
    {
        // Not a problem, because MERGE is an optional attribute.
        // The default value is "false".
        info._merge_val = false;
    }
    else
    {
        info._merge_val = toBool(merge_str);
    }

    while (!_dp_xmlReader.hasError() && _dp_xmlReader.readNextStartElement())
    {
        QStringRef name = _dp_xmlReader.name();
        if (name.compare(OBJECT, Qt::CaseInsensitive) == 0)
        {
            objectHandler(info);
        }
        else
        {
            QTK_WARN(logger) << QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::UNEXPECTED_ELEMENT).arg(name.toString());
            _dp_xmlReader.skipCurrentElement();
        }
    }

    if (_dp_xmlReader.hasError()) return;

    if (info._ocdref.isEmpty())
    {
        // Schema defines at least one OBJECT is required.
        QString msg = QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::MISSING_ELEMENT).arg(OBJECT).arg(info._pid_val);
        _dp_xmlReader.raiseError(msg);
        return;
    }

    _dp_designateInfos.push_back(info);
}

void QTKMTDataParser::ocdHandler()
{
    Q_ASSERT(_dp_xmlReader.isStartElement() && _dp_xmlReader.name().compare(OCD, Qt::CaseInsensitive) == 0);

    QStringRef name = _dp_xmlReader.name();
    QXmlStreamAttributes atts = _dp_xmlReader.attributes();
    QString ocd_name_val = atts.value(NAME).toString();
    if (ocd_name_val.isNull())
    {
        QString msg = QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::MISSING_ATTRIBUTE).arg(NAME).arg(name.toString());
        _dp_xmlReader.raiseError(msg);
        return;
    }

    QString ocd_description_val = atts.value(DESCRIPTION).toString();
    if (ocd_description_val.isNull())
    {
        // Not a problem, because DESCRIPTION is an optional attribute.
    }

    QString refID = atts.value(ID).toString();
    if (refID.isNull())
    {
        QString msg = QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::MISSING_ATTRIBUTE).arg(ID).arg(name.toString());
        _dp_xmlReader.raiseError(msg);
        return;
    }

    QTKObjectClassDefinitionImplPtr ocd(new QTKObjectClassDefinitionImpl(
                                            ocd_name_val, ocd_description_val,
                                            refID, _dp_localization, _dp_context));

    QList<QTKAttributeDefinitionImplPtr> ad_list;
    while (!_dp_xmlReader.hasError() && _dp_xmlReader.readNextStartElement())
    {
        QStringRef name2 = _dp_xmlReader.name();
        if (name2.compare(AD, Qt::CaseInsensitive) == 0)
        {
            attributeDefinitionHandler(ad_list);
        }
        else if (name2.compare(ICON, Qt::CaseInsensitive) == 0)
        {
            QTKMTIcon icon = iconHandler();
            if (!_dp_xmlReader.hasError())
            {
                // Because XML schema allows at most one icon for
                // one OCD, if more than one icons are read from
                // MetaData, then only the final icon will be kept.
                ocd->setIcon(icon);
            }
        }
        else
        {
            QTK_WARN(logger) << QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::UNEXPECTED_ELEMENT).arg(name2.toString());
            _dp_xmlReader.skipCurrentElement();
        }
    }

    if (_dp_xmlReader.hasError()) return;

    if (ad_list.isEmpty())
    {
        // Schema defines at least one AD is required.
        QString msg = QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::MISSING_ELEMENT).arg(AD).arg(refID);
        _dp_xmlReader.raiseError(msg);
        return;
    }
    // OCD gets all parsed ADs.
    foreach (QTKAttributeDefinitionImplPtr ad, ad_list)
    {
        ocd->addAttributeDefinition(ad, ad->isRequired());
    }

    _dp_OCDs.insert(refID, ocd);
}

void QTKMTDataParser::objectHandler(DesignateInfo& designateInfo)
{
    Q_ASSERT(_dp_xmlReader.isStartElement() && _dp_xmlReader.name().compare(OBJECT, Qt::CaseInsensitive) == 0);

    designateInfo._ocdref = _dp_xmlReader.attributes().value(OCDREF).toString();
    if (designateInfo._ocdref.isNull())
    {
        QString msg = QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::MISSING_ATTRIBUTE).arg(OCDREF).arg(_dp_xmlReader.name().toString());
        _dp_xmlReader.raiseError(msg);
        return;
    }

    while (!_dp_xmlReader.hasError() && _dp_xmlReader.readNextStartElement())
    {
        QStringRef name = _dp_xmlReader.name();
        if (name.compare(ATTRIBUTE, Qt::CaseInsensitive) == 0)
        {
            attributeHandler();
        }
        else
        {
            QTK_WARN(logger) << QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::UNEXPECTED_ELEMENT).arg(name.toString());
            _dp_xmlReader.skipCurrentElement();
        }
    }
}

void QTKMTDataParser::attributeHandler()
{
    Q_ASSERT(_dp_xmlReader.isStartElement() && _dp_xmlReader.name().compare(ATTRIBUTE, Qt::CaseInsensitive) == 0);
    while (_dp_xmlReader.readNextStartElement()) _dp_xmlReader.skipCurrentElement();
}

void QTKMTDataParser::attributeDefinitionHandler(QList<QTKAttributeDefinitionImplPtr>& ad_list)
{
    Q_ASSERT(_dp_xmlReader.isStartElement() && _dp_xmlReader.name().compare(AD, Qt::CaseInsensitive) == 0);

    QString name = _dp_xmlReader.name().toString();
    QXmlStreamAttributes atts = _dp_xmlReader.attributes();
    QString ad_name_val = atts.value(NAME).toString();
    if (ad_name_val.isNull())
    {
        // Not a problem, because NAME is an optional attribute.
    }

    QString ad_description_val = atts.value(DESCRIPTION).toString();
    if (ad_description_val.isNull())
    {
        // Not a problem, because DESCRIPTION is an optional attribute.
    }

    QString ad_id_val = atts.value(ID).toString();
    if (ad_id_val.isNull())
    {
        QString msg = QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::MISSING_ATTRIBUTE).arg(ID).arg(name);
        _dp_xmlReader.raiseError(msg);
        return;
    }

    int dataType;
    QStringRef ad_type_val = atts.value("", TYPE);
    if (ad_type_val.compare(STRING, Qt::CaseInsensitive) == 0)
    {
        dataType = QVariant::String;
    }
    else if (ad_type_val.compare(LONG, Qt::CaseInsensitive) == 0)
    {
        dataType = QVariant::LongLong;
    }
    else if (ad_type_val.compare(DOUBLE, Qt::CaseInsensitive) == 0)
    {
        dataType = QVariant::Double;
    }
    else if (ad_type_val.compare(INTEGER, Qt::CaseInsensitive) == 0)
    {
        dataType = QVariant::Int;
    }
    else if (ad_type_val.compare(CHAR, Qt::CaseInsensitive) == 0)
    {
        dataType = QVariant::Char;
    }
    else if (ad_type_val.compare(BOOLEAN, Qt::CaseInsensitive) == 0)
    {
        dataType = QVariant::Bool;
    }
    else if (ad_type_val.compare(PASSWORD, Qt::CaseInsensitive) == 0)
    {
        dataType = QTKAttributeDefinition::PASSWORD;
    }
    else
    {
        QString msg = QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::MISSING_ATTRIBUTE).arg(TYPE).arg(name);
        _dp_xmlReader.raiseError(msg);
        return;
    }

    QString ad_cardinality_str = atts.value(CARDINALITY).toString();
    int ad_cardinality_val = 0;
    if (ad_cardinality_str.isNull())
    {
        // Not a problem, because CARDINALITY is an optional attribute.
        // And the default value is 0.
    }
    else
    {
        ad_cardinality_val = ad_cardinality_str.toInt();
    }

    QString ad_min_val = atts.value(MIN).toString();
    if (ad_min_val.isNull())
    {
        // Not a problem, because MIN is an optional attribute.
    }

    QString ad_max_val = atts.value(MAX).toString();
    if (ad_max_val.isNull())
    {
        // Not a problem, because MAX is an optional attribute.
    }

    QString ad_defaults_str = atts.value(DEFAULT).toString();
    if (ad_defaults_str.isNull())
    {
        // Not a problem, because DEFAULT is an optional attribute.
        if (ad_cardinality_val == 0)
        {
            // But when it is not assigned, CARDINALITY cannot be '0'.
            QString msg = QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::nullptr_DEFAULTS);
            _dp_xmlReader.raiseError(msg);
            return;
        }
    }

    QString ad_required_val = atts.value(REQUIRED).toString();
    if (ad_required_val.isNull())
    {
        // Not a problem, because REQUIRED is an optional attribute.
        // And the default value is 'true'.
        ad_required_val = "true";
    }

    QTKAttributeDefinitionImplPtr ad(new QTKAttributeDefinitionImpl(
                                         ad_id_val, ad_name_val, ad_description_val, dataType,
                                         ad_cardinality_val, convert(ad_min_val, dataType), convert(ad_max_val, dataType),
                                         toBool(ad_required_val), _dp_localization, _dp_context, logger));

    if (ad_cardinality_val == 0)
    {
        // Attribute DEFAULT has one and only one occurance.
        ad->setDefaultValue(QStringList(ad_defaults_str), false);
    }
    else
    {
        // Attribute DEFAULT is a comma delimited list.
        ad->setDefaultValue(ad_defaults_str, false);
    }

    QStringList optionLabels;
    QStringList optionValues;
    while (!_dp_xmlReader.hasError() && _dp_xmlReader.readNextStartElement())
    {
        QStringRef name2 = _dp_xmlReader.name();
        if (name2.compare(OPTION, Qt::CaseInsensitive) == 0)
        {
            OptionInfo optionInfo;
            optionHandler(optionInfo);
            if (!_dp_xmlReader.hasError())
            {
                optionLabels.push_back(optionInfo._label_val);
                optionValues.push_back(optionInfo._value_val);
            }
        }
        else
        {
            QTK_WARN(logger) << QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::UNEXPECTED_ELEMENT).arg(name2.toString());
            _dp_xmlReader.skipCurrentElement();
        }
    }

    if (_dp_xmlReader.hasError()) return;

    ad->setOption(optionLabels, optionValues, true);
    ad_list.push_back(ad);
}

QTKMTIcon QTKMTDataParser::iconHandler()
{
    Q_ASSERT(_dp_xmlReader.isStartElement() && _dp_xmlReader.name().compare(ICON, Qt::CaseInsensitive) == 0);

    QXmlStreamAttributes atts = _dp_xmlReader.attributes();
    QString icon_resource_val = atts.value(RESOURCE).toString();
    if (icon_resource_val.isNull())
    {
        QString msg = QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::MISSING_ATTRIBUTE).arg(RESOURCE).arg(_dp_xmlReader.name().toString());
        _dp_xmlReader.raiseError(msg);
        return QTKMTIcon();
    }

    QString icon_size_val = atts.value(SIZE).toString();
    if (icon_size_val.isNull())
    {
        // Not a problem, because SIZE is an optional attribute.
        icon_size_val = "0";
    }

    while (_dp_xmlReader.readNextStartElement()) _dp_xmlReader.skipCurrentElement();
    return QTKMTIcon(icon_resource_val, icon_size_val.toInt(), _dp_plugin);
}

void QTKMTDataParser::optionHandler(OptionInfo& optionInfo)
{
    Q_ASSERT(_dp_xmlReader.isStartElement() && _dp_xmlReader.name().compare(OPTION, Qt::CaseInsensitive) == 0);

    QXmlStreamAttributes atts = _dp_xmlReader.attributes();
    optionInfo._label_val = atts.value(LABEL).toString();
    if (optionInfo._label_val.isNull())
    {
        QString msg = QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::MISSING_ATTRIBUTE).arg(LABEL).arg(_dp_xmlReader.name().toString());
        _dp_xmlReader.raiseError(msg);
        return;
    }

    optionInfo._value_val = atts.value(VALUE).toString();
    if (optionInfo._value_val.isNull())
    {
        QString msg = QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::MISSING_ATTRIBUTE).arg(VALUE).arg(_dp_xmlReader.name().toString());
        _dp_xmlReader.raiseError(msg);
        return;
    }

    while (_dp_xmlReader.readNextStartElement()) _dp_xmlReader.skipCurrentElement();
}

void QTKMTDataParser::errorHandler()
{
    switch (_dp_xmlReader.error())
    {
    case QXmlStreamReader::NotWellFormedError:
        QTK_WARN(logger) << "XML Document not well formed at line " << _dp_xmlReader.lineNumber() << ", col " << _dp_xmlReader.columnNumber();
        break;
    case QXmlStreamReader::PrematureEndOfDocumentError:
        QTK_WARN(logger) << "Premature end of XML Document at line " << _dp_xmlReader.lineNumber() << ", col " << _dp_xmlReader.columnNumber();
        break;
    case QXmlStreamReader::UnexpectedElementError:
        QTK_WARN(logger) << "Unexpected element at line " << _dp_xmlReader.lineNumber() << ", col " << _dp_xmlReader.columnNumber();
        break;
    case QXmlStreamReader::CustomError:
        QTK_ERROR(logger) << _dp_xmlReader.errorString() << "at line" << _dp_xmlReader.lineNumber() << ", col " << _dp_xmlReader.columnNumber();
        break;
    default:
        break;
    }
}

bool QTKMTDataParser::toBool(const QString& str)
{
    if (str.isEmpty()) return false;
    if (str.trimmed().compare("true", Qt::CaseInsensitive)) return true;
    if (str.trimmed().compare("1")) return true;
    return false;
}

QVariant QTKMTDataParser::convert(const QString& value, int type)
{
    if (value.isNull())
    {
        return QVariant();
    }

    if (type == QTKAttributeDefinition::PASSWORD || type == QVariant::String)
    {
        // PASSWORD should be treated like STRING.
        // Both the min and max of STRING are Integers.
        return QVariant::fromValue<int>(value.toInt());
    }
    else if (type == QVariant::LongLong)
    {
        return QVariant::fromValue<qlonglong>(value.toLongLong());
    }
    else if (type == QVariant::Int)
    {
        return QVariant::fromValue<int>(value.toInt());
    }
    else if (type == QVariant::Char)
    {
        return QVariant::fromValue<QChar>(value.at(0));
    }
    else if (type == QVariant::Double)
    {
        return QVariant::fromValue<double>(value.toDouble());
    }
    else if (type == QVariant::Bool)
    {
        return QVariant::fromValue<bool>(toBool(value));
    }
    else
    {
        // Unknown data type
        return QVariant();
    }
}

