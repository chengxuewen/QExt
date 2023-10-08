/*************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
** Copyright (C) 2017 feiyangqingyun. Contact: QQ:517216493
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

#ifndef _QEXTSLIDER_H
#define _QEXTSLIDER_H

#include <qextWidgetGlobal.h>

#include <QSlider>

class QEXTTooltip;
class QEXTSliderPrivate;
class QEXT_WIDGETS_API QEXTSlider : public QSlider
{
    Q_OBJECT

    Q_PROPERTY(int borderRadius READ borderRadius WRITE setBorderRadius)
    Q_PROPERTY(int arrowSize READ arrowSize WRITE setArrowSize)
    Q_PROPERTY(ArrowStyleType arrowStyle READ arrowStyle WRITE setArrowStyle)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor foregroundColor READ foregroundColor WRITE setForegroundColor)

    Q_PROPERTY(int toolTipWidth READ toolTipWidth WRITE setToolTipWidth)
    Q_PROPERTY(int toolTipHeight READ toolTipHeight WRITE setToolTipHeight)
    Q_PROPERTY(QFont toolTipFont READ toolTipFont WRITE setToolTipFont)

    Q_PROPERTY(bool timeVisible READ timeVisible WRITE setTimeVisible)
    Q_PROPERTY(bool clickEnable READ clickEnable WRITE setClickEnable)
    Q_PROPERTY(QString unitText READ unitText WRITE setUnitText)

public:
    enum ArrowStyleType
    {
        ArrowStyle_Left = 0,
        ArrowStyle_Right = 1,
        ArrowStyle_Top = 2,
        ArrowStyle_Bottom = 3
    };
    Q_ENUMS(ArrowStyleType)

    explicit QEXTSlider(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTSlider();

    int borderRadius() const;
    int arrowSize() const;
    ArrowStyleType arrowStyle() const;

    QColor backgroundColor() const;
    QColor foregroundColor() const;

    int toolTipWidth() const;
    int toolTipHeight() const;
    QFont toolTipFont() const;

    bool timeVisible() const;
    bool clickEnable() const;
    QString unitText() const;

    QEXTTooltip *tooltip() const;

Q_SIGNALS:
    void clicked();

public Q_SLOTS:
    void setBorderRadius(int radius);

    void setArrowSize(int size);

    void setArrowStyle(const ArrowStyleType &style);

    void setBackgroundColor(const QColor &color);

    void setForegroundColor(const QColor &color);

    void setToolTipWidth(int width);

    void setToolTipHeight(int height);

    void setToolTipFont(const QFont &font);

    void setTimeVisible(bool visiable);

    void setClickEnable(bool enable);

    void setUnitText(const QString &unit);

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

    QScopedPointer<QEXTSliderPrivate> dd_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTSlider)
    QEXT_DECL_PRIVATE_D(dd_ptr, QEXTSlider)
};

#endif // _QEXTSLIDER_H
