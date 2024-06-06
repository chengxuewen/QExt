#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <qextFontAwesome.h>

#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QListWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(700, 800);

    qextFontAwesome->setDefaultOption(QExtFontAwesome::Option_Color, QColor(255, 0, 0));
    qextFontAwesome->setDefaultOption(QExtFontAwesome::Option_ColorSelected, QColor(0, 255, 0));
    qextFontAwesome->setDefaultOption(QExtFontAwesome::Option_ColorSelectedOff, QColor(0, 0, 255));
    QExtFontAwesome::FontNameTextMap hasnMap = qextFontAwesome->fontNameTextMap();
    QList<QString> keyList = hasnMap.keys();
    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    ui->scrollAreaWidgetContents->setLayout(vBoxLayout);
    QHBoxLayout *hBoxLayout = QEXT_NULLPTR;
    for (int i = 0; i < hasnMap.size(); ++i)
    {
        if (0 == i % 4)
        {
            hBoxLayout = new QHBoxLayout;
            vBoxLayout->addLayout(hBoxLayout);
        }
        QString key = keyList.at(i);
        QExtFontAwesome::FontType type = hasnMap.value(key);
        QIcon icon = qextFontAwesome->icon(type);
        QToolButton *button = new QToolButton(this);
        button->setIcon(icon);
        button->setText(key);
        button->setIconSize(QSize(20, 20));
        button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        button->setFixedSize(140, 60);
        hBoxLayout->addWidget(button);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
