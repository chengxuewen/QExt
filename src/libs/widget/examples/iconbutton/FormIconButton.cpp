#include "FormIconButton.h"
#include "ui_FormIconButton.h"

#include <QColorDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QColor>

FormIconButton::FormIconButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormIconButton)
{
    ui->setupUi(this);
    this->init();
}

FormIconButton::~FormIconButton()
{
    delete ui;
}

void FormIconButton::setupForm()
{
    ui->disabledCheckBox->setChecked(!ui->pushButton->isEnabled());
//    ui->useThemeColorsCheckBox->setChecked(ui->pushButton->useThemeColors());
    ui->sizeSpinBox->setValue(ui->pushButton->iconSize().width());
}

void FormIconButton::updateWidget()
{
    ui->pushButton->setDisabled(ui->disabledCheckBox->isChecked());
//    ui->pushButton->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
    ui->pushButton->setIconSize(QSize(ui->sizeSpinBox->value(), ui->sizeSpinBox->value()));
}

void FormIconButton::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec()) {
        QColor color = dialog.selectedColor();
        QString senderName = sender()->objectName();
        if ("colorToolButton" == senderName) {
            ui->pushButton->setIconColor(color);
            ui->colorLineEdit->setText(color.toRgb().name());
        } else if ("disabledColorToolButton" == senderName) {
            ui->pushButton->setDisabledColor(color);
            ui->disabledColorLineEdit->setText(color.toRgb().name());
        }
    }
    setupForm();
}

void FormIconButton::init()
{
//    QVBoxLayout *layout = new QVBoxLayout;
//    setLayout(layout);

//    QWidget *widget = new QWidget;
//    layout->addWidget(widget);

//    QWidget *canvas = new QWidget;
//    canvas->setStyleSheet("QWidget { background: white; }");
//    layout->addWidget(canvas);

//    ui->setupUi(widget);
//    layout->setContentsMargins(20, 20, 20, 20);

//    layout = new QVBoxLayout;
//    canvas->setLayout(layout);
//    layout->addWidget(ui->pushButton);
//    layout->setAlignment(ui->pushButton, Qt::AlignCenter);

//    setupForm();

//    ui->pushButton->setIconColor(Qt::red);
    ui->pushButton->setIcon(QIcon(":/ic_accessible_24px.svg"));

    connect(ui->disabledCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->useThemeColorsCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
    connect(ui->colorToolButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(ui->disabledColorToolButton, SIGNAL(clicked(bool)), this, SLOT(selectColor()));
    connect(ui->sizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateWidget()));
}
