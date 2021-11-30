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

#ifndef _QEXTPROGRESSROUND_H
#define _QEXTPROGRESSROUND_H

#include <qextWidgetGlobal.h>

#include <QWidget>

class QEXT_WIDGETS_API QEXTProgressPie : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor bgColor READ getBgColor WRITE setBgColor)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor)
    Q_PROPERTY(QColor baseColor READ getBaseColor WRITE setBaseColor)
    Q_PROPERTY(QColor innerBgColor READ getInnerBgColor WRITE setInnerBgColor)
    Q_PROPERTY(QColor borderColor READ getBorderColor WRITE setBorderColor)
    Q_PROPERTY(QColor progressColor READ getProgressColor WRITE setProgressColor)

    Q_PROPERTY(double minValue READ getMinValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ getMaxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ getValue WRITE setValue)
    Q_PROPERTY(int precision READ getPrecision WRITE setPrecision)

    Q_PROPERTY(double nullPosition READ getNullPosition WRITE setNullPosition)
    Q_PROPERTY(double outlinePenWidth READ getOutlinePenWidth WRITE setOutlinePenWidth)
    Q_PROPERTY(double dataPenWidth READ getDataPenWidth WRITE setDataPenWidth)

    Q_PROPERTY(BarStyle barStyle READ getBarStyle WRITE setBarStyle)
    Q_PROPERTY(QString format READ getFormat WRITE setFormat)
    Q_PROPERTY(bool clockWise READ getClockWise WRITE setClockWise)

public:
    enum BarStyle {
        BarStyle_Pie = 1,   //饼状风格
    };
    Q_ENUMS(BarStyle)

    explicit QEXTProgressPie(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);

    void drawBg(QPainter *painter, const QRectF &baseRect);
    void drawBase(QPainter *painter, const QRectF &baseRect);
    void drawProgress(QPainter *painter, const QRectF &baseRect);
    void calculateInnerRect(const QRectF &baseRect, double outerRadius, QRectF &innerRect, double &innerRadius);
    void drawValue(QPainter *painter, const QRectF &innerRect, double innerRadius);

private:
    void rebuildDataBrushIfNeeded();

private:
    QColor bgColor;
    QColor textColor;
    QColor baseColor;
    QColor innerBgColor;
    QColor borderColor;
    QColor progressColor;

    double minValue;
    double maxValue;
    double value;
    int precision;

    double nullPosition;
    double outlinePenWidth;
    double dataPenWidth;

    BarStyle barStyle;
    QString format;
    bool clockWise;
    QGradientStops gradientData;

public:
    QColor getBgColor()             const;
    QColor getTextColor()           const;
    QColor getBaseColor()           const;
    QColor getInnerBgColor()        const;
    QColor getBorderColor()         const;
    QColor getProgressColor()       const;

    double getValue()               const;
    double getMinValue()            const;
    double getMaxValue()            const;
    int getPrecision()              const;

    double getNullPosition()        const;
    double getOutlinePenWidth()     const;
    double getDataPenWidth()        const;

    BarStyle getBarStyle()          const;
    QString	getFormat()             const;
    bool getClockWise()             const;
    QGradientStops getGradientData()const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public Q_SLOTS:
    void setBgColor(const QColor &bgColor);
    void setTextColor(const QColor &textColor);
    void setBaseColor(const QColor &baseColor);
    void setInnerBgColor(const QColor &innerBgColor);
    void setBorderColor(const QColor &borderColor);
    void setProgressColor(const QColor &progressColor);

    void setRange(double minValue, double maxValue);
    void setRange(int minValue, int maxValue);

    void setMinValue(double minValue);
    void setMaxValue(double maxValue);

    void setValue(double value);
    void setValue(int value);

    void setPrecision(int precision);

    void setNullPosition(double nullPosition);

    void setOutlinePenWidth(double outlinePenWidth);

    void setDataPenWidth(double dataPenWidth);

    void setBarStyle(const BarStyle &barStyle);

    void setFormat(const QString &format);

    void setClockWise(bool clockWise);

    void setGradientData(const QGradientStops &gradientData);
};

#endif // _QEXTPROGRESSROUND_H
