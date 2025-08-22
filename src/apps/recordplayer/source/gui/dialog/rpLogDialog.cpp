#include <rpLogDialog.h>
#include <ui_rpLogDialog.h>
#include <rpLogger.h>

#include <qextMessageBox.h>

#include <QFileSystemWatcher>
#include <QStandardPaths>
#include <QFileDialog>
#include <QScrollBar>
#include <QDateTime>
#include <QListView>
#include <QScroller>

class RPLogDialogPrivate
{
public:
    explicit RPLogDialogPrivate(RPLogDialog *q);
    virtual ~RPLogDialogPrivate();

    RPLogDialog * const q_ptr;
    const char *mCurrentCategoryName;

private:
    Q_DECLARE_PUBLIC(RPLogDialog)
    Q_DISABLE_COPY(RPLogDialogPrivate)
};

RPLogDialogPrivate::RPLogDialogPrivate(RPLogDialog *q)
    : q_ptr(q)
{
}

RPLogDialogPrivate::~RPLogDialogPrivate()
{

}

RPLogDialog::RPLogDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RPLogDialog)
    , dd_ptr(new RPLogDialogPrivate(this))
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::WindowStaysOnTopHint);
    this->setWindowModality(Qt::WindowModal);
    this->setWindowTitle(tr("Log"));
    this->initDialog();
    connect(qApp, &QApplication::aboutToQuit, this, &RPLogDialog::accept);
}

RPLogDialog::~RPLogDialog()
{
    delete ui;
}

void RPLogDialog::onClearLogButtonClicked()
{
    ui->textBrowserLogText->clear();
}

void RPLogDialog::onExportLogButtonClicked()
{
    Q_D(RPLogDialog);
    d->mCurrentCategoryName = (const char *)ui->comboBox->currentData().toULongLong();
    auto logger = RPLogger::instance(d->mCurrentCategoryName);
    if (!logger.isNull())
    {
        logger->exportLogFile();
    }
}

void RPLogDialog::refreshLog()
{
    Q_D(RPLogDialog);
    d->mCurrentCategoryName = (const char *)ui->comboBox->currentData().toULongLong();
    auto logger = RPLogger::instance(d->mCurrentCategoryName);
    if (!logger.isNull())
    {
        logger->readLogFile();
    }
}

void RPLogDialog::exportLogFileText(const QString &log)
{
    QString dateTime = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    QString exportName = QString("RecordPlayerLog_%1.txt").arg(dateTime);
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Log File"), exportName, "*.txt");
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream textStream(&file);
        auto logger = RPLogger::instance(RP_USER().categoryName());
        logger->readLogFile();
        textStream << log;
        file.flush();
        file.close();
    }
}

void RPLogDialog::initDialog()
{
    Q_D(RPLogDialog);
    QScroller::scroller(ui->textBrowserLogText)->grabGesture(ui->textBrowserLogText->viewport(),
                                                             QScroller::TouchGesture);

    QVector<RPLogger *> loggers;
    loggers.append(RPLogger::instance(RP_DEV().categoryName()).data());
    loggers.append(RPLogger::instance(RP_USER().categoryName()).data());
    ui->comboBox->setView(new QListView(ui->comboBox));
    for (auto &&logger : loggers)
    {
        ui->comboBox->addItem(logger->categoryName(), qulonglong(logger->categoryName()));
        connect(logger, &RPLogger::exportLogFileText, this, [=](const QString &log)
                {
                    auto sender = qobject_cast<RPLogger *>(this->sender());
                    if (sender && sender->categoryName() == d->mCurrentCategoryName)
                    {
                        this->exportLogFileText(log);
                    }
                });
        connect(logger, &RPLogger::newFormatedMessage, this, [=](QtMsgType type, const QString &msg) {
            auto sender = qobject_cast<RPLogger *>(this->sender());
            if (sender && sender->categoryName() == d->mCurrentCategoryName)
            {
                ui->textBrowserLogText->append(msg);
            }
        });
    }
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &RPLogDialog::onClearLogButtonClicked);

    connect(ui->pushButtonClearLog, &QPushButton::clicked, this, &RPLogDialog::onClearLogButtonClicked);
    connect(ui->pushButtonExportLog, &QPushButton::clicked, this, &RPLogDialog::onExportLogButtonClicked);
    this->refreshLog();
}
