// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef CONCURRENTPLOTCORE_MAINWINDOW_H
#define CONCURRENTPLOTCORE_MAINWINDOW_H

#include <QMainWindow>
#include <qextMemory.h>

class GraphModel;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event);

private:
    void initApplication();
    void writeSettings();
    void populateModel();

    QExtUniquePointer<GraphModel> m_graph_model;
};

#endif // CONCURRENTPLOTCORE_MAINWINDOW_H
