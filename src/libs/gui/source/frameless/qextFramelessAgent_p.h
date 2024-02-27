/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2024~Present ChengXueWen. Contact: 1398831004@qq.com
** Copyright (C) 2023-2024 Stdware Collections
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

#ifndef _QEXTFRAMELESSAGENT_P_H
#define _QEXTFRAMELESSAGENT_P_H

#include <qextFramelessAgent.h>
#include <private/qextAbstractFramelessContext_p.h>

#include <QScopedPointer>

class QEXT_GUI_API QExtFramelessAgentPrivate
{
public:
    typedef QExtAbstractFramelessContext *(*WindowContextFactoryMethod)();

    explicit QExtFramelessAgentPrivate(QExtFramelessAgent *q);
    virtual ~QExtFramelessAgentPrivate();

    void init();

    virtual QExtAbstractFramelessContext *createContext() const;

    void setup(QObject *host, QExtFramelessItemDelegate *delegate);

    QExtFramelessAgent *const q_ptr; // no need to initialize

    QScopedPointer<QExtAbstractFramelessContext> m_context;

    static WindowContextFactoryMethod windowContextFactoryMethod;

private:
    Q_DECLARE_PUBLIC(QExtFramelessAgent)
    Q_DISABLE_COPY(QExtFramelessAgentPrivate)
};

#endif // _QEXTFRAMELESSAGENT_P_H
