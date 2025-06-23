#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "widgetform.h"

#include <qextStyleThemes.h>
#include <qextScroller.h>

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
#include <QScroller>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QColorDialog>
#include <QProgressDialog>
#include <QStyleFactory>

#include <iostream>

struct MainWindowPrivate
{
    MainWindowPrivate(CMainWindow *_public) : q_ptr(_public), m_widgetForm(0) {}

    void setSomeIcons();
    void fillThemeMenu();
    void updateThemeColorButtons();
    void createThemeColorDockWidget();
    void loadThemeAwareToolbarActionIcons();

    void initPaletteColorTableWidget(const QPalette &palette = QPalette());

    Ui::MainWindow *ui;

    CMainWindow *q_ptr;
    QExtStyleThemes *mStyleThemes;
    QVector<QPushButton *> m_themeColorButtons;

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

    const QMap<QString, QString> &themeColors = mStyleThemes->themeColorVariables();
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
    for (QVector<QPushButton *>::Iterator iter = m_themeColorButtons.begin(); iter != m_themeColorButtons.end(); ++iter)
    {
        QColor color = mStyleThemes->themeColor((*iter)->text());
        QString textColor = (color.value() < 128) ? "#ffffff" : "#000000";
        QString buttonStylesheet = QString("background-color: %1; color: %2;"
                                           "border: none;").arg(color.name()).arg(textColor);
        (*iter)->setStyleSheet(buttonStylesheet);
    }
}

#define USE_STYLE_THEME_LIST 1

void MainWindowPrivate::fillThemeMenu()
{
    // Add actions for theme selection
    QMenu *menu = ui->menuThemes;
#if USE_STYLE_THEME_LIST
    QStringList themes = mStyleThemes->styleThemes(true);
#else
    QStringList themes = mStyleThemes->themes();
#endif
    for (QStringList::ConstIterator iter = themes.constBegin(); iter != themes.constEnd(); ++iter)
    {
        QAction *action = new QAction(*iter);
        QObject::connect(action, &QAction::triggered, q_ptr, &CMainWindow::onThemeActionTriggered);
        menu->addAction(action);
    }
#if USE_STYLE_THEME_LIST
    mStyleThemes->setCurrentStyleTheme(themes.first());
    mStyleThemes->updateStylesheet();
#endif
    qDebug() << "themes=" << themes;
}

void MainWindowPrivate::setSomeIcons()
{
    ui->actionToolbar->setIcon(mStyleThemes->styleIcon());
    QIcon Icon(":/full_features/images/logo_frame.svg");
    for (int i = 0; i < ui->listWidget_2->count(); ++i)
    {
        ui->listWidget_2->item(i)->setIcon(Icon);
    }
}

void MainWindowPrivate::loadThemeAwareToolbarActionIcons()
{
    ui->actionSelected->setIcon(mStyleThemes->loadThemeAwareSvgIcon(":/full_features/images/edit.svg"));
    ui->actionaction->setIcon(mStyleThemes->loadThemeAwareSvgIcon(":/full_features/images/folder_open.svg"));
    ui->actionaction2->setIcon(mStyleThemes->loadThemeAwareSvgIcon(":/full_features/images/save.svg"));
    ui->actionaction3->setIcon(mStyleThemes->loadThemeAwareSvgIcon(":/full_features/images/help_outline.svg"));
}

void MainWindowPrivate::initPaletteColorTableWidget(const QPalette &palette)
{
    static bool inited = false;
    if (!inited)
    {
        inited = true;
        ui->tableWidgetPalette->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tableWidgetPalette->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
#if 0
        QScroller *scroller = QScroller::scroller(ui->tableWidgetPalette);
        scroller->grabGesture(ui->tableWidgetPalette, QScroller::LeftMouseButtonGesture);
#else
        QExtScroller *scroller = QExtScroller::scroller(ui->tableWidgetPalette);
        scroller->grabGesture(ui->tableWidgetPalette, QExtScroller::LeftMouseButtonGesture);
#endif
    }
    QMetaEnum colorGroupMetaEnum = QMetaEnum::fromType<QPalette::ColorGroup>();
    QMetaEnum colorRoleMetaEnum = QMetaEnum::fromType<QPalette::ColorRole>();
    ui->tableWidgetPalette->setColumnCount(QPalette::NColorGroups + 1);
    ui->tableWidgetPalette->setRowCount(QPalette::NColorRoles);
    ui->tableWidgetPalette->setHorizontalHeaderItem(0, new QTableWidgetItem("Role"));
    for (int i = 0; i < QPalette::NColorGroups; ++i)
    {
        ui->tableWidgetPalette->setHorizontalHeaderItem(i + 1, new QTableWidgetItem(colorGroupMetaEnum.key(i)));
    }
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
    d->mStyleThemes = new QExtStyleThemes(this);
    d->mStyleThemes->setStylesDirPath();
    d->mStyleThemes->setOutputDirPath(qApp->applicationDirPath() + "/output");
#if !USE_STYLE_THEME_LIST
    d->mStyleThemes->setCurrentStyle("material");
    //    QApplication::setStyle(QStyleFactory::create("Fusion"));
    d->mStyleThemes->setDefaultTheme();
    d->mStyleThemes->updateStylesheet();
    this->setWindowIcon(d->mStyleThemes->styleIcon());
    qApp->setStyleSheet(d->mStyleThemes->styleSheet());
#endif
    connect(d->mStyleThemes, SIGNAL(styleSheetChanged(QString)), this, SLOT(onStyleManagerStylesheetChanged()));

    d->createThemeColorDockWidget();
    d->fillThemeMenu();
    d->setSomeIcons();
    d->loadThemeAwareToolbarActionIcons();

    connect(ui->pushButtonWidget, SIGNAL(clicked(bool)), this, SLOT(onWidgetButtonClicked()));
    qApp->installEventFilter(this);

    connect(ui->pushButtonMsgDialogInfo, SIGNAL(clicked(bool)), this, SLOT(onInfoMsgDialogButtonClicked()));
    connect(ui->pushButtonMsgDialogWarn, SIGNAL(clicked(bool)), this, SLOT(onWarnMsgDialogButtonClicked()));
    connect(ui->pushButtonMsgDialogCritical, SIGNAL(clicked(bool)), this, SLOT(onCriticalMsgDialogButtonClicked()));
    connect(ui->pushButtonMsgDialogQuestion, SIGNAL(clicked(bool)), this, SLOT(onQuestionMsgDialogButtonClicked()));
    connect(ui->pushButtonMsgDialogAbout, SIGNAL(clicked(bool)), this, SLOT(onAboutMsgDialogButtonClicked()));
    connect(ui->pushButtonMsgDialogAboutQt, SIGNAL(clicked(bool)), this, SLOT(onAboutQtMsgDialogButtonClicked()));
    connect(ui->pushButtonProcessDialog, SIGNAL(clicked(bool)), this, SLOT(onProcessDialogButtonClicked()));
    connect(ui->pushButtonColorDialog, SIGNAL(clicked(bool)), this, SLOT(onColorDialogButtonClicked()));
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
#if USE_STYLE_THEME_LIST
    d->mStyleThemes->setCurrentStyleTheme(action->text());
#else
    d->mStyleThemes->setCurrentTheme(action->text());
#endif
    d->mStyleThemes->updateStylesheet();
}

