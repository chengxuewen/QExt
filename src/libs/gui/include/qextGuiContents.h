#ifndef _QEXTGUICONTENTS_H
#define _QEXTGUICONTENTS_H

#include <qextGuiGlobal.h>
#include <qextGuiItemChangeListener.h>

#include <QObject>

class QEXTGuiContentsPrivate;
class QEXT_GUI_API QEXTGuiContents : public QObject, public QDeclarativeItemChangeListener
{
    Q_OBJECT
public:
    QEXTGuiContents(QEXTGuiGVItem *item);
    ~QEXTGuiContents();

    QRectF rectF() const;

    void childRemoved(QEXTGuiGVItem *item);
    void childAdded(QEXTGuiGVItem *item);

    void calcGeometry();
    void complete();

Q_SIGNALS:
    void rectChanged(QRectF);

protected:
    void itemVisibilityChanged(QEXTGuiGVItem *item) QEXT_DECL_OVERRIDE;
    void itemGeometryChanged(QEXTGuiGVItem *item, const QRectF &newGeometry, const QRectF &oldGeometry) QEXT_DECL_OVERRIDE;
    void itemDestroyed(QEXTGuiGVItem *item) QEXT_DECL_OVERRIDE;

    void calcHeight(QEXTGuiGVItem *changed = QEXT_DECL_NULLPTR);
    void calcWidth(QEXTGuiGVItem *changed = QEXT_DECL_NULLPTR);

    QScopedPointer<QEXTGuiContentsPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QEXTGuiContents)
    Q_DECLARE_PRIVATE(QEXTGuiContents)
};

#endif // _QEXTGUICONTENTS_H
