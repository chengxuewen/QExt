#ifndef _QEXTMVVMMODEL_P_H
#define _QEXTMVVMMODEL_P_H

#include <qextMvvmGlobal.h>
#include <qextMvvmItemManager.h>
#include <qextMvvmCommandService.h>
#include <qextMvvmModelMapper.h>

#include <QString>
#include <QScopedPointer>

class QEXTMvvmModel;
class QEXTMvvmModelPrivate
{
public:
    explicit QEXTMvvmModelPrivate(QEXTMvvmModel *q);
    virtual ~QEXTMvvmModelPrivate();

    QEXTMvvmModel * const q_ptr;

    QString m_modelType;
    QScopedPointer<QEXTMvvmItemManager> m_itemManager;
    QScopedPointer<QEXTMvvmCommandService> m_commands;
    QScopedPointer<QEXTMvvmModelMapper> m_mapper;
    QScopedPointer<QEXTMvvmItem> m_rootItem;

private:
    QEXT_DECL_DISABLE_COPY_MOVE(QEXTMvvmModelPrivate)
    QEXT_DECL_PUBLIC(QEXTMvvmModel)
};

#endif // _QEXTMVVMMODEL_P_H
