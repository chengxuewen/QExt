#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qextOnceFlag.h>
#include <qextMessageBox.h>

#include <QFile>
#include <QTimer>
#include <QFileDialog>
#include <QStandardPaths>

class MainWindowPrivate
{
    MainWindow * const q_ptr;
    Q_DECLARE_PUBLIC(MainWindow)
    Q_DISABLE_COPY(MainWindowPrivate)
public:
    explicit MainWindowPrivate(MainWindow *q);
    virtual ~MainWindowPrivate() {}

    int mAutoCloseTime;
    int mAutoCloseCounter;
    QExtOnceFlag mOnceFlag;
    QTimer mAutoCloseTimer;
    QString mCrashedAppName;
    QString mCrashedFilePath;
};

MainWindowPrivate::MainWindowPrivate(MainWindow *q)
    : q_ptr(q)
{
    mAutoCloseTimer.setInterval(0);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    , dd_ptr(new MainWindowPrivate(this))
{
    ui->setupUi(this);
    this->setAutoCloseTime(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start()
{
    Q_D(MainWindow);
    qextCallOnce(d->mOnceFlag, [=]()
                 {
                     connect(&d->mAutoCloseTimer, &QTimer::timeout, this, &MainWindow::onAutoCloseTimerTimeout);
                     d->mAutoCloseTimer.setInterval(1000);
                     if (d->mAutoCloseTime > 0)
                     {
                         d->mAutoCloseTimer.start();
                     }
                     QString describe;
                     if (!d->mCrashedAppName.isEmpty())
                     {
                         describe.append(QString("Application \"%1\" abnormal crashed!\n\n").arg(d->mCrashedAppName));
                     }
                     if (!d->mCrashedFilePath.isEmpty() && QFile::exists(d->mCrashedFilePath))
                     {
                         describe.append(QString("Generate crash dump logs files \"%1\".").arg(d->mCrashedFilePath));
                         ui->pushButtonExport->setVisible(true);
                     }
                     else
                     {
                         ui->pushButtonExport->setVisible(false);
                     }
                     connect(ui->pushButtonExport, &QPushButton::clicked, this, [=]()
                             {
                                 QFile file(d->mCrashedFilePath);
                                 QString locationPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
                                 QString desFilePath = QFileDialog::getSaveFileName(this, tr("Export crash dump file"),
                                                                                    locationPath + "/" + file.fileName(),
                                                                                    "*.dmp");
                                 if (!desFilePath.isEmpty())
                                 {
                                     QFile desFile(desFilePath);
                                     if (desFile.exists())
                                     {
                                         desFile.remove();
                                     }
                                     if (!QFile::copy(d->mCrashedFilePath, desFilePath))
                                     {
                                         QExtMessageBox::warning(this, tr("Export crash dump file"),
                                                                 tr("Export crash dump file failed!"), QMessageBox::Ok);
                                     }
                                 }
                             });
                     connect(ui->pushButtonClose, &QPushButton::clicked, this, [=]()
                             {
                                 this->close();
                             });
                     ui->label->setText(describe);
                     this->show();
                 });
}

int MainWindow::autoCloseTime() const
{
    Q_D(const MainWindow);
    return d->mAutoCloseTimer.interval();
}

void MainWindow::setAutoCloseTime(int msecs)
{
    Q_D(MainWindow);
    d->mAutoCloseTime = qMax(0, msecs);
    d->mAutoCloseCounter = d->mAutoCloseTime;
}

void MainWindow::setCrashedAppName(const QString &name)
{
    Q_D(MainWindow);
    d->mCrashedAppName = name;
}

void MainWindow::setCrashedFilePath(const QString &path)
{
    Q_D(MainWindow);
    d->mCrashedFilePath = path;
}

void MainWindow::onAutoCloseTimerTimeout()
{
    Q_D(MainWindow);
    if (--d->mAutoCloseCounter <= 0)
    {
        this->close();
    }
}

