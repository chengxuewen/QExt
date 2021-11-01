#ifndef QTKPLUGINRESOURCESTREEMODEL_H
#define QTKPLUGINRESOURCESTREEMODEL_H

#include <QTKPluginFramework/QTKPlugin>

#include <QAbstractItemModel>
#include <QDir>
#include <QSharedPointer>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKPluginResourceTreeItem;

class QTKPluginResourcesTreeModel : public QAbstractItemModel
{
public:

  QTKPluginResourcesTreeModel(QSharedPointer<const QTKPlugin> plugin, QObject* parent = 0);
  ~QTKPluginResourcesTreeModel();

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

  QSharedPointer<const QTKPlugin> plugin;
  QTKPluginResourceTreeItem* rootItem;

};

#endif // QTKPLUGINRESOURCESTREEMODEL_H
