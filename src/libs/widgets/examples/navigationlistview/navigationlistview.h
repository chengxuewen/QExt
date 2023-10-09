#ifndef NAVIGATIONLISTVIEW_H
#define NAVIGATIONLISTVIEW_H

#include <QWidget>
#include <QModelIndex>

namespace Ui
{
class NavigationListView;
}

class QExtNavigationListItem;
class NavigationListView : public QWidget
{
	Q_OBJECT

public:
    explicit NavigationListView(QWidget *parent = 0);
    ~NavigationListView();

private slots:
	void initForm();
    void onItemPressed1(QExtNavigationListItem *item);
    void onItemPressed2(QExtNavigationListItem *item);
    void onItemPressed3(QExtNavigationListItem *item);
    void onItemPressed4(QExtNavigationListItem *item);

private:
    Ui::NavigationListView *ui;
private:
    QList<QExtNavigationListItem *> m_parentItems1;
    QList<QExtNavigationListItem *> m_parentItems2;
    QList<QExtNavigationListItem *> m_parentItems3;
    QList<QExtNavigationListItem *> m_parentItems4;
};

#endif // NAVIGATIONLISTVIEW_H
