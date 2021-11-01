#include "qtkpluginbrowser.h"
#include "ui_qtkpluginbrowsermainwindow.h"
#include "qtkplugintablemodel.h"
#include "qtkpluginresourcestreemodel.h"
#include "qtkqtresourcestreemodel.h"
#include "qtklog4qteventhandler.h"

#include <qtkinfo.h>
#include <QTKPluginFramework/QTKServiceReference>
#include <QTKPluginFramework/QTKServiceException>
#include <QTKPluginFramework/QTKPluginConstants>
#include <QTKPluginFramework/QTKPluginException>
#include <QTKPluginFramework/QTKPluginFramework>
#include <QTKPluginFramework/QTKPluginContext>
#include <QTKPluginFramework/Service/Event/QTKEventConstants>

#include <QApplication>
#include <QMainWindow>
#include <QStringList>
#include <QDirIterator>
#include <QUrl>
#include <QSettings>
#include <QCloseEvent>
#include <QMetaEnum>

#define SETTINGS_WND_GEOM "mainwindow.geom"
#define SETTINGS_WND_STATE "mainwindow.state"

QTKPluginBrowser::QTKPluginBrowser(QTKPluginFramework* pPluginFramework)
    : m_pPluginFramework(pPluginFramework),
      m_pLogQt4EventHandler(nullptr)
{
    ui.setupUi(this);
    m_mapPluginEventTypeToString[QTKPluginEvent::Type_Installed] = "Installed";
    m_mapPluginEventTypeToString[QTKPluginEvent::Type_LazyActivation] = "Lazy Activation";
    m_mapPluginEventTypeToString[QTKPluginEvent::Type_Resolved] = "Resolved";
    m_mapPluginEventTypeToString[QTKPluginEvent::Type_Started] = "Started";
    m_mapPluginEventTypeToString[QTKPluginEvent::Type_Starting] = "Starting";
    m_mapPluginEventTypeToString[QTKPluginEvent::Type_Stopped] = "Stopped";
    m_mapPluginEventTypeToString[QTKPluginEvent::Type_Stopping] = "Stopping";
    m_mapPluginEventTypeToString[QTKPluginEvent::Type_Uninstalled] = "Uninstalled";
    m_mapPluginEventTypeToString[QTKPluginEvent::Type_Unresolved] = "Unresolved";
    m_mapPluginEventTypeToString[QTKPluginEvent::Type_Updated] = "Updated";

    pPluginFramework->getPluginContext()->connectFrameworkListener(this, SLOT(frameworkEvent(QTKPluginFrameworkEvent)));
    pPluginFramework->getPluginContext()->connectPluginListener(this, SLOT(pluginEvent(QTKPluginEvent)));
    pPluginFramework->getPluginContext()->connectServiceListener(this, "serviceEvent");

    QStringList pluginDirs;
    pluginDirs << QTK_PLUGIN_DIR;

    QStringListIterator dirIt(pluginDirs);
    while (dirIt.hasNext()) {
        QApplication::addLibraryPath(dirIt.next());
    }

    QStringList listLibFilter;
    listLibFilter << "*.dll" << "*.so" << "*.dylib";
    QDirIterator dirIter(pluginDirs.at(0), listLibFilter, QDir::Files);
    while(dirIter.hasNext()) {
        try {
            QSharedPointer<QTKPlugin> pPlugin = pPluginFramework->getPluginContext()->installPlugin(QUrl::fromLocalFile(dirIter.next()).toString());
            pPlugin->start(QTKPlugin::StartOption_StartActivationPolicy);
        } catch (const QTKPluginException &e) {
            qCritical() << e.printStackTrace();
        }
    }

    pPluginFramework->start();

    this->tabifyDockWidget(ui.qtResourcesDockWidget, ui.pluginResourcesDockWidget);

    m_pEditors = new QTKPluginBrowserEditors(ui.centralwidget);

    QAbstractItemModel *pPluginTableModel = new QTKPluginTableModel(pPluginFramework->getPluginContext(), this);
    ui.pluginsTableView->setModel(pPluginTableModel);

    QAbstractItemModel *pQtResourcesTreeModel = new QTKQtResourcesTreeModel(this);
    ui.qtResourcesTreeView->setModel(pQtResourcesTreeModel);

    connect(ui.pluginsTableView, SIGNAL(clicked(QModelIndex)), this, SLOT(pluginSelected(QModelIndex)));
    connect(ui.pluginsTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(pluginDoubleClicked(QModelIndex)));
    connect(ui.pluginResourcesTreeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(dbResourceDoubleClicked(QModelIndex)));
    connect(ui.qtResourcesTreeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(qtResourceDoubleClicked(QModelIndex)));

    m_pStartPluginNowAction = new QAction(QIcon(":/pluginbrowser/Images/run-now.png"), "Start Plugin (ignore activation policy)", this);
    m_pStartPluginAction = new QAction(QIcon(":/pluginbrowser/Images/run.png"), "Start Plugin", this);
    m_pStopPluginAction = new QAction(QIcon(":/pluginbrowser/Images/stop.png"), "Stop Plugin", this);

    connect(m_pStartPluginNowAction, SIGNAL(triggered()), this, SLOT(startPluginNow()));
    connect(m_pStartPluginAction, SIGNAL(triggered()), this, SLOT(startPlugin()));
    connect(m_pStopPluginAction, SIGNAL(triggered()), this, SLOT(stopPlugin()));

    m_pStartPluginNowAction->setEnabled(false);
    m_pStartPluginAction->setEnabled(false);
    m_pStopPluginAction->setEnabled(false);

    ui.pluginToolBar->addAction(m_pStartPluginNowAction);
    ui.pluginToolBar->addAction(m_pStartPluginAction);
    ui.pluginToolBar->addAction(m_pStopPluginAction);

    QSettings settings;
    if(settings.contains(SETTINGS_WND_GEOM)) {
        this->restoreGeometry(settings.value(SETTINGS_WND_GEOM).toByteArray());
    }
    if (settings.contains(SETTINGS_WND_STATE)) {
        this->restoreState(settings.value(SETTINGS_WND_STATE).toByteArray());
    }

    m_pLogQt4EventHandler = new QTKLog4QtEventHandler(this);
    QTKDictionary propertys;
    propertys[QTKEventConstants::EVENT_TOPICS] = "org/qtk/log4Qt/message";
    pPluginFramework->getPluginContext()->registerService<QTKEventHandler>(m_pLogQt4EventHandler, propertys);
    connect(m_pLogQt4EventHandler, SIGNAL(newLog4QtMessage(const QString &)), this, SLOT(appendLog4QtMessage(const QString &)));
}

