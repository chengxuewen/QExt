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

#ifndef _QEXTTUMBLER_H
#define _QEXTTUMBLER_H

#include <qextWidgetGlobal.h>

#include <QWidget>

class QEXTTumblerPrivate;
class QEXT_WIDGETS_API QEXTTumbler : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(QEXTTumbler)
    Q_DECLARE_PRIVATE_D(dd_ptr, QEXTTumbler)

    Q_PROPERTY(int m_currentIndex READ currentIndex WRITE setCurrentIndex)
    Q_PROPERTY(QString m_currentValue READ currentValue WRITE setCurrentValue)
    Q_PROPERTY(bool m_isHorizontal READ isHorizontal WRITE setHorizontal)

    Q_PROPERTY(QColor m_foregroundColor READ foregroundColor WRITE setForegroundColor)
    Q_PROPERTY(QColor m_backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor m_lineColor READ lineColor WRITE setLineColor)
    Q_PROPERTY(QColor m_textColor READ textColor WRITE setTextColor)

public:
    explicit QEXTTumbler(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTTumbler();

    QStringList valueList() const;
    int currentIndex() const;
    QString currentValue() const;
    bool isHorizontal() const;

    QColor foregroundColor() const;
    QColor backgroundColor() const;
    QColor lineColor() const;
    QColor textColor() const;

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public Q_SLOTS:
    void setValueList(const QStringList &values);

    void setCurrentIndex(int index);

    void setCurrentValue(const QString &value);

    void setHorizontal(bool horizontal);

    void setForegroundColor(const QColor &color);

    void setBackgroundColor(const QColor &color);

    void setLineColor(const QColor &color);

    void setTextColor(const QColor &color);

Q_SIGNALS:
    void currentIndexChanged(int index);
    void currentValueChanged(const QString &value);

protected:
    void wheelEvent(QWheelEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

    void drawBackground(QPainter *painter);
    void drawLine(QPainter *painter);
    void drawText(QPainter *painter, int index, int offset);

    void checkPosition();

    QScopedPointer<QEXTTumblerPrivate> dd_ptr;
};

#endif // _QEXTTUMBLER_H
