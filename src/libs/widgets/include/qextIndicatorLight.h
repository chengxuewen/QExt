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

#ifndef _QTKINDICATORLIGHT_H
#define _QTKINDICATORLIGHT_H

#include <qextWidgetGlobal.h>

#include <QWidget>
#include <QObject>

class QEXTIndicatorLightPrivate;
class QEXT_WIDGETS_API QEXTIndicatorLight : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(QEXTIndicatorLight)
    Q_DECLARE_PRIVATE_D(dd_ptr, QEXTIndicatorLight)

    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(QColor textLightColor READ lightTextColor WRITE setTextLightColor)
    Q_PROPERTY(QColor textNormalColor READ normalTextColor WRITE setTextNormalColor)
    Q_PROPERTY(QColor backgroundLightColor READ lightBackgroundColor WRITE setBackgroundLightColor)
    Q_PROPERTY(QColor backgroundNormalColor READ normalBackgroundColor WRITE setBackgroundNormalColor)
    Q_PROPERTY(int fontPixelSize READ fontPixelSize WRITE setFontPixelSize)

    Q_PROPERTY(QColor borderOutStartColor READ outBorderStartColor WRITE setBorderOutStartColor)
    Q_PROPERTY(QColor borderOutEndColor READ outBorderEndColor WRITE setBorderOutEndColor)
    Q_PROPERTY(QColor borderInStartColor READ inBorderStartColor WRITE setBorderInStartColor)
    Q_PROPERTY(QColor borderInEndColor READ inBorderEndColor WRITE setBorderInEndColor)

    Q_PROPERTY(bool isMoveEnable READ isMoveEnable WRITE setMoveEnable)
    Q_PROPERTY(bool overlayVisiable READ isOverlayVisiable WRITE setOverlayVisiable)
    Q_PROPERTY(QColor overlayColor READ overlayColor WRITE setOverlayColor)

    Q_PROPERTY(Style styleType READ styleType WRITE setStyleType)
    Q_PROPERTY(Shape shapeType READ shapeType WRITE setShapeType)

    Q_PROPERTY(bool lightState READ lightState WRITE setLightState)
    Q_PROPERTY(bool flickerState READ flickerState WRITE setFlickerState)
    Q_PROPERTY(int flickerInterval READ flickerInterval WRITE setFlickerInterval)

public:
    enum Style {
        Style_Green = 0,
        Style_Red,
        Style_Yellow,
        Style_Black,
        Style_Gray,
        Style_Blue,
        Style_LightBlue,
        Style_LightRed,
        Style_LightGreen
    };
    Q_ENUMS(Style)

    enum Shape {
        Shape_Circle = 0,
        Shape_Square,
        Shape_Triangle,
        Shape_Rounded
    };
    Q_ENUMS(Shape)

public:
    explicit QEXTIndicatorLight(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTIndicatorLight();

    QString text() const;
    QColor lightTextColor() const;
    QColor normalTextColor() const;
    QColor lightBackgroundColor() const;
    QColor normalBackgroundColor() const;
    int fontPixelSize() const;

    QColor outBorderStartColor() const;
    QColor outBorderEndColor() const;
    QColor inBorderStartColor() const;
    QColor inBorderEndColor() const;

    bool isMoveEnable() const;
    bool isOverlayVisiable() const;
    QColor overlayColor() const;

    Style styleType() const;
    Shape shapeType() const;

    bool lightState() const;
    bool flickerState() const;
    int flickerInterval() const;

    QSize sizeHint() const QEXT_DECL_OVERRIDE;
    QSize minimumSizeHint() const QEXT_DECL_OVERRIDE;

public Q_SLOTS:
    void setText(const QString &text);

    void setTextLightColor(const QColor &color);
    void setTextNormalColor(const QColor &color);

    void setBackgroundLightColor(const QColor &color);
    void setBackgroundNormalColor(const QColor &color);

    void setFontPixelSize(const int &size);

    void setBorderOutStartColor(const QColor &color);
    void setBorderOutEndColor(const QColor &color);

    void setBorderInStartColor(const QColor &color);
    void setBorderInEndColor(const QColor &color);

    void setMoveEnable(const bool &enable);
    void setOverlayVisiable(const bool &visiable);
    void setOverlayColor(const QColor &color);

    void setStyleType(const Style &type);
    void setShapeType(const Shape &type);

    void setLightState(const bool &state);
    void setFlickerState(const bool &state);
    void setFlickerInterval(const int &interval);
    void startFlicker();
    void stopFlicker();

protected Q_SLOTS:
    void flicker();

protected:
    bool eventFilter(QObject *watched, QEvent *event) QEXT_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *) QEXT_DECL_OVERRIDE;

    void drawBorderOut(QPainter *painter);
    void drawBorderIn(QPainter *painter);
    void drawBackground(QPainter *painter);
    void drawText(QPainter *painter);
    void drawOverlay(QPainter *painter);

    QScopedPointer<QEXTIndicatorLightPrivate> dd_ptr;
};

#endif // _QTKINDICATORLIGHT_H
