#ifndef _QEXTSTYLESHEETHOOKER_P_H
#define _QEXTSTYLESHEETHOOKER_P_H

#include <qextStyleSheetHooker.h>

#include <QPointer>

class QEXT_WIDGETS_API QExtStyleSheetHookerPrivate
{
public:
    explicit QExtStyleSheetHookerPrivate(QExtStyleSheetHooker *q);
    virtual ~QExtStyleSheetHookerPrivate();

    QExtStyleSheetHooker * const q_ptr;

    QPointer<QWidget> mTarget;

private:
    QEXT_DECLARE_PUBLIC(QExtStyleSheetHooker)
    QEXT_DECLARE_DISABLE_COPY_MOVE(QExtStyleSheetHookerPrivate)
};

#endif // _QEXTSTYLESHEETHOOKER_P_H
