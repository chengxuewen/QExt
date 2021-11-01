#include "qtkmticon_p.h"

#include <QTKPluginFramework/QTKPlugin>

QTKMTIcon::QTKMTIcon()
    : _size(-1)
{
}

QTKMTIcon::QTKMTIcon(const QString& fileName, int size, const QSharedPointer<QTKPlugin>& plugin)
    : _fileName(fileName), _size(size), _plugin(plugin)
{
}

QTKMTIcon::QTKMTIcon(const QString& fileName, const QSharedPointer<QTKPlugin>& plugin)
    : _fileName(fileName), _size(-1), _plugin(plugin)
{
}

QString QTKMTIcon::getIconName() const
{
    return _fileName;
}

int QTKMTIcon::getIconSize() const
{
    return _size;
}

QSharedPointer<QTKPlugin> QTKMTIcon::getIconPlugin() const
{
    return _plugin;
}

QTKMTIcon::operator bool () const
{
    return !_plugin.isNull();
}
