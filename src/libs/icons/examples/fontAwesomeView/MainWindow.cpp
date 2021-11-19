#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <qextIconsFontAwesome.h>

#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QListWidget>

LFAMMainWindow::LFAMMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(700, 800);

    qextIconsFontAwesome->setDefaultOption(QEXTIconsFontAwesome::Option_Color, QColor(255, 0, 0));
    qextIconsFontAwesome->setDefaultOption(QEXTIconsFontAwesome::Option_ColorSelected, QColor(0, 255, 0));
    qextIconsFontAwesome->setDefaultOption(QEXTIconsFontAwesome::Option_ColorSelectedOff, QColor(0, 0, 255));
    QEXTIconsFontAwesome::FontNameTextMap hasnMap = qextIconsFontAwesome->fontNameTextMap();
    QList<QString> keyList = hasnMap.keys();
    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    ui->scrollAreaWidgetContents->setLayout(vBoxLayout);
    QHBoxLayout *hBoxLayout = QEXT_DECL_NULLPTR;
    for (int i = 0; i < hasnMap.size(); ++i)
    {
        if (0 == i % 4)
        {
            hBoxLayout = new QHBoxLayout;
            vBoxLayout->addLayout(hBoxLayout);
        }
        QString key = keyList.at(i);
        QEXTIconsFontAwesome::FontType type = hasnMap.value(key);
        QIcon icon = qextIconsFontAwesome->icon(type);
        QToolButton *button = new QToolButton(this);
        button->setIcon(icon);
        button->setText(key);
        button->setIconSize(QSize(20, 20));
        button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        button->setFixedSize(140, 60);
        hBoxLayout->addWidget(button);
    }
}

LFAMMainWindow::~LFAMMainWindow()
{
    delete ui;
}
