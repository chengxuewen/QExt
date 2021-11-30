/*************************************************************************************
**
** Library: QEXT
**
** Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
** Copyright (C) 2019 feiyangqingyun. Contact: QQ:517216493
**
** License: MIT License
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the "Software"),
** to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense,
** and/or sell copies of the Software, and to permit persons to whom the
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
*************************************************************************************/

#ifndef _QEXTRINGCOMPASS_H
#define _QEXTRINGCOMPASS_H

#include <qextWidgetGlobal.h>

#include <QWidget>

class QEXTRingCompassPrivate;
class QEXT_WIDGETS_API QEXTRingCompass : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(QEXTRingCompass)
    Q_DECLARE_PRIVATE_D(dd_ptr, QEXTRingCompass)

    Q_PROPERTY(double value READ value WRITE setValue)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)
    Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderWidth)

    Q_PROPERTY(QColor northDotColor READ northDotColor WRITE setNorthDotColor)
    Q_PROPERTY(QColor otherDotColor READ otherDotColor WRITE setOtherDotColor)
    Q_PROPERTY(QColor pointerColor READ pointerColor WRITE setPointerColor)

public:
    explicit QEXTRingCompass(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTRingCompass();

    double value() const;
    QColor backgroundColor() const;
    QColor textColor() const;
    QColor borderColor() const;
    int borderWidth() const;

    QColor northDotColor() const;
    QColor otherDotColor() const;
    QColor pointerColor() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public Q_SLOTS:
    void setValue(double value);

    void setBackgroundColor(const QColor &color);

    void setTextColor(const QColor &color);

    void setBorderColor(const QColor &color);

    void setBorderWidth(int width);

    void setNorthDotColor(const QColor &color);

    void setOtherDotColor(const QColor &color);

    void setPointerColor(const QColor &color);

Q_SIGNALS:
    void valueChanged(double value);

protected:
    void paintEvent(QPaintEvent *);

    void drawBackground(QPainter *painter);
    void drawFourDots(QPainter *painter);
    void drawFourText(QPainter *painter);
    void drawPointer(QPainter *painter);
    void drawValue(QPainter *painter);

    QScopedPointer<QEXTRingCompassPrivate> dd_ptr;

};

#endif // _QEXTRINGCOMPASS_H
