// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef NODEEDITORCORE_MAINWINDOW_H
#define NODEEDITORCORE_MAINWINDOW_H

#include <QMainWindow>
#include <qextMemory.h>

class QTabWidget;

namespace NodeEditor {

class SampleModel;
class ModelEditorWidget;

//! A main window. Contain two sample models and tabs with two model editors.

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();
    virtual ~MainWindow() override;

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    void writeSettings();
    void initApplication();

    QExtUniquePointer<SampleModel> m_model;
    ModelEditorWidget* m_editorWidget{nullptr};
};

} // namespace NodeEditor

#endif // NODEEDITORCORE_MAINWINDOW_H
