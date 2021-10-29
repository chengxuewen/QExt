#ifndef _QEXTGUIGVVIEW_H
#define _QEXTGUIGVVIEW_H

#include <qextGuiGlobal.h>

#include <QGraphicsView>

class QEXTGuiGVViewPrivate;
class QEXT_GUI_API QEXTGuiGVView : public QGraphicsView
{
public:
    explicit QEXTGuiGVView(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTGuiGVView();


protected:
    QScopedPointer<QEXTGuiGVViewPrivate> d_ptr;

private:
    Q_DISABLE_COPY(QEXTGuiGVView)
    Q_DECLARE_PRIVATE(QEXTGuiGVView)
};

#endif // _QEXTGUIGVVIEW_H
