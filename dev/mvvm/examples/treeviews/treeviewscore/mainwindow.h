// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef TREEVIEWSCORE_MAINWINDOW_H
#define TREEVIEWSCORE_MAINWINDOW_H

#include <QMainWindow>
#include <qextMemory.h>

namespace TreeViews {

class SampleModel;

//! The main window of this application.

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

    QExtUniquePointer<SampleModel> m_sample_model;
};

} // namespace TreeViews

#endif // TREEVIEWSCORE_MAINWINDOW_H
