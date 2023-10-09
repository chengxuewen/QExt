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

#ifndef _QEXTSTYLETHEMESGLOBAL_H
#define _QEXTSTYLETHEMESGLOBAL_H

#include <qextGlobal.h>

/********************************************************************************
   QExt Compiler specific cmds for export and import code to DLL
********************************************************************************/
#ifdef QEXT_BUILD_SHARED // compiled as a dynamic lib.
    #ifdef QEXT_BUILD_STYLETHEMES_LIB // defined if we are building the lib
        #define QEXT_STYLETHEMS_API Q_DECL_EXPORT
    #else
        #define QEXT_STYLETHEMS_API Q_DECL_IMPORT
    #endif
    #define QEXT_STYLETHEMS_HIDDEN Q_DECL_HIDDEN
#else // compiled as a static lib.
    #define QEXT_STYLETHEMS_API
    #define QEXT_STYLETHEMS_HIDDEN
#endif


// Define ACSS_DEBUG_PRINT to enable a lot of debug output
#ifdef ACSS_DEBUG_PRINT
#define ACSS_PRINT(s) qDebug() << s
#else
#define ACSS_PRINT(s)
#endif

// Set ACSS_DEBUG_LEVEL to enable additional debug output and to enable layout
// dumps to qDebug and std::cout after layout changes
#define ACSS_DEBUG_LEVEL 0

#endif // _QEXTSTYLETHEMESGLOBAL_H
