#ifndef _QEXTMVVMMODELMAPPER_P_H
#define _QEXTMVVMMODELMAPPER_P_H

#include <qextMvvmGlobal.h>
#include <qextConnection.h>
#include <qextFunction.h>
#include <qextSignal.h>

#include <QMultiMap>

class QEXTMvvmItem;
class QEXTMvvmModel;
class QEXTMvvmTagRow;
class QEXTMvvmModelMapper;
class QEXT_MVVM_API QEXTMvvmModelMapperPrivate
{
public:
    explicit QEXTMvvmModelMapperPrivate(QEXTMvvmModelMapper *q);
    virtual ~QEXTMvvmModelMapperPrivate();

    QEXTMvvmModelMapper * const q_ptr;

    QEXTSignal<void, QEXTMvvmItem *, QEXTMvvmTagRow> m_itemAboutToBeInsertedSignal;
    QEXTSignal<void, QEXTMvvmItem *, QEXTMvvmTagRow> m_itemInsertedSignal;

    QEXTSignal<void, QEXTMvvmItem *, QEXTMvvmTagRow> m_itemAboutToBeRemovedSignal;
    QEXTSignal<void, QEXTMvvmItem *, QEXTMvvmTagRow> m_itemRemovedSignal;

    QEXTSignal<void, QEXTMvvmItem *, int> m_itemDataAboutToBeChangedSignal;
    QEXTSignal<void, QEXTMvvmItem *, int> m_itemDataChangedSignal;

    QEXTSignal<void, QEXTMvvmItem *> m_itemAboutToBeDestroyedSignal;
    QEXTSignal<void, QEXTMvvmItem *> m_itemDestroyedSignal;

    QEXTSignal<void, QEXTMvvmModel *> m_modelAboutToBeDestroyedSignal;
    QEXTSignal<void, QEXTMvvmModel *> m_modelDestroyedSignal;

    QEXTSignal<void, QEXTMvvmModel *> m_modelAboutToBeResetedSignal;
    QEXTSignal<void, QEXTMvvmModel *> m_modelResetedSignal;

    QMultiMap<void *, QEXTConnection> m_lisenterConnectionMap;

    bool m_active;
    QEXTMvvmModel *m_model;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmModelMapperPrivate)
    Q_DECLARE_PUBLIC(QEXTMvvmModelMapper)
};

#endif // _QEXTMVVMMODELMAPPER_P_H
