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

#ifndef _QEXTPROGRESSRING_H
#define _QEXTPROGRESSRING_H

#include <qextWidgetGlobal.h>

#include <QWidget>
#include <QEasingCurve>

class QEXTProgressRingPrivate;
class QEXT_WIDGETS_API QEXTProgressRing : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(double minValue READ minValue WRITE setMinValue)
    Q_PROPERTY(double maxValue READ maxValue WRITE setMaxValue)
    Q_PROPERTY(double value READ getValue WRITE setValue)
    Q_PROPERTY(int precision READ precision WRITE setPrecision)
    Q_PROPERTY(QString text READ text WRITE setText)

    Q_PROPERTY(bool clipCenter READ clipCenter WRITE setClipCenter)
    Q_PROPERTY(bool clockWise READ clockWise WRITE setClockWise)
    Q_PROPERTY(bool percentVisible READ percentVisible WRITE setPercentVisible)

    Q_PROPERTY(int alarmMode READ alarmMode WRITE setAlarmMode)
    Q_PROPERTY(int startAngle READ startAngle WRITE setStartAngle)
    Q_PROPERTY(int ringPadding READ ringPadding WRITE setRingPadding)
    Q_PROPERTY(int ringWidth READ ringWidth WRITE setRingWidth)

    Q_PROPERTY(bool animationEnable READ animationEnable WRITE setAnimationEnable)
    Q_PROPERTY(int animationDuration READ animationDuration WRITE setAnimationDuration)
    Q_PROPERTY(QEasingCurve::Type animationEasingCurve READ animationEasingCurve WRITE setAnimationEasingCurve)

    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor ringColor READ ringColor WRITE setRingColor)
    Q_PROPERTY(QColor ringBackgroundColor READ ringBackgroundColor WRITE setRingBgColor)
    Q_PROPERTY(QColor circleColor READ circleColor WRITE setCircleColor)

    Q_PROPERTY(int ringValue1 READ ringValue1 WRITE setRingValue1)
    Q_PROPERTY(int ringValue2 READ ringValue2 WRITE setRingValue2)
    Q_PROPERTY(int ringValue3 READ ringValue3 WRITE setRingValue3)

    Q_PROPERTY(QColor ringColor1 READ ringColor1 WRITE setRingColor1)
    Q_PROPERTY(QColor ringColor2 READ ringColor2 WRITE setRingColor2)
    Q_PROPERTY(QColor ringColor3 READ ringColor3 WRITE setRingColor3)

public:
    explicit QEXTProgressRing(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTProgressRing();

    double minValue() const;
    double maxValue() const;
    double getValue() const;
    int precision() const;
    QString text() const;

    bool clipCenter() const;
    bool clockWise() const;
    bool percentVisible() const;

    int alarmMode() const;
    int startAngle() const;
    int ringPadding() const;
    int ringWidth() const;

    bool animationEnable() const;
    int animationDuration() const;
    QEasingCurve::Type animationEasingCurve() const;

    QColor backgroundColor() const;
    QColor textColor() const;
    QColor ringColor() const;
    QColor ringBackgroundColor() const;
    QColor circleColor() const;

    int ringValue1() const;
    int ringValue2() const;
    int ringValue3() const;

    QColor ringColor1() const;
    QColor ringColor2() const;
    QColor ringColor3() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public Q_SLOTS:
    void setRange(double minValue, double maxValue);
    void setRange(int minValue, int maxValue);

    void setMinValue(double minValue);
    void setMaxValue(double maxValue);

    void setValue(double value);
    void setValue(int value);

    void setPrecision(int precision);
    void setText(const QString &text);

    void setClipCenter(bool clipCenter);
    void setClockWise(bool clockWise);
    void setPercentVisible(bool visiable);

    void setAlarmMode(int alarmMode);
    void setStartAngle(int startAngle);
    void setRingPadding(int padding);
    void setRingWidth(int width);

    void setAnimationEnable(bool enable);
    void setAnimationDuration(int duration);
    void setAnimationEasingCurve(QEasingCurve::Type easingCurve);

    void setBackgroundColor(const QColor &color);
    void setTextColor(const QColor &color);
    void setRingColor(const QColor &color);
    void setRingBgColor(const QColor &color);
    void setCircleColor(const QColor &color);

    void setRingValue1(int value);
    void setRingValue2(int value);
    void setRingValue3(int value);

    void setRingColor1(const QColor &color);
    void setRingColor2(const QColor &color);
    void setRingColor3(const QColor &color);

Q_SIGNALS:
    void valueChanged(int value);

protected:
    void paintEvent(QPaintEvent *);

    void drawBackground(QPainter *painter);
    void drawRing(QPainter *painter);
    void drawPadding(QPainter *painter);
    void drawCircle(QPainter *painter);
    void drawValue(QPainter *painter);

    QScopedPointer<QEXTProgressRingPrivate> dd_ptr;

private slots:
    void updateValue(const QVariant &value);

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTProgressRing)
    QEXT_DECL_PRIVATE_D(dd_ptr, QEXTProgressRing)
};

#endif // _QEXTPROGRESSRING_H
