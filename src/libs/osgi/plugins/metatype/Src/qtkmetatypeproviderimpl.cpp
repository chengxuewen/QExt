#include "qtkmetatypeproviderimpl_p.h"
#include "qtkobjectclassdefinitionimpl_p.h"
#include "qtkattributedefinitionimpl_p.h"
#include "qtkmtmsg_p.h"
#include "qtkmtdataparser_p.h"

#include <QTKPluginFramework/QTKPluginConstants>
#include <QTKPluginFramework/Service/Log/QTKLogService>
#include <QTKPluginFramework/Service/Metatype/QTKMetaTypeService>
#include <QTKCore/QTKException>

#include <QCoreApplication>
#include <QStringList>
#include <QBuffer>

QTK_CORE_USE_NAMESPACE

const QString QTKMetaTypeProviderImpl::METADATA_NOT_FOUND = "METADATA_NOT_FOUND";
const QString QTKMetaTypeProviderImpl::OCD_ID_NOT_FOUND = "OCD_ID_NOT_FOUND";
const QString QTKMetaTypeProviderImpl::ASK_INVALID_LOCALE = "ASK_INVALID_LOCALE";

const QString QTKMetaTypeProviderImpl::META_FILE_EXT = ".XML";
const QString QTKMetaTypeProviderImpl::RESOURCE_FILE_CONN = "_";
const QString QTKMetaTypeProviderImpl::RESOURCE_FILE_EXT = ".qm";
const QChar QTKMetaTypeProviderImpl::DIRECTORY_SEP = '/';


QTKMetaTypeProviderImpl::QTKMetaTypeProviderImpl(const QSharedPointer<QTKPlugin>& plugin, QTKLogService* logger)
    : m__pPlugin(plugin), m_pLogger(logger), _isThereMeta(false)
{
    // read all plugin's metadata files and build internal data structures
    _isThereMeta = readMetaFiles(plugin);

    if (!_isThereMeta)
    {
        QTK_DEBUG(logger) << QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::METADATA_NOT_FOUND)
                             .arg(plugin->getPluginId()).arg(plugin->getSymbolicName());
    }
}

QTKObjectClassDefinitionPtr QTKMetaTypeProviderImpl::getObjectClassDefinition(
        const QString& pid, const QLocale& locale)
{
    QTKObjectClassDefinitionImplPtr ocd;
    if (m__mapAllPidOCDs.contains(pid))
    {
        ocd = QTKObjectClassDefinitionImplPtr(new QTKObjectClassDefinitionImpl(*m__mapAllPidOCDs.value(pid).data()));
        ocd->setPluginLocalization(locale, m__pPlugin);
        return ocd;
    }
    else if (m_map_AllFPidOCDs.contains(pid))
    {
        ocd = QTKObjectClassDefinitionImplPtr(new QTKObjectClassDefinitionImpl(*m_map_AllFPidOCDs.value(pid).data()));
        ocd->setPluginLocalization(locale, m__pPlugin);
        return ocd;
    }
    else
    {
        QString msg = QCoreApplication::translate(QTKMTMsg::CONTEXT, QTKMTMsg::OCD_ID_NOT_FOUND).arg(pid);
        throw QTKInvalidArgumentException(msg);
    }
}

