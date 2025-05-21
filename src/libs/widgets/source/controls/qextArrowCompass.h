/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2016 feiyangqingyun. Contact: QQ:517216493
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

#ifndef _QEXTARROWCOMPASS_H
#define _QEXTARROWCOMPASS_H

#include <qextWidgetGlobal.h>

#include <QWidget>
#include <QEasingCurve>

class QExtArrowCompassPrivate;
class QEXT_WIDGETS_API QExtArrowCompass : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(double value READ value WRITE setValue)
    Q_PROPERTY(int precision READ precision WRITE setPrecision)

    Q_PROPERTY(bool animationVisible READ animationEnable WRITE setAnimationEnable)
    Q_PROPERTY(int animationDuration READ animationDuration WRITE setAnimationDuration)
    Q_PROPERTY(QEasingCurve::Type animationEasingCurve READ animationEasingCurve WRITE setAnimationEasingCurve)

    Q_PROPERTY(QColor crownStartColor READ crownStartColor WRITE setCrownStartColor)
    Q_PROPERTY(QColor crownEndColor READ crownEndColor WRITE setCrownEndColor)

    Q_PROPERTY(QColor backgroundStartColor READ backgroundStartColor WRITE setBackgroundStartColor)
    Q_PROPERTY(QColor backgroundEndColor READ backgroundEndColor WRITE setBackgroundEndColor)

    Q_PROPERTY(QColor darkColor READ darkColor WRITE setDarkColor)
    Q_PROPERTY(QColor lightColor READ lightColor WRITE setLightColor)

    Q_PROPERTY(QColor foregroundColor READ foregroundColor WRITE setForegroundColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)

    Q_PROPERTY(QColor northPointerColor READ northPointerColor WRITE setNorthPointerColor)
    Q_PROPERTY(QColor southPointerColor READ southPointerColor WRITE setSouthPointerColor)

    Q_PROPERTY(QColor centerStartColor READ centerStartColor WRITE setCenterStartColor)
    Q_PROPERTY(QColor centerEndColor READ centerEndColor WRITE setCenterEndColor)

public:
    explicit QExtArrowCompass(QWidget *parent = QEXT_NULLPTR);
    ~QExtArrowCompass();

    double value() const;
    int precision() const;

    bool animationEnable() const;
    int animationDuration() const;
    QEasingCurve::Type animationEasingCurve() const;

    QColor crownStartColor() const;
    QColor crownEndColor() const;

    QColor backgroundStartColor() const;
    QColor backgroundEndColor() const;

    QColor darkColor() const;
    QColor lightColor() const;

    QColor foregroundColor() const;
    QColor textColor() const;

    QColor northPointerColor() const;
    QColor southPointerColor() const;

    QColor centerStartColor() const;
    QColor centerEndColor() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public Q_SLOTS:
    void setValue(double value);
    void setValue(int value);

    void setPrecision(int precision);

    void setAnimationEnable(bool enable);
    void setAnimationDuration(int duration);
    void setAnimationEasingCurve(QEasingCurve::Type easingCurve);

    void setCrownStartColor(const QColor &color);
    void setCrownEndColor(const QColor &color);

    void setBackgroundStartColor(const QColor &color);
    void setBackgroundEndColor(const QColor &color);

    void setDarkColor(const QColor &color);
    void setLightColor(const QColor &color);

    void setForegroundColor(const QColor &color);
    void setTextColor(const QColor &color);

    void setNorthPointerColor(const QColor &color);
    void setSouthPointerColor(const QColor &color);

    void setCenterStartColor(const QColor &color);
    void setCenterEndColor(const QColor &color);

Q_SIGNALS:
    void valueChanged(int value);

protected:
    void paintEvent(QPaintEvent *);

    void drawCrownCircle(QPainter *painter);
    void drawBackgroundCircle(QPainter *painter);
    void drawScale(QPainter *painter);
    void drawScaleNum(QPainter *painter);
    void drawCoverOuterCircle(QPainter *painter);
    void drawCoverInnerCircle(QPainter *painter);
    void drawCoverCenterCircle(QPainter *painter);
    void drawPointer(QPainter *painter);
    void drawCenterCircle(QPainter *painter);
    void drawValue(QPainter *painter);

    QScopedPointer<QExtArrowCompassPrivate> dd_ptr;

private slots:
    void updateValue(const QVariant &value);

private:
    QEXT_DISABLE_COPY_MOVE(QExtArrowCompass)
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtArrowCompass)
};

#endif // _QEXTARROWCOMPASS_H
