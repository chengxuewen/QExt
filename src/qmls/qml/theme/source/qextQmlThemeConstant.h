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

#ifndef _QEXTQMLTHEMECONSTANT_H
#define _QEXTQMLTHEMECONSTANT_H

#include <qextQmlThemeGlobal.h>

namespace QExtQmlThemeConstant
{
QEXT_STATIC_CONSTANT_STRING(kInfo, "INFO")
QEXT_STATIC_CONSTANT_STRING(kInfoVersion, "version")
QEXT_STATIC_CONSTANT_STRING(kInfoAbout, "about")
QEXT_STATIC_CONSTANT_STRING(kInfoName, "name")
QEXT_STATIC_CONSTANT_STRING(kInfoAuthor, "author")

QEXT_STATIC_CONSTANT_STRING(kTheme, "THEME")
QEXT_STATIC_CONSTANT_STRING(kThemeGroupName, "groupName")
QEXT_STATIC_CONSTANT_STRING(kThemeState, "state")

QEXT_STATIC_CONSTANT_STRING(kProperty, "PROPERTY")
QEXT_STATIC_CONSTANT_STRING(kPropertyColor, "color")

QEXT_STATIC_CONSTANT_NUMBER(kVersionMajor, 0)
QEXT_STATIC_CONSTANT_NUMBER(kVersionMinor, 1)
} // namespace QExtQmlThemeConstant

#endif // _QEXTQMLTHEMECONSTANT_H
