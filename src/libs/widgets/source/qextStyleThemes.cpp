#include <private/qextStyleThemes_p.h>

#include <QMap>
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QRegularExpression>
#include <QFontDatabase>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QIcon>
#include <QApplication>
#include <QPalette>
#include <QStyle>
#include <QIconEngine>
#include <QSvgRenderer>
#include <QPainter>
#include <QSet>
#include <QMetaEnum>
#include <QStringView>

class QExtStyleThemesSvgIconEngine;

typedef QSet<QExtStyleThemesSvgIconEngine *> QExtStyleThemesSvgIconEngineSet;
Q_GLOBAL_STATIC(QExtStyleThemesSvgIconEngineSet, sg_iconEngineInstances)

/**
 * SvgIcon engine that supports loading from memory buffer
 */
class QExtStyleThemesSvgIconEngine : public QIconEngine
{
public:
    /**
     * Creates an icon engine with the given SVG content an assigned AndvancedStylesheet object
     */
    explicit QExtStyleThemesSvgIconEngine(const QByteArray &svgContent, QExtStyleThemes *styleThemes, const QString &mark = "")
        : m_svgTemplate(svgContent), m_styleTheme(styleThemes), m_styleVariable(mark)
    {
        this->update();
        sg_iconEngineInstances->insert(this);
    }

    /**
     * Removes itself from the set of instances
     */
    ~QExtStyleThemesSvgIconEngine() QEXT_OVERRIDE
    {
        if (!sg_iconEngineInstances.isDestroyed())
        {
            sg_iconEngineInstances->remove(this);
        }
    }

    /**
     * Update the SVG content with the current theme icon colors
     */
    void update()
    {
        m_svgContent = m_svgTemplate;
        m_styleTheme->replaceSvgColors(m_svgContent, m_styleVariable);
    }

    /**
     * Calls update for all m_icon engine instances
     */
    static void updateAllIcons()
    {
        QExtStyleThemesSvgIconEngineSet::Iterator iter = sg_iconEngineInstances->begin();
        while (iter != sg_iconEngineInstances->end())
        {
            (*iter)->update();
            iter++;
        }
    }

    virtual void paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state) QEXT_OVERRIDE
    {
        Q_UNUSED(mode);
        Q_UNUSED(state);

        QSvgRenderer renderer(m_svgContent);
        renderer.render(painter, rect);
    }

    virtual QIconEngine *clone() const QEXT_OVERRIDE
    {
        return new QExtStyleThemesSvgIconEngine(*this);
    }

    virtual QPixmap pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state) QEXT_OVERRIDE
    {
        // This function is necessary to create an EMPTY pixmap. It's called always before paint()
        QImage image(size, QImage::Format_ARGB32);
        image.fill(qRgba(0, 0, 0, 0));
        QPixmap pixmap = QPixmap::fromImage(image, Qt::NoFormatConversion);
        {
            QPainter painter(&pixmap);
            QRect rect(QPoint(0.0, 0.0), size);
            this->paint(&painter, rect, mode, state);
        }
        return pixmap;
    }

private:
    QByteArray m_svgContent; ///< memory buffer with SVG data load from file
    QByteArray m_svgTemplate;
    QExtStyleThemes *m_styleTheme;
    QString m_styleVariable;
};

QExtStyleThemesPrivate::QExtStyleThemesPrivate(QExtStyleThemes *q)
    : q_ptr(q), m_isDarkTheme(false)
{
}

QExtStyleThemesPrivate::~QExtStyleThemesPrivate()
{
}

bool QExtStyleThemesPrivate::generateStylesheet()
{
    Q_Q(QExtStyleThemes);
    QString cssTemplateFileName = m_jsonStyleParam.value("css_template").toString();
    if (cssTemplateFileName.isEmpty())
    {
        return false;
    }

    QString templateFilePath = q->currentStylePath() + "/" + cssTemplateFileName;
    if (!QFile::exists(templateFilePath))
    {
        this->setError(QExtStyleThemes::Error_CssTemplate,
                       "m_stylesheet folder does not contain the CSS template file " + cssTemplateFileName);
        return false;
    }

    QFile templateFile(q->currentStylePath() + "/" + cssTemplateFileName);
    templateFile.open(QIODevice::ReadOnly);
    QString content(templateFile.readAll());
    this->replaceStylesheetVariables(content);
    m_stylesheet = content;
    this->exportInternalStylesheet(QFileInfo(templateFilePath).baseName() + ".css");
    return true;
}

