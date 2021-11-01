#ifndef QTKATTRIBUTEDEFINITIONIMPL_P_H
#define QTKATTRIBUTEDEFINITIONIMPL_P_H

#include "qtkmtlocalizationelement_p.h"

#include <QTKPluginFramework/Service/Metatype/QTKAttributeDefinition>
#include <QTKPluginFramework/Service/Log/QTKLogService>

#include <QStringList>
#include <QVariant>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

/**
 * Implementation of QTKAttributeDefintion
 */
class QTKAttributeDefinitionImpl : public QTKAttributeDefinition
{

private:

    static const QChar SEPARATE;
    static const QChar CONTROL;

    QString _name;
    QString _id;
    QString _description;
    int _cardinality;
    int _dataType;
    QVariant _minValue;
    QVariant _maxValue;
    bool _isRequired;

    QTKMTLocalizationElement _locElem;

    QStringList _defaults;
    QStringList _values;
    QStringList _labels;

    QTKLogService* const _logger;

public:

    /**
   * Constructor of class QTKAttributeDefinitionImpl.
   */
    QTKAttributeDefinitionImpl(const QString& id, const QString& name, const QString& description,
                               int type, int cardinality, const QVariant& min, const QVariant& max,
                               bool isRequired, const QString& localization, const QString& context,
                               QTKLogService* logger);

    /*
   * @see QTKAttributeDefinition#getName()
   */
    QString getName() const;

    /**
   * Method to set the name of AttributeDefinition.
   */
    void setName(const QString& name);

    /*
   * @see QTKAttributeDefinition#getID()
   */
    QString getID() const;

    /**
   * Method to set the ID of QTKAttributeDefinition.
  */
    void setID(const QString& id);

    /*
   * @see QTKAttributeDefinition#getDescription()
  */
    QString getDescription() const;

    /**
   * Method to set the description of QTKAttributeDefinition.
   */
    void setDescription(const QString& description);

    /*
   * @see QTKAttributeDefinition#getCardinality()
   */
    int getCardinality() const;

    /**
   * Method to set the cardinality of QTKAttributeDefinition.
   */
    void setCardinality(int cardinality);

    /*
   * @see QTKAttributeDefinition#getType()
   */
    int getType() const;

    /**
   * Method to set the data type of QTKAttributeDefinition.
   */
    void setType(int type);

    /**
   * Method to get the required flag of QTKAttributeDefinition.
   */
    bool isRequired() const;

    /**
   * Method to set the required flag of QTKAttributeDefinition.
   */
    void setRequired(bool isRequired);

    /*
   * @see QTKAttributeDefinition#getOptionLabels()
   */
    QStringList getOptionLabels() const;

    /*
   * @see QTKAttributeDefinition#getOptionValues()
   */
    QStringList getOptionValues() const;

    /**
   * Method to set the Option values of QTKAttributeDefinition.
   */
    void setOption(const QStringList& labels, const QStringList& values,
                   bool needValidation);

    /*
   * @see QTKAttributeDefinition#getDefaultValue()
   */
    QStringList getDefaultValue() const;

    /**
   * Method to set the default value of QTKAttributeDefinition.
   * The given parameter is a comma delimited list needed to be parsed.
   */
    void setDefaultValue(const QString& defaults_str, bool needValidation);

    /**
   * Method to set the default value of QTKAttributeDefinition.
   * The given parameter is a String array of multi values.
   */
    void setDefaultValue(const QStringList& defaults, bool needValidation);

    /**
   * Method to set the validation value - min of QTKAttributeDefinition.
   */
    void setMinValue(const QVariant& minValue);

    /**
   * Method to set the validation value - max of QTKAttributeDefinition.
   */
    void setMaxValue(const QVariant& maxValue);

    /**
   * Method to set the plugin localization object.
   */
    void setPluginLocalization(const QTKPluginLocalization& pluginLoc);

    /*
   * @see QTKAttributeDefinition#validate(const QString&)
   */
    QString validate(const QString& value) const;

private:

    /**
   * Internal Method - to validate data in range.
   */
    QString validateRange(const QString& value) const;

    QStringList tokenizeValues(const QString& values) const;
};

typedef QSharedPointer<QTKAttributeDefinitionImpl> QTKAttributeDefinitionImplPtr;

#endif // QTKATTRIBUTEDEFINITIONIMPL_P_H
