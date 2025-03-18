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

#ifndef _QEXTSWITCHBUTTON_H
#define _QEXTSWITCHBUTTON_H

#include <qextWidgetGlobal.h>

#include <QWidget>

class QExtSwitchButtonPrivate;
class QEXT_WIDGETS_API QExtSwitchButton : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(int space READ space WRITE setSpace)
    Q_PROPERTY(int rectRadius READ rectRadius WRITE setRectRadius)
    Q_PROPERTY(bool checked READ checked WRITE setChecked)
    Q_PROPERTY(bool isTextVisible READ isTextVisible WRITE setTextVisible)
    Q_PROPERTY(bool isCircleVisible READ isCircleVisible WRITE setCircleVisible)
    Q_PROPERTY(bool isAnimationEnable READ isAnimationEnable WRITE setAnimationEnable)
    Q_PROPERTY(Style styleType READ styleType WRITE setStyleType)

    Q_PROPERTY(QColor backgroundOffColor READ backgroundOffColor WRITE setOffBackgroundColor)
    Q_PROPERTY(QColor backgroundOnColor READ backgroundOnColor WRITE setOnBackgroundColor)
    Q_PROPERTY(QColor sliderOffColor READ sliderOffColor WRITE setOffSliderColor)
    Q_PROPERTY(QColor sliderOnColor READ sliderOnColor WRITE setOnSliderColor)
    Q_PROPERTY(QColor textOffColor READ textOffColor WRITE setOffTextColor)
    Q_PROPERTY(QColor textOnColor READ textOnColor WRITE setOnTextColor)

    Q_PROPERTY(QString offText READ offText WRITE setOffText)
    Q_PROPERTY(QString onText READ onText WRITE setOnText)

public:
    enum Style
    {
        Style_Rect = 0,
        Style_CircleIn = 1,
        Style_CircleOut = 2
    };
    Q_ENUMS(Style)

    explicit QExtSwitchButton(QWidget *parent = QEXT_NULLPTR);
    ~QExtSwitchButton();

    int space() const;
    int rectRadius() const;
    bool checked() const;
    bool isTextVisible() const;
    bool isCircleVisible() const;
    bool isAnimationEnable() const;

    Style styleType() const;

    QColor backgroundOffColor() const;
    QColor backgroundOnColor() const;
    QColor sliderOffColor() const;
    QColor sliderOnColor() const;
    QColor textOffColor() const;
    QColor textOnColor() const;

    QString offText() const;
    QString onText() const;

    QSize sizeHint() const QEXT_OVERRIDE;
    QSize minimumSizeHint() const QEXT_OVERRIDE;

Q_SIGNALS:
    void checkedChanged(bool checked);

public Q_SLOTS:
    void setSpace(int space);

    void setRectRadius(int radius);

    void setChecked(bool checked);

    void setTextVisible(bool visiable);

    void setCircleVisible(bool visiable);

    void setAnimationEnable(bool enable);

    void setStyleType(const Style &style);

    void setOffBackgroundColor(const QColor &color);
    void setOnBackgroundColor(const QColor &color);

    void setOffSliderColor(const QColor &color);
    void setOnSliderColor(const QColor &color);

    void setOffTextColor(const QColor &color);
    void setOnTextColor(const QColor &color);

    void setOffText(const QString &text);
    void setOnText(const QString &text);

protected:
    void mousePressEvent(QMouseEvent *) QEXT_OVERRIDE;
    void resizeEvent(QResizeEvent *) QEXT_OVERRIDE;
    void paintEvent(QPaintEvent *) QEXT_OVERRIDE;

    void drawBackground(QPainter *painter);
    void drawSlider(QPainter *painter);

    QScopedPointer<QExtSwitchButtonPrivate> dd_ptr;

private Q_SLOTS:
    void change();
    void updateValue();

private:
    QEXT_DISABLE_COPY_MOVE(QExtSwitchButton)
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtSwitchButton)
};

#endif // _QEXTSWITCHBUTTON_H