bool QExtStyleThemesPrivate::exportInternalStylesheet(const QString &filename)
{
    return this->storeStylesheet(m_stylesheet, filename);
}

bool QExtStyleThemesPrivate::storeStylesheet(const QString &stylesheet, const QString &filename)
{
    Q_Q(QExtStyleThemes);
    QString outputPath = q->outputDirPath();
    QDir().mkpath(outputPath);
    QString outputFilename = outputPath + "/" + filename;
    QFile outputFile(outputFilename);
    if (!outputFile.open(QIODevice::WriteOnly))
    {
        this->setError(QExtStyleThemes::Error_CssExport,
                       "Exporting stylesheet " + filename + " caused error: " + outputFile.errorString());
        return false;
    }
    outputFile.write(stylesheet.toUtf8());
    outputFile.close();
    return true;
}

bool QExtStyleThemesPrivate::parseVariablesFromXml(QXmlStreamReader &reader, const QString &tagName,
                                                   QMap<QString, QString> &variables)
{
    while (reader.readNextStartElement())
    {
        if (reader.name() != tagName)
        {
            this->setError(QExtStyleThemes::Error_ThemeXml,
                           "Malformed theme file - expected tag <" + tagName + "> instead of " +
                               reader.name().toString());
            return false;
        }
        QStringRef name = reader.attributes().value("name");
        if (name.isEmpty())
        {
            this->setError(QExtStyleThemes::Error_ThemeXml,
                           "Malformed theme file - name attribute missing in <" + tagName + "> tag");
            return false;
        }

        QString value = reader.readElementText(QXmlStreamReader::SkipChildElements);
        if (value.isEmpty())
        {
            this->setError(QExtStyleThemes::Error_ThemeXml,
                           "Malformed theme file - text of <" + tagName + "> tag is empty");
            return false;
        }

        variables.insert(name.toString(), value);
    }

    return true;
}

bool QExtStyleThemesPrivate::parseThemeFile(const QString &fileName)
{
    Q_Q(QExtStyleThemes);
    QString themeFileName = q->currentStyleLocationPath(QExtStyleThemes::Location_Themes) + "/" + fileName;
    QFile themeFile(themeFileName);
    themeFile.open(QIODevice::ReadOnly);
    QXmlStreamReader reader(&themeFile);
    reader.readNextStartElement();
    if (reader.name() != QLatin1String("resources"))
    {
        this->setError(QExtStyleThemes::Error_ThemeXml,
                       "Malformed theme file - expected tag <resources> instead of " + reader.name().toString());
        return false;
    }

    m_isDarkTheme = (reader.attributes().value("dark").toInt() == 1);
    QMap<QString, QString> colorVariables;
    this->parseVariablesFromXml(reader, "color", colorVariables);
    m_themeVariables = m_styleVariables;
    insertIntoMap(m_themeVariables, colorVariables);
    m_themeColors = colorVariables;
    return true;
}

bool QExtStyleThemesPrivate::parseStyleJsonFile()
{
    Q_Q(QExtStyleThemes);
    QDir dir(q->currentStylePath());
    QFileInfoList jsonFiles = dir.entryInfoList(QStringList() << "*.json", QDir::Files);
    if (jsonFiles.count() < 1)
    {
        this->setError(QExtStyleThemes::Error_StyleJson,
                       "m_stylesheet folder does not contain a style json file");
        return false;
    }

    if (jsonFiles.count() > 1)
    {
        this->setError(QExtStyleThemes::Error_StyleJson,
                       "m_stylesheet folder contains multiple theme json files");
        return false;
    }

    QFile styleJsonFile(jsonFiles[0].absoluteFilePath());
    styleJsonFile.open(QIODevice::ReadOnly);

    QByteArray jsonData = styleJsonFile.readAll();
    QJsonParseError parseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData, &parseError);
    if (jsonDocument.isNull())
    {
        this->setError(QExtStyleThemes::Error_StyleJson,
                       "Loading style json file caused error: " + parseError.errorString());
        return false;
    }

    QJsonObject json = m_jsonStyleParam = jsonDocument.object();
    m_styleName = json.value("name").toString();
    if (m_styleName.isEmpty())
    {
        this->setError(QExtStyleThemes::Error_StyleJson, "No key \"name\" found in style json file");
        return false;
    }

    QMap<QString, QString> variables;
    QJsonObject jvariables = json.value("variables").toObject();
    for (QJsonObject::Iterator iter = jvariables.begin(); iter != jvariables.end(); ++iter)
    {
        variables.insert(iter.key(), jvariables.value(iter.key()).toString());
    }

    m_styleVariables = variables;
    m_iconFile = json.value("icon").toString();
    this->parsePaletteFromJson();

    m_defaultTheme = json.value("default_theme").toString();
    if (m_defaultTheme.isEmpty())
    {
        this->setError(QExtStyleThemes::Error_StyleJson, "No key \"default_theme\" found in style json file");
        return false;
    }

    return true;
}

