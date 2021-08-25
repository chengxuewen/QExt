#ifndef NAVLISTVIEWFORM_H
#define NAVLISTVIEWFORM_H

#include <QWidget>
#include <QModelIndex>

namespace Ui
{
class NavListWidgetForm;
}

class QEXTNavListWidgetItem;
class NavListWidgetForm : public QWidget
{
    Q_OBJECT

public:
    explicit NavListWidgetForm(QWidget *parent = 0);
    ~NavListWidgetForm();

private:
    Ui::NavListWidgetForm *ui;

private slots:
    void initForm();
    void onNavListWidgetPressed(const QModelIndex &index);
    void onItemPressed(QEXTNavListWidgetItem *item);

private:
    QList<QEXTNavListWidgetItem *> m_parentItems;
};

#endif // NAVLISTVIEWFORM_H
