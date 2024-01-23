/***********************************************************************************************************************
**
** Library: QExt
**
** Copyright (C) 2018 feiyangqingyun. Contact: QQ:517216493
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

#ifndef _QEXTNAVIGATIONBUTTON_H
#define _QEXTNAVIGATIONBUTTON_H

#include <qextWidgetGlobal.h>

#include <QPushButton>

class QExtNavigationButtonPrivate;
class QEXT_WIDGETS_API QExtNavigationButton : public QPushButton
{
    Q_OBJECT
public:
    enum PositionEnum
    {
        Position_Left = 0,
        Position_Right,
        Position_Top,
        Position_Bottom
    };
    Q_ENUM(PositionEnum)

    explicit QExtNavigationButton(QWidget *parent = QEXT_NULLPTR);
    ~QExtNavigationButton();

    void setCheckable(bool); // cover base class

    PositionEnum navigationPosition() const;
    void setNavigationPosition(PositionEnum position);

    int padding() const;
    void setPadding(int padding);

    int iconSpace() const;
    void setIconSpace(int space);

    bool isIconVisible() const;
    void setIconVisible(bool visiable);

    QSize sizeHint() const QEXT_OVERRIDE;
    QSize minimumSizeHint() const QEXT_OVERRIDE;

protected:
    void enterEvent(QEvent *) QEXT_OVERRIDE;
    void leaveEvent(QEvent *) QEXT_OVERRIDE;
    void paintEvent(QPaintEvent *) QEXT_OVERRIDE;

    void drawBackground(QPainter *painter);
    void drawText(QPainter *painter);
    void drawIcon(QPainter *painter);
    void drawLine(QPainter *painter);
    void drawTriangle(QPainter *painter);

    QScopedPointer<QExtNavigationButtonPrivate> dd_ptr;

private:
    QEXT_DISABLE_COPY_MOVE(QExtNavigationButton)
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtNavigationButton)
};

#endif // _QEXTNAVIGATIONBUTTON_H
