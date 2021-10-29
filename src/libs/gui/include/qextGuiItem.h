#ifndef _QEXTGUIITEM_H
#define _QEXTGUIITEM_H

#include <qextGuiGlobal.h>

#include <QObject>
#include <QSizeF>
#include <QPointF>

class QEXTGuiItemPrivate;
class QEXT_GUI_API QEXTGuiItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QEXTGuiItem *parentItem READ parentItem WRITE setParentItem NOTIFY parentItemChanged DESIGNABLE false FINAL)

    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged FINAL)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged FINAL)
    Q_PROPERTY(qreal z READ z WRITE setZ NOTIFY zChanged FINAL)
    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged RESET resetWidth FINAL)
    Q_PROPERTY(qreal height READ height WRITE setHeight NOTIFY heightChanged RESET resetHeight FINAL)
    Q_PROPERTY(qreal implicitWidth READ implicitWidth WRITE setImplicitWidth NOTIFY implicitWidthChanged FINAL)
    Q_PROPERTY(qreal implicitHeight READ implicitHeight WRITE setImplicitHeight NOTIFY implicitHeightChanged FINAL)

    Q_PROPERTY(QSizeF size READ size WRITE setSize NOTIFY sizeChanged FINAL)
    Q_PROPERTY(QPointF pos READ pos WRITE setPos NOTIFY posChanged FINAL)

    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged FINAL)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity NOTIFY opacityChanged FINAL)
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation NOTIFY rotationChanged FINAL)
    Q_PROPERTY(qreal scale READ scale WRITE setScale NOTIFY scaleChanged FINAL)
    Q_PROPERTY(bool visiable READ visiable WRITE setVisiable NOTIFY visibleChanged FINAL)
    Q_PROPERTY(bool clip READ clip WRITE setClip NOTIFY clipChanged FINAL)
    Q_PROPERTY(bool smooth READ smooth WRITE setSmooth NOTIFY smoothChanged FINAL)
    Q_PROPERTY(bool antialiasing READ antialiasing WRITE setAntialiasing NOTIFY antialiasingChanged RESET resetAntialiasing FINAL)

    Q_PROPERTY(bool focus READ hasFocus WRITE setFocus NOTIFY focusChanged FINAL)
    Q_PROPERTY(bool activeFocus READ hasActiveFocus NOTIFY activeFocusChanged FINAL)
    Q_PROPERTY(bool activeFocusOnTab READ hasActiveFocusOnTab WRITE setActiveFocusOnTab NOTIFY activeFocusOnTabChanged FINAL)

public:
    explicit QEXTGuiItem(QEXTGuiItem *parent = QEXT_DECL_NULLPTR);
    ~QEXTGuiItem();

    QEXTGuiItem *parentItem() const;
    void setParentItem(QEXTGuiItem *parent);

    bool enabled() const;
    void setEnabled(bool enabled);

    qreal opacity() const;
    void setOpacity(qreal opacity);

    qreal rotation() const;
    void setRotation(qreal rotation);

    qreal scale() const;
    void setScale(qreal scale);

    bool visiable() const;
    void setVisiable(bool visiable);

    bool clip() const;
    void setClip(bool clip);

    bool smooth() const;
    void setSmooth(bool smooth);

    bool antialiasing() const;
    void setAntialiasing(bool antialiasing);
    void resetAntialiasing();

    QSizeF size() const;
    void setSize(const QSizeF &size);

    QPointF pos() const;
    void setPos(const QPointF &pos);

    qreal width() const;
    void setWidth(qreal width);
    void resetWidth();

    qreal height() const;
    void setHeight(qreal height);
    void resetHeight();

    qreal implicitWidth() const;
    void setImplicitWidth(qreal width);

    qreal implicitHeight() const;
    void setImplicitHeight(qreal height);

    qreal x() const;
    void setX(qreal x);

    qreal y() const;
    void setY(qreal y);

    qreal z() const;
    void setZ(qreal z);

    bool hasFocus() const;
    void setFocus(bool focus);

    bool hasActiveFocus() const;
    void setActiveFocus(bool focus);

    bool hasActiveFocusOnTab() const;
    void setActiveFocusOnTab(bool focus);

Q_SIGNALS:
    void parentItemChanged();
    void enabledChanged();
    void opacityChanged();
    void rotationChanged();
    void scaleChanged();
    void visibleChanged();
    void clipChanged();
    void smoothChanged();
    void antialiasingChanged();
    void sizeChanged();
    void posChanged();
    void widthChanged();
    void heightChanged();
    void implicitWidthChanged();
    void implicitHeightChanged();
    void xChanged();
    void yChanged();
    void zChanged();
    void focusChanged();
    void activeFocusChanged();
    void activeFocusOnTabChanged();


protected:
    QEXTGuiItem(QEXTGuiItemPrivate *d, QEXTGuiItem *parent = QEXT_DECL_NULLPTR);

    QScopedPointer<QEXTGuiItemPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QEXTGuiItem)
    Q_DECLARE_PRIVATE(QEXTGuiItem)
};

#endif // _QEXTGUIITEM_H
