#include <rpApp.h>
#include <rpLogger.h>
#include <rpConfig.h>
#include <rpSettings.h>
#include <rpConstants.h>
#include <rpMainWindow.h>
#include <rpLanguageManager.h>
#include <rpKeyboardManager.h>

#include <qextOnceFlag.h>
#include <qextMessageBox.h>
#include <qextStyleThemes.h>
#include <qextPlotManager.h>
#include <qextBreakpadHandler.h>
#include <qextDAIODeviceManager.h>

#include <QMutex>
#include <QThread>
#include <QPointer>
#include <QMutexLocker>
#include <QCoreApplication>

namespace internal
{
QEXT_STATIC_CONSTANT_NUMBER(kSettingsVersionMajor, 0)
QEXT_STATIC_CONSTANT_NUMBER(kSettingsVersionMinor, 1)
}

class RPAppPrivate
{
public:
    explicit RPAppPrivate(RPApp *q);
    virtual ~RPAppPrivate();

    void initSingletonHandler();
    void setImportProfileFlag();

    void saveSettings();
    void loadSettings();

    RPApp *const q_ptr;

    QPointer<QExtDAIODeviceManager> mDAIODeviceManager;
    QPointer<RPLanguageManager> mLanguageManager;
    QPointer<RPKeyboardManager> mKeyboardManager;
    QPointer<QExtPlotManager> mPlotManager;
    QPointer<RPSettings> mSettings;
    QScopedPointer<RPMainWindow> mMainWindow;
    bool mImportProfile;

private:
    Q_DISABLE_COPY(RPAppPrivate)
    Q_DECLARE_PUBLIC(RPApp)
};

RPAppPrivate::RPAppPrivate(RPApp *q)
    : q_ptr(q)
    , mImportProfile(false)
{
}

RPAppPrivate::~RPAppPrivate()
{
    mMainWindow.reset();
    mDAIODeviceManager->destroy();
    mLanguageManager->destroy();
    mKeyboardManager->destroy();
    mPlotManager->destroy();
    mSettings->destroy();
}

void RPAppPrivate::initSingletonHandler()
{
    Q_Q(RPApp);
    mDAIODeviceManager = QExtDAIODeviceManager::instance();
    mLanguageManager = RPLanguageManager::instance();
    mKeyboardManager = RPKeyboardManager::instance();
    mPlotManager = QExtPlotManager::instance();
    mSettings = RPSettings::instance();
    QObject::connect(mSettings.data(), &RPSettings::requestUpdateSettings, q_ptr, [=]()
                     {
                         this->saveSettings();
                     });

    qextStyleThemes->bindStyleSheet(qApp);
    qextBreakpadHandler->setReporterStyleTheme(qextStyleThemes->currentStyleTheme());
    QObject::connect(qextStyleThemes, &QExtStyleThemes::currentThemeChanged, q, [=](const QString &/*theme*/)
                     {
                         qextBreakpadHandler->setReporterStyleTheme(qextStyleThemes->currentStyleTheme());
                     });
    QExtMessageBox::setCustomIcon(QExtMessageBox::Information,
                                  qextStyleThemes->loadThemeAwareSvgIcon(":/images/mark_infomation.svg"));
    QExtMessageBox::setCustomIcon(QExtMessageBox::Question,
                                  qextStyleThemes->loadThemeAwareSvgIcon(":/images/mark_question.svg", "success"));
    QExtMessageBox::setCustomIcon(QExtMessageBox::Warning,
                                  qextStyleThemes->loadThemeAwareSvgIcon(":/images/mark_warning.svg", "warning"));
    QExtMessageBox::setCustomIcon(QExtMessageBox::Critical,
                                  qextStyleThemes->loadThemeAwareSvgIcon(":/images/mark_warning.svg", "danger"));
}

void RPAppPrivate::setImportProfileFlag()
{
    mImportProfile = true;
}

void RPAppPrivate::saveSettings()
{
    QExtSerializable::SerializedItemsMap items;
    items[RPConstants::SETTINGS_GROUP_PLOTS] = mPlotManager->serializeSave();
    items[RPConstants::SETTINGS_GROUP_THEMES] = qextStyleThemes->serializeSave();
    items[RPConstants::SETTINGS_GROUP_MAINWINDOW] = mMainWindow->serializeSave();
    items[RPConstants::SETTINGS_GROUP_IODEVICE] = mDAIODeviceManager->serializeSave();
    mSettings->setVersion(internal::kSettingsVersionMajor,
                          internal::kSettingsVersionMinor);
    mSettings->saveFile(items);
}

void RPAppPrivate::loadSettings()
{
    const auto items = mSettings->loadFile();
    const auto settingsVersionMajor = mSettings->versionMajor();
    const auto settingsVersionMinor = mSettings->versionMinor();
    const auto settingsVersionString = mSettings->versionString();
    if (settingsVersionMajor != internal::kSettingsVersionMajor)
    {
        QExtMessageBox::warning(mMainWindow.data(), QObject::tr("Load profile"),
                                QObject::tr("The profile version %1 does not match the software version %2.%3,"
                                            "Skip the profile to preventing software configuration errors!").
                                arg(settingsVersionString).
                                arg(internal::kSettingsVersionMajor).
                                arg(internal::kSettingsVersionMinor),
                                QMessageBox::Ok);
        return;
    }
    mDAIODeviceManager->serializeLoad(items.value(RPConstants::SETTINGS_GROUP_IODEVICE).toMap());
    qextStyleThemes->serializeLoad(items.value(RPConstants::SETTINGS_GROUP_THEMES).toMap());
    mPlotManager->serializeLoad(items.value(RPConstants::SETTINGS_GROUP_PLOTS).toMap());

    mMainWindow.reset(new RPMainWindow);
    mMainWindow->serializeLoad(items.value(RPConstants::SETTINGS_GROUP_MAINWINDOW).toMap());
    mMainWindow->show();
}


RPApp::~RPApp()
{
}

RPApp *RPApp::instance()
{
    static QExtOnceFlag onceFlag;
    static RPApp *instance = nullptr;
    qextCallOnce(onceFlag, [=](){ instance = new RPApp; });
    return instance;
}

QMainWindow *RPApp::mainwindow() const
{
    Q_D(const RPApp);
    return d->mMainWindow.data();
}

void RPApp::raiseMainWindow()
{
    dd_ptr->mMainWindow->raise();
}

RPApp::RPApp(QObject *parent)
    : QObject(parent)
    , dd_ptr(new RPAppPrivate(this))
{
}

bool RPApp::startApp()
{
    Q_D(RPApp);
    static QExtOnceFlag initFlag;
    if (initFlag.enter())
    {
        d->initSingletonHandler();
        d->loadSettings();
        initFlag.leave();
        return true;
    }
    return false;
}

bool RPApp::quit()
{
    Q_D(RPApp);
    static QExtOnceFlag quitFlag;
    if (quitFlag.enter())
    {
        if (!d->mImportProfile)
        {
            d->saveSettings();
        }
        d->mDAIODeviceManager->clearAllIODevices();
        RPLogger::quitThread();
        this->deleteLater();
        quitFlag.leave();
        return true;
    }
    return false;
}

void RPApp::setImportProfileFlag()
{
    Q_D(RPApp);
    d->setImportProfileFlag();
}

void RPApp::saveSettings()
{
    Q_D(RPApp);
    d->saveSettings();
}
