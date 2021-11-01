#include "qtkattributedefinitionimpl_p.h"
#include "qtkmtmsg_p.h"

#include <QTKPluginFramework/Service/Log/QTKLogService>

#include <QCoreApplication>

const QChar QTKAttributeDefinitionImpl::SEPARATE = ',';
const QChar QTKAttributeDefinitionImpl::CONTROL = '\\';

QTKAttributeDefinitionImpl::QTKAttributeDefinitionImpl(
        const QString& id, const QString& name, const QString& description,
        int type, int cardinality, const QVariant& min, const QVariant& max,
        bool isRequired, const QString& localization, const QString& context, QTKLogService* logger)
    : _name(name), _id(id), _description(description), _cardinality(cardinality),
      _dataType(type), _minValue(min), _maxValue(max), _isRequired(isRequired),
      _locElem(localization, context), _logger(logger)
{

}

QString QTKAttributeDefinitionImpl::getName() const
{
    return _locElem.getLocalized(_name);
}

void QTKAttributeDefinitionImpl::setName(const QString& name)
{
    _name = name;
}

QString QTKAttributeDefinitionImpl::getID() const
{
    return _id;
}

void QTKAttributeDefinitionImpl::setID(const QString& id)
{
    _id = id;
}

QString QTKAttributeDefinitionImpl::getDescription() const
{
    return _locElem.getLocalized(_description);
}

void QTKAttributeDefinitionImpl::setDescription(const QString& description)
{
    _description = description;
}

int QTKAttributeDefinitionImpl::getCardinality() const
{
    return _cardinality;
}

void QTKAttributeDefinitionImpl::setCardinality(int cardinality)
{
    _cardinality = cardinality;
}

int QTKAttributeDefinitionImpl::getType() const
{
    return _dataType;
}

void QTKAttributeDefinitionImpl::setType(int type)
{
    _dataType = type;
}

bool QTKAttributeDefinitionImpl::isRequired() const
{
    return _isRequired;
}

void QTKAttributeDefinitionImpl::setRequired(bool isRequired)
{
    _isRequired = isRequired;
}

QStringList QTKAttributeDefinitionImpl::getOptionLabels() const
{
    if (_labels.isEmpty())
    {
        return QStringList();
    }

    QStringList returnedLabels;
    foreach(QString labelKey, _labels)
    {
        returnedLabels << _locElem.getLocalized(labelKey);
    }
    return returnedLabels;
}

QStringList QTKAttributeDefinitionImpl::getOptionValues() const
{
    return _values;
}

void QTKAttributeDefinitionImpl::setOption(
        const QStringList& labels, const QStringList& values, bool needValidation)
{
    //  if (labels.isEmpty() || values.isEmpty())
    //  {
    //    QTK_ERROR(_logger) << "QTKAttributeDefinitionImpl::setOption(QStringList, QStringList, bool)"
    //                     << QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::nullptr_OPTIONS);
    //    return;
    //  }

    if (labels.size() != values.size())
    {
        QTK_ERROR(_logger) << "QTKAttributeDefinitionImpl::setOption(QStringList, QStringList, bool)"
                           << QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::INCONSISTENT_OPTIONS);
        return;
    }

    _labels = labels;
    _values = values;

    if (needValidation)
    {
        for (int index = 0; index < _labels.size(); index++)
        {
            QString reason = validate(_values.value(index));
            if (!reason.isEmpty())
            {
                QTK_WARN(_logger) << QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::INVALID_OPTIONS).arg(_values.value(index)).arg(reason);
                _labels.removeAt(index);
                _values.removeAt(index);
                index--; // Because this one has been removed.
            }
        }
    }
}

QStringList QTKAttributeDefinitionImpl::getDefaultValue() const
{
    return _defaults;
}

void QTKAttributeDefinitionImpl::setDefaultValue(const QString& defaults_str, bool needValidation)
{
    setDefaultValue(tokenizeValues(defaults_str), needValidation);
}

void QTKAttributeDefinitionImpl::setDefaultValue(const QStringList& defaults, bool needValidation)
{
    Q_UNUSED(needValidation)

    _defaults = defaults;
    // Do we also need to make sure if defaults are validated?
}

void QTKAttributeDefinitionImpl::setMinValue(const QVariant& minValue)
{
    _minValue = minValue;
}

void QTKAttributeDefinitionImpl::setMaxValue(const QVariant& maxValue)
{
    _maxValue = maxValue;
}

void QTKAttributeDefinitionImpl::setPluginLocalization(const QTKPluginLocalization& pluginLoc)
{
    _locElem.setPluginLocalization(pluginLoc);
}