QString QExtStyleThemesPrivate::rgbaColor(const QString &rgbColor, float opacity)
{
    int alpha = 255 * opacity;
    QString rgbaColor = rgbColor;
    rgbaColor.insert(1, QString::number(alpha, 16));
    return rgbaColor;
}

void QExtStyleThemesPrivate::replaceStylesheetVariables(QString &templateContent)
{
    Q_Q(QExtStyleThemes);
    static const int opacityStrSize = QString("opacity(").size();
    // not use "\\{\\{.*\\}\\}" to avoid greedy patterns, to avoid matching multiple {{...}} structures at once
    static const QRegularExpression re("\\{\\{.*?}\\}");
    QRegularExpressionMatch match;
    int index = 0;
    while ((index = templateContent.indexOf(re, index, &match)) != -1)
    {
        QString valueString;
        QString matchString = match.captured();
        // Use only the value inside of the brackets {{ }} without the brackets
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        QStringRef templateVariable = matchString.midRef(2, matchString.size() - 4);
#else
        QStringRef templateVariable = QStringView(MatchString).sliced(2, MatchString.size() - 4);
#endif
        bool hasOpacity = templateVariable.endsWith(')');
        if (hasOpacity)
        {
            QVector<QStringRef> values = templateVariable.split(QChar('|'));
            valueString = q->themeVariableValue(values[0].toString());
            QStringRef opacityStr = values[1].mid(opacityStrSize, values[1].size() - opacityStrSize - 1);
            bool ok;
            float opacity = opacityStr.toFloat(&ok);
            valueString = this->rgbaColor(valueString, opacity);
        }
        else
        {
            valueString = q->themeVariableValue(templateVariable.toString());
        }

        templateContent.replace(index, matchString.size(), valueString);
        index += valueString.size();
    }
}

void QExtStyleThemesPrivate::addFonts(QDir *dir)
{
    Q_Q(QExtStyleThemes);
    /* I dont't know, if this is the right way to detect, if there are any widgets.
     * The call to QFontDatabase::addApplicationFont() will crash, if there are no widgets
     */
    // if (qApp->allWidgets().isEmpty())
    // {
    //     return;
    // }

    if (!dir)
    {
        QDir fontsDir(q->currentStyleLocationPath(QExtStyleThemes::Location_Fonts));
        this->addFonts(&fontsDir);
    }
    else
    {
        QStringList folders = dir->entryList(QDir::Dirs | QDir::NoDotAndDotDot);
        for (QStringList::Iterator iter = folders.begin(); iter != folders.end(); ++iter)
        {
            dir->cd(*iter);
            this->addFonts(dir);
            dir->cdUp();
        }

        QStringList fontFiles = dir->entryList({"*.ttf"}, QDir::Files);
        for (QStringList::Iterator iter = fontFiles.begin(); iter != fontFiles.end(); ++iter)
        {
            QString fontFilename = dir->absoluteFilePath(*iter);
            QFontDatabase::addApplicationFont(fontFilename);
        }
    }

    // qDebug() <<
}

