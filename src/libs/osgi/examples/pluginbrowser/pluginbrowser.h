#ifndef QTKPLUGINBROWSER_H
#define QTKPLUGINBROWSER_H

#include <ui_qtkpluginbrowsermainwindow.h>
#include "qtkpluginbrowsereditors.h"

#include <QTKPluginFramework/QTKPluginEvent>
#include <QTKPluginFramework/QTKPluginFrameworkEvent>
#include <QTKPluginFramework/QTKPluginFramework>
#include <QTKPluginFramework/QTKPlugin>
#include <QTKPluginFramework/QTKServiceEvent>

#include <QMainWindow>

QTK_PLUGINFRAMEWORK_USE_NAMESPACE

class QTKLog4QtEventHandler;

class QTKPluginBrowser : public QMainWindow
{
    Q_OBJECT

public:
    QTKPluginBrowser(QTKPluginFramework *pPluginFramework);

private Q_SLOTS:
    void pluginSelected(const QModelIndex &index);
    void pluginDoubleClicked(const QModelIndex &index);
    void qtResourceDoubleClicked(const QModelIndex &index);
    void dbResourceDoubleClicked(const QModelIndex &index);

    void frameworkEvent(const QTKPluginFrameworkEvent &event);
    void pluginEvent(const QTKPluginEvent &event);
    void serviceEvent(const QTKServiceEvent &event);

    void startPlugin();
    void startPluginNow();
    void stopPlugin();

    void appendLog4QtMessage(const QString &strMsg);

private:
    void closeEvent(QCloseEvent* pCloseEvent);
    void updatePluginToolbar(QSharedPointer<QTKPlugin> pPlugin);
    void startPlugin(QTKPlugin::StartOptions options);

    Ui::QTKPluginBrowserWindow ui;
    QMap<QTKPluginEvent::Type, QString> m_mapPluginEventTypeToString;
    QTKPluginFramework *m_pPluginFramework;
    QTKPluginBrowserEditors *m_pEditors;
    QAction *m_pStartPluginNowAction;
    QAction *m_pStartPluginAction;
    QAction *m_pStopPluginAction;
    QTKLog4QtEventHandler *m_pLogQt4EventHandler;
};

#endif // QTKPLUGINBROWSER_H
