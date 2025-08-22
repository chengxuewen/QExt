#include <rpLanguageManager.h>
#include <rpConstants.h>

#include <QStandardPaths>
#include <QApplication>
#include <QMutexLocker>
#include <QTranslator>
#include <QFileInfo>
#include <QFileInfo>
#include <QPointer>
#include <QMutex>
#include <QDebug>
#include <QList>
#include <QPair>
#include <QMap>
#include <QDir>

class RPLanguageManagerPrivate
{
public:
    explicit RPLanguageManagerPrivate(RPLanguageManager *q);
    virtual ~RPLanguageManagerPrivate();

    RPLanguageManager * const q_ptr;

    QMap<QString, QTranslator *> m_nameToTranslatorMap;
    QPointer<QTranslator> m_currentTranslator;
    QString m_currentLanguage;
    const QString m_translationsPath;

private:
    Q_DISABLE_COPY(RPLanguageManagerPrivate)
    Q_DECLARE_PUBLIC(RPLanguageManager)
};

RPLanguageManagerPrivate::RPLanguageManagerPrivate(RPLanguageManager *q)
    : q_ptr(q)
    , m_currentLanguage("Eng")
    , m_translationsPath(QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/translations")
{
    QDir dir(m_translationsPath);
    if (!dir.exists())
    {
        if (!dir.mkpath(m_translationsPath))
        {
            qCritical() << QString("RPLanguageManagerPrivate::RPLanguageManagerPrivate():mkpath %1 failed!").
                           arg(m_translationsPath);
        }
    }
}

RPLanguageManagerPrivate::~RPLanguageManagerPrivate()
{

}

RPLanguageManager::RPLanguageManager(QObject *parent)
    : QObject(parent)
    , dd_ptr(new RPLanguageManagerPrivate(this))
{
    this->refreshLanguages();
}

RPLanguageManager::~RPLanguageManager()
{

}

void RPLanguageManager::refreshLanguages()
{
    Q_D(RPLanguageManager);
    QString qmDir = d->m_translationsPath;
    QDir dir(qmDir);
    if (dir.exists())
    {
        auto fileInfos = dir.entryInfoList(QStringList("RecordPlayer_*.qm"), QDir::Files | QDir::NoSymLinks);
        for (auto &&fileInfo : fileInfos)
        {
            QString filePath = fileInfo.filePath();
            QString refName = filePath.mid(filePath.lastIndexOf("_") + 1);
            refName = refName.left(refName.lastIndexOf("."));
            QTranslator *translator = d->m_nameToTranslatorMap.value(refName, nullptr);
            if (nullptr == translator)
            {
                translator = new QTranslator(this);
            }
            if (translator->load(filePath))
            {
                d->m_nameToTranslatorMap.insert(refName, translator);
            }
            else
            {
                qCritical() << QString("RPLanguageManager::refreshLanguages():load translation qm file %1 failed!").
                               arg(filePath);
                continue;
            }
        }
    }
}

QStringList RPLanguageManager::languageList() const
{
    Q_D(const RPLanguageManager);
    QStringList list;
    list.append("Eng");
    list.append(d->m_nameToTranslatorMap.keys());
    return list;
}

QString RPLanguageManager::currentLanguage() const
{
    Q_D(const RPLanguageManager);
    return d->m_currentLanguage;
}

bool RPLanguageManager::setCurrentLanguage(const QString &language)
{
    Q_D(RPLanguageManager);
    if ("Eng" != language)
    {
        if (d->m_nameToTranslatorMap.contains(language))
        {
            QTranslator *translator = d->m_nameToTranslatorMap.value(language);
            d->m_currentLanguage = language;
            if (translator) {
                QCoreApplication::removeTranslator(d->m_currentTranslator.data());
                QCoreApplication::installTranslator(translator);
                d->m_currentTranslator = translator;
                emit this->languageChanged();
                return true;
            }
        }
        return false;
    }
    d->m_currentLanguage = "Eng";
    QCoreApplication::removeTranslator(d->m_currentTranslator.data());
    d->m_currentTranslator.clear();
    return true;
}

QString RPLanguageManager::translationsPath() const
{
    Q_D(const RPLanguageManager);
    return d->m_translationsPath;
}

void RPLanguageManager::loadSettings(QSettings *settings)
{
    settings->beginGroup(RPConstants::SETTINGS_GROUP_LANGUAGES);
    auto language = settings->value(RPConstants::SETTINGS_KEY_LANGUAGETYPE, "Eng").toString();
    this->setCurrentLanguage(language);
    settings->endGroup();
}

void RPLanguageManager::saveSettings(QSettings *settings)
{
    Q_D(RPLanguageManager);
    settings->beginGroup(RPConstants::SETTINGS_GROUP_LANGUAGES);
    settings->setValue(RPConstants::SETTINGS_KEY_LANGUAGETYPE, d->m_currentLanguage);
    settings->endGroup();
}
