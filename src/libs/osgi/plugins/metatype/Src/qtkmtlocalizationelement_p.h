#ifndef QTKMTLOCALIZATIONELEMENT_P_H
#define QTKMTLOCALIZATIONELEMENT_P_H

#include <QTKPluginFramework/QTKPluginLocalization>

#include <QLocale>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKMTLocalizationElement
{
    const QString _localization;
    const QString _context;
    QTKPluginLocalization _pl;

public:
    QTKMTLocalizationElement(const QString& localization, const QString& context);

    /**
   * Internal method
   */
    void setPluginLocalization(const QTKPluginLocalization& pl);

    /**
   * Method to get the localized text of inputed String.
   */
    QString getLocalized(const QString& key) const;

    QString getLocalizationBase() const;
};

#endif // QTKMTLOCALIZATIONELEMENT_P_H
