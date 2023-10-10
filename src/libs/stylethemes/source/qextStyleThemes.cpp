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
#include <QStringView>

#include <iostream>


class QExtStyleThemesSvgIconEngine;
typedef QSet<QExtStyleThemesSvgIconEngine *> QExtStyleThemesSvgIconEngineSet;
Q_GLOBAL_STATIC(QExtStyleThemesSvgIconEngineSet, sg_iconEngineInstances)


/**
 * SvgIcon engine that supports loading from memory buffer
 */
class QExtStyleThemesSvgIconEngine : public QIconEngine
{
private:
    QByteArray m_svgContent; ///< memory buffer with SVG data load from file
    QByteArray m_svgTemplate;
    QExtStyleThemes *m_styleTheme;

public:
    /**
     * Creates an icon engine with the given SVG content an assigned AndvancedStylesheet object
     */
    explicit QExtStyleThemesSvgIconEngine(const QByteArray &svgContent, QExtStyleThemes *styleThemes)
        : m_svgTemplate(svgContent)
        , m_styleTheme(styleThemes)
    {
        this->update();
        sg_iconEngineInstances->insert(this);
    }

    /**
     * Removes itself from the set of instances
     */
    virtual ~QExtStyleThemesSvgIconEngine()
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
        m_styleTheme->replaceSvgColors(m_svgContent);
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

    virtual void paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state) override
    {
        Q_UNUSED(mode);
        Q_UNUSED(state);

        QSvgRenderer renderer(m_svgContent);
        renderer.render(painter, rect);
    }

    virtual QIconEngine *clone() const QEXT_DECL_OVERRIDE
    {
        return new QExtStyleThemesSvgIconEngine(*this);
    }

    virtual QPixmap pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state) QEXT_DECL_OVERRIDE
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
};


QExtStyleThemesPrivate::QExtStyleThemesPrivate(QExtStyleThemes *q)
    : q_ptr(q)
    , m_isDarkTheme(false)
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
        this->setError(QExtStyleThemes::CssTemplateError,
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
    QString outputPath = q->currentStyleOutputPath();
    QDir().mkpath(outputPath);
    QString outputFilename = outputPath + "/" + filename;
    QFile outputFile(outputFilename);
    if (!outputFile.open(QIODevice::WriteOnly))
    {
        this->setError(QExtStyleThemes::CssExportError,
                       "Exporting stylesheet " + filename + " caused error: " + outputFile.errorString());
        return false;
    }
    outputFile.write(stylesheet.toUtf8());
    outputFile.close();
    return true;
}

