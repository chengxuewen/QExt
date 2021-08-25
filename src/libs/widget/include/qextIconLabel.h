#ifndef QEXTICONLABEL_H
#define QEXTICONLABEL_H

#include <qextWidgetGlobal.h>
#include <qextobject.h>

#include <QWidget>

#if (QT_VERSION < QT_VERSION_CHECK(5, 7, 0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QEXTIconLabelPrivate;
class QEXT_WIDGET_API QEXTIconLabel : public QWidget, public QEXTObject
{
    Q_OBJECT

public:
    explicit QEXTIconLabel(QWidget *parent = QEXT_DECL_NULLPTR);
    ~QEXTIconLabel();

protected:
    void paintEvent(QPaintEvent *) QEXT_DECL_OVERRIDE;

private:
    QEXT_DECL_PRIVATE(QEXTIconLabel)
    QEXT_DISABLE_COPY_MOVE(QEXTIconLabel)
};

#endif // QEXTICONLABEL_H
