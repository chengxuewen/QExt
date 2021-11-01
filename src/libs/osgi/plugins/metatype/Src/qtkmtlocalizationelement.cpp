#include "qtkmtlocalizationelement_p.h"

QTKMTLocalizationElement::QTKMTLocalizationElement(const QString& localization,
                                                   const QString& context)
    : _localization(localization), _context(context)
{

}

void QTKMTLocalizationElement::setPluginLocalization(const QTKPluginLocalization& pl)
{
    _pl = pl;
}

QString QTKMTLocalizationElement::getLocalized(const QString& key) const
{
    if (key.isEmpty())
    {
        return key;
    }

    QString localized = _pl.getLocalized(_context, key);
    if (localized.isEmpty())
    {
        // If no localization file available or no localized value found
        // for the key, then return the raw data
        return key;
    }

    return localized;
}

QString QTKMTLocalizationElement::getLocalizationBase() const
{
    return _localization;
}
