#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <qextIconFontAwesome.h>

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

    qextIconFontAwesome->setDefaultOption(QExtIconFontAwesome::Option_Color, QColor(255, 0, 0));
    qextIconFontAwesome->setDefaultOption(QExtIconFontAwesome::Option_ColorSelected, QColor(0, 255, 0));
    qextIconFontAwesome->setDefaultOption(QExtIconFontAwesome::Option_ColorSelectedOff, QColor(0, 0, 255));
    QExtIconFontAwesome::FontNameTextMap hasnMap = qextIconFontAwesome->fontNameTextMap();
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
        QExtIconFontAwesome::FontType type = hasnMap.value(key);
        QIcon icon = qextIconFontAwesome->icon(type);
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