void QTKPluginBrowser::pluginSelected(const QModelIndex &index)
{
    QVariant value = index.data(Qt::UserRole);

    QSharedPointer<QTKPlugin> pPlugin = m_pPluginFramework->getPluginContext()->getPlugin(value.toLongLong());
    if (!pPlugin) {
        return;
    }
    this->updatePluginToolbar(pPlugin);

    QAbstractItemModel *pOldModel = ui.pluginResourcesTreeView->model();
    ui.pluginResourcesTreeView->setModel(new QTKPluginResourcesTreeModel(pPlugin, this));
    if (pOldModel) {
        pOldModel->deleteLater();;
    }
}

void QTKPluginBrowser::updatePluginToolbar(QSharedPointer<QTKPlugin> pPlugin)
{
    m_pStartPluginNowAction->setEnabled(false);
    m_pStartPluginAction->setEnabled(false);
    m_pStopPluginAction->setEnabled(false);

    if (!pPlugin) {
        return;
    }

    const QTKPlugin::States startStates = QTKPlugin::State_Installed | QTKPlugin::State_Resolved | QTKPlugin::State_Stopping;
    const QTKPlugin::States stopStates = QTKPlugin::State_Starting | QTKPlugin::State_Active;
    if (startStates.testFlag(pPlugin->getState())) {
        m_pStartPluginNowAction->setEnabled(true);
        m_pStartPluginAction->setEnabled(true);
    }

    if (stopStates.testFlag(pPlugin->getState())) {
        m_pStopPluginAction->setEnabled(true);
    }
}

void QTKPluginBrowser::pluginDoubleClicked(const QModelIndex &index)
{
    long lPluginId = index.data(Qt::UserRole).toLongLong();
    QSharedPointer<QTKPlugin> pPlugin = m_pPluginFramework->getPluginContext()->getPlugin(lPluginId);

    QByteArray mfContent = pPlugin->getResource("/META-INF/MANIFEST.MF");
    QString strLocation = QString("/") + pPlugin->getSymbolicName() + "/META-INF/MANIFEST.MF";
    m_pEditors->openEditor(strLocation, mfContent, strLocation + " [cached]");

    QList<QTKServiceReference> listServiceRefs = pPlugin->getPluginContext()->getServiceReferences("");
    QListIterator<QTKServiceReference> iter(listServiceRefs);
    while (iter.hasNext()) {
        QTKServiceReference ref(iter.next());
        qDebug() << "QTKPluginBrowser::pluginDoubleClicked():Service from" << ref.getPlugin()->getSymbolicName() << ":" << ref.getPropertyKeys();
        qDebug() << "QTKPluginBrowser::pluginDoubleClicked():Object Classes:" << ref.getProperty(QTKPluginConstants::OBJECT_CLASS).toStringList();
    }
}

