/****************************************************************************
**
** Library: QEXTQmlQuick
**
** MIT License
**
** Copyright (c) 2021 chengxuewen <1398831004@qq.com>
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all
** copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
****************************************************************************/

#ifndef _QEXTQMLTHEMEJSONFILEPARSER_H
#define _QEXTQMLTHEMEJSONFILEPARSER_H

#include <qextQmlThemeGlobal.h>
#include <qextQmlThemeFileParser.h>

class QEXT_QMLTHEME_API QEXTQmlThemeJsonFileParser : public QEXTQmlThemeFileParser
{
public:
    QEXTQmlThemeJsonFileParser() {}
    ~QEXTQmlThemeJsonFileParser() {}

    virtual bool parseThemeFile(const QString &strPath, QMap<QString, QVariantMap> &themeDataMap, QString &strError) override;
    virtual bool generateThemeTemplateFile(QString &strError, QEXTQmlThemeBinder *pBinder = nullptr) override;
};

#endif // _QEXTQMLTHEMEJSONFILEPARSER_H
