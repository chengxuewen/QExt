#include "qtklogqdebug_p.h"

#include <QTKPluginFramework/QTKPluginConstants>

#include <QDateTime>
#include <QDebug>
#include <QStringList>

QTKLogQDebug::QTKLogQDebug() : logLevel(QTKLogService::LOG_DEBUG)
{
}

void QTKLogQDebug::log(int level, const QString& message, const std::exception* exception,
                       const char* file, const char* function, int line)
{
    Q_UNUSED(function)

    QString s = QDateTime::currentDateTime().toString(Qt::ISODate)
            .append(" - ").append(message);

    if (exception != 0)
    {
        s.append(" (").append(exception->what()).append(")");
    }

    if (file)
    {
        s.append(" [at ").append(file).append(":").append(QString::number(line)).append("]");
    }

    if (level == QTKLogService::LOG_WARNING)
    {
        qWarning() << s;
    }
    else if (level == QTKLogService::LOG_ERROR)
    {
        qCritical() << s;
    }
    else
    {
        qDebug() << s;
    }
}

void QTKLogQDebug::log(const QTKServiceReference& sr, int level, const QString& message,
                       const std::exception* exception,
                       const char* file, const char* function, int line)
{
    Q_UNUSED(function)

    QString s = QDateTime::currentDateTime().toString(Qt::ISODate)
            .append(" - [");

    s.append(sr.getProperty(QTKPluginConstants::SERVICE_ID).toString());
    s.append(";");
    QStringList clazzes = sr.getProperty(QTKPluginConstants::OBJECT_CLASS).toStringList();
    int i = 0;
    foreach (QString clazz, clazzes)
    {
        if (i > 0) s.append(",");
        s.append(clazz);
    }

    s.append(message);

    if(exception != 0)
    {
        s.append(" (").append(exception->what()).append(")");
    }

    if (file)
    {
        s.append(" [at ").append(file).append(":").append(QString::number(line)).append("]");
    }

    if (level == QTKLogService::LOG_WARNING)
    {
        qWarning() << s;
    }
    else if (level == QTKLogService::LOG_ERROR)
    {
        qCritical() << s;
    }
    else
    {
        qDebug() << s;
    }
}

int QTKLogQDebug::getLogLevel() const
{
    return logLevel;
}
