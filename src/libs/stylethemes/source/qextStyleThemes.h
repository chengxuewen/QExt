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

#ifndef _QEXTSTYLETHEMES_H
#define _QEXTSTYLETHEMES_H

#include <qextStyleThemesGlobal.h>

#include <QApplication>
#include <QObject>
#include <QWidget>
#include <QIcon>

class QExtStyleThemesPrivate;

class QEXT_STYLETHEMS_API QExtStyleThemes : public QObject
{
Q_OBJECT
public:
    typedef QPair<QString, QString> StringPair;
    typedef QVector<StringPair> ColorReplaceVector;

    enum ErrorEnum
    {
        NoError,
        CssTemplateError,
        CssExportError,
        ThemeXmlError,
        StyleJsonError,
        ResourceGeneratorError,
    };

    enum LocationEnum
    {
        ThemesLocation,
        ResourceTemplatesLocation,
        FontsLocation
    };

    explicit QExtStyleThemes(QObject *parent = 0);

    ~QExtStyleThemes() QEXT_DECL_OVERRIDE;

    /**
     * @brief Set the directory path that contains all styles.
     * @param path The styles dir path.
     */
    void setStylesDirPath(const QString &path);

    /**
     * @brief Returns the set styles dir
     * @return Styles dir
     */
    QString stylesDirPath() const;

    /**
     * @brief Returns the current style.
     * @return Style name.
     */
    QString currentStyle() const;

    /**
     * @brief Returns the absolute path of the current style.
     * If your styles stylesDirPath() is C:/styles and your current style is material then this function returns C:/styles/material
     * @return The absolute path of the current style.
     */
    QString currentStylePath() const;

    /**
     * @brief Returns the list of available styles in the given styles directory
     * @return Styles directory list.
     */
    const QStringList &styles() const;

    /**
     * @brief Returns a list of all themes for the current style.
     * If no style has been set, this function returns an empty list
     * @return A list of all themes for the current style.
     */
    const QStringList &themes() const;

    /**
     * @brief Returns a list of all theme variables for colors
     * @return
     */
    const QMap<QString, QString> &themeColorVariables() const;

    /**
     * @brief Returns the absolute dir path for the given location
     * @param location
     * @return
     */
    QString path(LocationEnum location) const;

    /**
     * @brief Returns the absolute output dir path where the generated styles will get stored.
     * @return
     * @see setOutputDirPath()
     */
    QString outputDirPath() const;

    /**
     * @brief Sets the output directory path where the generated theme will be stored
     * @param path
     */
    void setOutputDirPath(const QString &path);

    /**
     * @brief Returns the output path for the current style.
     * The output path is the outputDirPath() + the style name.
     * If your output path is C:/temp/styles and your style is material then this functions returns C:/temp/styles/qt_material
     * @return
     */
    QString currentStyleOutputPath() const;

    /**
     * @brief Returns the value for the given theme variable.
     * For example themeVariable("primaryColor") may return "#ac2300".
     * Returns an empty string, if the given theme variable does not exist.
     * @param variableId
     * @return
     */
    QString themeVariableValue(const QString &variableId) const;

    /**
     * @brief You can use this function to add or overwrite a theme variable.
     * You may use this function to add application specific colors that are not defined in the current style.
     * If you changed a theme variable or a number of theme variables then you should call updateStylesheet() to request
     * a reprocessing of the style template and to update the stylesheet.
     * @param variableId
     * @param value
     */
    void setThemeVariableValue(const QString &variableId, const QString &value);

    /**
     * @brief Returns the color for the given VariableId.
     * If VariableId is not a color variable, then this function returns an invalid QColor.
     * @param variableId
     * @return
     */
    QColor themeColor(const QString &variableId) const;

    /**
     * @brief Returns the current set theme
     * @return
     */
    QString currentTheme() const;

    /**
     * @brief Returns the processed style stylesheet.
     * If the style or the theme of a style changed, you can read the new stylesheet from this function
     * @return
     */
    QString styleSheet() const;

    /**
     * @brief This function replaces the style variables in the given template with the value of the registered style
     * variables.
     * You can use this function if you have split your stylesheet into several parts or if you use plugins that provide
     * additional stylesheets to get the processed stylesheed if the theme changed.
     * Returns the final stylesheet or an empty string in case of an error.
     * If the @a outputFile parameter is given, the generated stylesheet file will be stored into the currentStyleOutputPath()
     * folder with the given a outputFile name.
     * @param templateText
     * @param outputFile
     * @return
     */
    QString processStylesheetTemplate(const QString &templateText, const QString &outputFile = QString());

    /**
     * @brief Returns the icon for the current style or an empty icon if the style does not provide an icon
     * @return
     */
    const QIcon &styleIcon() const;

    /**
     * @brief Returns the error state of the object.
     * @return
     */
    ErrorEnum error() const;

