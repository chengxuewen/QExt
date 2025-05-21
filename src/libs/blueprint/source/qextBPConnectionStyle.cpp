#include <qextBPConnectionStyle.h>
#include <qextBPStyleCollection.h>

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValueRef>

#include <QDebug>

#include <random>

inline void initResources()
{
    Q_INIT_RESOURCE(qextBlueprint);
}

QExtBPConnectionStyle::QExtBPConnectionStyle()
{
    // Explicit resources inialization for preventing the static initialization
    // order fiasco: https://isocpp.org/wiki/faq/ctors#static-init-order
    initResources();

    // This configuration is stored inside the compiled unit and is loaded statically
    loadJsonFile(":/QExtBlueprint/DefaultStyle.json");
}

QExtBPConnectionStyle::QExtBPConnectionStyle(QString jsonText)
{
    loadJsonFile(":/QExtBlueprint/DefaultStyle.json");
    loadJsonText(jsonText);
}

void QExtBPConnectionStyle::setConnectionStyle(QString jsonText)
{
    QExtBPConnectionStyle style(jsonText);

    QExtBPStyleCollection::setConnectionStyle(style);
}

#ifdef STYLE_DEBUG
#define CONNECTION_STYLE_CHECK_UNDEFINED_VALUE(v, variable) \
{ \
    if (v.type() == QJsonValue::Undefined || v.type() == QJsonValue::Null) \
    qWarning() << "Undefined value for parameter:" << #variable; \
    }
#else
#define CONNECTION_STYLE_CHECK_UNDEFINED_VALUE(v, variable)
#endif

#define CONNECTION_VALUE_EXISTS(v) \
    (v.type() != QJsonValue::Undefined && v.type() != QJsonValue::Null)

#define CONNECTION_STYLE_READ_COLOR(values, variable) \
{ \
    auto valueRef = values[#variable]; \
    CONNECTION_STYLE_CHECK_UNDEFINED_VALUE(valueRef, variable) \
    if (CONNECTION_VALUE_EXISTS(valueRef)) { \
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
    } \
    }

#define CONNECTION_STYLE_WRITE_COLOR(values, variable) \
{ \
    values[#variable] = variable.name(); \
    }

#define CONNECTION_STYLE_READ_FLOAT(values, variable) \
{ \
    auto valueRef = values[#variable]; \
    CONNECTION_STYLE_CHECK_UNDEFINED_VALUE(valueRef, variable) \
    if (CONNECTION_VALUE_EXISTS(valueRef)) \
    variable = valueRef.toDouble(); \
    }

#define CONNECTION_STYLE_WRITE_FLOAT(values, variable) \
{ \
    values[#variable] = variable; \
    }

#define CONNECTION_STYLE_READ_BOOL(values, variable) \
{ \
    auto valueRef = values[#variable]; \
    CONNECTION_STYLE_CHECK_UNDEFINED_VALUE(valueRef, variable) \
    if (CONNECTION_VALUE_EXISTS(valueRef)) \
    variable = valueRef.toBool(); \
    }

#define CONNECTION_STYLE_WRITE_BOOL(values, variable) \
{ \
    values[#variable] = variable; \
    }

void QExtBPConnectionStyle::loadJson(const QJsonObject &json)
{
    QJsonValue nodeStyleValues = json["ConnectionStyle"];

    QJsonObject obj = nodeStyleValues.toObject();

    CONNECTION_STYLE_READ_COLOR(obj, ConstructionColor);
    CONNECTION_STYLE_READ_COLOR(obj, NormalColor);
    CONNECTION_STYLE_READ_COLOR(obj, SelectedColor);
    CONNECTION_STYLE_READ_COLOR(obj, SelectedHaloColor);
    CONNECTION_STYLE_READ_COLOR(obj, HoveredColor);

    CONNECTION_STYLE_READ_FLOAT(obj, LineWidth);
    CONNECTION_STYLE_READ_FLOAT(obj, ConstructionLineWidth);
    CONNECTION_STYLE_READ_FLOAT(obj, PointDiameter);

    CONNECTION_STYLE_READ_BOOL(obj, UseDataDefinedColors);
}

QJsonObject QExtBPConnectionStyle::toJson() const
{
    QJsonObject obj;

    CONNECTION_STYLE_WRITE_COLOR(obj, ConstructionColor);
    CONNECTION_STYLE_WRITE_COLOR(obj, NormalColor);
    CONNECTION_STYLE_WRITE_COLOR(obj, SelectedColor);
    CONNECTION_STYLE_WRITE_COLOR(obj, SelectedHaloColor);
    CONNECTION_STYLE_WRITE_COLOR(obj, HoveredColor);

    CONNECTION_STYLE_WRITE_FLOAT(obj, LineWidth);
    CONNECTION_STYLE_WRITE_FLOAT(obj, ConstructionLineWidth);
    CONNECTION_STYLE_WRITE_FLOAT(obj, PointDiameter);

    CONNECTION_STYLE_WRITE_BOOL(obj, UseDataDefinedColors);

    QJsonObject root;
    root["ConnectionStyle"] = obj;

    return root;
}

QColor QExtBPConnectionStyle::constructionColor() const
{
    return ConstructionColor;
}

QColor QExtBPConnectionStyle::normalColor() const
{
    return NormalColor;
}

QColor QExtBPConnectionStyle::normalColor(QString typeId) const
{
    std::size_t hash = qHash(typeId);

    std::size_t const hue_range = 0xFF;

    std::mt19937 gen(static_cast<unsigned int>(hash));
    std::uniform_int_distribution<int> distrib(0, hue_range);

    int hue = distrib(gen);
    int sat = 120 + hash % 129;

    return QColor::fromHsl(hue, sat, 160);
}

QColor QExtBPConnectionStyle::selectedColor() const
{
    return SelectedColor;
}

QColor QExtBPConnectionStyle::selectedHaloColor() const
{
    return SelectedHaloColor;
}

QColor QExtBPConnectionStyle::hoveredColor() const
{
    return HoveredColor;
}

float QExtBPConnectionStyle::lineWidth() const
{
    return LineWidth;
}

float QExtBPConnectionStyle::constructionLineWidth() const
{
    return ConstructionLineWidth;
}

float QExtBPConnectionStyle::pointDiameter() const
{
    return PointDiameter;
}

bool QExtBPConnectionStyle::useDataDefinedColors() const
{
    return UseDataDefinedColors;
}
