#ifndef QTKOBJECTCLASSDEFINITIONIMPL_P_H
#define QTKOBJECTCLASSDEFINITIONIMPL_P_H

#include "qtkmticon_p.h"
#include "qtkmtlocalizationelement_p.h"

#include <QTKPluginFramework/Service/Metatype/QTKObjectClassDefinition>
#include <QTKPluginFramework/QTKPluginLocalization>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKAttributeDefinitionImpl;

/**
 * Implementation of ObjectClassDefinition
 */
class QTKObjectClassDefinitionImpl : public QTKObjectClassDefinition
{
private:
    static const QChar LOCALE_SEP; // = '_'

    QString _name;
    QString _id;
    QString _description;

    QTKMTLocalizationElement _locElem;

    int _type;
    QList<QSharedPointer<QTKAttributeDefinitionImpl> > _required;
    QList<QSharedPointer<QTKAttributeDefinitionImpl> > _optional;
    QTKMTIcon _icon;

public:

    static const int PID; // = 0
    static const int FPID; // = 1

    /*
   * Constructor of class QTKObjectClassDefinitionImpl.
   */
    QTKObjectClassDefinitionImpl(const QString& name, const QString& description,
                                 const QString& id, const QString& localization,
                                 const QString& context, int type = 0);

    QTKObjectClassDefinitionImpl(const QTKObjectClassDefinitionImpl& other);

    /*
   * @see QTKObjectClassDefinition#getName()
   */
    QString getName() const;

    /**
   * Method to set the name of QTKObjectClassDefinition.
  */
    void setName(const QString& name);

    /*
   * @see QTKObjectClassDefinition#getID()
   */
    QString getID() const;

    /*
   * @see QTKObjectClassDefinition#getDescription()
   */
    QString getDescription() const;

    /*
   * Method to set the description of QTKObjectClassDefinition.
  */
    void setDescription(const QString& description);

    /*
  * @see QTKObjectClassDefinition#getAttributeDefinitions(Filter)
  */
    QList<QTKAttributeDefinitionPtr> getAttributeDefinitions(Filter filter);

    /*
   * Method to add one new AD to QTKObjectClassDefinition.
   */
    void addAttributeDefinition(const QSharedPointer<QTKAttributeDefinitionImpl>& ad,
                                bool isRequired);

    /*
   * @see QTKObjectClassDefinition#getIcon(int)
   */
    QByteArray getIcon(int sizeHint) const;

    /**
   * Method to set the icon of QTKObjectClassDefinition.
  */
    void setIcon(const QTKMTIcon& icon);

    /**
   * Method to get the type of QTKObjectClassDefinition.
  */
    int getType() const;

    /**
   * Method to set the type of QTKObjectClassDefinition.
   */
    void setType(int type);

    /**
   * Method to set the plugin localization object for this OCD and all its ADs.
   */
    void setPluginLocalization(const QLocale& assignedLocale, const QSharedPointer<QTKPlugin>& plugin);

    QString getLocalization() const;

};

typedef QSharedPointer<QTKObjectClassDefinitionImpl> QTKObjectClassDefinitionImplPtr;

#endif // QTKOBJECTCLASSDEFINITIONIMPL_P_H