void CMainWindow::onStyleManagerStylesheetChanged()
{
    qApp->setStyleSheet(d->mStyleThemes->styleSheet());
    d->updateThemeColorButtons();
}

void CMainWindow::onThemeColorButtonClicked()
{
    QColorDialog colorDialog;
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    QColor color = d->mStyleThemes->themeColor(button->text());
    colorDialog.setCurrentColor(color);
    if (colorDialog.exec() != QDialog::Accepted)
    {
        return;
    }
    color = colorDialog.currentColor();
    d->mStyleThemes->setThemeVariableValue(button->text(), color.name());
    d->mStyleThemes->updateStylesheet();
}

void CMainWindow::onWidgetButtonClicked()
{
    if (!d->m_widgetForm)
    {
        d->m_widgetForm = new WidgetForm(this);
    }
    d->m_widgetForm->show();
}

void CMainWindow::onWarnMsgDialogButtonClicked()
{
    QMessageBox::warning(this, "StyleTheme", "warning QMessageBox!", QMessageBox::No | QMessageBox::Yes);
}

void CMainWindow::onInfoMsgDialogButtonClicked()
{
    QMessageBox::information(this, "StyleTheme", "information QMessageBox!", QMessageBox::No | QMessageBox::Yes);
}

void CMainWindow::onCriticalMsgDialogButtonClicked()
{
    QMessageBox::critical(this, "StyleTheme", "critical QMessageBox!", QMessageBox::No | QMessageBox::Yes);
}

void CMainWindow::onQuestionMsgDialogButtonClicked()
{
    QMessageBox::question(this, "StyleTheme", "question QMessageBox!", QMessageBox::No | QMessageBox::Yes);
}

void CMainWindow::onAboutMsgDialogButtonClicked()
{
    QMessageBox::about(this, "StyleTheme", "about QMessageBox!");
}

void CMainWindow::onAboutQtMsgDialogButtonClicked()
{
    QMessageBox::aboutQt(this, "StyleTheme");
}

void CMainWindow::onColorDialogButtonClicked()
{
    QColorDialog::getColor(Qt::white, this, "StyleTheme QColorDialog");
}

void CMainWindow::onProcessDialogButtonClicked()
{
    QProgressDialog dialog("StyleTheme QProgressDialog", "Cancel", 0, 1000000, this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.show();
    for (int i = 0; i < dialog.maximum(); i++)
    {
        dialog.setValue(i);
        if (dialog.wasCanceled())
        {
            break;
        }
    }
    if (!dialog.wasCanceled())
    {
        dialog.setValue(dialog.maximum());
    }
}

bool CMainWindow::event(QEvent *event)
{
    return QMainWindow::event(event);
}

bool CMainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        QWidget *widget = qobject_cast<QWidget *>(watched);
        if (widget)
        {
            qDebug() << watched->objectName();
            d->initPaletteColorTableWidget(widget->palette());
        }
    }
    //    if (QString("QPushButton") == watched->metaObject()->className())
    //    {
    //        if (event->type() == QEvent::MouseButtonPress)
    //        {
    //            QPushButton *button = qobject_cast<QPushButton *>(watched);
    //            if (button)
    //            {
    //                qDebug() << watched->objectName();
    //                d->initPaletteColorTableWidget(button->palette());
    //            }
    //        }
    //    }
    return QMainWindow::eventFilter(watched, event);
}
