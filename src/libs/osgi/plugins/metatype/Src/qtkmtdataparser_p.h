#ifndef QTKMTDATAPARSER_P_H
#define QTKMTDATAPARSER_P_H

#include "qtkobjectclassdefinitionimpl_p.h"
#include "qtkattributedefinitionimpl_p.h"

#include <QTKPluginFramework/Service/Log/QTKLogService>

#include <QXmlStreamReader>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QIODevice;

/**
 * Meta XML Data Parser
 */
class QTKMTDataParser
{
private:

    static const QString METADATA; // = "MetaData"
    static const QString LOCALIZATION; // = "localization"
    static const QString CONTEXT; // = "context"
    static const QString OCD; // = "OCD"
    static const QString ICON; // = "Icon"
    static const QString AD; // = "AD"
    static const QString CARDINALITY; // = "cardinality"
    static const QString OPTION; // = "Option"
    static const QString LABEL; // = "label"
    static const QString VALUE; // = "value"
    static const QString MIN; // = "min"
    static const QString MAX; // = "max"
    static const QString TYPE; // = "type"
    static const QString SIZE; // = "size"
    static const QString ID; // = "id"
    static const QString NAME; // = "name"
    static const QString DESCRIPTION; // = "description"
    static const QString RESOURCE; // = "resource"
    static const QString PID; // = "pid"
    static const QString DEFAULT; // = "default"
    static const QString ADREF; // = "adref"
    static const QString CONTENT; // = "content"
    static const QString FACTORY; // = "factoryPid"
    static const QString PLUGIN; // = "plugin"
    static const QString OPTIONAL; // = "optional"
    static const QString OBJECT; // = "Object"
    static const QString OCDREF; // = "ocdref"
    static const QString ATTRIBUTE; // = "Attribute"
    static const QString DESIGNATE; // = "Designate"
    static const QString MERGE; // = "merge"
    static const QString REQUIRED; // = "required"

    static const QString INTEGER; // = "Integer"
    static const QString STRING; // = "String"
    static const QString DOUBLE; // = "Double"
    static const QString LONG; // = "Long"
    static const QString CHAR; // = "Char"
    static const QString BOOLEAN; // = "Boolean"
    static const QString PASSWORD; // = "Password"

    struct DesignateInfo
    {
        QString _pid_val;
        QString _factory_val;
        QString _plugin_val;
        bool _optional_val;
        bool _merge_val;
        QString _ocdref;

        DesignateInfo() : _optional_val(false), _merge_val(false)
        {}
    };

    QList<DesignateInfo> _dp_designateInfos;

    struct OptionInfo
    {
        QString _label_val;
        QString _value_val;
    };

    QSharedPointer<QTKPlugin> _dp_plugin;
    QXmlStreamReader _dp_xmlReader;

    // ObjectClassDefinitions in DataParser class w/ corresponding reference keys
    QHash<QString, QTKObjectClassDefinitionImplPtr> _dp_OCDs;
    // pid to ObjectClassDefinitions in DataParser class as a Hashtable
    QHash<QString, QTKObjectClassDefinitionImplPtr> _dp_pid_to_OCDs;
    // Localization in QTKMTDataParser class
    QString _dp_localization;
    // Localization context
    QString _dp_context;

    // Default visibility to avoid a plethora of synthetic accessor method warnings.
    QTKLogService* const logger;

public:

    /*
   * Constructor of class QTKMTDataParser.
   */
    QTKMTDataParser(const QSharedPointer<QTKPlugin>& plugin, QIODevice* device, QTKLogService* logger);

    /*
   * Main method to parse specific MetaData file.
   */
    QHash<QString, QTKObjectClassDefinitionImplPtr> doParse();

private:

    void metaDataHandler();
    void designateHandler();
    void ocdHandler();
    void objectHandler(DesignateInfo& designateInfo);
    void attributeHandler();
    void attributeDefinitionHandler(QList<QTKAttributeDefinitionImplPtr>& ad_list);
    QTKMTIcon iconHandler();
    void optionHandler(OptionInfo& optionInfo);

    void errorHandler();

    static bool toBool(const QString& str);

    /*
   * Convert QString for expected data type.
   */
    static QVariant convert(const QString& value, int type);

};

#endif // QTKMTDATAPARSER_P_H
