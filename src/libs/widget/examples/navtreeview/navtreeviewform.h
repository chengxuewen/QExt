#ifndef NAVLISTVIEWFORM_H
#define NAVLISTVIEWFORM_H

#include <QWidget>
#include <QModelIndex>

namespace Ui
{
    class NavTreeViewForm;
}

class NavTreeViewForm : public QWidget
{
    Q_OBJECT

public:
    explicit NavTreeViewForm(QWidget *parent = 0);
    ~NavTreeViewForm();

private:
    Ui::NavTreeViewForm *ui;

private slots:
    void initForm();

private slots:
    void on_navListView_pressed(const QModelIndex &index);
};

#endif // NAVLISTVIEWFORM_H
