#ifndef QEXTMVVMMODEL_H
#define QEXTMVVMMODEL_H

#include <qextmvvmglobal.h>
#include <qextmvvmitem.h>

#include <QObject>



class QEXTMvvmModelMapper;
class QEXT_MVVM_API QEXTMvvmModel
{
public:
    QEXTMvvmModel(const QString &modelType);
    virtual ~QEXTMvvmModel();

    QEXTMvvmItem* rootItem() const;

    QVariant data(QEXTMvvmItem* item, int role) const;
    bool setData(QEXTMvvmItem* item, const QVariant& value, int role);

    QEXTMvvmModelMapper *mapper() const;

private:
    QString m_model_type;
//    QScopedPointer<ItemManager> m_item_manager;
//    QScopedPointer<CommandService> m_commands;
    QScopedPointer<QEXTMvvmModelMapper> m_mapper;
    QScopedPointer<QEXTMvvmItem> m_root_item;
};



#endif // QEXTMVVMMODEL_H