QList<QLocale> QTKMetaTypeProviderImpl::getLocales() const
{
    if (!_locales.isEmpty())
        return checkForDefault(_locales);

    QStringList localizationFiles;
    // get all the localization resources for PIDS
    foreach(QTKObjectClassDefinitionImplPtr ocd, m__mapAllPidOCDs)
    {
        QString loc = ocd->getLocalization();
        if (!loc.isEmpty() && !localizationFiles.contains(loc))
        {
            localizationFiles << loc;
        }
    }
    // get all the localization resources for FPIDS
    foreach(QTKObjectClassDefinitionImplPtr ocd, m_map_AllFPidOCDs)
    {
        QString loc = ocd->getLocalization();
        if (!loc.isEmpty() && !localizationFiles.contains(loc))
        {
            localizationFiles << loc;
        }
    }

    if (localizationFiles.isEmpty())
    {
        localizationFiles << QTKPluginConstants::PLUGIN_LOCALIZATION_DEFAULT_BASENAME;
    }

    QList<QLocale> locales;
    foreach (QString localizationFile, localizationFiles)
    {
        int iSlash = localizationFile.lastIndexOf(DIRECTORY_SEP);
        QString baseDir;
        QString baseFileName;
        if (iSlash < 0)
        {
            baseDir = "";
        }
        else
        {
            baseDir = localizationFile.left(iSlash);
        }
        baseFileName = localizationFile + RESOURCE_FILE_CONN;
        QStringList resources = m__pPlugin->getResourceList(baseDir);
        foreach(QString resourceName, resources)
        {
            QString resource = baseDir + DIRECTORY_SEP + resourceName;
            if (resource.startsWith(baseFileName) && resource.toLower().endsWith(RESOURCE_FILE_EXT))
            {
                QString localeName = resource.mid(baseFileName.size(), resource.size() - baseFileName.size() - RESOURCE_FILE_EXT.length());
                locales.push_back(QLocale(localeName));
            }
        }
    }
    _locales = locales;
    return checkForDefault(_locales);
}

bool QTKMetaTypeProviderImpl::readMetaFiles(const QSharedPointer<QTKPlugin>& plugin)
{
    bool isThereMetaHere = false;

    QStringList allFileKeys = plugin->getResourceList(QTKMetaTypeService::METATYPE_DOCUMENTS_LOCATION);
    if (allFileKeys.isEmpty())
        return isThereMetaHere;

    foreach (QString fileName, allFileKeys)
    {
        bool _isMetaDataFile = false;

        QHash<QString, QTKObjectClassDefinitionImplPtr> pidToOCD;
        QByteArray resourceContent = plugin->getResource(QLatin1String(QTKMetaTypeService::METATYPE_DOCUMENTS_LOCATION) + "/" + fileName);
        if (!resourceContent.isEmpty())
        {
            QBuffer metaData(&resourceContent);
            try
            {
                // Assume all XML files are what we want by default.
                _isMetaDataFile = true;
                metaData.open(QIODevice::ReadOnly);
                QTKMTDataParser parser(plugin, &metaData, m_pLogger);
                pidToOCD = parser.doParse();
                if (pidToOCD.isEmpty())
                {
                    _isMetaDataFile = false;
                }
            }
            catch (const std::exception& )
            {
                // Ok, looks like it is not what we want.
                _isMetaDataFile = false;
            }

            if (_isMetaDataFile && !pidToOCD.isEmpty())
            {
                // We got some OCDs now.
                QHash<QString, QTKObjectClassDefinitionImplPtr>::ConstIterator end(pidToOCD.end());
                for (QHash<QString, QTKObjectClassDefinitionImplPtr>::ConstIterator it(pidToOCD.begin()); it != end; ++it)
                {
                    QString pid = it.key();
                    QTKObjectClassDefinitionImplPtr ocd = it.value();
                    if (ocd->getType() == QTKObjectClassDefinitionImpl::PID)
                    {
                        isThereMetaHere = true;
                        m__mapAllPidOCDs.insert(pid, ocd);
                    }
                    else
                    {
                        isThereMetaHere = true;
                        m_map_AllFPidOCDs.insert(pid, ocd);
                    }
                } // End of for
            }
        } // End of if(!resourceContent.isEmpty())
    } // End of foreach

    return isThereMetaHere;
}

QList<QLocale> QTKMetaTypeProviderImpl::checkForDefault(const QList<QLocale>& locales) const
{
    if (locales.isEmpty() || (locales.size() == 1 && QLocale() == locales[0]))
        return QList<QLocale>();
    return locales;
}