bool QExtStyleThemesPrivate::generateResourcesFor(const QString &subDir, const QJsonObject &jsonObject,
                                                  const QFileInfoList &entries)
{
    Q_Q(QExtStyleThemes);
    const QString outputDir = q->currentStyleOutputPath() + "/" + subDir;
    if (!QDir().mkpath(outputDir))
    {
        this->setError(QExtStyleThemes::Error_ResourceGenerator, "error creating resource output folder: " + outputDir);
        return false;
    }

    QExtStyleThemes::ColorReplaceVector colorReplaceVector = this->parseColorReplaceList(jsonObject);
    // Now loop through all resources svg files and replace the colors
    for (QFileInfoList::ConstIterator iter = entries.constBegin(); iter != entries.constEnd(); ++iter)
    {
        QFile svgFile(iter->absoluteFilePath());
        svgFile.open(QIODevice::ReadOnly);
        QByteArray content = svgFile.readAll();
        svgFile.close();
        q->replaceSvgColors(content, colorReplaceVector);
        QString outputFilename = outputDir + "/" + iter->fileName();
        QFile outputFile(outputFilename);
        outputFile.open(QIODevice::WriteOnly);
        outputFile.write(content);
        outputFile.close();
    }
    return true;
}

bool QExtStyleThemesPrivate::replaceColor(QByteArray &content, const QString &templateColor,
                                          const QString &themeColor) const
{
    QByteArray templateColorBytes = templateColor.toLatin1();
    if (content.contains(templateColorBytes))
    {
        content.replace(templateColorBytes, themeColor.toLatin1());
        return true;
    }
    return false;
}

void QExtStyleThemesPrivate::setDomAttribute(QDomElement &element, const QString &tagName, const QString &attrName,
                                             const QString &attrVal, const QStringList &exclusiveAttrNames,
                                             const QSet<QString> &ignoredAttrVals) const
{
    // if it has the tagname then overwritte desired attribute
    if (element.tagName() == tagName)
    {
        QString attribute = element.attribute(attrName);
        if (!exclusiveAttrNames.contains(attribute) || attribute.isEmpty())
        {
            bool exclusived = false;
            QStringList::ConstIterator iter = exclusiveAttrNames.begin();
            while (iter != exclusiveAttrNames.end())
            {
                if (element.hasAttribute(*iter))
                {
                    exclusived = true;
                }
                iter++;
            }
            if (!exclusived)
            {
                element.setAttribute(attrName, attrVal);
            }
        }
    }
    // loop all children
    QDomNodeList domNodeList = element.childNodes();
    for (int i = 0; i < domNodeList.count(); i++)
    {
        QDomNode node = domNodeList.at(i);
        if (node.isElement())
        {
            QDomElement childElement = node.toElement();
            this->setDomAttribute(childElement, tagName, attrName, attrVal, exclusiveAttrNames, ignoredAttrVals);
        }
    }
}

void QExtStyleThemesPrivate::setError(QExtStyleThemes::ErrorEnum error, const QString &errorString)
{
    m_error = error;
    m_errorString = errorString;
    if (m_error != QExtStyleThemes::Error_None)
    {
        qDebug() << "QExtStyleThemes error: " << m_error << " " << m_errorString;
    }
}

void QExtStyleThemesPrivate::parsePaletteFromJson()
{
    m_paletteBaseColor = QString();
    m_paletteColors.clear();
    QJsonObject jPalette = m_jsonStyleParam.value("palette").toObject();
    if (jPalette.isEmpty())
    {
        return;
    }

    m_paletteBaseColor = jPalette.value("base_color").toString();
    this->parsePaletteColorGroup(jPalette, QPalette::Active);
    this->parsePaletteColorGroup(jPalette, QPalette::Disabled);
    this->parsePaletteColorGroup(jPalette, QPalette::Inactive);
}

void QExtStyleThemesPrivate::parsePaletteColorGroup(QJsonObject &jPalette, QPalette::ColorGroup colorGroup)
{
    QJsonObject jColorGroup = jPalette.value(colorGroupString(colorGroup)).toObject();
    if (jColorGroup.isEmpty())
    {
        return;
    }

    for (QJsonObject::ConstIterator iter = jColorGroup.constBegin(); iter != jColorGroup.constEnd(); ++iter)
    {
        QPalette::ColorRole colorRole = colorRoleFromString(iter.key());
        if (QPalette::NoRole == colorRole)
        {
            continue;
        }
        this->m_paletteColors.append(PaletteColorEntry(colorGroup, colorRole, iter.value().toString()));
        if (QPalette::Active != colorGroup)
        {
            continue;
        }
    }
}

