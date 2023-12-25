/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2016 feiyangqingyun. Contact: QQ:517216493
** Copyright (C) 2022~Present ChengXueWen. Contact: 1398831004@qq.com.
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

#ifndef _QEXTWAVECHART_H
#define _QEXTWAVECHART_H

#include <qextWidgetGlobal.h>

#include <QWidget>

class QExtWaveChartPrivate;
class QEXT_WIDGETS_API QExtWaveChart : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(double minValue READ minValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ maxValue WRITE setMaxValue)
    Q_PROPERTY(double xAxisStep READ xAxisStep WRITE setXAxisStep)
    Q_PROPERTY(double yAxisStep READ yAxisStep WRITE setYAxisStep)

    Q_PROPERTY(double space READ space WRITE setSpace)
    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(bool smoothEnable READ smoothEnable WRITE setSmoothEnable)
    Q_PROPERTY(bool hLineVisible READ hLineVisible WRITE setHLineVisible)
    Q_PROPERTY(bool vLineVisible READ vLineVisible WRITE setVLineVisible)
    Q_PROPERTY(bool pointVisible READ pointVisible WRITE setPointVisible)
    Q_PROPERTY(bool pointBackgroundVisible READ pointBackgroundVisible WRITE setPointBackgroundVisible)

    Q_PROPERTY(QColor backgroundStartColor READ backgroundStartColor WRITE setBackgroundStartColor)
    Q_PROPERTY(QColor backgroundEndColor READ backgroundEndColor WRITE setBackgroundEndColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor pointColor READ pointColor WRITE setPointColor)

public:
    explicit QExtWaveChart(QWidget *parent = QEXT_NULLPTR);
    ~QExtWaveChart();

    double minValue() const;
    double maxValue() const;
    double xAxisStep() const;
    double yAxisStep() const;
    double hLineStep() const;
    double vLineStep() const;

    double space() const;
    QString title() const;
    bool smoothEnable() const;
    bool titleVisible() const;
    bool hLineVisible() const;
    bool vLineVisible() const;
    bool pointVisible() const;
    bool pointBackgroundVisible() const;

    QColor backgroundStartColor() const;
    QColor backgroundEndColor() const;
    QColor textColor() const;
    QColor pointColor() const;

    QSize sizeHint() const QEXT_OVERRIDE;
    QSize minimumSizeHint() const QEXT_OVERRIDE;

public Q_SLOTS:
    void addData(double data);
    void setData(const QVector<double> &data);
    void clearData();

    void setMinValue(double value);
    void setMaxValue(double value);
    void setXAxisStep(double step);
    void setYAxisStep(double step);
    void setHLineStep(double step);
    void setVLineStep(double step);

    void setSpace(double space);
    void setTitle(const QString &title);
    void setSmoothEnable(bool enable);
    void setTitleVisible(bool visiable);
    void setHLineVisible(bool visiable);
    void setVLineVisible(bool visiable);
    void setPointVisible(bool visiable);
    void setPointBackgroundVisible(bool visiable);

    void setBackgroundStartColor(const QColor &color);
    void setBackgroundEndColor(const QColor &color);
    void setTextColor(const QColor &color);
    void setPointColor(const QColor &color);

protected Q_SLOTS:
    void updateData();

protected:
    void paintEvent(QPaintEvent *) QEXT_OVERRIDE;

    void drawBackground(QPainter *painter);
    void drawBox(QPainter *painter);
    void drawText(QPainter *painter);
    void drawTitle(QPainter *painter);
    void drawPoint(QPainter *painter);

    QScopedPointer<QExtWaveChartPrivate> dd_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QExtWaveChart)
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtWaveChart)
};


#endif // _QEXTWAVECHART_H
