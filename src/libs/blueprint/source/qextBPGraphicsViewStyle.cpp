#include <qextBPGraphicsViewStyle.h>
#include <qextBPStyleCollection.h>

#include <QtCore/QFile>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValueRef>


inline void initResources()
{
    Q_INIT_RESOURCE(qextBlueprint);
}

QExtBPGraphicsViewStyle::QExtBPGraphicsViewStyle()
{
    // Explicit resources inialization for preventing the static initialization
    // order fiasco: https://isocpp.org/wiki/faq/ctors#static-init-order
    initResources();

    // This configuration is stored inside the compiled unit and is loaded statically
    loadJsonFile(":/DefaultStyle.json");
}

QExtBPGraphicsViewStyle::QExtBPGraphicsViewStyle(QString jsonText)
{
    loadJsonText(jsonText);
}

void QExtBPGraphicsViewStyle::setStyle(QString jsonText)
{
    QExtBPGraphicsViewStyle style(jsonText);

    QExtBPStyleCollection::setGraphicsViewStyle(style);
}

#ifdef STYLE_DEBUG
#define FLOW_VIEW_STYLE_CHECK_UNDEFINED_VALUE(v, variable) \
{ \
    if (v.type() == QJsonValue::Undefined || v.type() == QJsonValue::Null) \
    qWarning() << "Undefined value for parameter:" << #variable; \
    }
#else
#define FLOW_VIEW_STYLE_CHECK_UNDEFINED_VALUE(v, variable)
#endif

#define FLOW_VIEW_STYLE_READ_COLOR(values, variable) \
{ \
    auto valueRef = values[#variable]; \
    FLOW_VIEW_STYLE_CHECK_UNDEFINED_VALUE(valueRef, variable) \
    if (valueRef.isArray()) { \
    auto colorArray = valueRef.toArray(); \
    std::vector<int> rgb; \
    rgb.reserve(3); \
    for (auto it = colorArray.begin(); it != colorArray.end(); ++it) { \
    rgb.push_back((*it).toInt()); \
    } \
    variable = QColor(rgb[0], rgb[1], rgb[2]); \
    } else { \
    variable = QColor(valueRef.toString()); \
    } \
    }

#define FLOW_VIEW_STYLE_WRITE_COLOR(values, variable) \
{ \
    values[#variable] = variable.name(); \
    }

void QExtBPGraphicsViewStyle::loadJson(const QJsonObject &json)
{
    QJsonValue nodeStyleValues = json["GraphicsViewStyle"];

    QJsonObject obj = nodeStyleValues.toObject();

    FLOW_VIEW_STYLE_READ_COLOR(obj, BackgroundColor);
    FLOW_VIEW_STYLE_READ_COLOR(obj, FineGridColor);
    FLOW_VIEW_STYLE_READ_COLOR(obj, CoarseGridColor);
}

QJsonObject QExtBPGraphicsViewStyle::toJson() const
{
    QJsonObject obj;

    FLOW_VIEW_STYLE_WRITE_COLOR(obj, BackgroundColor);
    FLOW_VIEW_STYLE_WRITE_COLOR(obj, FineGridColor);
    FLOW_VIEW_STYLE_WRITE_COLOR(obj, CoarseGridColor);

    QJsonObject root;
    root["GraphicsViewStyle"] = obj;

    return root;
}