const QString &QExtStyleThemesPrivate::iconDefaultColor()
{
    Q_Q(const QExtStyleThemes);
    if (!m_iconDefaultColor.isEmpty())
    {
        return m_iconDefaultColor;
    }

    QJsonValue jsonIconDefaultColor = m_jsonStyleParam.value("icon_default_color");
    if (!jsonIconDefaultColor.isString())
    {
        return m_iconDefaultColor;
    }

    m_iconDefaultColor = jsonIconDefaultColor.toString();
    // If the color starts with an hashtag, then we have a real color value
    // If it does not start with # then it is a theme variable
    if (!m_iconDefaultColor.startsWith('#'))
    {
        m_iconDefaultColor = q->themeVariableValue(m_iconDefaultColor);
    }
    return m_iconDefaultColor;
}

const QExtStyleThemes::ColorReplaceVector &QExtStyleThemesPrivate::iconColorReplaceList() const
{
    if (m_iconColorReplaceList.count() > 0)
    {
        return m_iconColorReplaceList;
    }

    QJsonObject jsonIconColors = m_jsonStyleParam.value("icon_colors").toObject();
    if (jsonIconColors.isEmpty())
    {
        return m_iconColorReplaceList;
    }

    m_iconColorReplaceList = this->parseColorReplaceList(jsonIconColors);
    return m_iconColorReplaceList;
}

QExtStyleThemes::ColorReplaceVector QExtStyleThemesPrivate::parseColorReplaceList(const QJsonObject &jsonObject) const
{
    Q_Q(const QExtStyleThemes);
    // Fill the color replace list with the values read from style json file
    QExtStyleThemes::ColorReplaceVector colorReplaceVector;
    for (QJsonObject::ConstIterator iter = jsonObject.constBegin(); iter != jsonObject.constEnd(); ++iter)
    {
        QString templateColor = iter.key();
        QString themeColor = iter.value().toString();
        // If the color starts with an hashtag, then we have a real color value
        // If it does not start with # then it is a theme variable
        if (!themeColor.startsWith('#'))
        {
            themeColor = q->themeVariableValue(themeColor);
        }
        colorReplaceVector.append({templateColor, themeColor});
    }

    return colorReplaceVector;
}

QPalette::ColorRole QExtStyleThemesPrivate::colorRoleFromString(const QString &text)
{
    static QMap<QString, QPalette::ColorRole> colorRoleMap =
    {{"WindowText", QPalette::WindowText},
      {"Button", QPalette::Button},
      {"Light", QPalette::Light},
      {"Midlight", QPalette::Midlight},
      {"Dark", QPalette::Dark},
      {"Mid", QPalette::Mid},
      {"Text", QPalette::Text},
      {"BrightText", QPalette::BrightText},
      {"ButtonTextd", QPalette::ButtonText},
      {"Base", QPalette::Base},
      {"Window", QPalette::Window},
      {"Shadow", QPalette::Shadow},
      {"Highlight", QPalette::Highlight},
      {"HighlightedText", QPalette::HighlightedText},
      {"Link", QPalette::Link},
      {"LinkVisited", QPalette::LinkVisited},
      {"AlternateBase", QPalette::AlternateBase},
      {"NoRole", QPalette::NoRole},
      {"ToolTipBase", QPalette::ToolTipBase},
      {"ToolTipText", QPalette::ToolTipText},
#if QT_VERSION >= 0x050C00
      {"PlaceholderText", QPalette::PlaceholderText}
#endif
    };

    return colorRoleMap.value(text, QPalette::NoRole);
}

QString QExtStyleThemesPrivate::colorGroupString(QPalette::ColorGroup colorGroup)
{
    switch (colorGroup)
    {
    case QPalette::Active:
        return "active";
    case QPalette::Disabled:
        return "disabled";
    case QPalette::Inactive:
        return "inactive";
    default:
        return QString();
    }
    return QString();
}

QExtStyleThemes::QExtStyleThemes(QObject *parent)
    : QObject(parent), dd_ptr(new QExtStyleThemesPrivate(this))
{
}

QExtStyleThemes::~QExtStyleThemes()
{
}

void QExtStyleThemes::setStylesDirPath(const QString &path)
{
    Q_D(QExtStyleThemes);
    d->m_stylesDir = path.isEmpty() ? ":/QExtWidgets/stylethemes" : path;
    QDir Dir(d->m_stylesDir);
    d->m_styles = Dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
}