QString QTKAttributeDefinitionImpl::validate(const QString& value) const
{
    if (value.isNull())
    {
        return QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::nullptr_IS_INVALID);
    }

    if ((_minValue.isNull()) && (_maxValue.isNull()))
    {
        // Password is treated like String.
        if (_dataType != QVariant::String && _dataType != QVariant::UserType)
        {
            // No validation present
            return QString();
        }
        if (_values.size() < 1)
            // No validation present
            return QString();
    }

    // Addtional validation for STRING.
    // PASSWORD is treated like STRING.
    if ((_dataType == QVariant::String || _dataType == QVariant::UserType) && _values.size() > 0 && !_values.contains(value))
    {
        return QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::VALUE_OUT_OF_OPTION).arg(value);
    }

    try
    {
        if (_cardinality != 0)
        {
            QStringList value_list = tokenizeValues(value);

            if (value_list.size() > _cardinality)
            {
                return QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::TOO_MANY_VALUES).arg(value).arg(_cardinality);
            }
            for (int i = 0; i < value_list.size(); i++)
            {
                QString return_msg = validateRange(value_list.value(i));
                if (!return_msg.isEmpty())
                {
                    // Returned String states why the value is invalid.
                    return return_msg;
                }
            }
            // No problems detected
            return "";
        }
        // Only when cardinality is '0', it comes here.
        QString return_msg = validateRange(value);
        return return_msg;
    }
    catch (const std::exception& e)
    {
        return QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::EXCEPTION_MESSAGE).arg("std::exception").arg(e.what());
    }
}

QString QTKAttributeDefinitionImpl::validateRange(const QString& value) const
{
    bool rangeError = false;

    switch (_dataType)
    {
    // PASSWORD is treated like STRING.
    case QVariant::UserType:
    case QVariant::String:
    {
        if (!_minValue.isNull() && value.length() < _minValue.toInt())
        {
            rangeError = true;
        }
        else if (!_maxValue.isNull() && value.length() > _maxValue.toInt())
        {
            rangeError = true;
        }
        break;
    }
    case QVariant::LongLong:
    {
        qlonglong longVal = value.toLongLong();
        if (!_minValue.isNull() && longVal < _minValue.toLongLong())
        {
            rangeError = true;
        }
        else if (!_maxValue.isNull() && longVal > _maxValue.toLongLong())
        {
            rangeError = true;
        }
        break;
    }
    case QVariant::Int:
    {
        int intVal = value.toInt();
        if (!_minValue.isNull() && intVal < _minValue.toInt())
        {
            rangeError = true;
        }
        else if (!_maxValue.isNull() && intVal > _maxValue.toInt())
        {
            rangeError = true;
        }
        break;
    }
    case QVariant::Char:
    {
        QChar charVal = value.at(0);
        if (!_minValue.isNull() && charVal < _minValue.toChar())
        {
            rangeError = true;
        }
        else if (!_maxValue.isNull() && charVal > _maxValue.toChar())
        {
            rangeError = true;
        }
        break;
    }
    case QVariant::Double:
    {
        double doubleVal = value.toDouble();
        if (!_minValue.isNull() && doubleVal < _minValue.toDouble())
        {
            rangeError = true;
        }
        else if (!_maxValue.isNull() && doubleVal > _maxValue.toDouble())
        {
            rangeError = true;
        }
        break;
    }
    case QVariant::Bool:
        // shouldn't ever get boolean - this is a range validation
    default :
        return QString();
    }

    if (rangeError)
    {
        return QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::VALUE_OUT_OF_RANGE).arg(value);
    }
    // No problems detected
    return "";
}

QStringList QTKAttributeDefinitionImpl::tokenizeValues(const QString& values) const
{
    QStringList result;
    if (!values.isEmpty())
    {
        QString buffer;
        for (int i = 0; i < values.size(); i++)
        {
            if (values.at(i) == CONTROL)
            {
                if (i + 1 < values.size())
                {
                    buffer.append(values.at(++i));
                    continue;
                }
                // CONTROL char should not occur in last char.
                QTK_ERROR(_logger) << QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::TOKENIZER_GOT_INVALID_DATA);
                // It's an invalid char, but since it's the last one,
                // just ignore it.
                continue;
            }
            if (values.at(i) == SEPARATE)
            {
                result.push_back(buffer.trimmed());
                buffer.clear();
                continue;
            }
            buffer.append(values.at(i));
        }
        // Don't forget the final one.
        result.push_back(buffer.trimmed());
    }
    return result;
}