void QTKPluginBrowser::qtResourceDoubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index)
}

void QTKPluginBrowser::dbResourceDoubleClicked(const QModelIndex &index)
{
    QString strResPath = index.data(Qt::UserRole).toString();
    if (strResPath.isEmpty() || strResPath.endsWith('/')) {
        return;
    }

    qDebug() << "QTKPluginBrowser::dbResourceDoubleClicked():Trying to open: " << strResPath;

    QModelIndex pluginIndex = ui.pluginsTableView->selectionModel()->selectedIndexes().first();
    long lPluginId = pluginIndex.data(Qt::UserRole).toLongLong();

    QSharedPointer<QTKPlugin> pPlugin = m_pPluginFramework->getPluginContext()->getPlugin(lPluginId);

    QByteArray resContent = pPlugin->getResource(strResPath);
    QString strLocation = QString("/") + pPlugin->getSymbolicName() + strResPath;
    m_pEditors->openEditor(strLocation, resContent, strLocation + " [cached]");
}

void QTKPluginBrowser::frameworkEvent(const QTKPluginFrameworkEvent &event)
{
    QString strEvent = QString("FrameworkEvent: [" + event.getPlugin()->getSymbolicName() + "]" + event.getErrorString());
    ui.eventTextBrowser->append(strEvent);
}

void QTKPluginBrowser::pluginEvent(const QTKPluginEvent &event)
{
    QString strEvent = QString("PluginEvent: [" + event.getPlugin()->getSymbolicName() + "]" + m_mapPluginEventTypeToString[event.getType()]);
    ui.eventTextBrowser->append(strEvent);

    QSharedPointer<QTKPlugin> pPlugin = event.getPlugin();
    QModelIndexList listSelection = ui.pluginsTableView->selectionModel()->selectedIndexes();
    if (!listSelection.isEmpty() && listSelection.first().data(Qt::UserRole).toLongLong() == pPlugin->getPluginId()) {
        this->updatePluginToolbar(pPlugin);
    }
}

void QTKPluginBrowser::serviceEvent(const QTKServiceEvent &event)
{
    QString strEvent;
    strEvent.append("ServiceEvent: [");
    strEvent.append(QTKServiceEvent::getTypeName(event.getType()));
    strEvent.append("]");
    QList<QSharedPointer<QTKPlugin> > listPlugins = event.getServiceReference().getUsingPlugins();
    if (!listPlugins.isEmpty()) {
        strEvent.append(" UsingPlugins:");
    }
    foreach (QSharedPointer<QTKPlugin> pPlugin, listPlugins) {
        strEvent.append(QString(" %1").arg(pPlugin->getSymbolicName()));
    }
    ui.eventTextBrowser->append(strEvent);
}

void QTKPluginBrowser::startPlugin()
{
    this->startPlugin(QTKPlugin::StartOption_StartTransient | QTKPlugin::StartOption_StartActivationPolicy);
}

void QTKPluginBrowser::startPluginNow()
{
    this->startPlugin(QTKPlugin::StartOption_StartTransient);
}

void QTKPluginBrowser::startPlugin(QTKPlugin::StartOptions options)
{
    QModelIndex selection = ui.pluginsTableView->selectionModel()->currentIndex();
    QVariant value = selection.data(Qt::UserRole);

    QSharedPointer<QTKPlugin> pPlugin = m_pPluginFramework->getPluginContext()->getPlugin(value.toLongLong());
    pPlugin->start(options);
}

void QTKPluginBrowser::stopPlugin()
{
    QModelIndex selection = ui.pluginsTableView->selectionModel()->currentIndex();
    QVariant value = selection.data(Qt::UserRole);

    QSharedPointer<QTKPlugin> pPlugin = m_pPluginFramework->getPluginContext()->getPlugin(value.toLongLong());
    pPlugin->stop();
}

void QTKPluginBrowser::appendLog4QtMessage(const QString &strMsg)
{
    ui.textBrowser_log->append(strMsg);
}

void QTKPluginBrowser::closeEvent(QCloseEvent *pCloseEvent)
{
    QSettings settings;
    settings.setValue(SETTINGS_WND_GEOM, this->saveGeometry());
    settings.setValue(SETTINGS_WND_STATE, this->saveState());
    QMainWindow::closeEvent(pCloseEvent);
}
