#ifndef WIDGETFORM_H
#define WIDGETFORM_H

#include <QWidget>

namespace Ui {
class WidgetForm;
}

class WidgetFormPrivate;
class WidgetForm : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetForm(QWidget *parent = 0);
    ~WidgetForm();

private:
    Ui::WidgetForm *ui;
    WidgetFormPrivate *dd_ptr;
    Q_DECLARE_PRIVATE_D(dd_ptr, WidgetForm)
    Q_DISABLE_COPY(WidgetForm)
};

#endif // WIDGETFORM_H
