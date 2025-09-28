/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2021 ChengXueWen.
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

#ifndef _QEXTQMLTHEMEJSONFILEPARSER_H
#define _QEXTQMLTHEMEJSONFILEPARSER_H

#include <qextQmlThemeFileParser.h>

class QEXT_QMLTHEME_API QExtQmlThemeJsonFileParser : public QExtQmlThemeFileParser
{
public:
    QExtQmlThemeJsonFileParser() {}
    ~QExtQmlThemeJsonFileParser() override {}

    bool parseThemeFile(const QString &path, QMap<QString, QVariantMap> &themeDataMap, QString &error) override;
    bool generateThemeTemplateFile(QString &error, QExtQmlThemeBinder *binder = nullptr) override;
};

#endif // _QEXTQMLTHEMEJSONFILEPARSER_H
