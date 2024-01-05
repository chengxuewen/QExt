#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <qextFluentIcons.h>
#include <qextMaterialIcons.h>

#include <QIcon>
#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QListWidget>
#include <QMetaEnum>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1080, 960);

    typedef QPair<QWidget *, QExtIconsResource *> WidgetIconsResourcePair;
    QVector<WidgetIconsResourcePair> scrollAreaWidgetIcons;
    scrollAreaWidgetIcons.append(WidgetIconsResourcePair(ui->scrollAreaWidgetContentsFluent, new QEXTFluentIcons(this)));
    scrollAreaWidgetIcons.append(WidgetIconsResourcePair(ui->scrollAreaWidgetContentsMaterial, new QEXTMaterialIcons(this)));
    QVector<WidgetIconsResourcePair>::Iterator iter = scrollAreaWidgetIcons.begin();
    while (iter != scrollAreaWidgetIcons.end())
    {
        QExtIconsResource *iconsResource = iter->second;
        QStringList iconNameList = iconsResource->iconNameList();
        QVBoxLayout *vBoxLayout = new QVBoxLayout;
        iter->first->setLayout(vBoxLayout);
        QHBoxLayout *hBoxLayout = QEXT_NULLPTR;
        for (int i = 0; i < iconNameList.size(); ++i)
        {
            if (0 == i % 6)
            {
                hBoxLayout = new QHBoxLayout;
                vBoxLayout->addLayout(hBoxLayout);
            }
            QString iconName = iconNameList.at(i);
            QIcon icon(iconsResource->iconResource(iconName));
            QToolButton *button = new QToolButton(this);
            button->setIcon(icon);
            button->setText(iconName);
            button->setIconSize(QSize(40, 40));
            button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
            button->setFixedSize(140, 60);
            hBoxLayout->addWidget(button);
        }
        iter++;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
