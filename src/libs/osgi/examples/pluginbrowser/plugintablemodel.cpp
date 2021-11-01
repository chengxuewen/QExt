#include "qtkplugintablemodel.h"

#include <QTKPluginFramework/QTKPlugin>
#include <QTKPluginFramework/QTKPluginContext>

QTKPluginTableModel::QTKPluginTableModel(QTKPluginContext* pc, QObject* parent)
    : QAbstractTableModel(parent)
{
    plugins = pc->getPlugins();
    pc->connectPluginListener(this, SLOT(pluginChanged(QTKPluginEvent)));
}

QVariant QTKPluginTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) return QVariant();

    QSharedPointer<QTKPlugin> plugin = plugins.at(index.row());
    if (role == Qt::DisplayRole)
    {
        int col = index.column();
        if (col == 0)
        {
            return QVariant(plugin->getSymbolicName());
        }
        else if (col == 1)
        {
            return QVariant(plugin->getVersion().toString());
        }
        else if (col == 2)
        {
            return QVariant(getStringForState(plugin->getState()));
        }
    }
    else if (role == Qt::UserRole)
    {
        return QVariant::fromValue<qlonglong>(plugin->getPluginId());
    }

    return QVariant();
}

QVariant QTKPluginTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        if (section == 0)
        {
            return QVariant("Plugin");
        }
        else if (section == 1)
        {
            return QVariant("Version");
        }
        else if (section == 2)
        {
            return QVariant("State");
        }
    }

    return QVariant();
}

int QTKPluginTableModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    return 3;
}

int QTKPluginTableModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    return plugins.size();
}

QString QTKPluginTableModel::getStringForState(const QTKPlugin::State state) const
{
    static const QString uninstalled("UNINSTALLED");
    static const QString installed("INSTALLED");
    static const QString resolved("RESOLVED");
    static const QString starting("STARTING");
    static const QString stopping("STOPPING");
    static const QString active("ACTIVE");

    switch(state)
    {
    case QTKPlugin::State_Uninstalled: return uninstalled;
    case QTKPlugin::State_Installed: return installed;
    case QTKPlugin::State_Resolved: return resolved;
    case QTKPlugin::State_Starting: return starting;
    case QTKPlugin::State_Stopping: return stopping;
    case QTKPlugin::State_Active: return active;
    default: return QString("unknown");
    }
}

void QTKPluginTableModel::pluginChanged(const QTKPluginEvent& event)
{
    QModelIndex topLeftIndex = createIndex(plugins.indexOf(event.getPlugin()), 0);
    QModelIndex bottomRightIndex = createIndex(topLeftIndex.row(), columnCount()-1);
    emit dataChanged(topLeftIndex, bottomRightIndex);
}
