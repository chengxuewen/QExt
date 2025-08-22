#include <rpMainWindow.h>
#include <ui_rpMainWindow.h>
#include <rpConstants.h>
#include <rpLogger.h>
#include <rpConfig.h>
#include <rpApp.h>

#include <qextMessageBox.h>
#include <qextStyleThemes.h>

#include <DockManager.h>

#include <QTextCharFormat>
#include <QDesktopWidget>
#include <QCloseEvent>
#include <QDateTime>
#include <QPointer>
#include <QDebug>
#include <QLabel>
#include <QFile>

class RPMainWindowPrivate
{
public:
    explicit RPMainWindowPrivate(RPMainWindow *q);
    virtual ~RPMainWindowPrivate();

    RPMainWindow *const q_ptr;

    ads::CDockManager* mDockManager;

private:
    Q_DISABLE_COPY(RPMainWindowPrivate)
    Q_DECLARE_PUBLIC(RPMainWindow)
};

RPMainWindowPrivate::RPMainWindowPrivate(RPMainWindow *q)
    : q_ptr(q)
{
}

RPMainWindowPrivate::~RPMainWindowPrivate()
{
}


RPMainWindow::RPMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RPMainWindow)
    , dd_ptr(new RPMainWindowPrivate(this))
{
    ui->setupUi(this);
    this->setWindowTitle(QString("%1 %2").arg(RP_PROGRAM_NAME, RP_VERSION_STRING));
    this->setWindowIcon(QIcon(":/images/RecordPlayer_Icon.ico"));
    this->initTitleBar();
    this->initContent();
    this->initStatusBar();
    // dd_ptr->mNavButtons[Page_Measure]->click();
    ui->toolBar->addAction(new QAction(QIcon(":/images/RecordPlayer_Icon.ico"), "test", this));
    ui->toolBar->setMovable(false);

    Q_D(RPMainWindow);
    d->mDockManager = new ads::CDockManager(this);

    QLabel* l = new QLabel();
    l->setWordWrap(true);
    l->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    l->setText("Lorem ipsum dolor sit amet, consectetuer adipiscing elit. ");

    // Create a dock widget with the title Label 1 and set the created label
    // as the dock widget content
    ads::CDockWidget* dockWidget = new ads::CDockWidget("Label 1");
    dockWidget->setWidget(l);
    d->mDockManager->addDockWidget(ads::TopDockWidgetArea, dockWidget);
}

RPMainWindow::~RPMainWindow()
{
    delete ui;
}

QExtSerializable::SerializedItemsMap RPMainWindow::serializeSave() const
{
    QExtSerializable::SerializedItemsMap items;
    items[RPConstants::SETTINGS_KEY_MAINWINDOW_GEOMETRY] = this->saveGeometry();
    items[RPConstants::SETTINGS_KEY_MAINWINDOW_STATE] = this->saveState();
    return items;
}

void RPMainWindow::serializeLoad(const SerializedItemsMap &items)
{
    this->restoreGeometry(items.value(RPConstants::SETTINGS_KEY_MAINWINDOW_GEOMETRY).toByteArray());
    this->restoreState(items.value(RPConstants::SETTINGS_KEY_MAINWINDOW_STATE).toByteArray());
}

void RPMainWindow::initTitleBar()
{
    Q_D(RPMainWindow);
    /*nav btn*/
    int iconWidth = 30;
    int iconHeight = 30;

}

void RPMainWindow::initContent()
{

}

void RPMainWindow::initStatusBar()
{

}

bool RPMainWindow::eventFilter(QObject *watched, QEvent *event)
{
    return QMainWindow::eventFilter(watched, event);
}

void RPMainWindow::closeEvent(QCloseEvent *event)
{
    int ret = QExtMessageBox::question(this, tr("Close confirm dialog!"),
                                       tr("You really want to close RecordPlayer?"),
                                       QMessageBox::Yes | QMessageBox::No);
    if (QMessageBox::Yes == ret)
    {
        RPApp::instance()->quit();
        QMainWindow::closeEvent(event);
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void RPMainWindow::changeEvent(QEvent *event)
{
    if (QEvent::LanguageChange == event->type())
    {
        ui->retranslateUi(this);
    }
    QMainWindow::changeEvent(event);
}

