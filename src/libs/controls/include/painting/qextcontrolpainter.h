#ifndef QEXTPAINTER_H
#define QEXTPAINTER_H

#include <qextcontrolsglobal.h>
#include <qextcontrolcolor.h>
#include <qextcontrolfont.h>
#include <qextcontrolbrush.h>
#include <qextcontrolpen.h>

#include <QFontDatabase>
#include <QPen>
#include <QFontInfo>
#include <QFont>
#include <QPainter>
#include <QGraphicsDropShadowEffect>

class QEXT_CONTROLS_API QEXTPainter
{
public:
    enum LineCapType {
        CAP_BUTT = 0,
        CAP_ROUND = 1,
        CAP_SQUARE = 2
    };
    enum LineJoin {
        JOIN_ROUND = 1,
        JOIN_BEVEL = 3,
        JOIN_MITER = 4
    };

    QEXTPainter();
    virtual ~QEXTPainter();

    /*Render styles*/
    const QEXTBrush &brush() const;
    void setBrush(const QEXTBrush &brush);

    const QEXTPen &pen() const;
    void setPen(const QEXTPen &pen);

    const QEXTFont &font() const;
    void setFont(const QEXTFont &font);

    qreal opacity() const;
    void setOpacity(qreal opacity);

    /*State Handling*/
    void save();
    void restore();
    void reset();

    //    /*Frame controls*/
    //    void beginFrame(float width, float height);
    //    void beginFrameAt(float x, float y, float width, float height);
    //    void endFrame();
    //    void cancelFrame();


    //    // *** Transforms ***
    //    void resetTransform();
    //    void transform(const QTransform &transform);
    //    void translate(float x, float y);
    //    void translate(const QPointF &point);
    //    void rotate(float angle);
    //    void skewX(float angle);
    //    void skewY(float angle);
    //    void scale(float scale);
    //    void scale(float scaleX, float scaleY);
    //    const QTransform currentTransform() const;

    //    // *** Scissoring ***
    //    //
    //    // Scissoring allows you to clip the rendering into a rectangle. This is useful for varius
    //    // user interface cases like rendering a text edit or a timeline.

    //    void setClipRect(float x, float y, float w, float h);
    //    void setClipRect(const QRectF &rect);
    //    void resetClipping();

    //    //  *** Paths ***

    //    void beginPath();
    //    void closePath();
    //    void moveTo(float x, float y);
    //    void moveTo(const QPointF &point);
    //    void lineTo(float x, float y);
    //    void lineTo(const QPointF &point);
    //    void bezierTo(float c1x, float c1y, float c2x, float c2y, float x, float y);
    //    void bezierTo(const QPointF &controlPoint1, const QPointF &controlPoint2, const QPointF &endPoint);
    //    void quadTo(float cx, float cy, float x, float y);
    //    void quadTo(const QPointF &controlPoint, const QPointF &endPoint);
    //    void arcTo(float c1x, float c1y, float c2x, float c2y, float radius);
    //    void arcTo(const QPointF &controlPoint1, const QPointF &controlPoint2, float radius);

    //    void arc(float cx, float cy, float radius, float a0, float a1, PathWinding direction=QNanoPainter::WINDING_CW);
    //    void arc(const QPointF &centerPoint, float radius, float a0, float a1, PathWinding direction=QNanoPainter::WINDING_CW);
    //    void rect(float x, float y, float width, float height);
    //    void rect(const QRectF &rect);
    //    void roundedRect(float x, float y, float width, float height, float radius);
    //    void roundedRect(const QRectF &rect, float radius);
    //    void roundedRect(float x, float y, float width, float height, float radiusTopLeft, float radiusTopRight, float radiusBottomRight, float radiusBottomLeft);
    //    void roundedRect(const QRectF &rect, float radiusTopLeft, float radiusTopRight, float radiusBottomRight, float radiusBottomLeft);
    //    void ellipse(float centerX, float centerY, float radiusX, float radiusY);
    //    void ellipse(const QRectF &rect);
    //    void circle(float centerX, float centerY, float radius);
    //    void circle(const QPointF &centerPoint, float radius);

    //    void setPathWinding(PathWinding winding);
    //    void beginSolidSubPath();
    //    void beginHoleSubPath();

    //    void fill();
    //    void stroke();

    //    // *** Direct drawing ***

    //    void fillRect(float x, float y, float width, float height);
    //    void fillRect(const QRectF &rect);
    //    void strokeRect(float x, float y, float width, float height);
    //    void strokeRect(const QRectF &rect);

    //    // *** Images ***

    //    void drawImage(QNanoImage &image, float x, float y);
    //    void drawImage(QNanoImage &image, float x, float y, float width, float height);
    //    void drawImage(QNanoImage &image, const QRectF destinationRect);
    //    void drawImage(QNanoImage &image, const QRectF sourceRect, const QRectF destinationRect);

    //    // *** Text ***

    //    void setFont(QNanoFont &font);
    //    void setTextAlign(TextAlign align);
    //    void setTextBaseline(TextBaseline baseline);

    //    void fillText(const QString &text, float x, float y, float maxWidth = -1);
    //    void fillText(const QString &text, const QPointF &point, float maxWidth = -1);
    //    void fillText(const QString &text, const QRectF &rect);

    //    const QRectF textBoundingBox(const QString &text, float x, float y, float maxWidth = -1);

    //    // *** Other ***

    //    void setAntialias(float antialias);
    //    void setPixelAlign(PixelAlign align);
    //    void setPixelAlignText(PixelAlign align);
    //    float devicePixelRatio() const;

    //    // ***** Static methods *****

    //    static float mmToPx(float mm);
    //    static float ptToPx(float pt);
};

#endif // QEXTPAINTER_H
