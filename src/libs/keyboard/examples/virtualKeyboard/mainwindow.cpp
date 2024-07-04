#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDialog>
#include <QInputDialog>
#include <QByteArray>
#include <QTextCodec>
#include <QFileDialog>
#include <QFileInfo>
#include <QString>
#include <QCompleter>

#include <qextVirtualKeyboard.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->initForm();
}

MainWindow::~MainWindow()
{
    delete ui;
    exit(0);
}

void MainWindow::initForm()
{
    //Set to disable input
    ui->txt->setProperty("noinput", true);

    //Set the pop-up numeric keypad
    //ui->textEdit->setProperty("flag", "number");

    //Place the input method into uppercase automatically
    ui->comboBox->setProperty("upper", true);

    //Set read-only property
    ui->textBrowser->setReadOnly(true);

    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
    connect(QExtVirtualKeyboard::instance(), SIGNAL(receiveValue(QString)), this, SLOT(receiveValue(QString)));
}

void MainWindow::returnPressed()
{
    qDebug() << "returnPressed";
}

void MainWindow::accepted()
{
    QInputDialog *d = (QInputDialog *)sender();
    QString text = QString("result: %1").arg(d->textValue());
    ui->lineEdit->setText(text);
}

void MainWindow::textValueChanged(QString text)
{
    ui->lineEdit->setText(text);
}

void MainWindow::fileSelected(QString fileName)
{
    QString text = QString("fileName: %1").arg(fileName);
    ui->lineEdit->setText(text);

    QFile file(fileName);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QByteArray ba = file.readAll();
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QString str = codec->toUnicode(ba);
        ui->textEdit->setText(str);
        file.close();
    }
}

void MainWindow::receiveValue(const QString &value)
{
    ui->lineEdit->setText(QString("当前输入: %1").arg(value));
}

QString MainWindow::getFileName(const QString &filter, const QString &defaultDir, const QString &fileName)
{
    QString file;
    QFileDialog dialog;
    dialog.setFixedSize(900, 600);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setWindowTitle("保存文件");
    dialog.setLabelText(QFileDialog::Accept, "保存(&S)");
    dialog.setLabelText(QFileDialog::Reject, "取消(&C)");
    dialog.selectFile(fileName);
    dialog.setNameFilter(filter);
    dialog.setDirectory(defaultDir);

    if (dialog.exec() == 1) {
        file = dialog.selectedFiles().value(0);
        file = QFileInfo(file).suffix().isEmpty() ? "" : file;
    }

    return file;
}

void MainWindow::on_btnDialog_clicked()
{
    QDialog dialog;
    dialog.setWindowModality(Qt::WindowModal);
    QLineEdit *txt = new QLineEdit(&dialog);
    txt->setVisible(true);
    dialog.exec();
}

void MainWindow::on_btnInputDialog_clicked()
{
    QInputDialog *d = new QInputDialog(this);
    d->setAttribute(Qt::WA_DeleteOnClose);
    connect(d, SIGNAL(accepted()), this, SLOT(accepted()));
    connect(d, SIGNAL(textValueChanged(QString)), this, SLOT(textValueChanged(QString)));
    d->show();
}

void MainWindow::on_btnFileDialog_clicked()
{
    QFileDialog *d = new QFileDialog(this);
    d->setWindowTitle("打开文件");

    //The input box in the following method Settings dialog box does not require input
    d->setOption(QFileDialog::DontUseNativeDialog, true);
    QLineEdit *txt = d->findChild<QLineEdit *>("fileNameEdit");
    txt->setProperty("noinput", true);

    d->setAttribute(Qt::WA_DeleteOnClose);
    connect(d, SIGNAL(fileSelected(QString)), this, SLOT(fileSelected(QString)));
    d->show();
}

void MainWindow::on_btnSaveDialog_clicked()
{
    QFileDialog *d = new QFileDialog(this);
    d->setWindowTitle("保存文件");

    //Set the input box does not need automatic prompt, or the focus will jump randomly here in QT4, causing the input method to be hidden
    d->setOption(QFileDialog::DontUseNativeDialog, true);
    QLineEdit *txt = d->findChild<QLineEdit *>("fileNameEdit");
    txt->setCompleter(new QCompleter);

    d->setAttribute(Qt::WA_DeleteOnClose);
    d->show();
}

void MainWindow::on_btnSaveDialog2_clicked()
{
    QString fileName = this->getFileName("保存文件(*.*)", qApp->applicationDirPath(), "test.xls");
    qDebug() << fileName;
}

void MainWindow::on_btnAbout_clicked()
{
    qApp->aboutQt();
}

void MainWindow::on_btnOpen_clicked()
{
    QExtVirtualKeyboard::instance()->show();
}

void MainWindow::on_btnClose_clicked()
{
    QExtVirtualKeyboard::instance()->hide();
}
