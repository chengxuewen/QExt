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

#ifndef _QEXTNAVIGATIONBAR_H
#define _QEXTNAVIGATIONBAR_H

#include <qextWidgetGlobal.h>

#include <QWidget>

class QExtNavigationBarPrivate;
class QEXT_WIDGETS_API QExtNavigationBar : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor backgroundStartColor READ backgroundStartColor WRITE setBackgroundStartColor)
    Q_PROPERTY(QColor backgroundEndColor READ backgroundEndColor WRITE setBackgroundEndColor)

    Q_PROPERTY(QColor barStartColor READ barStartColor WRITE setBarStartColor)
    Q_PROPERTY(QColor barEndColor READ barEndColor WRITE setBarEndColor)

    Q_PROPERTY(QColor textNormalColor READ textNormalColor WRITE setTextNormalColor)
    Q_PROPERTY(QColor textSelectColor READ textSelectColor WRITE setTextSelectColor)

    Q_PROPERTY(QString items READ items WRITE setItems)
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex)
    Q_PROPERTY(QString currentItem READ currentItem WRITE setCurrentItem)

    Q_PROPERTY(int backgroundRadius READ backgroundRadius WRITE setBackgroundRadius)
    Q_PROPERTY(int barRadius READ barRadius WRITE setBarRadius)
    Q_PROPERTY(int space READ space WRITE setSpace)

    Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor)

    Q_PROPERTY(BarStyleType barStyle READ barStyle WRITE setBarStyle)

    Q_PROPERTY(bool keyMoveEnable READ keyMoveEnable WRITE setKeyMoveEnable)
    Q_PROPERTY(bool isHorizontal READ isHorizontal WRITE setHorizontal)
    Q_PROPERTY(bool isFlat READ isFlat WRITE setFlat)

public:
    enum BarStyleType {
        BarStyle_Rect = 0,
        BarStyle_Line_Top = 1,
        BarStyle_Line_Right = 2,
        BarStyle_Line_Bottom = 3,
        BarStyle_Line_Left = 4
    };
    Q_ENUMS(BarStyleType)

    explicit QExtNavigationBar(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QExtNavigationBar();

    QColor backgroundStartColor() const;
    QColor backgroundEndColor() const;

    QColor barStartColor() const;
    QColor barEndColor() const;

    QColor textNormalColor() const;
    QColor textSelectColor() const;

    QString items() const;
    int currentIndex() const;
    QString currentItem() const;

    int backgroundRadius() const;
    int barRadius() const;
    int space() const;

    int lineWidth() const;
    QColor lineColor() const;

    BarStyleType barStyle() const;

    bool keyMoveEnable() const;
    bool isHorizontal() const;
    bool isFlat() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public Q_SLOTS:
    void clearItem();

    void setBackgroundStartColor(const QColor &color);
    void setBackgroundEndColor(const QColor &color);

    void setBarStartColor(const QColor &color);
    void setBarEndColor(const QColor &color);

    void setTextNormalColor(const QColor &color);
    void setTextSelectColor(const QColor &color);

    void setItems(const QString &items);
    void setCurrentIndex(int index);
    void setCurrentItem(const QString &item);

    void setBackgroundRadius(int radius);
    void setBarRadius(int radius);

    void setSpace(int space);

    void setLineWidth(int width);
    void setLineColor(const QColor &color);

    void setBarStyle(const BarStyleType &style);

    void setKeyMoveEnable(bool enable);
    void setHorizontal(bool horizontal);
    void setFlat(bool flat);

    void moveFirst();
    void moveLast();
    void movePrevious();
    void moveNext();
    void moveTo(int index);
    void moveTo(const QString &item);
    void moveTo(const QPointF &point);

Q_SIGNALS:
    void currentItemChanged(int index, const QString &item);

protected Q_SLOTS:
    void slide();

protected:
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
    void paintEvent(QPaintEvent *);

    void drawBackground(QPainter *painter);
    void drawBar(QPainter *painter);
    void drawText(QPainter *painter);

    QScopedPointer<QExtNavigationBarPrivate> dd_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QExtNavigationBar)
    QEXT_DECL_PRIVATE_D(dd_ptr, QExtNavigationBar)
};

#endif // _QEXTNAVIGATIONBAR_H
