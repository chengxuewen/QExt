#include <qextNumberKeyboard.h>
#include <ui_qextNumberKeyboard.h>

QExtNumberKeyboard::QExtNumberKeyboard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QExtNumberKeyboard)
{
    ui->setupUi(this);
}

QExtNumberKeyboard::~QExtNumberKeyboard()
{
    delete ui;
}
