#ifndef QTKPLUGINTABLEMODEL_H
#define QTKPLUGINTABLEMODEL_H

#include <QTKPluginFramework/QTKPlugin>
#include <QTKPluginFramework/QTKPluginEvent>
#include <QTKPluginFramework/QTKPluginContext>

#include <QAbstractTableModel>
#include <QList>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKPluginTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    QTKPluginTableModel(QTKPluginContext* pc, QObject* parent = 0);

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const;

protected Q_SLOTS:

    void pluginChanged(const QTKPluginEvent& event);

private:

    QString getStringForState(const QTKPlugin::State state) const;

    QList<QSharedPointer<QTKPlugin> > plugins;
};

#endif // QTKPLUGINTABLEMODEL_H
