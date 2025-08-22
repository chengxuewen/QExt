/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2019 feiyangqingyun. Contact: QQ:517216493
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

#ifndef _QEXTNUMBERLED_H
#define _QEXTNUMBERLED_H

#include <qextWidgetGlobal.h>

#include <QWidget>
#include <QObject>

class QExtNumberLedPrivate;
class QEXT_WIDGETS_API QExtNumberLed : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int number READ number WRITE setNumber)
    Q_PROPERTY(int space READ space WRITE setSpace)

    Q_PROPERTY(QColor backgroundStartColor READ backgroundStartColor WRITE setBackgroundStartColor)
    Q_PROPERTY(QColor backgroundEndColor READ backgroundEndColor WRITE setBackgroundEndColor)

    Q_PROPERTY(QColor numberStartColor READ numberStartColor WRITE setNumberStartColor)
    Q_PROPERTY(QColor numberEndColor READ numberEndColor WRITE setNumberEndColor)

    Q_PROPERTY(Symbol symbolType READ symbolType WRITE setSymbolType)
public:
    enum Symbol {
        Symbol_None = 0,
        Symbol_Dot,
        Symbol_Colon,
        Symbol_Line
    };
    Q_ENUMS(Symbol)

public:
    explicit QExtNumberLed(QWidget *parent = QEXT_NULLPTR);
    ~QExtNumberLed();

    int number() const;
    int space() const;

    QColor backgroundStartColor() const;
    QColor backgroundEndColor() const;

    QColor numberStartColor() const;
    QColor numberEndColor() const;

    Symbol symbolType() const;

    QSize sizeHint() const QEXT_OVERRIDE;
    QSize minimumSizeHint() const QEXT_OVERRIDE;

public Q_SLOTS:
    void setNumber(int number);

    void setSpace(int space);

    void setBackgroundStartColor(const QColor &color);
    void setBackgroundEndColor(const QColor &color);

    void setNumberStartColor(const QColor &color);
    void setNumberEndColor(const QColor &color);

    void setSymbolType(const Symbol &type);

protected:
    void paintEvent(QPaintEvent *) QEXT_OVERRIDE;

    void drawBackground(QPainter *painter);
    void drawNumber(QPainter *painter);

    QScopedPointer<QExtNumberLedPrivate> dd_ptr;

private:
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtNumberLed)
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtNumberLed)
};

#endif // _QEXTNUMBERLED_H
