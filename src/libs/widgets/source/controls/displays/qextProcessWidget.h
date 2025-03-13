/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2024~present chengxuewen. Contact: 1398831004@qq.com
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

#ifndef _QEXTPROCESSWIDGET_H
#define _QEXTPROCESSWIDGET_H

#include <qextWidgetGlobal.h>

#include <QWidget>

class QExtProcessWidgetPrivate;
class QEXT_WIDGETS_API QExtProcessWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QExtProcessWidget(QWidget *parent = nullptr);
    ~QExtProcessWidget() QEXT_OVERRIDE;

    QString processPath() const;
    QString workingPath() const;
    QStringList processArgs() const;

Q_SIGNALS:
    void workingPathChanged(const QString &path);
    void processPathChanged(const QString &path);
    void processArgsChanged(const QStringList &args);

public Q_SLOTS:
    void setProcessPath(const QString &path);
    void setWorkingPath(const QString &path);
    void setProcessArgs(const QStringList &args);

    bool startProcess();

protected Q_SLOTS:
    void onProcessStarted();
    void onProcessFinished();

protected:
    QScopedPointer<QExtProcessWidgetPrivate> dd_ptr;

private:
    QEXT_DISABLE_COPY_MOVE(QExtProcessWidget)
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtProcessWidget)
};

#endif // _QEXTPROCESSWIDGET_H
