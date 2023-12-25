#include "widgetform.h"
#include "ui_widgetform.h"
#include <navigationbutton/frmnavigationbutton.h>

class WidgetFormPrivate
{
public:
    explicit WidgetFormPrivate(WidgetForm *q);
    virtual ~WidgetFormPrivate();

    WidgetForm * const q_ptr;

private:
    Q_DECLARE_PUBLIC(WidgetForm)
    Q_DISABLE_COPY(WidgetFormPrivate)
};

WidgetFormPrivate::WidgetFormPrivate(WidgetForm *q)
    : q_ptr(q)
{

}

WidgetFormPrivate::~WidgetFormPrivate()
{

}


WidgetForm::WidgetForm(QWidget *parent) :
    QWidget(parent, Qt::Dialog),
    ui(new Ui::WidgetForm)
    , dd_ptr(new WidgetFormPrivate(this))
{
    ui->setupUi(this);
    ui->stackedWidget->addWidget(new FrmNavigationButton(this));
}

WidgetForm::~WidgetForm()
{
    delete ui;
    delete dd_ptr;
}
