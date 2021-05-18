#ifndef QEXTCONTROLBASE_H
#define QEXTCONTROLBASE_H

#include <qextcontrolsglobal.h>

#include <qextobject.h>

#include <QPaintEvent>
#include <QPainter>
#include <QObject>
#include <QRectF>
#include <QSize>



class QEXTControlBasePrivate;
class QEXT_CONTROLS_API QEXTControlBase : public QObject, public QEXTObject
{
    Q_OBJECT
public:
    explicit QEXTControlBase(QObject *parent = QEXT_NULLPTR);
    ~QEXTControlBase();

protected:
    virtual void controlPaintPixmap(QPainter *painter) = 0;
    virtual QSize controlSizeHint() const = 0;
    virtual QSize controlMinimumSizeHint() const = 0;

    virtual void controlPaintEvent(QPaintEvent *event);
    virtual bool controlEvent(QEvent *event);
    virtual void controlKeyPressEvent(QKeyEvent *event);
    virtual void controlKeyReleaseEvent(QKeyEvent *event);
    virtual void controlMousePressEvent(QMouseEvent *event);
    virtual void controlMouseReleaseEvent(QMouseEvent *event);
    virtual void controlMouseMoveEvent(QMouseEvent *event);
    virtual void controlFocusInEvent(QFocusEvent *event);
    virtual void controlFocusOutEvent(QFocusEvent *event);
    virtual void controlContextMenuEvent(QContextMenuEvent *event);
    virtual void controlTabletEvent(QTabletEvent *event);
    virtual void controlActionEvent(QActionEvent *event);
    virtual void controlDragEnterEvent(QDragEnterEvent *event);
    virtual void controlDragMoveEvent(QDragMoveEvent *event);
    virtual void controlDragLeaveEvent(QDragLeaveEvent *event);
    virtual void controlDropEvent(QDropEvent *event);

private:
    QEXT_DISABLE_COPY_MOVE(QEXTControlBase)
    QEXT_DECLARE_PRIVATE(QEXTControlBase)
};



#endif // QEXTCONTROLBASE_H
