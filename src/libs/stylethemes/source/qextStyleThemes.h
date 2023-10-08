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

#ifndef _QEXTSTYLETHEMES_H
#define _QEXTSTYLETHEMES_H

#include <QApplication>
#include <QObject>
#include <QWidget>

class QEXTStyleThemePrivate;
class QEXTStyleTheme : public QObject
{
    Q_OBJECT
public:
    virtual ~QEXTStyleTheme() {}

    virtual QString styleName() const = 0;
    virtual QString themeName(int type) const = 0;

    virtual int currentTheme() const = 0;
    virtual void setCurrentTheme(int type) = 0;

    virtual QString styleSheet() const = 0;
    virtual QString additionalStyle() const = 0;
    virtual void setAdditionalStyle(const QString &style) = 0;
    virtual void addAdditionalStyle(const QString &style) = 0;
};

#endif // _QEXTSTYLETHEMES_H
