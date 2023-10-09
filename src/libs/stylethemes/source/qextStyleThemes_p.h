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

class QEXT_STYLETHEMS_API QExtStyleThemePrivate
{
public:
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

    explicit QExtStyleThemePrivate(QExtStyleTheme *q);
    virtual ~QExtStyleThemePrivate();

    bool generateStylesheet(); // Generate the final stylesheet from the stylesheet template file
    bool exportInternalStylesheet(const QString &Filename); // Export the internal generated stylesheet
    bool storeStylesheet(const QString &Stylesheet, const QString &Filename); // Store the given stylesheet
    /* Parse a list of theme variables */
    bool parseVariablesFromXml(QXmlStreamReader &s, const QString &VariableTagName, QMap<QString, QString> &Variable);
    bool parseThemeFile(const QString &ThemeFilename); // Parse the theme file for
    bool parseStyleJsonFile(); // Parse the style JSON file
    /* Creates an Rgba color from a given color and an opacity value in the range from 0 (transparent) to 1 (opaque) */
    QString rgbaColor(const QString &RgbColor, float Opacity);
    void replaceStylesheetVariables(QString &Template); // Replace the stylesheet variables in the given template
    void addFonts(QDir *Dir = nullptr); // Register the style fonts to the font database
    /* Generate the resources for the variuous states */
    bool generateResourcesFor(const QString &SubDir, const QJsonObject &JsonObject, const QFileInfoList &Entries);
    /* Replace the in the given content the template color string with the theme color string */
    void replaceColor(QByteArray &Content, const QString &TemplateColor, const QString &ThemeColor) const;
    /* Set error code and error string */
    void setError(QExtStyleTheme::eError Error, const QString &ErrorString);
    /*Convenience function to ease clearing the error*/
    void clearError()
    {
        setError(QExtStyleTheme::NoError, QString());
    }
    void parsePaletteFromJson(); // Parse palette from JSON file
    /* Parse palette color group from the given palette json parameters */
    void parsePaletteColorGroup(QJsonObject &jPalette, QPalette::ColorGroup ColorGroup);
    /* Use this function to access the icon color replace list, to ensure, that is is properly initialized */
    const QExtStyleTheme::ColorReplaceVector &iconColorReplaceList() const;
    /* Parse a color replace list from the given JsonObject */
    QExtStyleTheme::ColorReplaceVector parseColorReplaceList(const QJsonObject &JsonObject) const;

    QExtStyleTheme * const q_ptr;

    QString StylesDir;
    QString OutputDir;
    QMap<QString, QString> StyleVariables;
    QMap<QString, QString> ThemeColors;
    QMap<QString, QString> ThemeVariables;// theme variables contains StyleVariables and ThemeColors
    QString Stylesheet;
    QString CurrentStyle;
    QString CurrentTheme;
    QString DefaultTheme;
    QString StyleName;
    QString IconFile;
    QVector<QExtStyleTheme::StringPair> ResourceReplaceList;
    QVector<PaletteColorEntry> PaletteColors;
    QString PaletteBaseColor;
    QJsonObject JsonStyleParam;
    QString ErrorString;
    QExtStyleTheme::eError Error;
    mutable QIcon Icon;
    QStringList Styles;
    QStringList Themes;
    bool IsDarkTheme = false;
    mutable QExtStyleTheme::ColorReplaceVector IconColorReplaceList;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QExtStyleThemePrivate)
    QEXT_DECL_PUBLIC(QExtStyleTheme)
};

#endif //_QEXTSTYLETHEMES_P_H