QString QExtStyleThemes::stylesDirPath() const
{
    Q_D(const QExtStyleThemes);
    return d->m_stylesDir;
}

QString QExtStyleThemes::currentStyle() const
{
    Q_D(const QExtStyleThemes);
    return d->m_currentStyle;
}

QString QExtStyleThemes::currentStylePath() const
{
    Q_D(const QExtStyleThemes);
    return d->m_stylesDir + "/" + d->m_currentStyle;
}

const QStringList &QExtStyleThemes::styles() const
{
    Q_D(const QExtStyleThemes);
    return d->m_styles;
}

const QStringList &QExtStyleThemes::themes() const
{
    Q_D(const QExtStyleThemes);
    return d->m_themes;
}

QStringList QExtStyleThemes::themes(const QString &style) const
{
    Q_D(const QExtStyleThemes);
    QString stylePath = d->m_stylesDir + "/" + style;
    QDir dir(this->styleLocationPath(stylePath, Location_Themes));
    QStringList themes = dir.entryList(QStringList() << "*.xml", QDir::Files);
    for (QStringList::Iterator iter = themes.begin(); iter != themes.end(); ++iter)
    {
        iter->replace(".xml", "");
    }
    return themes;
}

QStringList QExtStyleThemes::styleThemes() const
{
    QStringList styleThemes;
    QStringList styles = this->styles();
    for (QStringList::ConstIterator stylesIter = styles.begin(); stylesIter != styles.end(); ++stylesIter)
    {
        QStringList themes = this->themes(*stylesIter);
        for (QStringList::ConstIterator themesIter = themes.begin(); themesIter != themes.end(); ++themesIter)
        {
            styleThemes.append(QString("%1 %2").arg(*stylesIter).arg(*themesIter));
        }
    }
    return styleThemes;
}

QStringList QExtStyleThemes::styleThemes(const QString &style) const
{
    QStringList styleThemes;
    QStringList themes = this->themes(style);
    for (QStringList::ConstIterator themesIter = themes.begin(); themesIter != themes.end(); ++themesIter)
    {
        styleThemes.append(QString("%1 %2").arg(style).arg(*themesIter));
    }
    return styleThemes;
}

const QMap<QString, QString> &QExtStyleThemes::themeColorVariables() const
{
    Q_D(const QExtStyleThemes);
    return d->m_themeColors;
}

QString QExtStyleThemes::styleLocationPath(const QString &stylePath, QExtStyleThemes::LocationEnum location) const
{
    switch (location)
    {
    case Location_Fonts:
        return stylePath + "/fonts";
    case Location_Themes:
        return stylePath + "/themes";
    case Location_SvgsTemplates:
        return stylePath + "/svgs";
    }
    return QString();
}

QString QExtStyleThemes::currentStyleLocationPath(QExtStyleThemes::LocationEnum location) const
{
    return this->styleLocationPath(this->currentStylePath(), location);
}

QString QExtStyleThemes::outputDirPath() const
{
    Q_D(const QExtStyleThemes);
    return d->m_outputDir;
}

void QExtStyleThemes::setOutputDirPath(const QString &path)
{
    Q_D(QExtStyleThemes);
    d->m_outputDir = path;
    QDir::addSearchPath("icon", path);
}

QString QExtStyleThemes::currentStyleOutputPath() const
{
    Q_D(const QExtStyleThemes);
    return this->outputDirPath() + "/" + d->m_currentStyle;
}

QString QExtStyleThemes::themeVariableValue(const QString &variableId) const
{
    Q_D(const QExtStyleThemes);
    return d->m_themeVariables.value(variableId, QString());
}

void QExtStyleThemes::setThemeVariableValue(const QString &variableId, const QString &value)
{
    Q_D(QExtStyleThemes);
    d->m_themeVariables.insert(variableId, value);
    QMap<QString, QString>::Iterator iter = d->m_themeColors.find(variableId);
    if (iter != d->m_themeColors.end())
    {
        iter.value() = value;
    }
}

QColor QExtStyleThemes::themeColor(const QString &variableId) const
{
    Q_D(const QExtStyleThemes);
    QString colorString = d->m_themeColors.value(variableId, QString());
    return colorString.isEmpty() ? QColor() : QColor(colorString);
}

