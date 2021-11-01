#ifndef QTKMTICON_P_H
#define QTKMTICON_P_H

#include <QTKPluginFramework/QTKPlugin>

#include <QString>
#include <QSharedPointer>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

/**
 * Represents an Icon with a name and a size
 */
class QTKMTIcon
{

private:

    QString _fileName;
    int _size;
    QSharedPointer<QTKPlugin> _plugin;

public:

    QTKMTIcon();

    /**
   * Constructor of class QTKMTIcon.
   */
    QTKMTIcon(const QString& fileName, int size, const QSharedPointer<QTKPlugin>& plugin);

    /**
   * Constructor of class QTKMTIcon.
   */
    QTKMTIcon(const QString& fileName, const QSharedPointer<QTKPlugin>& plugin);

    /**
   * Method to get the icon's file name.
   */
    QString getIconName() const;

    /**
   * returns the size specified when the icon was created
   *
   * @return size or -1 if no size was specified
   */
    int getIconSize() const;

    /**
   * Method to get the plugin having this Icon.
   */
    QSharedPointer<QTKPlugin> getIconPlugin() const;

    operator bool () const;
};

#endif // QTKMTICON_P_H
