/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2021~Present ChengXueWen. Contact: 1398831004@qq.com
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

#ifndef _QEXTFRAMELESSMAINWINDOW_H
#define _QEXTFRAMELESSMAINWINDOW_H

#include <qextWidgetGlobal.h>

#include <QMainWindow>

class QExtFramelessMainWindowPrivate;
class QEXT_WIDGETS_API QExtFramelessMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit QExtFramelessMainWindow(QWidget *parent = QEXT_NULLPTR);
    ~QExtFramelessMainWindow();

    void setPadding(int padding);
    void setMoveEnable(bool moveEnable);
    void setResizeEnable(bool resizeEnable);

    void setTitleBar(QWidget *titleBar);

signals:
    void titleDoubleClicked();
    void windowStateChanged(bool max);

protected:
    void showEvent(QShowEvent *event) QEXT_OVERRIDE;
    bool eventFilter(QObject *watched, QEvent *event) QEXT_OVERRIDE;
    void paintEvent(QPaintEvent *event) QEXT_OVERRIDE;

    //Intercepting system events is used to fix a BUG that wakes up the system after sleep
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result) QEXT_OVERRIDE;
#else
    bool nativeEvent(const QByteArray &eventType, void *message, long *result) QEXT_OVERRIDE;
#endif

    //Qt4 spelled
#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
#ifdef Q_OS_WIN
    bool winEvent(MSG *message, long *result);
#endif
#endif

    //Event filter recognition drag stretch etc
    void doWindowStateChange(QEvent *event);
    void doResizeEvent(QEvent *event);

    QScopedPointer<QExtFramelessMainWindowPrivate> dd_ptr;

private:
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtFramelessMainWindow)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtFramelessMainWindow)
};

#endif // _QEXTFRAMELESSMAINWINDOW_H
