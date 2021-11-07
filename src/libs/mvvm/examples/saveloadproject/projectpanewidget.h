// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef PROJECTPANEWIDGET_H
#define PROJECTPANEWIDGET_H

#include <qextGlobal.h>

#include <QWidget>

class QLabel;

//! Panel with labels to hold project name and project dir. Part of RecentProjectsWidget.

class ProjectPaneWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectPaneWidget(QWidget* parent = nullptr);

    void setCurrentProject(const QString& project_dir, bool is_modified = false);

    void clear();

    void setActive(bool value);

signals:
    void projectSelected(const QString& project_dir);

protected:
    void paintEvent(QPaintEvent*) QEXT_DECL_OVERRIDE;
    void enterEvent(QEvent*) QEXT_DECL_OVERRIDE;
    void leaveEvent(QEvent*) QEXT_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent* event) QEXT_DECL_OVERRIDE;

private:
    QLabel* m_current_project_title{nullptr};
    QLabel* m_current_project_dir{nullptr};
    QColor m_widget_color;
    bool m_active{false};
    QString m_project_dir;
};

#endif // PROJECTPANEWIDGET_H
