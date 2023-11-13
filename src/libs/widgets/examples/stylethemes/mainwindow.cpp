#include "mainwindow.h"
#include "ui_mainwindow.h"

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
#include <iostream>


/**
 * Private data class - pimpl
 */
struct MainWindowPrivate
{
    Ui::MainWindow ui;

    CMainWindow *q_ptr;
    QExtStyleThemes* m_styleThemes;
    QVector<QPushButton*> m_themeColorButtons;

    /**
	 * Private data constructor
     */
    MainWindowPrivate(CMainWindow* _public) : q_ptr(_public) {}

    void createThemeColorDockWidget();
    void fillThemeMenu();
    void setSomeIcons();
    void updateThemeColorButtons();

    /**
	 * Loads theme aware icons for the actions in the toolbar
     */
    void loadThemeAwareToolbarActionIcons();
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
    QMenu *menu = ui.menuThemes;
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
    ui.actionToolbar->setIcon(m_styleThemes->styleIcon());
    QIcon Icon(":/full_features/images/logo_frame.svg");
    for (int i = 0; i < ui.listWidget_2->count(); ++i)
    {
        ui.listWidget_2->item(i)->setIcon(Icon);
    }
}


void MainWindowPrivate::loadThemeAwareToolbarActionIcons()
{
    ui.actionSelected->setIcon(m_styleThemes->loadThemeAwareSvgIcon(":/full_features/images/edit.svg"));
    ui.actionaction->setIcon(m_styleThemes->loadThemeAwareSvgIcon(":/full_features/images/folder_open.svg"));
    ui.actionaction2->setIcon(m_styleThemes->loadThemeAwareSvgIcon(":/full_features/images/save.svg"));
    ui.actionaction3->setIcon(m_styleThemes->loadThemeAwareSvgIcon(":/full_features/images/help_outline.svg"));
}


CMainWindow::CMainWindow(QWidget *parent)
    : QMainWindow(parent),
    d(new MainWindowPrivate(this))
{
    d->ui.setupUi(this);
    d->m_styleThemes = new QExtStyleThemes(this);
    d->m_styleThemes->setStylesDirPath();
    d->m_styleThemes->setOutputDirPath(qApp->applicationDirPath() + "/output");
    d->m_styleThemes->setCurrentStyle("material");
    d->m_styleThemes->setDefaultTheme();
    d->m_styleThemes->updateStylesheet();
    this->setWindowIcon(d->m_styleThemes->styleIcon());
    qApp->setStyleSheet(d->m_styleThemes->styleSheet());
    connect(d->m_styleThemes, SIGNAL(stylesheetChanged()), this, SLOT(onStyleManagerStylesheetChanged()));

    d->createThemeColorDockWidget();
    d->fillThemeMenu();
    d->setSomeIcons();
    d->loadThemeAwareToolbarActionIcons();
}

CMainWindow::~CMainWindow()
{
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

