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

#ifndef _QEXTFRAMELESSSTYLEAGENT_H
#define _QEXTFRAMELESSSTYLEAGENT_H

#include <QObject>
#include <QWindow>

#include <qextFramelessUtils.h>

class QExtFramelessStyleAgentPrivate;
class QEXT_GUI_API QExtFramelessStyleAgent : public QObject
{
    Q_OBJECT
public:
    explicit QExtFramelessStyleAgent(QObject *parent = QEXT_NULLPTR);
    ~QExtFramelessStyleAgent() QEXT_OVERRIDE;

    enum SystemTheme
    {
        Unknown,
        Light,
        Dark,
        HighContrast,
    };
    Q_ENUM(SystemTheme)

public:
    SystemTheme systemTheme() const;

Q_SIGNALS:
    void systemThemeChanged();

protected:
    QExtFramelessStyleAgent(QExtFramelessStyleAgentPrivate *d, QObject *parent = QEXT_NULLPTR);

    QScopedPointer<QExtFramelessStyleAgentPrivate> dd_ptr;

private:
    Q_DECLARE_PRIVATE_D(dd_ptr, QExtFramelessStyleAgent)
    QEXT_DISABLE_COPY_MOVE(QExtFramelessStyleAgent)
};

#endif // _QEXTFRAMELESSSTYLEAGENT_H
