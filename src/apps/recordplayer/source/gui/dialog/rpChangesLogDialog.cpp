#include <rpChangesLogDialog.h>
#include <ui_rpChangesLogDialog.h>
#include <rpConfig.h>

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QScroller>
#include <QFileInfo>
#include <QTextStream>
#include <QApplication>

#include <stdexcept>

RPChangesLogDialog::RPChangesLogDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RPChangesLogDialog)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    this->setWindowTitle(tr("Changes Log"));
    this->initDialog();
}

RPChangesLogDialog::~RPChangesLogDialog()
{
    delete ui;
}

void RPChangesLogDialog::initDialog()
{
    QString changesText;
    QString applicationDirPath = qApp->applicationDirPath();
#ifdef Q_OS_MAC
    applicationDirPath.append("/../../..");
#endif
    if (0)
    {
        QDir changesDir(QString("%1/changes").arg(applicationDirPath));
        qDebug() << "changesDir=" << changesDir;
        if (changesDir.exists())
        {
            QFileInfoList fileInfoList = changesDir.entryInfoList(QStringList() << "changes-*");
            for (auto &&info : fileInfoList)
            {
                QFile file(info.filePath());
                if (file.exists())
                {
                    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
                    {
                        QTextStream in(&file);
                        changesText.append("##############################################################\n");
                        changesText.append(in.readAll());
                        changesText.append("\n");
                        changesText.append("\n");
                        changesText.append("\n");
                        file.close();
                    }
                }
            }
        }
        ui->textBrowser->setText(changesText);
    }
    else
    {
        QString changesFilePath = QString("%1/changes/changes-%2").arg(applicationDirPath, RP_VERSION_STRING);
        QFile file(changesFilePath);
        if (file.exists())
        {
            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QTextStream in(&file);
                QString text = in.readAll();
                ui->textBrowser->setText(text);
                file.close();
            }
        }
    }
    QScroller::scroller(ui->textBrowser)->grabGesture(ui->textBrowser->viewport(), QScroller::TouchGesture);
    connect(ui->pushButton, &QPushButton::clicked, this, &RPChangesLogDialog::accept);

    connect(ui->pushButtonCrashTest, &QPushButton::clicked, this, [=]()
            {
                int var = 11;
                Q_UNUSED(var);
                throw std::runtime_error("crash test");
            });
}
