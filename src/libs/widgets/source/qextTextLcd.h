/*************************************************************************************
**
** Library: QExt
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

#ifndef _QEXTTEXTLCD_H
#define _QEXTTEXTLCD_H

#include <qextWidgetGlobal.h>

#include <QWidget>
#include <QObject>

class QEXTTextLcdPrivate;
class QEXT_WIDGETS_API QEXTTextLcd : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(int textAlignment READ textAlignment WRITE setTextAlignment)

    Q_PROPERTY(int fontPixelSize READ fontPixelSize WRITE setFontPixelSize)
    Q_PROPERTY(int rowCount READ rowCount WRITE setRowCount)
    Q_PROPERTY(double spaceFactory READ spaceFactory WRITE setSpaceFactory)
    Q_PROPERTY(bool isHighLightBorderEnable READ isHighLightBorderEnable WRITE setHighLightBorderEnable)

    Q_PROPERTY(Animation animationType READ animationType WRITE setAnimationType)
    Q_PROPERTY(int animationInterval READ animationInterval WRITE setAnimationInterval)

    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)
    Q_PROPERTY(QColor foregroundColor READ foregroundColor WRITE setForegroundColor)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)

public:
    enum Animation {
        Animation_Static = 0,
        Animation_LeftToRight,
        Animation_RightToLeft,
        Animation_TopToBottom,
        Animation_BottomToTop
    };
    Q_ENUMS(Animation)

public:
    explicit QEXTTextLcd(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTTextLcd();

    QString text() const;
    int textAlignment() const;

    int fontPixelSize() const;
    int rowCount() const;
    double spaceFactory() const;
    bool isHighLightBorderEnable() const;

    Animation animationType() const;
    int animationInterval() const;

    QColor textColor() const;
    QColor foregroundColor() const;
    QColor backgroundColor() const;

    QSize sizeHint() const QEXT_DECL_OVERRIDE;
    QSize minimumSizeHint() const QEXT_DECL_OVERRIDE;

public Q_SLOTS:
    void setText(const QString &strText);

    void setTextAlignment(const int &iAlign);

    void setFontPixelSize(const int &iSize);
    void setRowCount(const int &iCount);
    void setSpaceFactory(const double &dFac);
    void setHighLightBorderEnable(const bool &bEnable);

    void setAnimationType(const Animation &eType);
    void setAnimationInterval(const int &iInterval);

    void setTextColor(const QColor &color);
    void setForegroundColor(const QColor &color);
    void setBackgroundColor(const QColor &color);

protected Q_SLOTS:
    void updateOffsetValue();

protected:
    void paintEvent(QPaintEvent *) QEXT_DECL_OVERRIDE;

    QScopedPointer<QEXTTextLcdPrivate> dd_ptr;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTTextLcd)
    QEXT_DECL_PRIVATE_D(dd_ptr, QEXTTextLcd)
};

#endif // _QEXTTEXTLCD_H
