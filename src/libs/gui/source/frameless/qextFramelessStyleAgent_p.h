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

#ifndef _QEXTFRAMELESSSTYLEAGENT_P_H
#define _QEXTFRAMELESSSTYLEAGENT_P_H

#include <QHash>

#include <qextFramelessStyleAgent.h>

class QExtFramelessStyleAgentPrivate : public QObject
{
public:
    explicit QExtFramelessStyleAgentPrivate(QExtFramelessStyleAgent *q);
    ~QExtFramelessStyleAgentPrivate() QEXT_OVERRIDE;

    void init();

    QExtFramelessStyleAgent * const q_ptr;

    QExtFramelessStyleAgent::SystemTheme systemTheme = QExtFramelessStyleAgent::Unknown;

    void setupSystemThemeHook();
    void removeSystemThemeHook();

    void notifyThemeChanged(QExtFramelessStyleAgent::SystemTheme theme);

private:
    Q_DECLARE_PUBLIC(QExtFramelessStyleAgent)
    QEXT_DISABLE_COPY_MOVE(QExtFramelessStyleAgentPrivate)
};

#endif // _QEXTFRAMELESSSTYLEAGENT_P_H
