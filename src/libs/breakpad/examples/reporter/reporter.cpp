#include "reporter.h"
#include "ui_reporter.h"

#include <QTimer>
#include <QDateTime>

#include <TestThread.h>
#include <qextBreakpadHandler.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setApplicationName("ReporterExample");
    QCoreApplication::setApplicationVersion("0.0.1");
    QCoreApplication::setOrganizationName("OrgName");
    QCoreApplication::setOrganizationDomain("name.org");

    // Set directory to store dumps and url to upload
    qextBreakpadHandler->setDumpPath("crashes");

// Set server type for uploading
#if defined(SOCORRO)
    qextBreakpadHandler->setUploadUrl(QUrl("http://[your.site.com]/submit"));
#elif defined(CALIPER)
    qextBreakpadHandler->setUploadUrl(QUrl("http://[your.site.com]/crash_upload"));
#endif

    // Create the dialog and show it
    ReporterExample example;
    example.show();

    // Run the app
    return app.exec();
}

ReporterExample::ReporterExample(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReporterExample)
{
    // Create and configure the user interface
    ui->setupUi(this);
    this->setWindowTitle("ReporterExample (qBreakpad v." + QExtBreakpadHandler::version() + ")");

    ui->urlLineEdit->setText(qextBreakpadHandler->uploadUrl());
    ui->dumpFilesTextEdit->appendPlainText(qextBreakpadHandler->dumpFileList().join("\n"));

    // Force crash app when the close button is clicked
    connect(ui->crashButton, SIGNAL(clicked()), this, SLOT(crash()));

    // upload dumps when the updates button is clicked
    connect(ui->uploadButton, SIGNAL(clicked()), this, SLOT(uploadDumps()));
}

ReporterExample::~ReporterExample()
{
    delete ui;
}

void ReporterExample::crash()
{
    qsrand(QDateTime::currentDateTime().toTime_t());
    TestThread t1(false, qrand());
    TestThread t2(true, qrand());

    t1.start();
    t2.start();

    QTimer::singleShot(3000, qApp, SLOT(quit()));
}

void ReporterExample::uploadDumps()
{
    qextBreakpadHandler->sendDumps();
}
