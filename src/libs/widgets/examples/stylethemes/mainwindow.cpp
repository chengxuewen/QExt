#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widgetform.h"

#include <qextStyleThemes.h>

#include <QDir>
#include <QApplication>
#include <QAction>
#include <QListWidgetItem>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QColorDialog>
#include <QDebug>
#include <QMetaEnum>
#include <QHBoxLayout>
#include <QStyleFactory>

#include <iostream>

/**
 * Private data class - pimpl
 */
struct MainWindowPrivate
{
    MainWindowPrivate(CMainWindow* _public) : q_ptr(_public), m_widgetForm(0) {}

    void setSomeIcons();
    void fillThemeMenu();
    void updateThemeColorButtons();
    void createThemeColorDockWidget();
    void loadThemeAwareToolbarActionIcons();

    void initPaletteColorTableWidget(const QPalette &palette = QPalette());

    Ui::MainWindow *ui;

    CMainWindow *q_ptr;
    QExtStyleThemes* m_styleThemes;
    QVector<QPushButton*> m_themeColorButtons;

    WidgetForm *m_widgetForm;
};


void MainWindowPrivate::createThemeColorDockWidget()
{
    QDockWidget *dock = new QDockWidget(("Change Theme"), q_ptr);
    QWidget *widget = new QWidget(dock);
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setSpacing(12);
    widget->setLayout(layout);
    dock->setWidget(widget);
    q_ptr->addDockWidget(Qt::LeftDockWidgetArea, dock);
    dock->setFloating(true);

    const QMap<QString, QString> &themeColors = m_styleThemes->themeColorVariables();
    for (QMap<QString, QString>::ConstIterator iter = themeColors.constBegin(); iter != themeColors.constEnd(); ++iter)
    {
        QPushButton *button = new QPushButton(iter.key());
        QObject::connect(button, &QPushButton::clicked, q_ptr, &CMainWindow::onThemeColorButtonClicked);
        layout->addWidget(button);
        m_themeColorButtons.append(button);
    }

    this->updateThemeColorButtons();
}


void MainWindowPrivate::updateThemeColorButtons()
{
    for (QVector<QPushButton*>::Iterator iter = m_themeColorButtons.begin(); iter != m_themeColorButtons.end(); ++iter)
    {
        QColor color = m_styleThemes->themeColor((*iter)->text());
        QString textColor = (color.value() < 128) ? "#ffffff" : "#000000";
        QString buttonStylesheet = QString("background-color: %1; color: %2;"
                                           "border: none;").arg(color.name()).arg(textColor);
        (*iter)->setStyleSheet(buttonStylesheet);
    }
}


void MainWindowPrivate::fillThemeMenu()
{
    // Add actions for theme selection
    QMenu *menu = ui->menuThemes;
    const QStringList &themes = m_styleThemes->themes();
    for (QStringList::ConstIterator iter = themes.constBegin(); iter != themes.constEnd(); ++iter)
    {
        QAction *action = new QAction(*iter);
        QObject::connect(action, &QAction::triggered, q_ptr, &CMainWindow::onThemeActionTriggered);
        menu->addAction(action);
    }
}


void MainWindowPrivate::setSomeIcons()
{
    ui->actionToolbar->setIcon(m_styleThemes->styleIcon());
    QIcon Icon(":/full_features/images/logo_frame.svg");
    for (int i = 0; i < ui->listWidget_2->count(); ++i)
    {
        ui->listWidget_2->item(i)->setIcon(Icon);
    }
}


void MainWindowPrivate::loadThemeAwareToolbarActionIcons()
{
    ui->actionSelected->setIcon(m_styleThemes->loadThemeAwareSvgIcon(":/full_features/images/edit.svg"));
    ui->actionaction->setIcon(m_styleThemes->loadThemeAwareSvgIcon(":/full_features/images/folder_open.svg"));
    ui->actionaction2->setIcon(m_styleThemes->loadThemeAwareSvgIcon(":/full_features/images/save.svg"));
    ui->actionaction3->setIcon(m_styleThemes->loadThemeAwareSvgIcon(":/full_features/images/help_outline.svg"));
}

