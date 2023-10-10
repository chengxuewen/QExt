/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2023~Present ChengXueWen. Contact: 1398831004@qq.com.
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
** documentation files (the "Software"), to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
** and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions
** of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
** TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
** CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
** IN THE SOFTWARE.
**
***********************************************************************************************************************/

#ifndef _QEXTSTYLETHEMES_P_H
#define _QEXTSTYLETHEMES_P_H

#include <qextStyleThemes.h>

#include <QXmlStreamReader>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDir>

class QEXT_STYLETHEMS_API QExtStyleThemesPrivate
{
public:
    /**
     * Groups the data the build a parsed palette color entry
     */
    struct PaletteColorEntry
    {
        QPalette::ColorGroup Group;
        QPalette::ColorRole Role;
        QString ColorVariable;

        PaletteColorEntry(QPalette::ColorGroup group = QPalette::Active,
                          QPalette::ColorRole role = QPalette::NoRole,
                          const QString &variable = QString())
            : Group(group)
            , Role(role)
            , ColorVariable(variable)
        {

        }

        bool isValid() const
        {
            return !ColorVariable.isEmpty() && Role != QPalette::NoRole;
        }
    };

    explicit QExtStyleThemesPrivate(QExtStyleThemes *q);
    virtual ~QExtStyleThemesPrivate();

    bool generateStylesheet(); // Generate the final stylesheet from the stylesheet template file
    bool exportInternalStylesheet(const QString &filename); // Export the internal generated stylesheet
    bool storeStylesheet(const QString &stylesheet, const QString &filename); // Store the given stylesheet
    /* Parse a list of theme variables */
    bool parseVariablesFromXml(QXmlStreamReader &reader, const QString &tagName, QMap<QString, QString> &variables);
    bool parseThemeFile(const QString &fileName); // Parse the theme file for
    bool parseStyleJsonFile(); // Parse the style JSON file
    /* Creates an Rgba color from a given color and an opacity value in the range from 0 (transparent) to 1 (opaque) */
    QString rgbaColor(const QString &RgbColor, float Opacity);
    void replaceStylesheetVariables(QString &templateContent); // Replace the stylesheet variables in the given template
    void addFonts(QDir *Dir = nullptr); // Register the style fonts to the font database
    /* Generate the resources for the variuous states */
    bool generateResourcesFor(const QString &subDir, const QJsonObject &JsonObject, const QFileInfoList &entries);
    /* Replace the in the given content the template color string with the theme color string */
    void replaceColor(QByteArray &content, const QString &templateColor, const QString &themeColor) const;
    /* Set error code and error string */
    void setError(QExtStyleThemes::ErrorEnum error, const QString &ErrorString);
    /*Convenience function to ease clearing the error*/
    void clearError() { this->setError(QExtStyleThemes::NoError, QString()); }
    void parsePaletteFromJson(); // Parse palette from JSON file
    /* Parse palette color group from the given palette json parameters */
    void parsePaletteColorGroup(QJsonObject &jPalette, QPalette::ColorGroup colorGroup);
    /* Use this function to access the icon color replace list, to ensure, that is is properly initialized */
    const QExtStyleThemes::ColorReplaceVector &iconColorReplaceList() const;
    /* Parse a color replace list from the given JsonObject */
    QExtStyleThemes::ColorReplaceVector parseColorReplaceList(const QJsonObject &jsonObject) const;

    /* Converts a color role string into a color role enum */
    static QPalette::ColorRole colorRoleFromString(const QString &text);
    /* Returns the color group string for a given QPalette::ColorGroup */
    static QString colorGroupString(QPalette::ColorGroup colorGroup);

    template<class Key, class T>
    static void insertIntoMap(QMap<Key, T> &Map, const QMap<Key, T> &map)
    {
#if QT_VERSION >= 0x050F00
        Map.insert(map);
#else
        for (auto itc = map.constBegin(); itc != map.constEnd(); ++itc)
        {
            Map.insert(itc.key(), itc.value());
        }
#endif
    }

    QExtStyleThemes * const q_ptr;

    QString m_stylesDir;
    QString m_outputDir;
    QMap<QString, QString> m_themeColors;
    QMap<QString, QString> m_styleVariables;
    QMap<QString, QString> m_themeVariables;// theme variables contains StyleVariables and ThemeColors
    QString m_stylesheet;
    QString m_currentStyle;
    QString m_currentTheme;
    QString m_defaultTheme;
    QString m_styleName;
    QString m_iconFile;
    QVector<QExtStyleThemes::StringPair> ResourceReplaceList;
    QVector<PaletteColorEntry> m_paletteColors;
    QString m_paletteBaseColor;
    QJsonObject m_jsonStyleParam;
    QString m_errorString;
    QExtStyleThemes::ErrorEnum m_error;
    mutable QIcon m_icon;
    QStringList m_styles;
    QStringList m_themes;
    bool m_isDarkTheme;
    mutable QExtStyleThemes::ColorReplaceVector m_iconColorReplaceList;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QExtStyleThemesPrivate)
    QEXT_DECL_PUBLIC(QExtStyleThemes)
};

#endif //_QEXTSTYLETHEMES_P_H
