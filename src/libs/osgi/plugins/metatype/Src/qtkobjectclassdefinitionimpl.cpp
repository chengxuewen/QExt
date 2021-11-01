#include "qtkobjectclassdefinitionimpl_p.h"
#include "qtkattributedefinitionimpl_p.h"

#include <QTKPluginFramework/QTKPlugin>
#include <QTKPluginFramework/QTKPluginConstants>

const int QTKObjectClassDefinitionImpl::PID = 0;
const int QTKObjectClassDefinitionImpl::FPID = 1;
const QChar QTKObjectClassDefinitionImpl::LOCALE_SEP = '_';

QTKObjectClassDefinitionImpl::QTKObjectClassDefinitionImpl(const QString& name, const QString& description,
                                                           const QString& id, const QString& localization,
                                                           const QString& context, int type)
    : _name(name), _id(id), _description(description), _locElem(localization, context), _type(type)
{
}

QTKObjectClassDefinitionImpl::QTKObjectClassDefinitionImpl(const QTKObjectClassDefinitionImpl& other)
    : _name(other._name), _id(other._id), _description(other._description),
      _locElem(other._locElem), _type(other._type), _icon(other._icon)
{
    for (int i = 0; i < _required.size(); i++)
    {
        QTKAttributeDefinitionImplPtr ad(new QTKAttributeDefinitionImpl(*_required.value(i).data()));
        this->addAttributeDefinition(ad, true);
    }
    for (int i = 0; i < _optional.size(); i++)
    {
        QTKAttributeDefinitionImplPtr ad(new QTKAttributeDefinitionImpl(*_optional.value(i).data()));
        this->addAttributeDefinition(ad, false);
    }
}

QString QTKObjectClassDefinitionImpl::getName() const
{
    return _locElem.getLocalized(_name);
}

void QTKObjectClassDefinitionImpl::setName(const QString& name)
{
    _name = name;
}

QString QTKObjectClassDefinitionImpl::getID() const
{
    return _id;
}

QString QTKObjectClassDefinitionImpl::getDescription() const
{
    return _locElem.getLocalized(_description);
}

void QTKObjectClassDefinitionImpl::setDescription(const QString& description)
{
    _description = description;
}

QList<QTKAttributeDefinitionPtr> QTKObjectClassDefinitionImpl::getAttributeDefinitions(Filter filter)
{
    QList<QTKAttributeDefinitionPtr> atts;
    switch (filter)
    {
    case REQUIRED:
    {
        foreach(QTKAttributeDefinitionImplPtr impl, _required)
        {
            atts.push_back(impl);
        }
        return atts;
    }
    case OPTIONAL:
    {
        foreach(QTKAttributeDefinitionImplPtr impl, _optional)
        {
            atts.push_back(impl);
        }
        return atts;
    }
    case ALL:
    default :
    {
        foreach(QTKAttributeDefinitionImplPtr impl, _required)
        {
            atts.push_back(impl);
        }
        foreach(QTKAttributeDefinitionImplPtr impl, _optional)
        {
            atts.push_back(impl);
        }
        return atts;
    }
    }
}

void QTKObjectClassDefinitionImpl::addAttributeDefinition(const QTKAttributeDefinitionImplPtr& ad, bool isRequired)
{
    if (isRequired)
    {
        _required.push_back(ad);
    }
    else
    {
        _optional.push_back(ad);
    }
}

QByteArray QTKObjectClassDefinitionImpl::getIcon(int sizeHint) const
{
    if (!_icon || _icon.getIconSize() != sizeHint)
    {
        return QByteArray();
    }
    QSharedPointer<QTKPlugin> p = _icon.getIconPlugin();
    return p->getResource(_locElem.getLocalized(_icon.getIconName()));
}

void QTKObjectClassDefinitionImpl::setIcon(const QTKMTIcon& icon)
{
    _icon = icon;
}

int QTKObjectClassDefinitionImpl::getType() const
{
    return _type;
}

void QTKObjectClassDefinitionImpl::setType(int type)
{
    _type = type;
}

void QTKObjectClassDefinitionImpl::setPluginLocalization(const QLocale& assignedLocale, const QSharedPointer<QTKPlugin>& plugin)
{
    QTKPluginLocalization pluginLoc = plugin->getPluginLocalization(assignedLocale, _locElem.getLocalizationBase());
    _locElem.setPluginLocalization(pluginLoc);

    foreach(QTKAttributeDefinitionImplPtr impl, _required)
    {
        impl->setPluginLocalization(pluginLoc);
    }

    foreach(QTKAttributeDefinitionImplPtr impl, _optional)
    {
        impl->setPluginLocalization(pluginLoc);
    }
}

QString QTKObjectClassDefinitionImpl::getLocalization() const
{
    return _locElem.getLocalizationBase();
}

