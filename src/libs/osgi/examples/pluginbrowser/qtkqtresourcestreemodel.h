#ifndef QTKQTRESOURCESTREEMODEL_H
#define QTKQTRESOURCESTREEMODEL_H

#include <QAbstractItemModel>
#include <QDir>

class QTKQtResourceTreeItem;

class QTKQtResourcesTreeModel : public QAbstractItemModel
{
public:

  QTKQtResourcesTreeModel(QObject* parent = 0);
  ~QTKQtResourcesTreeModel();

  QVariant data(const QModelIndex &index, int role) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant headerData(int section, Qt::Orientation orientation,
                     int role = Qt::DisplayRole) const;
  QModelIndex index(int row, int column,
                   const QModelIndex &parent = QModelIndex()) const;
  QModelIndex parent(const QModelIndex &index) const;
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;

private:

  QTKQtResourceTreeItem* rootItem;

};

#endif // QTKQTRESOURCESTREEMODEL_H