bool QExtStyleThemesPrivate::parseVariablesFromXml(QXmlStreamReader &reader, const QString &tagName, QMap<QString, QString> &variables)
{
    Q_Q(QExtStyleThemes);
    while (reader.readNextStartElement())
    {
        if (reader.name() != tagName)
        {
            this->setError(QExtStyleThemes::ThemeXmlError,
                           "Malformed theme file - expected tag <" + tagName + "> instead of " + reader.name().toString());
            return false;
        }
        QStringRef name = reader.attributes().value("name");
        if (name.isEmpty())
        {
            this->setError(QExtStyleThemes::ThemeXmlError,
                           "Malformed theme file - name attribute missing in <" + tagName + "> tag");
            return false;
        }

        QString value = reader.readElementText(QXmlStreamReader::SkipChildElements);
        if (value.isEmpty())
        {
            this->setError(QExtStyleThemes::ThemeXmlError,
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
    QString themeFileName = q->path(QExtStyleThemes::ThemesLocation) + "/" + fileName;
    QFile themeFile(themeFileName);
    themeFile.open(QIODevice::ReadOnly);
    QXmlStreamReader reader(&themeFile);
    reader.readNextStartElement();
    if (reader.name() != QLatin1String("resources"))
    {
        this->setError(QExtStyleThemes::ThemeXmlError,
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
        this->setError(QExtStyleThemes::StyleJsonError,
                       "m_stylesheet folder does not contain a style json file");
        return false;
    }

    if (jsonFiles.count() > 1)
    {
        this->setError(QExtStyleThemes::StyleJsonError,
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
        this->setError(QExtStyleThemes::StyleJsonError,
                       "Loading style json file caused error: " + parseError.errorString());
        return false;
    }

    QJsonObject json = m_jsonStyleParam = jsonDocument.object();
    m_styleName = json.value("name").toString();
    if (m_styleName.isEmpty())
    {
        this->setError(QExtStyleThemes::StyleJsonError, "No key \"name\" found in style json file");
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
        this->setError(QExtStyleThemes::StyleJsonError, "No key \"default_theme\" found in style json file");
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
    QRegularExpression re("\\{\\{.*\\}\\}");
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
    /* I dont't know, if this is the right way to detect, if there are any widgets. The call to
     * QFontDatabase::addApplicationFont() will crash, if there are no widgets */
    if (qApp->allWidgets().isEmpty())
    {
        return;
    }

    if (!dir)
    {
        QDir fontsDir(q->path(QExtStyleThemes::FontsLocation));
        this->addFonts(&fontsDir);
    }
    else
    {
        QStringList folders = dir->entryList(QDir::Dirs | QDir::NoDotAndDotDot);
        for (QStringList::Iterator iter = folders.begin(); iter != folders.end(); ++iter)
        {
            dir->cd(*iter);
            addFonts(dir);
            dir->cdUp();
        }

        QStringList fontFiles = dir->entryList({"*.ttf"}, QDir::Files);
        for (QStringList::Iterator iter = folders.begin(); iter != folders.end(); ++iter)
        {
            QString fontFilename = dir->absoluteFilePath(*iter);
            QFontDatabase::addApplicationFont(fontFilename);
        }
    }
}

bool QExtStyleThemesPrivate::generateResourcesFor(const QString &subDir, const QJsonObject &jsonObject, const QFileInfoList &entries)
{
    Q_Q(QExtStyleThemes);
    const QString outputDir = q->currentStyleOutputPath() + "/" + subDir;
    if (!QDir().mkpath(outputDir))
    {
        this->setError(QExtStyleThemes::ResourceGeneratorError, "error creating resource output folder: " + outputDir);
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

void QExtStyleThemesPrivate::replaceColor(QByteArray &content, const QString &templateColor, const QString &themeColor) const
{
    content.replace(templateColor.toLatin1(), themeColor.toLatin1());
}

void QExtStyleThemesPrivate::setError(QExtStyleThemes::ErrorEnum error, const QString &errorString)
{
    m_error = error;
    m_errorString = errorString;
    if (m_error != QExtStyleThemes::NoError)
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

const QExtStyleThemes::ColorReplaceVector &QExtStyleThemesPrivate::iconColorReplaceList() const
{
    if (m_iconColorReplaceList.count())
    {
        return m_iconColorReplaceList;
    }

    QJsonObject jIconColors = m_jsonStyleParam.value("icon_colors").toObject();
    if (jIconColors.isEmpty())
    {
        return m_iconColorReplaceList;
    }

    m_iconColorReplaceList = this->parseColorReplaceList(jIconColors);
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
    case QPalette::Active: return "active";
    case QPalette::Disabled: return "disabled";
    case QPalette::Inactive: return "inactive";
    default: return QString();
    }
    return QString();
}



QExtStyleThemes::QExtStyleThemes(QObject *parent)
    : QObject(parent)
    , dd_ptr(new QExtStyleThemesPrivate(this))
{

}

QExtStyleThemes::~QExtStyleThemes()
{

}

void QExtStyleThemes::setStylesDirPath(const QString &path)
{
    Q_D(QExtStyleThemes);
    d->m_stylesDir = path;
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

const QMap<QString, QString> &QExtStyleThemes::themeColorVariables() const
{
    Q_D(const QExtStyleThemes);
    return d->m_themeColors;
}

QString QExtStyleThemes::path(LocationEnum location) const
{
    Q_D(const QExtStyleThemes);
    switch (location)
    {
    case ThemesLocation:
        return this->currentStylePath() + "/themes";
    case ResourceTemplatesLocation:
        return this->currentStylePath() + "/resources";
    case FontsLocation:
        return this->currentStylePath() + "/fonts";
    }
    return QString();
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
        QColor color = themeColor(iter->ColorVariable);
        if (color.isValid())
        {
            palette.setColor(iter->Group, iter->Role, themeColor(iter->ColorVariable));
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
    const QExtStyleThemes::ColorReplaceVector &ReplaceList = colorReplaceVector.isEmpty() ? d->iconColorReplaceList()
                                                                                          : colorReplaceVector;
    QExtStyleThemes::ColorReplaceVector::ConstIterator iter = ReplaceList.begin();
    while (iter != ReplaceList.end())
    {
        d->replaceColor(svgContent, iter->first, iter->second);
        iter++;
    }
}

QIcon QExtStyleThemes::loadThemeAwareSvgIcon(const QString &fileName)
{
    QFile svgFile(fileName);
    svgFile.open(QIODevice::ReadOnly);
    QByteArray content = svgFile.readAll();
    return QIcon(new QExtStyleThemesSvgIconEngine(content, this));
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
    QDir dir(path(ThemesLocation));
    d->m_themes = dir.entryList({"*.xml"}, QDir::Files);
    for (QStringList::Iterator iter = d->m_themes.begin(); iter != d->m_themes.end(); ++iter)
    {
        iter->replace(".xml", "");
    }
    bool result = d->parseStyleJsonFile();
    QDir::addSearchPath("icon", currentStyleOutputPath());
    d->addFonts();
    emit this->currentStyleChanged(d->m_currentStyle);
    emit this->stylesheetChanged();
    return result;
}

bool QExtStyleThemes::updateStylesheet()
{
    Q_D(QExtStyleThemes);
    if (!this->processStyleTemplate())
    {
        return false;
    }

    d->m_iconColorReplaceList.clear();
    QExtStyleThemesSvgIconEngine::updateAllIcons();
    if (!d->generateStylesheet() && (error() != QExtStyleThemes::NoError))
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
    QDir resourceDir(path(QExtStyleThemes::ResourceTemplatesLocation));
    QFileInfoList entries = resourceDir.entryInfoList({"*.svg"}, QDir::Files);

    QJsonObject jresources = d->m_jsonStyleParam.value("resources").toObject();
    if (jresources.isEmpty())
    {
        d->setError(QExtStyleThemes::StyleJsonError, "Key resources missing in style json file");
        return false;
    }

    // Process all resource generation variants
    bool result = true;
    for (QJsonObject::ConstIterator iter = jresources.constBegin(); iter != jresources.constEnd(); ++iter)
    {
        QJsonObject param = iter.value().toObject();
        if (param.isEmpty())
        {
            d->setError(QExtStyleThemes::StyleJsonError, "Key resources missing in style json file");
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
    qApp->setPalette(generateThemePalette());
}
