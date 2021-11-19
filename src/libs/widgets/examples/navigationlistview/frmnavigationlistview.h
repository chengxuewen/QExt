#ifndef FRMNAVIGATIONLISTVIEW_H
#define FRMNAVIGATIONLISTVIEW_H

#include <QWidget>
#include <QModelIndex>

namespace Ui
{
class FrmNavigationListView;
}

class QEXTNavigationListItem;
class FrmNavigationListView : public QWidget
{
    Q_OBJECT

public:
    explicit FrmNavigationListView(QWidget *parent = 0);
    ~FrmNavigationListView();

private:
    Ui::FrmNavigationListView *ui;

private slots:
    void initForm();
    void onNavListWidgetPressed(const QModelIndex &index);
    void onItemPressed(QEXTNavigationListItem *item);

private:
    QList<QEXTNavigationListItem *> m_parentItems;
};

#endif // FRMNAVIGATIONLISTVIEW_H