QString QExtStyleThemes::currentTheme() const
{
    Q_D(const QExtStyleThemes);
    return d->m_currentTheme;
}

QString QExtStyleThemes::currentStyleTheme() const
{
    Q_D(const QExtStyleThemes);
    return QString("%1 %2").arg(d->m_currentStyle).arg(d->m_currentTheme);
}

QString QExtStyleThemes::styleSheet() const
{
    Q_D(const QExtStyleThemes);
    return d->m_stylesheet;
}

QString QExtStyleThemes::processStylesheetTemplate(const QString &templateText, const QString &outputFile)
{
    Q_D(QExtStyleThemes);
    QString stylesheet = templateText;
    d->replaceStylesheetVariables(stylesheet);
    if (!outputFile.isEmpty())
    {
        d->storeStylesheet(stylesheet, outputFile);
    }
    return stylesheet;
}

const QIcon &QExtStyleThemes::styleIcon() const
{
    Q_D(const QExtStyleThemes);
    if (d->m_icon.isNull() && !d->m_iconFile.isEmpty())
    {
        d->m_icon = QIcon(currentStylePath() + "/" + d->m_iconFile);
    }
    return d->m_icon;
}

QExtStyleThemes::ErrorEnum QExtStyleThemes::error() const
{
    Q_D(const QExtStyleThemes);
    return d->m_error;
}

QString QExtStyleThemes::errorString() const
{
    Q_D(const QExtStyleThemes);
    return d->m_errorString;
}

QPalette QExtStyleThemes::generateThemePalette() const
{
    Q_D(const QExtStyleThemes);
    QPalette palette = qApp->palette();
    if (!d->m_paletteBaseColor.isEmpty())
    {
        QColor color = themeColor(d->m_paletteBaseColor);
        if (color.isValid())
        {
            palette = QPalette(color);
        }
    }

    QVector<QExtStyleThemesPrivate::PaletteColorEntry>::ConstIterator iter = d->m_paletteColors.constBegin();
    while (iter != d->m_paletteColors.constEnd())
    {
        QColor color = this->themeColor(iter->colorVariable);
        if (color.isValid())
        {
#if 0
            QMetaEnum colorGroupEnum = QMetaEnum::fromType<QPalette::ColorGroup>();
            QMetaEnum colorRoleEnum = QMetaEnum::fromType<QPalette::ColorRole>();
            qDebug() << QString("group=%1, role=%2, color=%3")
                            .arg(colorGroupEnum.valueToKey(iter->group))
                            .arg(colorRoleEnum.valueToKey(iter->role))
                            .arg(color.name());
#endif
            palette.setColor(iter->group, iter->role, color);
        }
        iter++;
    }

    return palette;
}

const QJsonObject &QExtStyleThemes::styleParameters() const
{
    Q_D(const QExtStyleThemes);
    return d->m_jsonStyleParam;
}

bool QExtStyleThemes::isCurrentThemeDark() const
{
    Q_D(const QExtStyleThemes);
    return d->m_isDarkTheme;
}

void QExtStyleThemes::replaceSvgColors(QByteArray &svgContent, const ColorReplaceVector &colorReplaceVector)
{
    Q_D(QExtStyleThemes);
    QSet<QString> replacedColorSet;
    const QExtStyleThemes::ColorReplaceVector &replaceList = colorReplaceVector.isEmpty() ? d->iconColorReplaceList()
                                                                                          : colorReplaceVector;
    QExtStyleThemes::ColorReplaceVector::ConstIterator iter = replaceList.begin();
    while (iter != replaceList.end())
    {
        if (d->replaceColor(svgContent, iter->first, iter->second))
        {
            replacedColorSet.insert(iter->first);
        }
        iter++;
    }
    replacedColorSet.insert("none");

    QDomDocument domDocument;
    domDocument.setContent(svgContent);
    QDomElement domElement = domDocument.documentElement();
    d->setDomAttribute(domElement, "path", "fill", d->iconDefaultColor(), QStringList() << "style", replacedColorSet);
    svgContent = domDocument.toByteArray();
}

