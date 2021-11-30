/*************************************************************************************
**
** Library: QEXT
**
** Copyright (C) 2021 ChengXueWen. Contact: 1398831004@qq.com
** Copyright (C) 2016 feiyangqingyun. Contact: QQ:517216493
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

#ifndef _QEXTTOOLTIP_H
#define _QEXTTOOLTIP_H

#include <qextWidgetGlobal.h>

#include <QLabel>

class QEXTTooltipPrivate;
class QEXT_WIDGETS_API QEXTTooltip : public QLabel
{
    Q_OBJECT
    Q_DISABLE_COPY(QEXTTooltip)
    Q_DECLARE_PRIVATE_D(dd_ptr, QEXTTooltip)

    Q_PROPERTY(int borderRadius READ borderRadius WRITE setBorderRadius)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor foregroundColor READ foregroundColor WRITE setForegroundColor)

    Q_PROPERTY(bool arrowVisiable READ arrowVisiable WRITE setArrowVisiable)
    Q_PROPERTY(int arrowSize READ arrowSize WRITE setArrowSize)
    Q_PROPERTY(ArrowPositionType arrowPosition READ arrowPosition WRITE setArrowPosition)

    Q_PROPERTY(bool triangleVisiable READ triangleVisiable WRITE setTriangleVisiable)
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

    explicit QEXTTooltip(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTTooltip();

    int borderRadius() const;
    QColor backgroundColor() const;
    QColor foregroundColor() const;

    bool arrowVisiable() const;
    int arrowSize() const;
    ArrowPositionType arrowPosition() const;

    bool triangleVisiable() const;
    int triangleLen() const;
    TrianglePositionType trianglePosition() const;
    QColor triangleColor() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public Q_SLOTS:
    void setBorderRadius(int radius);

    void setBackgroundColor(const QColor &color);

    void setForegroundColor(const QColor &color);

    void setArrowVisiable(bool visiable);

    void setArrowSize(int size);

    void setArrowPosition(const ArrowPositionType &position);

    void setTriangleVisiable(bool visiable);

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

    QScopedPointer<QEXTTooltipPrivate> dd_ptr;
};

#endif // _QEXTTOOLTIP_H