void MainWindowPrivate::initPaletteColorTableWidget(const QPalette &palette)
{
    QMetaEnum colorGroupMetaEnum = QMetaEnum::fromType<QPalette::ColorGroup>();
    QMetaEnum colorRoleMetaEnum = QMetaEnum::fromType<QPalette::ColorRole>();
    ui->tableWidgetPalette->setColumnCount(QPalette::NColorGroups + 1);
    ui->tableWidgetPalette->setRowCount(QPalette::NColorRoles);
    ui->tableWidgetPalette->setHorizontalHeaderItem(0, new QTableWidgetItem("Role"));
    for (int i = 0; i < QPalette::NColorGroups; ++i)
    {
        ui->tableWidgetPalette->setHorizontalHeaderItem(i + 1, new QTableWidgetItem(colorGroupMetaEnum.key(i)));
    }
    ui->tableWidgetPalette->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    for (int i = 0; i < QPalette::NColorRoles; ++i)
    {
        QTableWidgetItem *itemRole = new QTableWidgetItem(colorRoleMetaEnum.valueToKey(i));
        ui->tableWidgetPalette->setItem(i, 0, itemRole);
        for (int j = 0; j < QPalette::NColorGroups; ++j)
        {
            QBrush brush = palette.brush(QPalette::ColorGroup(j), QPalette::ColorRole(i));
            QHBoxLayout *layout = new QHBoxLayout;
            QWidget *widget = new QWidget;
            widget->setLayout(layout);
            QLabel *labelName = new QLabel(widget);
            labelName->setText(brush.color().name());
            labelName->setFixedWidth(100);
            QLabel *labelColor = new QLabel(widget);
            labelColor->setFixedWidth(100);
            labelColor->setStyleSheet(QString("background:%1").arg(brush.color().name()));
            layout->addWidget(labelName);
            layout->addWidget(labelColor);
            layout->setMargin(0);
            layout->setSpacing(0);
            ui->tableWidgetPalette->setCellWidget(i, j + 1, widget);
        }
    }
}


CMainWindow::CMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , d(new MainWindowPrivate(this))
{
    ui->setupUi(this);
    d->ui = ui;
    d->m_styleThemes = new QExtStyleThemes(this);
    d->m_styleThemes->setStylesDirPath();
    d->m_styleThemes->setOutputDirPath(qApp->applicationDirPath() + "/output");
//    d->m_styleThemes->setCurrentStyle("material");
    d->m_styleThemes->setCurrentStyle("fusion");
//    QApplication::setStyle(QStyleFactory::create("Fusion"));
    d->m_styleThemes->setDefaultTheme();
    d->m_styleThemes->updateStylesheet();
    this->setWindowIcon(d->m_styleThemes->styleIcon());
    qApp->setStyleSheet(d->m_styleThemes->styleSheet());
    connect(d->m_styleThemes, SIGNAL(stylesheetChanged()), this, SLOT(onStyleManagerStylesheetChanged()));

    d->createThemeColorDockWidget();
    d->fillThemeMenu();
    d->setSomeIcons();
    d->loadThemeAwareToolbarActionIcons();

    connect(ui->pushButtonWidget, SIGNAL(clicked(bool)), this, SLOT(onWidgetButtonClicked()));
    qApp->installEventFilter(this);

//    qDebug() << this->font().family();
}

CMainWindow::~CMainWindow()
{
    delete ui;
    delete d;
}


void CMainWindow::onThemeActionTriggered()
{
    QAction *action = qobject_cast<QAction *>(sender());
    d->m_styleThemes->setCurrentTheme(action->text());
    d->m_styleThemes->updateStylesheet();
}


void CMainWindow::onStyleManagerStylesheetChanged()
{
    qApp->setStyleSheet(d->m_styleThemes->styleSheet());
    d->updateThemeColorButtons();
}


void CMainWindow::onThemeColorButtonClicked()
{
    QColorDialog colorDialog;
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    QColor color = d->m_styleThemes->themeColor(button->text());
    colorDialog.setCurrentColor(color);
    if (colorDialog.exec() != QDialog::Accepted)
    {
        return;
    }
    color = colorDialog.currentColor();
    d->m_styleThemes->setThemeVariableValue(button->text(), color.name());
    d->m_styleThemes->updateStylesheet();
}

void CMainWindow::onWidgetButtonClicked()
{
    if (!d->m_widgetForm)
    {
        d->m_widgetForm = new WidgetForm(this);
    }
    d->m_widgetForm->show();
}

bool CMainWindow::event(QEvent *event)
{
    return QMainWindow::event(event);
}

bool CMainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (QString("QPushButton") == watched->metaObject()->className())
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QPushButton *button = qobject_cast<QPushButton *>(watched);
            if (button)
            {
                qDebug() << watched->objectName();
                d->initPaletteColorTableWidget(button->palette());
            }
        }
    }
    return QMainWindow::eventFilter(watched, event);
}