void QExtStyleThemes::replaceSvgColors(QByteArray &svgContent, const QString &variable)
{
    Q_D(QExtStyleThemes);
    if (d->m_styleVariables.contains(variable))
    {
        const QString color = d->m_styleVariables.value(variable);
        QDomDocument domDocument;
        domDocument.setContent(svgContent);
        QDomElement domElement = domDocument.documentElement();
        d->setDomAttribute(domElement, "path", "fill", color, QStringList() << "style");
        svgContent = domDocument.toByteArray();
    }
    else
    {
        this->replaceSvgColors(svgContent);
    }
}

QIcon QExtStyleThemes::loadThemeAwareSvgIcon(const QString &fileName, const QString &variable)
{
    QFile svgFile(fileName);
    svgFile.open(QIODevice::ReadOnly);
    QByteArray content = svgFile.readAll();
    return QIcon(new QExtStyleThemesSvgIconEngine(content, this, variable));
}

bool QExtStyleThemes::setCurrentTheme(const QString &theme)
{
    Q_D(QExtStyleThemes);
    d->clearError();
    if (d->m_jsonStyleParam.isEmpty())
    {
        return false;
    }
    if (!d->parseThemeFile(theme + ".xml"))
    {
        return false;
    }
    d->m_currentTheme = theme;
    emit this->currentThemeChanged(d->m_currentTheme);
    return true;
}

void QExtStyleThemes::setDefaultTheme()
{
    Q_D(QExtStyleThemes);
    this->setCurrentTheme(d->m_defaultTheme);
}

bool QExtStyleThemes::setCurrentStyle(const QString &style)
{
    Q_D(QExtStyleThemes);
    d->clearError();
    d->m_currentStyle = style;
    QDir dir(this->currentStyleLocationPath(Location_Themes));
    d->m_themes = dir.entryList(QStringList() << "*.xml", QDir::Files);
    for (QStringList::Iterator iter = d->m_themes.begin(); iter != d->m_themes.end(); ++iter)
    {
        iter->replace(".xml", "");
    }
    bool result = d->parseStyleJsonFile();
    d->addFonts();
    emit this->currentStyleChanged(d->m_currentStyle);
    emit this->stylesheetChanged();
    return result;
}

bool QExtStyleThemes::setCurrentStyleTheme(const QString &styleTheme)
{
    QStringList split = styleTheme.split(" ");
    if (2 == split.size())
    {
        if (this->setCurrentStyle(split.first()))
        {
            this->setDefaultTheme();
            return this->setCurrentTheme(split.last());
        }
    }
}

bool QExtStyleThemes::updateStylesheet()
{
    Q_D(QExtStyleThemes);
    if (!this->processStyleTemplate())
    {
        return false;
    }

    d->m_iconDefaultColor.clear();
    d->m_iconColorReplaceList.clear();
    QExtStyleThemesSvgIconEngine::updateAllIcons();
    if (!d->generateStylesheet() && (error() != QExtStyleThemes::Error_None))
    {
        return false;
    }

    emit this->stylesheetChanged();
    return true;
}

bool QExtStyleThemes::processStyleTemplate()
{
    this->updateApplicationPaletteColors();
    return this->generateResources();
}

bool QExtStyleThemes::generateResources()
{
    Q_D(QExtStyleThemes);
    QDir resourceDir(this->currentStyleLocationPath(QExtStyleThemes::Location_SvgsTemplates));
    QFileInfoList entries = resourceDir.entryInfoList({"*.svg"}, QDir::Files);

    QJsonObject jsonResources = d->m_jsonStyleParam.value("resources").toObject();
    if (jsonResources.isEmpty())
    {
        d->setError(QExtStyleThemes::Error_StyleJson, "Key resources missing in style json file");
        return false;
    }

    // Process all resource generation variants
    bool result = true;
    for (QJsonObject::ConstIterator iter = jsonResources.constBegin(); iter != jsonResources.constEnd(); ++iter)
    {
        QJsonObject param = iter.value().toObject();
        if (param.isEmpty())
        {
            d->setError(QExtStyleThemes::Error_StyleJson, "Key resources missing in style json file");
            result = false;
            continue;
        }
        if (!d->generateResourcesFor(iter.key(), param, entries))
        {
            result = false;
        }
    }

    return result;
}

void QExtStyleThemes::updateApplicationPaletteColors()
{
    qApp->setPalette(this->generateThemePalette());
}
