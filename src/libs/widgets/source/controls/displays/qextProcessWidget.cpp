#include <private/qextProcessWidget_p.h>

#include <QDir>
#include <QDebug>
#include <QWindow>

QExtProcessWidgetPrivate::QExtProcessWidgetPrivate(QExtProcessWidget *q)
    : q_ptr(q)
{
}

QExtProcessWidgetPrivate::~QExtProcessWidgetPrivate()
{
    if (!m_timer.isNull())
    {
        m_timer->stop();
    }
    if (!m_process.isNull() && m_process->isOpen())
    {
        m_process->close();
    }
}

QTimer *QExtProcessWidgetPrivate::timer()
{
    if (m_timer.isNull())
    {
        m_timer.reset(new QTimer);
    }
    return m_timer.data();
}

QProcess *QExtProcessWidgetPrivate::process()
{
    if (m_process.isNull())
    {
        m_process.reset(new QProcess);
        QObject::connect(m_process.data(), SIGNAL(started()), q_ptr, SLOT(onProcessStarted()));
        QObject::connect(m_process.data(), SIGNAL(finished(int)), q_ptr, SLOT(onProcessFinished()));
    }
    return m_process.data();
}

QExtProcessWidget::QExtProcessWidget(QWidget *parent)
    : QWidget(parent)
    , dd_ptr(new QExtProcessWidgetPrivate(this))
{

}

QExtProcessWidget::~QExtProcessWidget()
{

}

QString QExtProcessWidget::processPath() const
{
    Q_D(const QExtProcessWidget);
    return d->m_processPath;
}

QString QExtProcessWidget::workingPath() const
{
    Q_D(const QExtProcessWidget);
    return d->m_workingPath;
}

QStringList QExtProcessWidget::processArgs() const
{
    Q_D(const QExtProcessWidget);
    return d->m_processArgs;
}

void QExtProcessWidget::setProcessPath(const QString &path)
{
    Q_D(QExtProcessWidget);
    if (path != d->m_processPath)
    {
        d->m_processPath = path;
        emit this->processPathChanged(path);
    }
}

void QExtProcessWidget::setWorkingPath(const QString &path)
{
    Q_D(QExtProcessWidget);
    if (path != d->m_workingPath)
    {
        d->m_workingPath = path;
        QDir dir;
        if (!dir.exists(path))
        {
            dir.mkpath(path);
        }
        emit this->workingPathChanged(path);
    }
}

void QExtProcessWidget::setProcessArgs(const QStringList &args)
{
    Q_D(QExtProcessWidget);
    if (args != d->m_processArgs)
    {
        d->m_processArgs = args;
        emit this->processArgsChanged(args);
    }
}

bool QExtProcessWidget::startProcess()
{
    Q_D(QExtProcessWidget);
    if (d->m_processPath.isEmpty())
    {
        return false;
    }
    d->m_process->start(d->m_processPath, d->m_processArgs);
    return true;
}

void QExtProcessWidget::onProcessStarted()
{

}

void QExtProcessWidget::onProcessFinished()
{

}
