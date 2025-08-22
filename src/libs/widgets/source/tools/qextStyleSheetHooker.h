#ifndef _QEXTSTYLESHEETHOOKER_H
#define _QEXTSTYLESHEETHOOKER_H

#include <QObject>
#include <QWidget>

#include <qextWidgetGlobal.h>

class QExtStyleSheetHookerPrivate;
class QEXT_WIDGETS_API QExtStyleSheetHooker : public QObject
{
    Q_OBJECT
public:
    explicit QExtStyleSheetHooker(QObject *parent = QEXT_NULLPTR);
    ~QExtStyleSheetHooker() QEXT_OVERRIDE;

    QWidget *hookTarget() const;
    void setHookTarget(QWidget *target);

Q_SIGNALS:
    void hookTargetChanged(QWidget *target);

protected:
    bool eventFilter(QObject *watched, QEvent *event) QEXT_OVERRIDE;

    QScopedPointer<QExtStyleSheetHookerPrivate> dd_ptr;

private:
    QEXT_DECLARE_PRIVATE_D(dd_ptr, QExtStyleSheetHooker)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtStyleSheetHooker)
};

#endif // _QEXTSTYLESHEETHOOKER_H
