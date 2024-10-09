#include "widcontainerwindow.h"
#include "ui_widcontainerwindow.h"
#include <qextWindowUtils.h>

#include <QTimer>
#include <QFrame>
#include <QDebug>
#include <QThread>

widcontainerWindow::widcontainerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::widcontainerWindow)
{
    ui->setupUi(this);
    this->resize(800, 600);
    this->setCentralWidget(new QWidget(this));
    this->centralWidget()->setStyleSheet("background-color: rgb(239, 41, 41);");
    connect(&m_process, SIGNAL(started()), this, SLOT(onProcessStarted()));
    connect(&m_process, SIGNAL(finished(int)), this, SLOT(onProcessFinished()));
    connect(&m_process, SIGNAL(errorOccurred(QProcess::ProcessError)), this, SLOT(onProcessFailed()));
    m_timer.setInterval(5);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(onTimerTimeout()));
    m_widget = NULL;
    m_window = NULL;
}

widcontainerWindow::~widcontainerWindow()
{
    if (m_widget)
    {
        m_widget->deleteLater();
    }
    m_process.close();
    delete ui;
}

void widcontainerWindow::load()
{
    //    QThread::sleep(2);
    QString exePath = QT_BIN_DIR;
#ifdef Q_OS_WIN
    exePath += "/assistant.exe";
#else
    exePath += "/assistant";
#endif
    exePath = "remmina";
    m_process.start(exePath);
}

void widcontainerWindow::resizeEvent(QResizeEvent *event)
{
    QSize size = this->centralWidget()->size();
    if (m_widget)
    {
//        m_widget->resize(size);
        m_widget->setGeometry(0, 0, size.width(), size.height());
        m_widget->update();
    }
    if (m_window)
    {
//        m_window->resize(size);
    }
    QMainWindow::resizeEvent(event);
}

void widcontainerWindow::onProcessStarted()
{
    //    QThread::sleep(2);
#if 1
    m_timer.start();
#else
    qint64 pid = m_process.processId();
    WId winId = 0;
    while (0 == winId)
    {
        //        qDebug() << "winId=" << winId;
        winId = QExtWindowUtils::winIdFromProcessId(pid);
    }
    if (0 != winId)
    {
        QWindow *childWin = QWindow::fromWinId(winId);
        if (childWin)
        {
            //            m_timer.stop();
            //            childWin->setFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
            childWin->setFlags(Qt::FramelessWindowHint);
            m_widget = QWidget::createWindowContainer(childWin, this->centralWidget(), Qt::Widget);
            m_widget->setFixedSize(this->centralWidget()->size());

            WId pWId = this->winId();
            m_widget->setProperty("_q_embedded_native_parent_handle", QVariant(pWId));
            m_widget->winId();
            m_widget->windowHandle()->setParent(this->windowHandle());
            childWin->setParent(this->windowHandle());
            qDebug() << "widget=" << m_widget;
        }
        //    qDebug() << "winId=" << winId;
        qDebug() << "childWin=" << childWin;
    }
#endif

    //    WId mwinId = QExtWindowUtils::winIdFromProcessId(QApplication::applicationPid());
    //    Q_ASSERT(this->winId() == mwinId);
}

void widcontainerWindow::onProcessFinished()
{
    //    m_timer.stop();
}

void widcontainerWindow::onProcessFailed()
{
    m_timer.stop();
}

void widcontainerWindow::onTimerTimeout()
{
    //    qDebug() << "widcontainerWindow::onTimerTimeout()";
    qint64 pid = m_process.processId();
    WId winId = QExtWindowUtils::winIdFromProcessId(pid);
    qDebug() << "winId=" << winId;
    if (0 != winId)
    {
        if (NULL == m_window)
        {
            m_window = QWindow::fromWinId(winId);
        }
        qDebug() << "childWin=" << m_window;
        if (m_window)
        {
            m_window->setFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
            //            childWin->setFlags(Qt::FramelessWindowHint);
            if (!m_widget)
            {
                m_widget = QWidget::createWindowContainer(m_window, this->centralWidget(), Qt::Widget);
                QThread::msleep(50);
                m_window->setParent(this->windowHandle());
                WId pWId = this->winId();
                m_widget->setProperty("_q_embedded_native_parent_handle", QVariant(pWId));
//                m_widget->winId();
//                m_widget->windowHandle()->setParent(this->centralWidget()->windowHandle());
                //                childWin->setParent(this->windowHandle());
                qDebug() << "childWin->parent()2 =" << m_window->parent();
                m_widget->setFixedSize(this->centralWidget()->size());
                m_timer.stop();
            }
        }
    }
}
