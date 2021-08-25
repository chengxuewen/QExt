#ifndef NAVLISTVIEW_H
#define NAVLISTVIEW_H

#include <QWidget>
#include <QModelIndex>

namespace Ui
{
class NavTreeView;
}

class NavTreeView : public QWidget
{
	Q_OBJECT

public:
    explicit NavTreeView(QWidget *parent = 0);
    ~NavTreeView();

private slots:
	void initForm();

private:
    Ui::NavTreeView *ui;
};

#endif // NAVLISTVIEW_H
