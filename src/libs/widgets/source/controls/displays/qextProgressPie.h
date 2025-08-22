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

#ifndef _QEXTPROGRESSROUND_H
#define _QEXTPROGRESSROUND_H

#include <qextWidgetGlobal.h>

#include <QWidget>

class QExtProgressPiePrivate;
class QEXT_WIDGETS_API QExtProgressPie : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor baseColor READ baseColor WRITE setBaseColor)
    Q_PROPERTY(QColor innerBgColor READ innerBgColor WRITE setInnerBackgroundColor)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)
    Q_PROPERTY(QColor progressColor READ progressColor WRITE setProgressColor)

    Q_PROPERTY(double minValue READ minValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ maxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ value WRITE setValue)
    Q_PROPERTY(int precision READ precision WRITE setPrecision)

    Q_PROPERTY(double nullPosition READ nullPosition WRITE setNullPosition)
    Q_PROPERTY(double outlinePenWidth READ outlinePenWidth WRITE setOutlinePenWidth)
    Q_PROPERTY(double dataPenWidth READ dataPenWidth WRITE setDataPenWidth)

    Q_PROPERTY(BarStyle barStyle READ barStyle WRITE setBarStyle)
    Q_PROPERTY(QString format READ format WRITE setFormat)
    Q_PROPERTY(bool clockWise READ clockWise WRITE setClockWise)

public:
    enum BarStyle
    {
        BarStyle_Pie = 1,   //饼状风格
    };
    Q_ENUMS(BarStyle)

    explicit QExtProgressPie(QWidget *parent = QEXT_NULLPTR);
    ~QExtProgressPie();

    QColor backgroundColor() const;
    QColor textColor() const;
    QColor baseColor() const;
    QColor innerBgColor() const;
    QColor borderColor() const;
    QColor progressColor() const;

    double value() const;
    double minValue() const;
    double maxValue() const;
    int precision() const;

    double nullPosition() const;
    double outlinePenWidth() const;
    double dataPenWidth() const;

    BarStyle barStyle() const;
    QString	format() const;
    bool clockWise() const;
    QGradientStops gradientData() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public Q_SLOTS:
    void setBackgroundColor(const QColor &color);
    void setTextColor(const QColor &color);
    void setBaseColor(const QColor &color);
    void setInnerBackgroundColor(const QColor &color);
    void setBorderColor(const QColor &color);
    void setProgressColor(const QColor &color);

    void setRange(double minValue, double maxValue);
    void setRange(int minValue, int maxValue);

    void setMinValue(double minValue);
    void setMaxValue(double maxValue);

    void setValue(double value);
    void setValue(int value);

    void setPrecision(int precision);

    void setNullPosition(double nullPosition);

    void setOutlinePenWidth(double width);

    void setDataPenWidth(double width);

    void setBarStyle(BarStyle barStyle);

    void setFormat(const QString &format);

    void setClockWise(bool clockWise);

    void setGradientData(const QGradientStops &gradientData);

protected:
    void paintEvent(QPaintEvent *);

    void drawBackground(QPainter *painter, const QRectF &baseRect);
    void drawBase(QPainter *painter, const QRectF &baseRect);
    void drawProgress(QPainter *painter, const QRectF &baseRect);
    void calculateInnerRect(const QRectF &baseRect, double outerRadius, QRectF &innerRect, double &innerRadius);
    void drawValue(QPainter *painter, const QRectF &innerRect, double innerRadius);

    QScopedPointer<QExtProgressPiePrivate> dd_ptr;

private:
    void rebuildDataBrushIfNeeded();

    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtProgressPie)
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtProgressPie)
};

#endif // _QEXTPROGRESSROUND_H
