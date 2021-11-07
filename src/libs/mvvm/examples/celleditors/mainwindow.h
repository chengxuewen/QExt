// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qextGlobal.h>

#include <QMainWindow>

#include <QScopedPointer>

class QTabWidget;

namespace CellEditors
{

class SampleModel;

//! A main window. Contain two sample models and tabs with two model editors.

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    virtual ~MainWindow() QEXT_DECL_OVERRIDE;

protected:
    void closeEvent(QCloseEvent* event) QEXT_DECL_OVERRIDE;

private:
    void write_settings();
    void init_application();
    void init_models();

    QTabWidget* m_tabWidget{nullptr};
    QScopedPointer<SampleModel> m_model;
};

} // namespace CellEditors

#endif //  MAINWINDOW_H
