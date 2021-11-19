#ifndef NAVIGATIONLISTVIEW_H
#define NAVIGATIONLISTVIEW_H

#include <QWidget>
#include <QModelIndex>

namespace Ui
{
class NavigationListView;
}

class QEXTNavigationListItem;
class NavigationListView : public QWidget
{
	Q_OBJECT

public:
    explicit NavigationListView(QWidget *parent = 0);
    ~NavigationListView();

private slots:
	void initForm();
    void onItemPressed1(QEXTNavigationListItem *item);
    void onItemPressed2(QEXTNavigationListItem *item);
    void onItemPressed3(QEXTNavigationListItem *item);
    void onItemPressed4(QEXTNavigationListItem *item);

private:
    Ui::NavigationListView *ui;
private:
    QList<QEXTNavigationListItem *> m_parentItems1;
    QList<QEXTNavigationListItem *> m_parentItems2;
    QList<QEXTNavigationListItem *> m_parentItems3;
    QList<QEXTNavigationListItem *> m_parentItems4;
};

#endif // NAVIGATIONLISTVIEW_H
