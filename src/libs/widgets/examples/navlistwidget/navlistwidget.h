#ifndef NAVLISTWIDGET_H
#define NAVLISTWIDGET_H

#include <QWidget>
#include <QModelIndex>

namespace Ui
{
class NavListWidget;
}

class QEXTNavListWidgetItem;
class NavListWidget : public QWidget
{
	Q_OBJECT

public:
    explicit NavListWidget(QWidget *parent = 0);
    ~NavListWidget();

private slots:
	void initForm();
    void onItemPressed1(QEXTNavListWidgetItem *item);
    void onItemPressed2(QEXTNavListWidgetItem *item);
    void onItemPressed3(QEXTNavListWidgetItem *item);
    void onItemPressed4(QEXTNavListWidgetItem *item);

private:
    Ui::NavListWidget *ui;
private:
    QList<QEXTNavListWidgetItem *> m_parentItems1;
    QList<QEXTNavListWidgetItem *> m_parentItems2;
    QList<QEXTNavListWidgetItem *> m_parentItems3;
    QList<QEXTNavListWidgetItem *> m_parentItems4;
};

#endif // NAVLISTWIDGET_H
