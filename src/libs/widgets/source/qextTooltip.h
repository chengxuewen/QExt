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

#ifndef _QEXTTOOLTIP_H
#define _QEXTTOOLTIP_H

#include <qextWidgetGlobal.h>

#include <QLabel>

class QExtTooltipPrivate;
class QEXT_WIDGETS_API QExtTooltip : public QLabel
{
    Q_OBJECT

    Q_PROPERTY(int borderRadius READ borderRadius WRITE setBorderRadius)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor foregroundColor READ foregroundColor WRITE setForegroundColor)

    Q_PROPERTY(bool arrowVisible READ arrowVisible WRITE setArrowVisible)
    Q_PROPERTY(int arrowSize READ arrowSize WRITE setArrowSize)
    Q_PROPERTY(ArrowPositionType arrowPosition READ arrowPosition WRITE setArrowPosition)

    Q_PROPERTY(bool triangleVisible READ triangleVisible WRITE setTriangleVisible)
    Q_PROPERTY(int triangleLen READ triangleLen WRITE setTriangleLen)
    Q_PROPERTY(TrianglePositionType trianglePosition READ trianglePosition WRITE setTrianglePosition)
    Q_PROPERTY(QColor triangleColor READ triangleColor WRITE setTriangleColor)

public:
    enum ArrowPositionType
    {
        ArrowPosition_Left = 0,
        ArrowPosition_Right = 1,
        ArrowPosition_Top = 2,
        ArrowPosition_Bottom = 3
    };
    Q_ENUMS(ArrowPositionType)

    enum TrianglePositionType
    {
        TrianglePosition_Left = 0,
        TrianglePosition_Right = 1,
        TrianglePosition_Top = 2,
        TrianglePosition_Bottom = 3
    };
    Q_ENUMS(TrianglePositionType)

    explicit QExtTooltip(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QExtTooltip();

    int borderRadius() const;
    QColor backgroundColor() const;
    QColor foregroundColor() const;

    bool arrowVisible() const;
    int arrowSize() const;
    ArrowPositionType arrowPosition() const;

    bool triangleVisible() const;
    int triangleLen() const;
    TrianglePositionType trianglePosition() const;
    QColor triangleColor() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public Q_SLOTS:
    void setBorderRadius(int radius);

    void setBackgroundColor(const QColor &color);

    void setForegroundColor(const QColor &color);

    void setArrowVisible(bool visiable);

    void setArrowSize(int size);

    void setArrowPosition(const ArrowPositionType &position);

    void setTriangleVisible(bool visiable);

    void setTriangleLen(int len);

    void setTrianglePosition(const TrianglePositionType &position);

    void setTriangleColor(const QColor &color);

Q_SIGNALS:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

    void drawBackground(QPainter *painter);
    void drawText(QPainter *painter);
    void drawTriangle(QPainter *painter);

    QScopedPointer<QExtTooltipPrivate> dd_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QExtTooltip)
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtTooltip)
};

#endif // _QEXTTOOLTIP_H