    /**
     * @brief Returns a string describing the last error that occured
     */
    QString errorString() const;

    /**
     * @brief This function creates a palette with the theme colors of the currently selected theme
     */
    QPalette generateThemePalette() const;

    /**
     * @brief Read access to the Json object with all stlye parameters
     * @return Parameters json object
     */
    const QJsonObject &styleParameters() const;

    /**
     * @brief The function returns true, if the current theme is a dark theme and false if the current theme is a light
     * theme.
     * The application can use this functions to adjust settings depending on dark or light theme
     */
    bool isCurrentThemeDark() const;

    /**
     * @brief Replace svg color in the given @a svgContent file with theme colors.
     * If an optional @a colorReplaceVector is provided, then the given list is used to replace the colors in the given
     * @a svgContent file.
     * If no color replace list is given, the internal color replace list parsed from style json file is used
     * @param svgContent
     * @param colorReplaceVector
     */
    void replaceSvgColors(QByteArray &svgContent, const ColorReplaceVector &colorReplaceVector = ColorReplaceVector());

    /**
     * @brief Loads svg data from the given @a filename and then passes the loaded svg data to replaceSvgColors() function
     * to replace colors with theme colors.
     * The function uses the parsed theme colors to replace the colors in the given svg icon.
     * If the theme changes, all icons that are loaded with this function are automatically updated to the new theme colors.
     * @param filename The svg file name.
     * @return
     */
    QIcon loadThemeAwareSvgIcon(const QString &fileName);

public slots:

    /**
     * @brief Sets the theme to use.
     * Use the theme name without the file extension. That means, if your theme file id dark_cyan.xml then set the theme
     * to `dark_cyan' Returns true on success and false on error.
     * Changing the theme does not trigger a stylesheet update. So after changing the theme, you can add or overwrite
     * theme variables via setThemeVariableValue() To trigger processing of the style template, you need to call explicitely
     * updateStylesheet().
     * @param theme The theme name.
     * @return Set theme success returns true, otherwise returns false
     */
    bool setCurrentTheme(const QString &theme);

    /**
     * @brief Sets the default theme that is given in the style Json file
     */
    void setDefaultTheme();

    /**
     * @brief Set the current style
     * @param style The style name.
     * @return Set style success returns true, otherwise returns false
     */
    bool setCurrentStyle(const QString &style);

    /**
     * @brief Call this function if you would like to reprocess the style template.
     * Call this function, if you have changed the theme or some theme variables via setThemeVariable() to request an
     * update of the stylesheet.
     * The function updates the application palette with the theme colors (updateApplicationPaletteColors()), generates
     * the theme SVG rseouces (generateResources()) and then generates the stylesheet if it has a template file.
     * If you have split your stylesheet into several pieces or if your would like to separate the update of the resources
     * and the generation of the stylehseets, then you should not use this function. Instead, call processStyleTemplate()
     * to generate the SVG resources and update the palette an then use processStylesheetTemplate() to generate the style
     * sheets.
     * @return Update success returns true, otherwise returns false
     */
    bool updateStylesheet();

    /**
     * @brief Call this function, if you would like to update the SVG files and the application palette. The function
     * calls generateResources() and updateApplicationPaletteColors().
     * The functio will not update or create any stylesheet.
     * After calling this function, you can use the processStylesheetTemplate() function to manually generate the style
     * sheets from stylesheet template files.
     * @return Process success returns true, otherwise returns false
     */
    bool processStyleTemplate();

    /**
     * @brief Generate the required icons for this theme.
     * You can call this function, if you changed some theme settings or theme variables and if you would like to recreate
     * the svg resources of this style.If you call updateStylesheet(), then this function will be called automatically
     * @return Generate success returns true, otherwise returns false
     */
    bool generateResources();

    /**
     * @brief Update the palette colors with the colors read from json file.
     * This function is called automatically if updateStylesheet() is called.
     * The function creates a palette with theme colors via generateThemePalette() and then assigns the platte to the
     * application object
     */
    void updateApplicationPaletteColors();


signals:

    /**
     * @brief This signal is emitted if the selected style changed
     * @param style The Style name.
     */
    void currentStyleChanged(const QString &style);

    /**
     * @brief This signal is emitted, if the selected theme in a style changed
     * @param theme The theme name.
     */
    void currentThemeChanged(const QString &theme);

    /**
     * @brief This signal is emitted if the stylesheet changed.
     * The stylesheed changes if the style changes, the theme changes or if a style variable changed an the user
     * requested a styleheet update
     */
    void stylesheetChanged();

protected:
    QScopedPointer<QExtStyleThemesPrivate> dd_ptr;

private:

    QEXT_DECL_DISABLE_COPY_MOVE(QExtStyleThemes)

    QEXT_DECL_PRIVATE_D(dd_ptr, QExtStyleThemes)
};

#endif // _QEXTSTYLETHEMES_H
